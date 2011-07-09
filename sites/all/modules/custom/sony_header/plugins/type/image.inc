<?php
// $Id$

/**
 * @file
 * A plugin for displaying images.
 */

// Include our file API abstractions.
_sony_header_include('file');

/**
 * Implementation of hook_sony_header_type().
 */
function sony_header_image_sony_header_type() {
  return array(
    'tag' => 'image',
    'content' => FALSE,
    'container' => FALSE,
    'render' => 'sony_header_image_render',
    'delete' => 'sony_header_image_delete',
    'settings form' => 'sony_header_image_settings_form',
    'settings form validate' => 'sony_header_image_settings_form_validate',
    'settings form submit' => 'sony_header_image_settings_form_submit',
  );
}

/**
 * Image plugin render overide.
 */
function sony_header_image_render(&$xml, &$element, &$item) {

  $src = $item->attributes['src'];

  // Replace src with the path to the real file.
  $item->attributes['src'] = sony_header_flexi_file_render(sony_header_flexi_file_load($item->attributes['src']));

  foreach (array('scale', 'target', 'tracking', 'href') as $tag) {
    if (empty($item->attributes[$tag])) {
      unset($item->attributes[$tag]);
    }
  }
}

function sony_header_image_settings_form(&$form, &$form_state) {
  // Make sure we accept multi part data or we'll just loose the image.
  $form['#attributes']['enctype'] = 'multipart/form-data';

  $attributes = $form_state['#item']->attributes;
  if (isset($attributes['src']) && is_numeric($attributes['src'])) {
    $file = sony_header_load_file($attributes['src']);
  }

  $form['attributes']['src'] = array(
    '#type' => 'sony_header_flexi_file',
    '#title' => t('Image file'),
    '#file_type' => 'image',
    '#source' => 'src',
    '#weight' => -1,
    '#required' => TRUE,
    '#default_value' => ($attributes['src']) ? $attributes['src'] : array(),
  );

  // Provide all the default options.
  sony_header_default_settings_form($form, $form_state);

$form['attributes']['href'] = array(
    '#title' => 'href',
    '#type' => 'textfield',
    '#size' => 120,
    '#maxlength' => 250,
    '#default_value' => ($attributes['href']) ? $attributes['href'] : '',
    '#description' => t('Optional path to link to. If empty, the image will not be a link.')
  );  
  
  $form['attributes']['target'] = array(
    '#title' => t('Target'),
    '#type' => 'select',
    '#options' => array(
      '' => t('Same window'),
      '_blank' => t('New window'),
    ),
    '#default_value' => ($attributes['target']) ? $attributes['target'] : '',
  );

  $form['attributes']['tracking'] = array(
    '#type' => 'textfield',
    '#title' => t('Tracking'),
    '#default_value' => ($attributes['tracking']) ? $attributes['tracking'] : '',
    // TODO - Get a better description
     '#description' => t('Implementation of Google Analytics in our Flash Header Tool. In the field above, enter <strong>the web property ID</strong>. This is also known as the <em>UA number</em> of your tracking code and looks like <code>UA-xxxxx-yy</code>, where the x\'s and y\'s are replaced with the numbers that correspond to your account and profile information for the object you are tracking. See <a href="/apis/analytics/docs/concepts/gaConceptsAccounts.html#webProperty" target="blank">Web Property</a> for more information.'),
  );
  
 $form['attributes']['dropshadow'] = array(
    '#type' => 'checkbox',
    '#title' => t('Dropshadow'),
     '#default_value' => ($attributes['dropshadow'] == null || $attributes['dropshadow'] == 'false') ? FALSE : TRUE,
   // '#default_value' => ($attributes['dropshadow']) && $attributes['dropshadow'] == 'false' ? FALSE : "true"
  );
 
  $form['attributes']['scale']= array(
    '#type' => 'textfield',
    '#title' => t('Scale'),
    '#default_value' => ($attributes['scale']) ? $attributes['scale'] : '0',
    '#size' => 5,
    '#description' => t('A value between 0 and 1 by which to scale the image.'),
  );
  
}

function sony_header_image_settings_form_validate($form, &$form_state) {
  // Do default validation of default elements.
  sony_header_default_settings_form_validate($form, $form_state);

  // Make sure the scale value is between the allowed values.
  if ($form_state['values']['attributes']['scale'] > 1 || $form_state['values']['attributes']['scale'] < 0) {
    form_error($form['attributes']['scale'], 'Invalid scale value.');
  }
}

function sony_header_image_settings_form_submit(&$form, &$form_state) {
  // Convert checkboxes into usable values.
  if ($form_state['values']['attributes']['dropshadow'] == 1) {
    $form_state['values']['attributes']['dropshadow'] = 'true';
  }
  else {
    $form_state['values']['attributes']['dropshadow'] = 'false';
  }

  $defaults = isset($form_state['#item']->attributes['src']) ?  $form_state['#item']->attributes['src'] : array();
  $form_state['values']['attributes']['src'] = sony_header_flexi_file_submit(
    $form['attributes']['src'],
    $form_state['values']['attributes']['src'],
    $defaults);
}

function sony_header_image_delete($item) {
  if (!empty($item->attributes['src']['file'])) {
    sony_header_file_delete($item->attributes['src']['file']);
  }
}