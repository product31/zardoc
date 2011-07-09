<?php
// $Id$
/**
 * @file
 * Provider callback include.
 *
 * Function hooks for emaudio providers.
 */

/**
 * hook emaudio_PROVIDER_info
 *
 * This returns information relevant to a specific 3rd party audio provider
 * @return
 *   an array of strings requested by various admin and other forms
 *   'name' => the translated name of the provider
 *   'url' => the url to the main page for the provider
 *   'settings_description' => a description of the provider that will be posted in the admin settings form
 *   'supported_features' => an array of rows describing the state of certain supported features by the provider.
 *      These will be rendered in a table, with the columns being 'Feature', 'Supported', 'Notes'.
 */
function emaudio_emaudio_audio_player_info() {
  return array(
    'provider' => 'audio-player',
    'name' => t('Audio Player'),
    'url' => 'http://wpaudioplayer.com/standalone',
    'settings_description' => t('Renders a custom url using the WordPress Audio Player flash.'),
    'supported_features' => array(
      array(t('Autoplay'), t('Yes'), ''),
      array(t('RSS Attachment'), t('No'), ''),
      array(t('Thumbnails'), t('No'), t('')),
    ),
  );
}

/**
 * hook emaudio_PROVIDER_settings
 * this should return a subform to be added to the emaudio_settings() admin settings page.
 * note that a form field will already be provided, at $form['PROVIDER'] (such as $form['podomatic'])
 * so if you want specific provider settings within that field, you can add the elements to that form field.
 */
function emaudio_emaudio_audio_player_settings() {
  $form = array();
  return $form;
}

/**
 * hook emaudio_PROVIDER_extract
 * this is called to extract the video code from a pasted URL or embed code.
 * @param $embed
 *   an optional string with the pasted URL or embed code
 * @return
 *   either an array of regex expressions to be tested, or a string with the audio code to be used
 *   if the hook tests the code itself, it should return either the string of the audio code (if matched), or an empty array.
 *   otherwise, the calling function will handle testing the embed code against each regex string in the returned array.
 */
function emaudio_emaudio_audio_player_extract($embed = '') {
  return $embed;
}
