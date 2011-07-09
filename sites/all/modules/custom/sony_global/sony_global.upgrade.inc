<?php
// $Id$
/**
 * @file
 * file_description
 */

/**
 * Upgrade from the previous country_code implementation.
 * This is specifically aimed at the Pink site, since after that this should not
 * be necessary again.
 */
function sony_global_upgrade() {
  if (variable_get('sony_global_upgraded', 0)) {
    _sony_global_upgrade_views();
    $output = '<p>The upgrade has already been performed.</p>';
  }
  else {
    $output = drupal_get_form('sony_global_upgrade_form');
  }

  return $output;
}

function sony_global_upgrade_form() {
  $form = array();
  return confirm_form($form,
    t('Are you sure you want to upgrade?'),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/global',
    t('This action cannot be undone.'),
    t('Upgrade'),
    t('Cancel')
  );
}

/**
 * Submit handler for the confirmation form.  Set the batch, then let it go.
 */
function sony_global_upgrade_form_submit($form, &$form_state) {
  $batch = array(
    'title' => t('Upgrading Sony Global Implementation'),
    'operations' => array(
      array('_sony_global_upgrade_batch_process_deprecated_languages', array()),
      array('_sony_global_upgrade_batch_process_update_languages', array()),
      array('_sony_global_upgrade_batch_process_language_switcher', array()),
      array('_sony_global_upgrade_batch_process_disable_country_code', array()),
    ),
    'finished' => '_sony_global_upgrade_finished',
    'file' => drupal_get_path('module', 'sony_global') .'/sony_global.upgrade.inc',
  );

  batch_set($batch);
}

/**
 * Convert nodes using deprecated languages to an appropriate language.
 * Then delete the deprecated languages.
 */
function _sony_global_upgrade_batch_process_deprecated_languages(&$context) {
  $languages = language_list();
  $deprecated = array(
    'en-US' => 'en',
    'fr'    => 'fr-FR',
    'de'    => 'de-DE',
    'it'    => 'it-IT',
    'es'    => 'es-ES',
    'sv'    => 'sv-SE',
  );

  foreach ($deprecated as $old => $new) {
    // update any nodes using a deprecated language to the new language
    db_query('UPDATE {node} SET language="%s" WHERE language="%s"', $new, $old);
    $affected = db_affected_rows();

    // delete the deprecated language
    db_query('DELETE FROM {languages} WHERE language = "%s"', $old);

    drupal_set_message(format_plural($affected,
      'Changed the language of 1 node from %old-language to %new-language.',
      'Changed the language of @count nodes from %old-language to %new-language.',
      array('%old-language' => $old, '%new-language' => $new)));
    drupal_set_message(t('Deleted language %old-language.', array('%old-language' => $old)));

  }
  $context['message'] = t('Deprecated languages removed.');
}

/**
 * Install/update the default languages
 */
function _sony_global_upgrade_batch_process_update_languages(&$context) {
  module_load_include('inc', 'sony_global', 'sony_global.languages');
  sony_global_update_languages();

  if (module_exists('country_code')) {
    $enabled_countries = country_code_countries();
    $keys = '"'. implode('","', array_keys($enabled_countries)) .'"';

    db_query('UPDATE {languages} SET enabled = 0 WHERE prefix NOT IN ('. $keys .')');
  }

  sony_global_language_variables_update();

  $context['message'] = t('Default languages installed.');
}

/**
 * Enable the language switcher block in the country_bar region
 */
function _sony_global_upgrade_batch_process_language_switcher(&$context) {
  $theme = variable_get('theme_default', 'garland');
  $result = db_query('SELECT * FROM {blocks} WHERE module = "country_code" AND delta = 0');
  while ($row = db_fetch_object($result)) {
    db_query('UPDATE {blocks} SET region = "%s", status = %d WHERE module = "locale" AND delta = 0 AND theme = "%s"', $row->region, $row->status, $row->theme);
  }
  $context['message'] = t('Language switcher block configured.');
}

/**
 * Disable the country_code and sony_i18n modules. Then change some variables
 * that were probably set differently while using country_code.
 */
function _sony_global_upgrade_batch_process_disable_country_code(&$context) {
  module_disable(array('country_code', 'sony_i18n'));

  variable_set('language_negotiation', LANGUAGE_NEGOTIATION_PATH_DEFAULT);
  variable_set('i18n_selection_mode', 'off');

  $context['message'] = t('country_code and sony_i18n disabled. Default global settings configured.');
}

/**
 * Figure out which views need to be upgraded.
 */
function _sony_global_upgrade_views() {
  $views = views_get_all_views();
  $affected_views = array();
  foreach ($views as $view) {
    foreach ($view->display as $display_id => $display) {
      if (isset($display->display_options['filters']['country_code_current'])) {
        $affected_views[] = $view->name .':'. $display->display_title .' '. l('Edit', 'admin/build/views/edit/'. $view->name, array('query' => drupal_get_destination()));
      }
    }
  }

  if ($affected_views) {
    $message = 'The following views are still using the country code filter.
      These should be updated to use the language filter instead. '. theme('item_list', $affected_views);
    drupal_set_message($message, 'warning');
  }
}

/**
 * Upgrade finished.  Give an appropriate message and clear the cache.
 */
function _sony_global_upgrade_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('Upgrade finished successfully.'));
  }
  else {
    drupal_set_message(t('Upgrade finished with an error.'), 'error');
  }

  drupal_flush_all_caches();

  variable_set('sony_global_upgraded', 1);
}