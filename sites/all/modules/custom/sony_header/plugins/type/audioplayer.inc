<?php
// $Id$

/**
 * @file
 * Audio Player element type.
 */

/**
 * Implementation of hook_sony_header_type().
 */
function sony_header_audioplayer_sony_header_type() {
  return array(
    'tag' => 'audioPlayer',
    'content' => FALSE,
    'container' => TRUE,
    'children' => array('track'),
    // Use the default render for now. We don't need to do anything fancy.
    'render' => 'sony_header_audioplayer_render',
    'import' => 'sony_header_audioplayer_import',
    'settings form' => 'sony_header_audioplayer_settings_form',
    // 'settings form validate' => 'sony_header_audioplayer_settings_form_validate',
    'settings form submit' => 'sony_header_audioplayer_settings_form_submit',
  );
}

function sony_header_audioplayer_render(&$xml, &$element, &$item) {

  // Convert bool values into bool strings.
  foreach (array('autoPlay', 'showControls') as $key) {
    $item->attributes[$key] = $item->attributes[$key] ? 'true' : 'false';
  }

  $format = $item->attributes['format'];
  unset($item->attributes['format']);

  unset($item->attributes['delay']);
  unset($item->attributes['transition']);

  foreach (array('volume', 'state') as $optional) {
    if (empty($item->attributes[$optional])) {
      unset($item->attributes[$optional]);
    }
  }

  $options = array_filter($format);

  if (!empty($options)) {

    $format_xml = $xml->createElement('format');
    foreach ($options as $name => $option) {
      $attribute = $xml->createAttribute($name);
      $attribute->appendChild(
        $xml->createTextNode($option)
      );
      $format_xml->appendChild($attribute);
    }
    $element->appendChild($format_xml);
  }
}

function sony_header_audioplayer_settings_form(&$form, &$form_state) {
  // <audioPlayer id='audio' autoPlay='true'  x='786' y='325' z='2' showControls='true' volume='.5'><!--state='random'>-->
  // Provide all the default options.
  sony_header_default_settings_form($form, $form_state);
  $item = $form_state['#item'];

  unset($form['attributes']['delay']);
  unset($form['attributes']['transition']);

  // - autoPlay - string, true | false
  $form['attributes']['autoPlay'] = array(
    '#title' => t('Auto Play'),
    '#type' => 'checkbox',
    '#default_value' => isset($item->attributes['autoPlay']) ? $item->attributes['autoPlay'] : '',
    '#description' => t('Begin playback as soon as player is loaded.'),
  );
  // - showControls - string, true | false
  $form['attributes']['showControls'] = array(
    '#title' => t('Show Controls'),
    '#type' => 'checkbox',
    '#default_value' => isset($item->attributes['showControls']) ? $item->attributes['showControls'] : '',
    '#description' => t('Show player controls. Allows user to interact with video (pause, advance, mute).'),
  );
  // - volume - decimal, 0.0 - 1.0
  $form['attributes']['volume'] = array(
    '#title' => t('Volume'),
    '#type' => 'textfield',
    '#size' => '3',
    '#default_value' => isset($item->attributes['volume']) ? $item->attributes['volume'] : '',
    '#description' => t('Volume level. Value between 0.0 and 1.0.'),
  );
  // - state = 'random', optional
  $form['attributes']['state'] = array(
    '#title' => t('State'),
    '#type' => 'select',
    '#options' => array(
      0 => '-- disabled --',
      'random' => t('Random'),
    ),
  );

  ctools_include('dependent');
  // <format>
  $format = isset($form_state['#item']->attributes['format']) ? $form_state['#item']->attributes['format'] : array();
  $form['format'] = array(
    '#title' => t('Format'),
    '#type' => 'fieldset',
    '#input' => TRUE,
    '#tree' => TRUE,
    '#id' => 'edit-format',
    '#prefix' => '<div><div id="edit-format">',
    '#suffix' => '</div></div>',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array(
      'edit-attributes-showControls' => array('1'),
    ),
  );

  //- buttonColor - hex color, no hash(#)
  $form['format']['buttonColor'] = array(
    '#title' => t('Button Color'),
    '#type' => 'textfield',
    '#default_value' => isset($format['buttonColor']) ? $format['buttonColor'] : '',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-showControls' => array('1')),
  );
  // - buttonRollColor - hex color, no hash(#)
  $form['format']['buttonRollColor'] = array(
    '#title' => t('Button Roll Color'),
    '#type' => 'textfield',
    '#default_value' => isset($format['buttonRollColor']) ? $format['buttonRollColor'] : '',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-showControls' => array('1')),
  );
  // - symbolColor - hex color, no hash(#)
  $form['format']['symbolColor'] = array(
    '#title' => t('Symbol Color'),
    '#type' => 'textfield',
    '#default_value' => isset($format['symbolColor']) ? $format['symbolColor'] : '',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-showControls' => array('1')),
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-showControls' => array('1')),
  );
  // - symbolRollColor - hex color, no hash(#)
  $form['format']['symbolRollColor'] = array(
    '#title' => t('Symbol Roll Color'),
    '#type' => 'textfield',
    '#default_value' => isset($format['symbolRollColor']) ? $format['symbolRollColor'] : '',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-showControls' => array('1')),
  );
  // - progressBarColor - hex color, no hash(#)
  $form['format']['progressBarColor'] = array(
    '#title' => t('Progress Bar Color'),
    '#type' => 'textfield',
    '#default_value' => isset($format['progressBarColor']) ? $format['progressBarColor'] : '',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-showControls' => array('1')),
  );
  // - barColor - hex color, no hash(#)
  $form['format']['barColor'] = array(
    '#title' => t('Bar Color'),
    '#type' => 'textfield',
    '#default_value' => isset($format['barColor']) ? $format['barColor'] : '',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-showControls' => array('1')),
  );
}

function sony_header_audioplayer_settings_form_submit(&$form, &$form_state) {

  $form_state['values']['attributes']['format'] = $form_state['values']['format'];
}

/**
 * Audioplayer import plugin callback.
 */
function sony_header_audioplayer_import(&$item, &$element) {

  $formatting = array();
  if (isset($element->format)) {
    foreach ($element->format->attributes() as $k => $v) {
      $formatting[$k] = (string) $v;
    }
  }

  // Store controls back to the item object.
  $item->attributes['format'] = $formatting;
}
