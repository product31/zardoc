<?php
// $Id$

/**
 * @file
 * Sony Canonical Filters Include.
 */

/**
 * Filter to strip trailing slashes from url.
 */
function _sony_canonical_slashes($url) {
  $url['path'] = rtrim(  $url['path'], "/" );
  return $url;
}

/**
 * Filter to strip country (language code) from url.
 */
function _sony_canonical_country($url) {
  $front = url('<front>');
  $base_path = base_path();
  $languages = language_list();
  $prefixes = array();
  foreach ($languages as $language) {
    $prefix = $base_path . $language->prefix;
    if ($front == $prefix) {
      $prefix = preg_quote( $prefix, '/' );
      $url['path'] =  preg_replace( "/" . $prefix . "/" , "", $url['path'], 1);
    }
  }
  return $url;
}

/**
 * Filter to strip home slug from url.
 */
function _sony_canonical_home($url) {
  if (drupal_is_front_page()) {
    $slug = variable_get('site_frontpage', FALSE);
    if ($slug !== FALSE) {
      $url['path'] = url('<front>');
    }
  }
  return $url;
}

/**
 * Filter to strip query string from url.
 */
function _sony_canonical_query($url) {
  unset($url['query']);
  return $url;

}