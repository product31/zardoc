<?php

function m2_gracenote_admin_form() {
  module_load_include('inc', 'content', 'includes/content.node_form');
  $form = array();
  $type = content_types('track');
  $field = $type['fields']['field_gracenote_lyrics'];

  $form['nodes'] = array(
    '#tree' => TRUE,
  );

  $languages = language_list();

  $result = pager_query('SELECT n.nid FROM {node} n WHERE n.type = "track" AND (n.language = "" OR n.language = "en")', 100, 0);
  while ($row = db_fetch_array($result)) {
    $node = node_load($row['nid']);
    $album_nid = $node->field_album[0]['nid'];
    $album = node_load($album_nid);
    if ($album->language == '' || $album->language == 'en') {
      $form['nodes'][$album_nid][$node->nid]['#node'] = $node;
      $form['nodes'][$album_nid][$node->nid] += content_field_form($form['nodes'][$album_nid][$node->nid], $form_state, $field);
      $form['nodes'][$album_nid][$node->nid]['field_gracenote_lyrics'][0]['#title'] = $node->title;
      if ($node->language && $languages[$node->language]) {
        $form['nodes'][$album_nid][$node->nid]['field_gracenote_lyrics'][0]['#title'] .= ' ('. $languages[$node->language]->name.')';
      }
      else {
        $form['nodes'][$album_nid][$node->nid]['field_gracenote_lyrics'][0]['#title'] .= ' (Language neutral)';
      }
    }
  }

  foreach (element_children($form['nodes']) as $album_nid) {
    $album = node_load($album_nid);
    $form['nodes'][$album_nid]['#type'] = 'fieldset';
    $form['nodes'][$album_nid]['#title'] = $album->title;
    if ($album->language && $languages[$album->language]) {
      $form['nodes'][$album_nid]['#title'] .= ' ('. $languages[$album->language]->name.')';
    }
    else {
      $form['nodes'][$album_nid]['#title'] .= ' (Language neutral)';
    }
  }

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save changes'),
  );
  $form['pager'] = array('#value' => theme('pager', NULL, 100, 0));
  return $form;
}

function m2_gracenote_admin_form_submit($form, &$form_state) {
  module_load_include('inc', 'node', 'node.pages');
  foreach ($form_state['values']['nodes'] as $album_nid => $tracks) {
    foreach ($tracks as $nid => $item) {
      $node = node_load($nid);
      $item = (object)$item;
      if ($node->field_gracenote_lyrics[0]['m2id'] != $item->field_gracenote_lyrics[0]['m2id']) {
        node_object_prepare($node);
        $node->field_gracenote_lyrics[0] = $item->field_gracenote_lyrics[0];
        node_validate($node, $form['nodes'][$nid]);
        node_save($node);
        drupal_set_message(t('Updated lyrics for track %track_title.', array('%track_title' => $node->title)));
      }
      $node = null;
    }
  }

  $query = '';
  if (isset($_GET['page'])) {
    $query = 'page='. $_GET['page'];
  }
  $form_state['redirect'] = array('admin/sony/lyrics_admin', $query);
}
