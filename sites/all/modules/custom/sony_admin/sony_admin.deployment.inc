<?php
// $Id$

/**
 * @file
 * Include file for deployment settings section
 */

/**
 * Form callback for /admin/deployment/[live|dev]
 */
function sony_admin_deployment_settings_form(&$form_state, $mode) {
  $form['mode'] = array(
    '#type' => 'value',
    '#value' => $mode,
  );

  return confirm_form($form,
    t('Are you sure you want to change the site setting to %mode mode?', array('%mode' => ($mode == 'live' ? 'Live Production' : 'Development'))),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/deployment',
    t('This action cannot be undone.'),
    t('Submit'),
    t('Cancel')
  );
}

/**
 * Form submit handler
 */
function sony_admin_deployment_settings_form_submit(&$form_state, $form) {
  if ($form_state['mode'] == 'live') {
    variable_set('cache', CACHE_NORMAL);
    drupal_set_message('Page cache enabled.');

    variable_set('block_cache', CACHE_NORMAL);
    drupal_set_message('Block cache enabled.');

    variable_set('preprocess_css', 1);
    drupal_set_message('CSS optimization enabled.');

    variable_set('preprocess_js', 0);
    drupal_set_message('JS optimization disabled.');

    variable_set('error_level', 0);
    drupal_set_message('Error reporting set to log only.');
  }
  else {
    variable_set('cache', CACHE_DISABLED);
    drupal_set_message('Page cache disabled.');

    variable_set('block_cache', CACHE_DISABLED);
    drupal_set_message('Block cache disabled.');

    variable_set('preprocess_css', 0);
    drupal_set_message('CSS optimization disabled.');

    variable_set('preprocess_js', 0);
    drupal_set_message('JS optimization disabled.');

    variable_set('error_level', 1);
    drupal_set_message('Error reporting set to log and screen.');
  }

  drupal_flush_all_caches();
  drupal_set_message('Error reporting set to log and screen.');
}

