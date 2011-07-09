<?php
// $Id$

/**
 * @file
 *
 */

/**
 * Implementation of hook_sony_header_type().
 */
function sony_header_textarea_sony_header_type() {
  return array(
    'tag' => 'textArea',
    'content' => TRUE,
    'container' => FALSE,
    'render' => 'sony_header_textarea_render',
    'settings form' => 'sony_header_textarea_settings_form',
    'settings form submit' => 'sony_header_textarea_settings_form_submit',
  );
}

/**
 * Render callback for textarea element.
 */
function sony_header_textarea_render(&$xml, &$element, &$item) {
  if (!empty($item->content)) {
    $element->appendChild(
      // We have to CDATA this to allow it to render as HTML in flash.
      $xml->createCDATASection($item->content)
    );
  }
}

function sony_header_textarea_settings_form(&$form, &$form_state) {

  // Provide all the default options.
  sony_header_default_settings_form($form, $form_state);

  $attributes = $form_state['#item']->attributes;

  $form['attributes']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => isset($attributes['width']) ? $attributes['width'] : 500,
    '#description' => t( 'Please enter the width of this text area, in pixels, but without the "px" at the end of it. There is no option for hight.')
  );

  $form['attributes']['dropshadow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Dropshadow'),
    //'#default_value' => isset($attributes['dropshadow']) && $attributes['dropshadow'] == 'false' ? FALSE : "true"
    '#default_value' => ($attributes['dropshadow'] == null || $attributes['dropshadow'] == 'false') ? FALSE : TRUE,
  );
  
  $form['attributes']['multiline'] = array(
    '#type' => 'checkbox',
    '#title' => t('Multiline '),
    '#default_value' => ($attributes['multiline'] == null || $attributes['multiline'] == 'false') ? FALSE : TRUE,
  );
}

/**
 * Carousel settings submit callback.
 *
 * Convert checkboxes into usable values.
 */
function sony_header_textarea_settings_form_submit(&$form, &$form_state) {
  if ($form_state['values']['attributes']['dropshadow'] == 1) {
    $form_state['values']['attributes']['dropshadow'] = 'true';
  }
  else {
    $form_state['values']['attributes']['dropshadow'] = 'false';
  }

  if ($form_state['values']['attributes']['multiline'] ==1 ) {
    $form_state['values']['attributes']['multiline'] = 'true';
  }
  else {
    $form_state['values']['attributes']['multiline'] = 'false';
  }
}
