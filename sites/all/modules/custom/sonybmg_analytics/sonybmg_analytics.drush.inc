<?php
// $Id$

/**
 * @file
 * Custom drush commands.
 */

/**
 * Implementation of hook_drush_command().
 */
function sonybmg_analytics_drush_command() {
  $items = array();

  $items['analytics dashboard-enable'] = array(
    'callback' => 'sonybmg_analytics_drush_dashboard_enable',
    'description' => 'Enable and configure the sonybmg_analytics module for use with the Artist Dashboard API.',
    'options' => array(
      '--all' => 'Run on all sites in the current environment.',
    ),
  );
  
  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function sonybmg_analytics_drush_help($section) {
  switch ($section) {
    case 'drush:analytics dashboard-enable':
      return dt("Enable and configure the sonybmg_analytics module for use with the Artist Dashboard API.");
  }
}

/**
 * Drush callback for "drush analytics dashboard-enable".
 */
function sonybmg_analytics_drush_dashboard_enable() {
  if (drush_get_option('all') && function_exists('_sony_drush_get_all')) {
    $sites = _sony_drush_get_all();
    foreach ($sites as $site => $uri) {
      $ret = drush_backend_invoke('analytics dashboard-enable', array('uri' => $uri), 'GET', FALSE);
      $message = sprintf("%-32s %s", $site, trim($ret['output']));
      drush_print($message);
    }
    return;
  }
  
  switch (drush_drupal_major_version()) {
    case 5:
      return drush_set_error('SONY_THEME_REGISTRY_5', 'The Dashboard API is not available for Drupal 5.');
      break;
    case 6:
    default:
      // This call will also include install.inc, which is needed for drupal_install_modules().
      module_load_install('sonybmg_analytics');

      drupal_install_modules(array('services', 'rest_server', 'sonybmg_analytics'));
      _sonybmg_analytics_create_dashboard_key();
      _sonybmg_analytics_set_permissions();
      
      drush_print(dt('Dashboard API Enabled'));
      break;
  }
}
