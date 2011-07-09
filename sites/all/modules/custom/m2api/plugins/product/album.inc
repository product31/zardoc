<?php
/**
 * @file
 * Manage digital albums.
 */

$plugin = array(
  'settings_form' => 'm2api_album_settings_form',
  'default_settings' => array('release_date_action' => 'if_empty'),
  'node_type' => 'album',
  'expand' => 'instances',
  'insert' => 'm2api_album_insert',
  'update' => 'm2api_album_update',
  'hash_fields' => array('title', 'artist_text', 'copyright', 'year', 'disc_count', 'graphic', 'genre', 'artists', 'tracks'),
);

/**
 * This plugin definition can be simply deleted when we ugprade to CTools 1.3
 */
function m2api_album_m2api_product() {
  return array(
    'settings_form' => 'm2api_album_settings_form',
    'default_settings' => array('release_date_action' => 'if_empty'),
    'node_type' => 'album',
    'expand' => 'instances',
    'insert' => 'm2api_album_insert',
    'update' => 'm2api_album_update',
    'hash_fields' => array('title', 'artist_text', 'copyright', 'year', 'disc_count', 'graphic', 'genre', 'artists', 'tracks'),
  );
}

function m2api_album_settings_form($settings) {
  $form['release_date_action'] = array(
    '#type' => 'select',
    '#title' => t('Use M2 release dates'),
    '#options' => array(
      'always' => t('Always'),
      'if_empty' => t('When not already set'),
      'never' => t('Never'),
    ),
    '#default_value' => $settings['release_date_action'],
  );
  return $form;
}

function m2api_album_insert($doc) {
  $node = new stdClass();
  $node->type = 'album';
  $node->body = '';
  $node->teaser = node_teaser($node->body);
  $node->language = language_default('language');
  $node->uid = 1;

  module_load_include('inc', 'node', 'node.pages');
  node_object_prepare($node);

  _m2api_album_node_data($doc, $node);
  node_save($node);
}

function m2api_album_update($doc, &$node) {
  _m2api_album_node_data($doc, $node);
  node_save($node);
}

/**
 * This should be done after a full node load or on a new node after running
 * it through node_object_prepare().
 */
function _m2api_album_node_data($doc, &$node) {
  // TODO: need to refactor this API so that the settings are passed in.
  $settings = m2api_get_product_settings('album');

  $node->title = $doc->title;
  $node->m2api_document = $doc;

  // TODO: it might make sense to check for changes to the image...
  if (empty($node->field_album_cover[0]['fid']) && !empty($doc->graphic)) {
    // Check that it's a valid image and determine the file type.
    $info = getimagesize($doc->graphic);
    $extensions = array(IMG_GIF => 'gif', IMG_JPG => 'jpg', IMG_PNG => 'png');
    if ($info && $extensions[$info[2]]) {
      // Get a temporary filename.
      $temp_path = file_directory_temp() ."/{$doc->id}.{$extensions[$info[2]]}";
      // Download the image to a temporary file...
      if (copy($doc->graphic, $temp_path)) {
        // ...then move it to the files directory.
        module_load_include('inc', 'filefield', 'field_file');
        $file = field_file_save_file($temp_path, array(), file_directory_path());
        $file->data = array();
        $file->list = 0;
        $node->field_album_cover[0] = $file;
      }
    }
  }

  $node->field_artist[0]['value'] = $doc->artist_text;

  if (!empty($doc->release_dates->US)) {
    $datetime = $doc->release_dates->US . 'T00:00:00';
    $timezone_name = 'America/New_York';
    $timezone = timezone_open($timezone_name);

    // Always fill out our release date field...
    $node->field_m2_available_date[0] = array(
      'value' => $datetime,
      'timezone' => $timezone_name,
      'offset' => timezone_offset_get($timezone, date_create($datetime, $timezone)),
    );
    // ...and optionally fill out the one provided by sonybmg_discography.
    if ($settings['release_date_action'] == 'always' || ($settings['release_date_action'] == 'if_empty' && empty($node->field_release_date[0]['value']))) {
      $node->field_release_date[0] = $node->field_m2_available_date[0];
    }
  }
}