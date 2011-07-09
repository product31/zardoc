<?php
// $Id: media_brightcove.cck.inc,v 1.1.4.2 2010/07/13 19:24:57 aaron Exp $

/**
 *  @file
 *  CCK settings functions for Media: Brightcove.
 */

/**
 * Add field widget overrides of default settings.
 */
function _media_brightcove_emfield_widget_settings_extra($op, $widget) {
  if ($op == 'form') {
    if ($widget['module'] == 'emvideo') {
      $form['media_brightcove'] = array(
        '#type' => 'fieldset',
        '#title' => t('Media: Brightcove options'),
        '#description' => t('These advanced options will override the display of Brightcove media when handled by this field.'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form['media_brightcove'][media_brightcove_variable_name('publisher_id')] = array(
        '#type' => 'textfield',
        '#title' => t('Publisher ID'),
        '#description' => t('You may override the source of videos here, by entering the unique Brightcove Publisher ID here, which can be found on your !profile', array('!profile' => l(t('Brightcove profile page'), 'https://my.brightcove.com/#', array('attributes' => array('target' => '_blank'))))),
        '#default_value' => isset($widget[media_brightcove_variable_name('publisher_id')]) ? $widget[media_brightcove_variable_name('publisher_id')] : media_brightcove_variable_get('publisher_id'),
      );

      $form['media_brightcove'][media_brightcove_variable_name('full_player_id')] = array(
        '#type' => 'textfield',
        '#title' => t('Full-Size Player ID'),
        '#description' => t("The BrightCove player ID for use on the Full Size video display. You can find the code at your !players.", array('!players' => l(t('Brightcove players page'), 'https://my.brightcove.com/#publishing', array('attributes' => array('target' => '_blank'))))),
        '#default_value' => isset($widget[media_brightcove_variable_name('full_player_id')]) ? $widget[media_brightcove_variable_name('full_player_id')] : media_brightcove_variable_get('full_player_id'),
        '#size' => 13,
        '#maxlength' => 13,
        '#suffix' => '<div id="media-brightcove-full-player-id-preview"></div>',
      );
      $form['media_brightcove'][media_brightcove_variable_name('preview_player_id')] = array(
        '#type' => 'textfield',
        '#title' => t('Preview Player ID'),
        '#description' => t("The BrightCove player ID for use on the Preview Size video display. You can find the code at your !players.", array('!players' => l(t('Brightcove players page'), 'https://my.brightcove.com/#publishing', array('attributes' => array('target' => '_blank'))))),
        '#default_value' => isset($widget[media_brightcove_variable_name('preview_player_id')]) ? $widget[media_brightcove_variable_name('preview_player_id')] : media_brightcove_variable_get('preview_player_id'),
        '#size' => 13,
        '#maxlength' => 13,
        '#suffix' => '<div id="media-brightcove-preview-player-id-preview"></div>',
      );

      $form['media_brightcove']['api'] = array(
        '#type' => 'fieldset',
        '#title' => t('API settings'),
        '#description' => t("These settings are for the !api.", array('!api' => l(t("Brightcove developer's API"), MEDIA_BRIGHTCOVE_API_URL, array('attributes' => array('target' => '_blank'))))),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form['media_brightcove']['api'][media_brightcove_variable_name('read_token')] = array(
        '#type' => 'textfield',
        '#title' => t('Read token'),
        '#description' => t("Your Read Token, for retrieving thumbnails. Don't forget to add any trailing periods (for instance, ..). You can find your tokens in the API Management section of your !account.", array('!account' => l(t('Brightcove account page'), 'https://my.brightcove.com/admin/', array('attributes' => array('target' => '_blank'))))),
        '#default_value' => isset($widget[media_brightcove_variable_name('read_token')]) ? $widget[media_brightcove_variable_name('read_token')] : media_brightcove_variable_get('read_token'),
      );
      $form['media_brightcove']['api'][media_brightcove_variable_name('write_token')] = array(
        '#type' => 'textfield',
        '#title' => t('Write token'),
        '#description' => t("Your Write Token, for uploading videos. Don't forget to add any trailing periods (for instance, ..). You can find your tokens in the API Management section of your !account.", array('!account' => l(t('Brightcove account page'), 'https://my.brightcove.com/admin/', array('attributes' => array('target' => '_blank'))))),
        '#default_value' => isset($widget[media_brightcove_variable_name('write_token')]) ? $widget[media_brightcove_variable_name('write_token')] : media_brightcove_variable_get('write_token'),
      );

      drupal_add_js(drupal_get_path('module', 'media_brightcove') .'/includes/media_brightcove.admin.js');
      drupal_add_js(array('mediaBrightcove' => array('adminSettings' => array('width' => 486, 'height' => 412))), 'setting');

      return $form;
    }
  }
  else if ($op == 'save') {
    $columns = array();
    if ($widget['module'] == 'emvideo') {
      $columns = array(
        media_brightcove_variable_name('publisher_id'),
        media_brightcove_variable_name('full_player_id'),
        media_brightcove_variable_name('preview_player_id'),
        media_brightcove_variable_name('read_token'),
        media_brightcove_variable_name('write_token'),
      );
    }
    return $columns;
  }
}
