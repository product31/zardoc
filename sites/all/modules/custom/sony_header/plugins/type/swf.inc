<?php
// $Id$

/**
 * @file
 * A plugin for displaying swfs.
 */

// Include our file API abstractions.
_sony_header_include('file');

/**
 * Implementation of hook_sony_header_type().
 */
function sony_header_swf_sony_header_type() {
  return array(
    'tag' => 'swf',
    'content' => FALSE,
    'container' => FALSE,
    'render' => 'sony_header_swf_render',
    'delete' => 'sony_header_swf_delete',
    'settings form' => 'sony_header_swf_settings_form',
    'settings form submit' => 'sony_header_swf_settings_form_submit',
  );
}

/**
 * SWF plugin render overide.
 */
function sony_header_swf_render(&$xml, &$element, &$item) {

  // Replace src with the path to the real file.
  $item->attributes['src'] = sony_header_flexi_file_render(sony_header_flexi_file_load($item->attributes['src']));

}

function sony_header_swf_settings_form(&$form, &$form_state) {
  // Make sure we accept multi part data or we'll just loose the swf.
  $form['#attributes']['enctype'] = 'multipart/form-data';

  $attributes = $form_state['#item']->attributes;
  if (isset($attributes['src']) && is_numeric($attributes['src'])) {
    $file = sony_header_load_file($attributes['src']);
  }

  $form['attributes']['src'] = array(
    '#type' => 'sony_header_flexi_file',
    '#title' => t('SWF file'),
    '#source' => 'src',
    '#default_value' => isset($attributes['src']) ? $attributes['src'] : array(),
    '#file_type' => 'swf',
    '#file_types' => 'swf',
    '#required' => TRUE,
    '#weight' => -1,
  );

  // Provide all the default options.
  sony_header_default_settings_form($form, $form_state);
}

function sony_header_swf_settings_form_submit(&$form, &$form_state) {

  $defaults = isset($form_state['#item']->attributes['src']) ?  $form_state['#item']->attributes['src'] : array();
  $form_state['values']['attributes']['src'] = sony_header_flexi_file_submit(
    $form['attributes']['src'],
    $form_state['values']['attributes']['src'],
    $defaults);
}

function sony_header_swf_delete($item) {
  if (!empty($item->attributes['src']['file'])) {
    sony_header_file_delete($item->attributes['src']['file']);
  }
}
