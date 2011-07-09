<?php

function sony_video_setup_import_form() {
  // Basic system settings form
  $form = array();
  $form['sony_video_bc3_playlist_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Brightcove3 Playlist ID'),
    '#description' => t('The Playlist ID that you want to use to import videos to this site.'),
    '#default_value' => variable_get('sony_video_bc3_playlist_id', ''),
  );
  $form = system_settings_form($form);
  
  // Modify for our needs
  $video_feed = variable_get('sony_video_feed', '');
  if ($video_feed) {
    $form['current_video_feed'] = array(
      '#type' => 'markup',
      '#value' => t("Video import feed: !link", array('!link' => l("NID $video_feed", "node/$video_feed"))),
    );
  }
  $form['buttons']['submit']['#value'] = $video_feed ? t('Update video import feed') : t('Create video import feed');
  $form['#submit'][] = 'sony_video_bc_feed_save';
  
  return $form;
}

function sony_video_bc_feed_save($form, &$form_state) {
  $video_feed = variable_get('sony_video_feed', '');
  // create new feed node
  if (!$video_feed) {
    $node = array('type' => 'feed');

    $form_state = array();
    $form_state['values']['title'] = 'Artist Videos';
    $form_state['values']['body'] = '';
    $form_state['values']['name'] = 'adminn';
    $form_state['values']['op'] = t('Save');
    $form_state['values']['feedapi'] = array(
      'feedapi_url' => 'http://dummy',
      'refresh_on_create' => 0,
      'update_existing' => 1,
      'skip' => 0,
      'items_delete' => 0,
      'processors' => array(
        'feedapi_node' => array(
          'content_type' => 'video',
          'input_format' => 1,
          'author' => 'adminn',
          'language' => 'en',
          'node_date' => 'feed',
          'promote' => 0,
          'x_dedupe' => 0,
        ),
      ),
    );
    module_load_include('inc', 'node', 'node.pages');
    drupal_execute('feed_node_form', $form_state, (object)$node);
  
    // save the ID
    $nid = db_result(db_query_range("SELECT nid FROM {node} WHERE title='%s' ORDER BY nid DESC", $form_state['values']['title'], 0, 1));
    if ($nid) {
      // Save our feed NID
      variable_set('sony_video_feed', $nid);
      // Set up eparser
      module_load_include('inc', 'feedapi_eparser', 'feedapi_eparser.settings');
      _feedapi_eparser_clear_settings($form_state['#node']->nid);
      $fep = new stdClass;
      $fep->nid = $nid;
      $fep->type = 'sonyVideo';
      $fep->namespaces = array();
      $fep->download = 'drupal_http_request';
      drupal_write_record('feedapi_eparser_node', $fep);
      // Set up mapper
      $fm = new stdClass;
      $fm->nid = $nid;
      $fm->mapping = 'a:4:{s:34:"a:1:{i:0;s:16:"shortDescription";}";s:36:"a:2:{i:0;s:4:"node";i:1;s:4:"body";}";s:30:"a:1:{i:0;s:12:"fake_bc_link";}";s:47:"a:2:{i:0;s:7:"emvideo";i:1;s:11:"field_video";}";s:22:"a:1:{i:0;s:5:"title";}";s:37:"a:2:{i:0;s:4:"node";i:1;s:5:"title";}";s:32:"a:1:{i:0;s:14:"sony_bc_pd_url";}";s:57:"a:2:{i:0;s:7:"content";i:1;s:21:"field_progressive_url";}";}';
      drupal_write_record('feedapi_mapper', $fm);
      // Done
      drupal_set_message(t('Video import feed created.'));
    }
  }
}
