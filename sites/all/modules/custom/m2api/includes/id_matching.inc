<?php

/**
 * @file
 * These are forms for matching M2 ids to albums and tracks that already exist
 * in Drupal. It should work but it's definitley not clean.
 */


function m2api_album_id_match_form($form_state = NULL) {
  // @TODO: this should really have a confirmation form. I'm skipping it
  // because there's not time right now and this will be used infrequently.

  m2api_include('api');

  // Figure out what's unmatched
  $unmatched = array();
  $result = db_query("SELECT n.nid FROM {node} n LEFT JOIN {m2api_nodes} m ON n.nid = m.nid
    WHERE m.nid IS NULL AND n.type = 'album' AND (n.nid = n.tnid OR n.tnid = 0) ORDER BY n.title");
  while (($row = db_fetch_object($result)) && ($node = node_load($row->nid))) {
    $unmatched[$node->nid] = $node;
  }

  // Bail if there's nothing to do here.
  if (empty($unmatched)) {
    $form['empty'] = array('#value' => t("Good job! You get a gold star. Every album has an M2 id. Did you <a href='!link'>associate all the tracks</a>?", array('!link' => url('admin/content/m2api/id_matcher/tracks'))));
    return $form;
  }

  // Bail if there's a problem talking to M2.
  if (!m2api_can_connect()) {
    return array('error' => array('#value' => t('Cannot connect to M2.')));
  }

  // Figure out all the m2 ids that we know about.
  $existing = array();
  $result = db_query("SELECT m.nid, m.m2id FROM {m2api_nodes} m INNER JOIN {node} n WHERE n.type = 'album' AND (n.nid = n.tnid OR n.tnid = 0)");
  while ($row = db_fetch_object($result)) {
    $existing[$row->m2id] = $row->nid;
  }

  // Load the lists of content from M2 that have been matched.
  $albums = array_diff_key(m2api_get_albums('instances'), $existing);

  // Build an options array omitting any albums .
  $options = array(NULL => t('- Select one -'));
  foreach ($albums as $album) {
    $options[$album->id] = $album->title .' - '. $album->release_dates->US .' Id: '. $album->id;
  }
  asort($options);

  // Put a copy of the M2 objects into the form so we can pass them to
  // m2api_nodeapi().
  $form['m2_albums'] = array(
    '#type' => 'value',
    '#value' => $albums,
  );

  $form['drupal_albums']['#type'] = 'value';
  $form['albums']['#tree'] = TRUE;
  foreach ($unmatched as $node) {
    $form['albums'][$node->nid]['title'] = array(
      '#type' => 'item',
      '#value' => l($node->title, 'node/'. $node->nid),
    );
    $form['albums'][$node->nid]['language'] = array(
      '#type' => 'item',
      '#value' => check_plain($node->language),
    );
    $form['albums'][$node->nid]['release_date'] = array(
      '#type' => 'item',
      '#value' => isset($node->field_release_date[0]['value']) ? check_plain(reset(explode('T', $node->field_release_date[0]['value']))) : '',
    );
    $form['albums'][$node->nid]['m2id'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => NULL,
      '#access' => count($options) > 1,
    );

    // Store some extra node info for user feedback.
    $form['drupal_albums']['#value'][$node->nid] = (object) array(
      'title' => $node->title,
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Validate that they don't submit an m2id for more than one album.
 */
function m2api_album_id_match_form_validate($form, &$form_state) {
  $seen = array();
  foreach ($form_state['values']['albums'] as $nid => $row) {
    if (!empty($row['m2id'])) {
      $seen[$row['m2id']][] = $nid;
    }
  }
  foreach ($seen as $m2id => $nids) {
    if (count($nids) > 1) {
      foreach ($nids as $nid) {
        form_set_error('albums]['. $nid .'][m2id', t('You selected @title more than once.', array('@title' => $form_state['values']['m2_albums'][$m2id]->title)));
      }
    }
  }
}

function m2api_album_id_match_form_submit($form, &$form_state) {
  foreach ($form_state['values']['albums'] as $nid => $row) {
    if (!empty($row['m2id']) && isset($form_state['values']['m2_albums'][$row['m2id']])) {
      // Dirty hack to avoid duplicating code from m2api_nodeapi().
      $node = (object) array(
        'nid' => $nid,
        'type' => 'album',
        'title' => $form_state['values']['drupal_albums'][$nid]->title,
        'm2api_document' => $form_state['values']['m2_albums'][$row['m2id']]
      );
      m2api_nodeapi($node, 'update');
      drupal_set_message(t('Assigned M2 id %m2id to the <a href="!link">%title</a> album.', array('%m2id' => $row['m2id'], '!link' => url('node/'. $node->nid), '%title' => $node->title)));
    }
  }
}

function theme_m2api_album_id_match_form($form) {
  $header = array(t('Title'), t('Language'), t('Release Date'), t('M2 ID'));
  $rows = array();
  foreach (element_children($form['albums']) as $key) {
    $rows[] = array(
      drupal_render($form['albums'][$key]['title']),
      drupal_render($form['albums'][$key]['language']),
      drupal_render($form['albums'][$key]['release_date']),
      drupal_render($form['albums'][$key]['m2id']),
    );
  }

  $output = '';
  if (!empty($rows)) {
    $output .= theme('table', $header, $rows);
  }
  return $output . drupal_render($form);
}

function m2api_track_id_match_form($form_state = NULL) {
  // @TODO: this should really have a confirmation form. I'm skipping it
  // because there's not time right now and this will be used infrequently.

  m2api_include('api');

  // Get the CCK info so we query agains fields.
  $album_field = content_fields('field_album', 'track');
  $track_field = content_fields('field_track_number', 'track');
  $disc_field = content_fields('field_disc_number', 'track');
  $album_db = content_database_info($album_field);
  $track_db = content_database_info($track_field);
  $disc_db = content_database_info($disc_field);

  // Warn about albums with no M2 ID.
  $count = db_result(db_query("SELECT COUNT(n.nid) FROM {node} n
    LEFT JOIN {m2api_nodes} m ON n.nid = m.nid
    WHERE m.m2id IS NULL AND n.type = 'album' AND (n.nid = n.tnid OR n.tnid = 0)"));
  if ($count) {
    drupal_set_message(format_plural($count, 'There is one album without an M2 ID. You will need to <a href="!link">associate it</a> before you can associate its tracks.', 'There are @count albums without M2 IDs. You will need to <a href="!link">associate them</a> before you can associate their tracks.', array('!link' => url('admin/content/m2api/id_matcher/albums'))), 'warning', FALSE);
  }

  // Warn about tracks with no album.
  $count = db_result(db_query("SELECT COUNT(n.nid) FROM {node} n
    LEFT JOIN {{$album_db['table']}} a ON n.vid = a.vid
    WHERE n.type = 'track' AND (n.nid = n.tnid OR n.tnid = 0) AND a.{$album_db['columns']['nid']['column']} IS NULL"));
  if ($count) {
    drupal_set_message(format_plural($count, "There is one track that does not have an album.", 'There are @count tracks without albums assigned.'), 'warning', FALSE);
  }

  // Do the long query to avoid calling node_load() on all the tracks.
  $query = "SELECT tn.nid AS track_nid, tn.title AS track_title,
    tn.language AS track_language, an.nid AS album_nid, an.title AS album_title,
    am.m2id AS album_m2id,
    d.{$disc_db['columns']['value']['column']} AS disc_num,
    t.{$track_db['columns']['value']['column']} AS track_num
    FROM {node} tn
    LEFT JOIN {m2api_nodes} tm ON tn.nid = tm.nid
    INNER JOIN {{$track_db['table']}} t ON tn.vid = t.vid
    INNER JOIN {{$disc_db['table']}} d ON tn.vid = d.vid
    INNER JOIN {{$album_db['table']}} a ON tn.vid = a.vid
    INNER JOIN {node} an ON an.nid = a.{$album_db['columns']['nid']['column']}
    INNER JOIN {m2api_nodes} am ON am.nid = CASE an.tnid WHEN 0 THEN an.nid ELSE an.tnid END
    WHERE tn.type = 'track' AND (an.nid = an.tnid OR an.tnid = 0) AND tm.m2id IS NULL
    ORDER BY an.title, d.{$disc_db['columns']['value']['column']} ASC, t.{$track_db['columns']['value']['column']} ASC";
  $result = db_query($query);
  $unmatched_tracks = array();
  $albums = array();
  while (($track_row = db_fetch_object($result))) {
    $unmatched_tracks[$track_row->album_m2id][$track_row->track_nid] = $track_row;
  }

  // Bail if there's nothing to do here.
  if (empty($unmatched_tracks)) {
    if ($tracks_without_album || $useless_albums) {
      $form['empty'] = array('#value' => t("You've done what you can. Go fix those problems and come back."));
    }
    else {
      $form['empty'] = array('#value' => t("Good job! You get a gold star. Every track has an M2 ID."));
    }
    return $form;
  }

  // Bail if there's a problem talking to M2.
  if (!m2api_can_connect()) {
    return array('error' => array('#value' => t('Cannot connect to M2.')));
  }

  // Fetch the albums with expanded track info.
  $m2_albums = m2api_get_albums();
  $m2_tracks = m2api_get_tracks();

  // Figure out all the m2 ids that we know about.
  $existing = array();
  $result = db_query("SELECT m.nid, m.m2id FROM {m2api_nodes} m INNER JOIN {node} n
    WHERE n.type = 'track' AND (n.nid = n.tnid OR n.tnid = 0)");
  while ($row = db_fetch_object($result)) {
    $existing[$row->m2id] = $row->nid;
  }

  // Put a copy of the M2 objects into the form so we can pass them to
  // m2api_nodeapi().
  $form['m2_tracks'] = array(
    '#type' => 'value',
    '#value' => array(),
  );
  $form['drupal_tracks']['#type'] = 'value';

  foreach ($unmatched_tracks as $album_m2id => $track_rows) {
    $m2_album = $m2_albums[$album_m2id];
    $first_row = reset($track_rows);
    $album_nid = $first_row->album_nid;
    $album_title = $first_row->album_title;

    // Build the list of unused tracks for this album and an array for
    // trying to match track names.
    $options = array(NULL => t('- Select one -'));
    $default_values = array();
    foreach ($m2_album->tracks as $m2_track_id) {
      // Only add it to the list if we have the track but it doesn't have
      // an existing mapping.
      if (!isset($existing[$m2_track_id]) && isset($m2_tracks[$m2_track_id])) {
        $m2_track = $m2_tracks[$m2_track_id];
        $form['m2_tracks']['#value'][$m2_track->id] = $m2_track;
        $options[$m2_track->id] = $m2_track->track_number .') '. $m2_track->title .' - Id: '. $m2_track->id;
        $default_values[$m2_track->disc_number .'-'. $m2_track->track_number .'-'. drupal_strtolower(trim($m2_track->title))] = $m2_track->id;
      }
    }

    $form['albums'][$album_nid]['title'] = array(
      '#type' => 'item',
      '#value' => l($album_title, 'node/'. $album_nid),
    );
    $form['albums'][$album_nid]['tracks']['#tree'] = TRUE;
    foreach ($track_rows as $track_nid => $track_row) {
      $disc_number = isset($track_row->disc_num) ? $track_row->disc_num : 1;
      $track_number = isset($track_row->track_num) ? $track_row->track_num : '';
      $m2_key = $disc_number .'-'. $track_number .'-'. drupal_strtolower(trim($track_row->track_title));
      $form['albums'][$album_nid]['tracks'][$track_nid]['disc'] = array(
        '#type' => 'item',
        '#value' => check_plain($disc_number),
      );
      $form['albums'][$album_nid]['tracks'][$track_nid]['track'] = array(
        '#type' => 'item',
        '#value' => check_plain($track_number),
      );
      $form['albums'][$album_nid]['tracks'][$track_nid]['title'] = array(
        '#type' => 'item',
        '#value' => l($track_row->track_title, 'node/'. $track_nid),
      );
      $form['albums'][$album_nid]['tracks'][$track_nid]['m2id'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => isset($default_values[$m2_key]) ? $default_values[$m2_key] : NULL,
        '#access' => count($options) > 1,
      );

      // Store some extra node info for the confirmation form.
      $form['drupal_tracks']['#value'][$track_nid] = (object) array(
        'title' => $track_row->track_title,
      );
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Validate that they don't submit an m2id for more than one track.
 */
function m2api_track_id_match_form_validate($form, &$form_state) {
  $seen = array();
  foreach ($form_state['values']['tracks'] as $nid => $row) {
    if (!empty($row['m2id'])) {
      $seen[$row['m2id']][] = $nid;
    }
  }
  foreach ($seen as $m2id => $nids) {
    if (count($nids) > 1) {
      foreach ($nids as $nid) {
        form_set_error('tracks]['. $nid .'][m2id', t('You selected @title more than once.', array('@title' => $form_state['values']['m2_tracks'][$m2id]->title)));
      }
    }
  }
}

function m2api_track_id_match_form_submit($form, &$form_state) {
  foreach ($form_state['values']['tracks'] as $nid => $row) {
    if (!empty($row['m2id']) && isset($form_state['values']['m2_tracks'][$row['m2id']])) {
      // Dirty hack to avoid duplicating code from m2api_nodeapi().
      $node = (object) array(
        'nid' => $nid,
        'type' => 'track',
        'title' => $form_state['values']['drupal_tracks'][$nid]->title,
        'm2api_document' => $form_state['values']['m2_tracks'][$row['m2id']]
      );
      m2api_nodeapi($node, 'update');
      drupal_set_message(t('Assigned M2 id %m2id to the <a href="!link">%title</a> track.', array('%m2id' => $row['m2id'], '!link' => url('node/'. $node->nid), '%title' => $node->title)));
    }
  }
}

function theme_m2api_track_id_match_form($form) {
  $output = '';
  if (isset($form['albums'])) {
    foreach (element_children($form['albums']) as $album_key) {
      $header = array(t('Disc'), t('Track'), t('Title'), t('M2 ID'));
      $rows = array();
      foreach (element_children($form['albums'][$album_key]['tracks']) as $track_key) {
        $rows[] = array(
          drupal_render($form['albums'][$album_key]['tracks'][$track_key]['disc']),
          drupal_render($form['albums'][$album_key]['tracks'][$track_key]['track']),
          drupal_render($form['albums'][$album_key]['tracks'][$track_key]['title']),
          drupal_render($form['albums'][$album_key]['tracks'][$track_key]['m2id']),
        );
      }
      if (!empty($rows)) {
        $output .= theme('table', $header, $rows, array(), drupal_render($form['albums'][$album_key]['title']));
      }
      $output .= drupal_render($form['albums'][$album_key]);
    }
  }
  return $output . drupal_render($form);
}
