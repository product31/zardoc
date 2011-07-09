<?php
// $Id$

/**
 * @file
 * Config items
 */

/**
 * Implementation of hook_sony_header_type().
 */
function sony_header_config_sony_header_type() {
  return array(
    'tag' => 'config',
    'content' => FALSE,
    'container' => FALSE,
    'system' => TRUE,
    'render' => 'sony_header_config_render',
  );
}

/**
 * Render callback for config element.
 */
function sony_header_config_render(&$xml, &$element, &$item) {
  // We only want 2 attributes so filter down to just those 2.
  $item->attributes = array_intersect_key($item->attributes, array(
    'cssPath' => TRUE,
    'fontPath' => TRUE,
    'embedFonts' => TRUE,
    'checkPolicy' => TRUE,
  ));

  $assets = base_path() . drupal_get_path('module', 'sony_header') . '/assets';
  $attributes = $item->attributes;

  // Replace cssPath with the path to the real file.
  if (!empty($attributes['cssPath']['file'])) {
    $file = sony_header_load_file($attributes['cssPath']['file']);

    // Call base path directly because url() will include localizations breaking
    // the actual path on global sites. Yuck.
    $item->attributes['cssPath'] = base_path() . $file->filepath;
  }
  elseif (!empty($attributes['cssPath']['path'])) {
    $item->attributes['cssPath'] = $attributes['cssPath']['path'];
  }
  else {
    $item->attributes['cssPath'] = "$assets/default.css";
  }

  // Replace fontPath with the path to the real file.
  if (!empty($attributes['fontPath']['file'])) {
    $file = sony_header_load_file($attributes['fontPath']['file']);

    // Call base path directly because url() will include localizations breaking
    // the actual path on global sites. Yuck.
    $item->attributes['fontPath'] = base_path() . $file->filepath;
  }
  elseif (!empty($attributes['fontPath']['path'])) {
    $item->attributes['fontPath'] = $attributes['fontPath']['path'];
  }
  else {
    $item->attributes['fontPath'] = "$assets/fonts.swf";
  }
}
