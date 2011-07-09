<?php
// $Id$

/**
 * @file
 * file_description
 */

/**
 * Admin settings form callback
 */
function sony_coppa_settings() {
  $form['sony_coppa_site_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Sony BMG Site ID'),
    '#description' => t('The ID assigned to this site by Sony BMG.'),
    '#default_value' => variable_get('sony_coppa_site_id', NULL),
    '#size' => 10,
  );

  $form['sony_coppa_audience'] = array(
    '#type' => 'radios',
    '#title' => t('COPPA Audience'),
    '#description' => t('Choose audience of the site. Do not guess. If you do not know for sure, ask someone who does.'),
    '#options' => array(
      SONY_COPPA_GENERAL_AUDIENCE => t('General Audience'),
      SONY_COPPA_ATTRACTIVE_TO_CHILDREN => t('REAC: There is a "Reasonable Expectation that the website will be Attractive to Children" under 13.'),
      SONY_COPPA_DIRECTED_TO_CHILDREN => t('Directed toward Children'),
    ),
    '#default_value' => variable_get('sony_coppa_audience', NULL),
  );

  $form = system_settings_form($form);
  $form['#submit'][] = 'sony_coppa_settings_submit';

  return $form;
}

function sony_coppa_settings_submit($form, &$form_state) {
  // A little backwards compatibility for code using the old 'sony_coppa_reac'
  // variable. Any non-general audience sites are considered reac by the old
  // standard.
  $form_state['values']['sony_coppa_reac'] = (int) ($form_state['values']['sony_coppa_audience'] != SONY_COPPA_GENERAL_AUDIENCE);

  // Since we use hook_menu_alter() to switch the user registration form let's
  // just take the hit and rebuild the menus to be sure it's correct.
  menu_rebuild();
}

/**
 * Admin settings related to 'Directed to Children' registration
 */
function sony_coppa_settings_registration() {
  if (sony_coppa_audience() != SONY_COPPA_DIRECTED_TO_CHILDREN) {
    drupal_set_message('These settings only apply when the site\'s audience is set to <em>Directed to Children</em>.');
    return array();
  }

  $form['sony_coppa_registration_username_part1'] = array(
    '#type' => 'textarea',
    '#title' => t('Username segments, part 1'),
    '#default_value' => variable_get('sony_coppa_registration_username_part1', ''),
  );
  $form['sony_coppa_registration_username_part2'] = array(
    '#type' => 'textarea',
    '#title' => t('Username segments, part 2'),
    '#default_value' => variable_get('sony_coppa_registration_username_part2', ''),
  );
  $form['sony_coppa_registration_privacy_questions'] = array(
    '#type' => 'textarea',
    '#title' => t('Privacy questions'),
    '#default_value' => variable_get('sony_coppa_registration_privacy_questions', ''),
  );

  return system_settings_form($form);
}

