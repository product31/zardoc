<?php
/**
 * @file
 * Manage tracks.
 */

$plugin = array(
  'settings_form' => 'm2api_track_settings_form',
  'default_settings' => array('audio_url_action' => 'always'),
  'node_type' => 'track',
  'expand' => 'full_track',
  'insert' => 'm2api_track_insert',
  'update' => 'm2api_track_update',
  'hash_fields' => array('isrc', 'title', 'artist_text', 'copyright', 'year', 'album', 'track_number', 'disc_number', 'full_track', 'preview', 'pricing'),
);

/**
 * This plugin definition can be simply deleted when we ugprade to CTools 1.3
 */
function m2api_track_m2api_product() {
  return array(
    'settings_form' => 'm2api_track_settings_form',
    'default_settings' => array('audio_url_action' => 'always'),
    'node_type' => 'track',
    'expand' => 'full_track',
    'insert' => 'm2api_track_insert',
    'update' => 'm2api_track_update',
    'hash_fields' => array('isrc', 'title', 'artist_text', 'copyright', 'year', 'album', 'track_number', 'disc_number', 'full_track', 'preview', 'pricing'),
  );
}

function m2api_track_settings_form($settings) {
  $form['audio_url_action'] = array(
    '#type' => 'select',
    '#title' => t('Use M2 30-second previews'),
    '#options' => array(
      'always' => t('Always'),
      'if_empty' => t('When not already set'),
      'never' => t('Never'),
    ),
    '#default_value' => $settings['audio_url_action'],
  );

  return $form;
}

function m2api_track_insert($doc) {
  $node = new stdClass();
  $node->type = 'track';
  $node->body = '';
  $node->teaser = node_teaser($node->body);
  $node->language = language_default('language');
  $node->uid = 1;

  module_load_include('inc', 'node', 'node.pages');
  node_object_prepare($node);

  _m2api_track_node_data($doc, $node);
  node_save($node);
}

function m2api_track_update($doc, &$node) {
  _m2api_track_node_data($doc, $node);
  node_save($node);
}

/**
 * This should be done after a full node load or on a new node after running
 * it through node_object_prepare().
 */
function _m2api_track_node_data($doc, &$node) {
  // TODO: need to refactor this API so that the settings are passed in.
  $settings = m2api_get_product_settings('track');

  $node->title = $doc->title;

  // Older code was putting the track into the products array. Not certain this
  // makes sense.
  if (empty($doc->instances)) {
    $doc->instances[] = (object) array('id' => $doc->id, 'type' => $doc->type);
  }
  $node->m2api_document = $doc;

  // Parent album.
  if ($album_doc = m2api_document_load($doc->album, 'album')) {
    m2api_process_updates($album_doc);
    if ($album_node = m2api_document_node_load($doc->album)) {
      $node->field_album[0]['nid'] = $album_node->nid;
    }
  }

  $node->field_disc_number[0]['value'] = $doc->disc_number;
  $node->field_track_number[0]['value'] = $doc->track_number;

  // Try to parse out the preview URL.
  $preview = is_numeric($doc->preview) ? m2api_document_load($doc->preview, 'preview') : $doc->preview;
  $preview_url = FALSE;
  if ($preview && !empty($preview->media->s3->master)) {
    // Optionally fill out the one provided by sonybmg_discography...
    if ($settings['audio_url_action'] == 'always' || ($settings['audio_url_action'] == 'if_empty' && empty($node->field_audio_file_url[0]['value']))) {
      $node->field_audio_file_url[0]['value'] = $preview->media->s3->master;
    }
    // ...and r2_music.
    if ($settings['audio_url_action'] == 'always' || ($settings['audio_url_action'] == 'if_empty' && empty($node->field_audio_link[0]['url']))) {
      $node->field_audio_link[0]['url'] = $preview->media->s3->master;
    }
  }

  $full_track = is_numeric($doc->full_track) ? m2api_document_load($doc->full_track, 'full_track') : $doc->full_track;
  if ($full_track) {
    // Code modified from getid3's getid3_lib::PlaytimeString() function.
    $playtimeseconds = abs($full_track->duration);
    $contentseconds = round((($playtimeseconds / 60) - floor($playtimeseconds / 60)) * 60);
    $contentminutes = floor($playtimeseconds / 60);
    if ($contentseconds >= 60) {
      $contentseconds -= 60;
      $contentminutes++;
    }
    $duration = intval($contentminutes).':'.str_pad($contentseconds, 2, 0, STR_PAD_LEFT);
    // Couple of different names for the field so just assign it to all.
    $node->field_track_duration[0]['value'] = $duration;
    $node->field_length[0]['value'] = $duration;
    $node->field_track_length[0]['value'] = $duration;
  }

//  $node->field_lyrics = array(0 => array());
//  $node->field_track_video_url = array(0 => array());
//  $node->field_gracenote_lyrics = array(0 => array());
//  $node->field_song_download_links = array(0 => array());
}
