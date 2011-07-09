<?php

/**
 * @file
 * These are forms for matching M2 ids to albums and tracks that already exist
 * in Drupal. It should work but it's definitley not clean.
 */


function m2_product_products_match_form($form_state = NULL) {
  // @TODO: this should really have a confirmation form. I'm skipping it
  // because there's not time right now and this will be used infrequently.

  m2api_include('api');
  ctools_include('plugins');
  dsm("in the physical products match form");

  if (m2api_can_connect()) {
    $products = m2api_get_products();
    dsm($products);
    // Figure out what's unmatched
    /*
    $unmatched = array();
    $result = db_query("SELECT n.nid FROM {node} n LEFT JOIN {m2api_nodes} m ON n.nid = m.nid
      WHERE m.nid IS NULL AND n.type = 'album' AND n.language IN ('', '%s') ORDER BY n.title", language_default('language'));
    while (($row = db_fetch_object($result)) && ($node = node_load($row->nid))) {
      $unmatched[$node->nid] = $node;
    }

    // Bail if there's nothing to do here.
    if (empty($unmatched)) {
      $form['empty'] = array('#value' => t("Good job! You get a gold star. Every album has an M2 id. Did you <a href='!link'>associate all the tracks</a>?", array('!link' => url('admin/content/m2api/id_matcher/tracks'))));
      return $form;
    }

    // Figure out all the m2 ids that we know about.
    $existing = array();
    $result = db_query("SELECT m.nid, m.m2id FROM {m2api_nodes} m INNER JOIN {node} n WHERE n.type = 'album' AND n.language IN ('', '%s')", language_default('language'));
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
        '#value' => check_plain($node->title),
      );
      $form['albums'][$node->nid]['release_date'] = array(
        '#type' => 'item',
        '#value' => isset($node->field_release_date[0]['value']) ? check_plain(reset(explode('T', $node->field_release_date[0]['value']))) : '',
      );
      $form['albums'][$node->nid]['m2id'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => NULL,
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
     *
     */
  }

  return $form;
}

/**
 * Validate that they don't submit an m2id for more than one album.
 */
function m2_product_products_match_form_validate($form, &$form_state) {
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

function m2_product_products_match_form_submit($form, &$form_state) {
  foreach ($form_state['values']['albums'] as $nid => $row) {
    if (!empty($row['m2id']) && isset($form_state['values']['m2_albums'][$row['m2id']])) {
      // Dirty hack to avoid duplicating code from m2api_nodeapi().
      $node = (object) array(
        'nid' => $nid,
        'type' => 'm2_product',
        'title' => $form_state['values']['drupal_albums'][$nid]->title,
        'm2api_document' => $form_state['values']['m2_albums'][$row['m2id']]
      );
      m2api_nodeapi($node, 'update');
      drupal_set_message(t('Assigned M2 id %m2id to the <a href="!link">%title</a> album.', array('%m2id' => $row['m2id'], '!link' => url('node/'. $node->nid), '%title' => $node->title)));
    }
  }
}

function theme_m2_product_products_match_form($form) {
  $header = array(t('Title'), t('Release Date'), t('M2 ID'));
  $rows = array();
  foreach (element_children($form['albums']) as $key) {
    $rows[] = array(
      drupal_render($form['albums'][$key]['title']),
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
