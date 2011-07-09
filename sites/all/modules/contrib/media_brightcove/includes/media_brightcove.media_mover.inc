<?php
// $Id: media_brightcove.media_mover.inc,v 1.1.2.5 2010/08/26 15:54:41 aaron Exp $

/**
 * @file
 * Functions to implement Media Mover behavior for Media: Brightcove.
 */

/**
 * Upload a video to Brightcove through Media Mover.
 */
function media_brightcove_upload_video($file, $configuration) {
  $title = $configuration['media_brightcove_default_title'];
  $description = $configuration['media_brightcove_default_description'];
  $tags = '';
  $node = NULL;

  if ($file['nid']) {
    $node = node_load($file['nid']);
    if ($node) {
      $title = $node->title;
      if ($body = truncate_utf8(strip_tags($node->body), media_brightcove_variable_get('description_length'), TRUE, TRUE)) {
        $description = $body;
      }
    }
    else {
      watchdog('media_brightcove', 'Unable to upload !file to Brightcove, as it belongs to node %nid which has been deleted.', array('!file' => l($file['filepath'], $file['filepath']), '%nid' => $file['nid']), WATCHDOG_ERROR);
    }
  }

  $filepath = media_mover_api_config_current_file($file);
  $fileinfo = pathinfo($filepath);

  $echove = new Echove(media_brightcove_variable_get('read_token'), media_brightcove_variable_get('write_token'));

  // Create an array of required meta data.
  $metaData = array(
    'name' => $title,
    'shortDescription' => $description,
  );

  // Allow other modules to alter the MetaData before sending to Brightcove.
  drupal_alter('media_brightcove_metadata', $metaData, $node);

  try {
    // Upload the video and save the video ID.
    $id = (string)$echove->createMedia('video', $filepath, $metaData);
  }
  catch (Exception $error) {
    watchdog('media_brightcove', 'Unhandled error from Brightcove when attempting to upload !file: %error', array('!file' => l($filepath, $filepath), '%error' => $error->getMessage()), WATCHDOG_ERROR);
    return FALSE;
  }

  watchdog('media_brightcove', 'Successfully uploaded video to Brightcove: !video', array('!video' => l($title, media_brightcove_video_url($id))), WATCHDOG_NOTICE);
  return media_brightcove_video_url($id);
}

/**
 * Media Mover configuration form element for Media: Brightcove.
 *
 * @see media_brightcove_validate_configuration().
 */
function media_brightcove_config($configuration) {
  $form['media_brightcove_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Upload to Brightcove configuration'),
    '#element_validate' => array('media_brightcove_validate_configuration', array('media_brightcove_config'))
  );

  $form['media_brightcove_config']['media_brightcove_default_title'] = array(
    '#title' => t('Default title'),
    '#type' => 'textfield',
    '#default_value' => $configuration['media_brightcove_default_title'] ? $configuration['media_brightcove_default_title'] : '',
    '#description' => t('Videos which do not belong to a node will be given this title.'),
  );

  $form['media_brightcove_config']['media_brightcove_default_description'] = array(
    '#title' => t('Default description'),
    '#type' => 'textarea',
    '#default_value' => $configuration['media_brightcove_default_description'] ? $configuration['media_brightcove_default_description'] : 'Default description',
    '#description' => t('Videos which do not belong to a node will be given this description.'),
  );

  return $form;
}
