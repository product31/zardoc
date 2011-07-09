<?php
// $Id$

/**
 * @file
 * Carousel element type.
 */

/**
 * Implementation of hook_sony_header_type().
 */
function sony_header_track_sony_header_type() {
  return array(
    'tag' => 'track',
    'content' => TRUE,
    'render' => 'sony_header_track_render',
    // Use the default render for now. We don't need to do anything fancy.
    'settings form' => 'sony_header_track_settings_form',
  );
}

function sony_header_track_render(&$xml, &$element, &$item) {

  // The image is optional?
  foreach (array('img', 'startTime', 'endTime') as $optional) {
    if (empty($item->attributes[$optional])) {
      unset($item->attributes[$optional]);
    }
  }

}

function sony_header_track_settings_form(&$form, &$form_state) {

  $form['content']['#title'] = t('Title');
  $form['content']['#type'] = 'textfield';

  // Audio and video tracks actually have different fields.
  switch ($form_state['#parent']->type) {
    case 'videoplayer':
      sony_header_track_video_settings_form($form, $form_state);
      break;

    case 'audioplayer':
      sony_header_track_audio_settings_form($form, $form_state);
      break;

  }
}

function sony_header_track_video_settings_form(&$form, &$form_state) {

  $form['attributes']['src'] = array(
    '#title' => t('Source'),
    '#type' => 'textfield',
    '#description' => t('Video source url.'),
    '#default_value' => isset($form_state['#item']->attributes['src']) ? $form_state['#item']->attributes['src'] : '',
  );
}

function sony_header_track_audio_settings_form(&$form, &$form_state) {

  $form['attributes']['rtmp'] = array(
    '#title' => t('RTMP'),
    '#type' => 'textfield',
    '#description' => t('The base RTMP URL.'),
    '#default_value' => isset($form_state['#item']->attributes['rtmp']) ? $form_state['#item']->attributes['rtmp'] : '',
  );

  $form['attributes']['src'] = array(
    '#title' => t('Source'),
    '#type' => 'textfield',
    '#description' => t('Audio source url.'),
    '#default_value' => isset($form_state['#item']->attributes['src']) ? $form_state['#item']->attributes['src'] : '',
  );

  $form['attributes']['img'] = array(
    '#title' => t('Image'),
    '#type' => 'textfield',
    '#description' => t('Image source url.'),
    '#default_value' => isset($form_state['#item']->attributes['img']) ? $form_state['#item']->attributes['img'] : '',
  );

  $form['attributes']['startTime'] = array(
    '#title' => t('Start Time'),
    '#type' => 'textfield',
    '#description' => t('Optional player start time.'),
    '#default_value' => isset($form_state['#item']->attributes['startTime']) ? $form_state['#item']->attributes['startTime'] : '',
  );
  $form['attributes']['endTime'] = array(
    '#title' => t('End Time'),
    '#type' => 'textfield',
    '#description' => t('Optional player end time.'),
    '#default_value' => isset($form_state['#item']->attributes['endTime']) ? $form_state['#item']->attributes['endTime'] : '',
  );
}
