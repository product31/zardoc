<?php
// $Id: media_brightcove.admin.inc,v 1.1.2.7 2010/07/13 19:24:57 aaron Exp $

/**
 * @file
 * Administrative functions for Media: Brightcove.
 */

/**
 * The administrative settings form for Media: Brightcove.
 */
function media_brightcove_settings() {
  $form = media_brightcove_admin_form();
  $form['settings_info'] = array(
    '#type' => 'item',
    '#value' => t('These settings specifically affect videos displayed from !brightcove. You can also read more about its !api.', array('!brightcove' => l(t('Brightcove.com'), MEDIA_BRIGHTCOVE_MAIN_URL, array('attributes' => array('target' => '_blank'))), '!api' => l(t("developer's API"), MEDIA_BRIGHTCOVE_API_URL, array('attributes' => array('target' => '_blank'))))),
    '#weight' => -10,
  );
  return system_settings_form($form);
}

/**
 * This form will be displayed both at /admin/settings/media_brightcove and
 * admin/content/emfield.
 */
function media_brightcove_admin_form() {
  // Find the Echove library.
  $echove_path = media_brightcove_echove_path();

  if (!$echove_path) {
    drupal_set_message(t("You need to download the !echove and extract the entire contents of the archive into the %path folder of your server.", array('!echove' => l(t('Echove PHP library'), 'http://echove.net/', array('attributes' => array('target' => '_blank'))), '%path' => 'sites/all/libraries')), 'error');
  }

  $form = array();

  $form['player'] = array(
    '#type' => 'fieldset',
    '#title' => t('Player settings'),
    '#description' => t('These settings are for the various !players.', array('!players' => l(t('Brightcove players'), 'https://my.brightcove.com/#publishing', array('attributes' => array('target' => '_blank'))))),
    '#collapsible' => TRUE,
  );
  $form['player'][media_brightcove_variable_name('publisher_id')] = array(
    '#type' => 'textfield',
    '#title' => t('Publisher ID'),
    '#description' => t("Your BrightCove Publisher ID. You can find it on your !profile.", array('!profile' => l(t('Brightcove profile page'), 'https://my.brightcove.com/#', array('attributes' => array('target' => '_blank'))))),
    '#default_value' => media_brightcove_variable_get('publisher_id'),
    '#size' => 13,
    '#maxlength' => 13,
  );
  $form['player'][media_brightcove_variable_name('full_player_id')] = array(
    '#type' => 'textfield',
    '#title' => t('Full-Size Player ID'),
    '#description' => t("The default BrightCove player ID for use on the Full Size video display. You can find the code at your !players. You may override this in the individual field settings.", array('!players' => l(t('Brightcove players page'), 'https://my.brightcove.com/#publishing', array('attributes' => array('target' => '_blank'))))),
    '#default_value' => media_brightcove_variable_get('full_player_id'),
    '#size' => 13,
    '#maxlength' => 13,
    '#suffix' => '<div id="media-brightcove-full-player-id-preview"></div>',
  );
  $form['player'][media_brightcove_variable_name('preview_player_id')] = array(
    '#type' => 'textfield',
    '#title' => t('Preview Player ID'),
    '#description' => t("The default BrightCove player ID for use on the Preview Size video display. You can find the code at your !players. You may override this in the individual field settings.", array('!players' => l(t('Brightcove players page'), 'https://my.brightcove.com/#publishing', array('attributes' => array('target' => '_blank'))))),
    '#default_value' => media_brightcove_variable_get('preview_player_id'),
    '#size' => 13,
    '#maxlength' => 13,
    '#suffix' => '<div id="media-brightcove-preview-player-id-preview"></div>',
  );

  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('API settings'),
    '#description' => t("These settings are for the !api.", array('!api' => l(t("Brightcove developer's API"), MEDIA_BRIGHTCOVE_API_URL, array('attributes' => array('target' => '_blank'))))),
    '#collapsible' => TRUE,
  );
  $form['api'][media_brightcove_variable_name('echove_path')] = array(
    '#type' => 'textfield',
    '#title' => t('Path to Echove library'),
    '#description' => t("You need to download the !echove and extract the entire contents of the archive into the %path folder of your server. The module will attempt to autodiscover its path, but you may override that by entering the path here.", array('!echove' => l(t('Echove PHP library'), 'http://echove.net/', array('attributes' => array('target' => '_blank'))), '%path' => 'sites/all/libraries')),
    '#default_value' => $echove_path,
  );
  $form['api'][media_brightcove_variable_name('read_token')] = array(
    '#type' => 'textfield',
    '#title' => t('Read token'),
    '#description' => t("Your Read Token, for retrieving thumbnails. Don't forget to add any trailing periods (for instance, ..). You can find your tokens in the API Management section of your !account.", array('!account' => l(t('Brightcove account page'), 'https://my.brightcove.com/admin/', array('attributes' => array('target' => '_blank'))))),
    '#default_value' => media_brightcove_variable_get('read_token'),
  );
  $form['api'][media_brightcove_variable_name('write_token')] = array(
    '#type' => 'textfield',
    '#title' => t('Write token'),
    '#description' => t("Your Write Token, for uploading videos. Don't forget to add any trailing periods (for instance, ..). You can find your tokens in the API Management section of your !account.", array('!account' => l(t('Brightcove account page'), 'https://my.brightcove.com/admin/', array('attributes' => array('target' => '_blank'))))),
    '#default_value' => media_brightcove_variable_get('write_token'),
  );

  $form['api']['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['api']['advanced'][media_brightcove_variable_name('description_length')] = array(
    '#type' => 'textfield',
    '#title' => t('Video short description length'),
    '#description' => t('Brightcove imposes a maximum length allowed for their required video (short) descriptions. You should only change this value if Brightcove changes that limit. See the !reference for more information.', array('!reference' => l(t('Brightcove Media API Objects Reference page'), 'http://support.brightcove.com/en/docs/media-api-objects-reference', array('attributes' => array('target' => '_blank'))))),
    '#default_value' => media_brightcove_variable_get('description_length'),
  );

  $form['status'] = array(
    '#type' => 'fieldset',
    '#title' => t('Status settings'),
    '#description' => t("Settings relating to the availability status of a video."),
    '#collapsible' => TRUE,
  );
  $form['status'][media_brightcove_variable_name('check_for_unavailable')] = array(
    '#type' => 'checkbox',
    '#title' => t('Check for unavailable videos'),
    '#description' => t("If checked, then the message below will be displayed if a recently uploaded video is not yet available."),
    '#default_value' => media_brightcove_variable_get('check_for_unavailable'),
  );
  $form['status'][media_brightcove_variable_name('status_display_unavailable')] = array(
    '#type' => 'textarea',
    '#title' => t('Unavailable video message'),
    '#description' => t("If the checkbox above is checked, and you have a message below (which may contain HTML), it will be displayed if a video is not yet available for viewing."),
    '#default_value' => media_brightcove_variable_get('status_display_unavailable'),
  );

  drupal_add_js(drupal_get_path('module', 'media_brightcove') .'/includes/media_brightcove.admin.js');
  drupal_add_js(array('mediaBrightcove' => array('adminSettings' => array('width' => 486, 'height' => 412))), 'setting');

  return $form;
}
