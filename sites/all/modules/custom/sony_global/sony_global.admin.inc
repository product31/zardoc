<?php
// $Id$
/**
 * @file
 * Admin page callbacks for the sony_global module.
 */

/**
 * Form callback for admin/global/configure
 */
function sony_global_admin_configure() {
  $form['links'] = array(
    '#type' => 'fieldset',
    '#title' => t('Language links'),
    '#tree' => 0,
  );

  $form['links']['sony_global_language_selector_style'] = array(
    '#type' => 'radios',
    '#title' => t('Language selector style'),
    '#options' => array(
      'default' => t('Default - Flag icons listed horizontally.'),
      'dropdown' => t('Drop-down'),
      'slider' => t('Slider'),
    ),
    '#default_value' => sony_global_language_selector_style(),
  );
  $form['links']['i18n_hide_translation_links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide content translation links'),
    '#description' => t('Hide the links to translations in content body and teasers. If you choose this option, switching language will only be available from the language switcher block.'),
    '#default_value' => variable_get('i18n_hide_translation_links', 0),
  );

  // From locale_languages_configure_form at admin/settings/language/configure
  $form['locale'] = array(
    '#type' => 'fieldset',
    '#title' => t('Locale'),
    '#tree' => 0,
  );
  $form['locale']['language_negotiation'] = array(
    '#title' => t('Language negotiation'),
    '#type' => 'radios',
    '#options' => array(
      LANGUAGE_NEGOTIATION_NONE => t('None.'),
      LANGUAGE_NEGOTIATION_PATH_DEFAULT => t('Path prefix only.'),
      LANGUAGE_NEGOTIATION_PATH => t('Path prefix with language fallback.'),
      LANGUAGE_NEGOTIATION_DOMAIN => t('Domain name only.')),
    '#default_value' => variable_get('language_negotiation', LANGUAGE_NEGOTIATION_NONE),
    '#description' => t("Select the mechanism used to determine your site's presentation language. <strong>Modifying this setting may break all incoming URLs and should be used with caution in a production environment.</strong>")
  );

  // From i18n_admin_settings() at admin/settings/i18n
  module_load_include('inc', 'i18n', 'i18n.admin');
  $form['i18n'] = array(
    '#type' => 'fieldset',
    '#title' => t('i18n'),
    '#tree' => 0,
  );
  $form['i18n']['i18n_selection_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Content selection mode'),
    '#default_value' => variable_get('i18n_selection_mode', 'simple'),
    '#options' => _i18n_selection_mode(),
    '#description' => t('Determines which content to show depending on the current page language and the default language of the site.'),
  );

  $form['node'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content types'),
    '#tree' => 0,
    '#theme' => 'sony_global_admin_configure_node_types'
  );
  foreach (node_get_types() as $type) {
    $form['node'][$type->type] = array(
      '#title' => $type->name,
    );

    // From locale_form_alter('node_type_form') and translation_form_alter('node_type_form')
    $form['node'][$type->type]['language_content_type_'. $type->type] = array(
      '#type' => 'radios',
      '#default_value' => variable_get('language_content_type_'. $type->type, 0),
      '#options' => array(
        0 => t('Disabled'),
        1 => t('Enabled'),
        TRANSLATION_ENABLED => t('Enabled, with translation'),
      ),
    );

    // Add extended language support option to content type form.
    $form['node'][$type->type]['i18n_node_'. $type->type] = array(
      '#type' => 'radios',
      '#default_value' => variable_get('i18n_node_'. $type->type, LANGUAGE_SUPPORT_NORMAL),
      '#options' => _i18n_content_language_options(),
    );

  }

  $form = system_settings_form($form);
  $form['buttons']['reset']['#submit'] = array('sony_global_admin_reset_to_defaults');

  return $form;
}

/**
 * Theme the content type settings as a table
 */
function theme_sony_global_admin_configure_node_types($form) {
  $headers = array(
    t('Content Type'),
    t('Multilingual Support'),
    t('Extended language support'),
  );
  $rows = array();
  foreach (element_children($form) as $key) {
    $rows[] = array(
      array('data' => $form[$key]['#title'], 'header' => TRUE),
      drupal_render($form[$key]['language_content_type_'. $key]),
      drupal_render($form[$key]['i18n_node_'. $key]),
    );
  }
  $output = theme('table', $headers, $rows);
  return $output . drupal_render($form);
}

function sony_global_admin_reset_to_defaults($form, &$form_state) {
  _sony_global_admin_reset_to_defaults();
}

function _sony_global_admin_reset_to_defaults() {
  variable_set('language_negotiation', LANGUAGE_NEGOTIATION_PATH_DEFAULT);
  variable_set('i18n_selection_mode', 'off');
  drupal_set_message(t('Sony global default configuration variables reset.'));
}