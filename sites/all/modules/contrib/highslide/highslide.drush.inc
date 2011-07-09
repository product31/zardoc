<?php
// $Id: highslide.drush.inc,v 1.2 2010/08/24 12:42:57 q0rban Exp $

/**
 * @file
 *   Drush integration for Highslide module.
 */

/**
 * Implementation of hook_drush_command().
 *
 * @return
 *   An associative array describing your command(s).
 */
function highslide_drush_command() {
  $items = array();

  $items['highslide-js'] = array(
    'callback' => 'highslide_drush_highslide_js',
    'description' => dt('Downloads the latest Highslide JS file from Github.'),
    'arguments' => array(
      'path' => dt('Optional. A path to the highslide module. If omitted Drush will use the default location.'),
    ),
  );

  return $items;
}

function highslide_drush_highslide_js() {
  $args = func_get_args();
  $path = $args[0] ? $args[0] : drupal_get_path('module', 'highslide') .'/highslide';
  $js_path = 'http://github.com/q0rban/drupal-highslide-js/raw/master/highslide-full.min.js';
  $existing = _highslide_js_path();

  if ($existing && !drush_confirm(dt('Highslide JS appears to already exist at !path.  Continuing may overwrite this file.  Do you still want to proceed?', array('!path' => $existing)))) {
    return;
  }

  drush_op('chdir', $path);
  if (drush_shell_exec("wget -N $js_path")) {
    drush_log(dt('Highslide JS has been downloaded to @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to download the Highslide JS to @path', array('@path' => $path)), 'error');
  }
}