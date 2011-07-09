<?php
// $Id: geoip.admin.inc,v 1.3 2010/05/20 21:05:28 drewish Exp $

/**
 * @file
 * Admin functions for geoip module.
 */

/**
 * Menu callback and form builder for admin/settings/geoip.
 */
function geoip_admin_settings() {
  $form['geoip_data_file'] = array(
    '#type' => 'textfield',
    '#title' => t('GeoIP data file location'),
    '#description' => t('The path to the GeoIP database file.'),
    '#default_value' => variable_get('geoip_data_file', 'sites/all/libraries/geoip/GeoIP.dat'),
    '#after_build' => array('geoip_data_file_validate'),
  );
  $form['geoip_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('GeoIP debug mode'),
    '#description' => t('With this setting enabled, an IP may be passed in through the query string using the <kbd>geoip_debug</kbd> parameter. This should not be used on production sites.'),
    '#default_value' => variable_get('geoip_debug', FALSE),
  );

  return system_settings_form($form);
}

/**
 * Validate that the geoip_data_file exists.
 */
function geoip_data_file_validate($form_element) {
  $file = $form_element['#value'];

  if (!file_exists($file)) {
    form_error($form_element, t('The GeoIP data file could not be located at the specified location.'));
  }
  else {
    $mtime = filemtime($file);
    if ($mtime < strtotime('1 months ago')) {
      drupal_set_message(t('The GeoIP database file is more than a month old. Download the latest file at <a href="@url">MaxMind.com</a>.', array('@url' => 'http://www.maxmind.com/download/geoip/database/GeoIP.dat.gz')), 'warning');
    }
  }

  return $form_element;
}

