<?php
// $Id$

/**
 * @file
 * Video Player element type.
 */

/**
 * Implementation of hook_sony_header_type().
 */
function sony_header_videoplayer_sony_header_type() {
  return array(
    'tag' => 'vidPlayer',
    'content' => FALSE,
    'container' => TRUE,
    'children' => array('track'),
    // Use the default render for now. We don't need to do anything fancy.
    'render' => 'sony_header_videoplayer_render',
    'import' => 'sony_header_videoplayer_import',
    'settings form' => 'sony_header_videoplayer_settings_form',
    'settings form validate' => 'sony_header_videoplayer_settings_form_validate',
    'settings form submit' => 'sony_header_videoplayer_settings_form_submit',
  );
}

function sony_header_videoplayer_render(&$xml, &$element, &$item) {

  // Convert bool values into bool strings.
  foreach (array('autoPlay', 'showControls', 'stroke') as $key) {
    $item->attributes[$key] = $item->attributes[$key] ? 'true' : 'false';
  }

  if (!$item->attributes['width']) {
    unset($item->attributes['width']);
  }

  $format = $item->attributes['format'];
  unset($item->attributes['format']);

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

function sony_header_videoplayer_settings_form(&$form, &$form_state) {
  // <vidPlayer x='285' y='40' z='0' transition='alpha' delay= '1' autoPlay='true' showControls='true' controlsPosition='overlayCenter' width='423.5' stroke='true'>
  // Provide all the default options.
  sony_header_default_settings_form($form, $form_state);
  ctools_include('dependent');
  $item = $form_state['#item'];

  $form['attributes']['width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#default_value' => isset($item->attributes['width']) ? $item->attributes['width'] : '',
    '#description' => t('Width of video player. Will resize video if needed to fit within the width.'),
    '#size' => '10',
  );

  $form['attributes']['autoPlay'] = array(
    '#title' => t('Auto Play'),
    '#type' => 'checkbox',
    '#default_value' => isset($item->attributes['autoPlay']) ? $item->attributes['autoPlay'] : '',
    '#description' => t('Begin playback as soon as player is loaded.'),
  );

  $form['attributes']['showControls'] = array(
    '#title' => t('Show Controls'),
    '#type' => 'checkbox',
    '#default_value' => isset($item->attributes['showControls']) ? $item->attributes['showControls'] : '',
    '#description' => t('Show player controls. Allows user to interact with video (pause, advance, mute).'),
  );

  $options = array(
    'center',
    'left',
    'right',
    'overlayCenter',
    'overlayLeft',
    'overlayRight',
  );
  $form['attributes']['controlsPosition'] = array(
    '#title' => t('Controls Position'),
    '#type' => 'select',
    '#options' => array_combine($options, $options),
    '#default_value' => isset($item->attributes['controlsPosition']) ? $item->attributes['controlsPosition'] : 'center',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-showControls' => array('1')),
  );
  $form['attributes']['stroke'] = array(
    '#title' => t('Stroke'),
    '#type' => 'checkbox',
    '#default_value' => isset($item->attributes['stroke']) ? $item->attributes['stroke'] : '',
  );

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
      'edit-attributes-stroke' => array('1'),
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
  // - strokeColor - hex color, no hash(#)
  $form['format']['strokeColor'] = array(
    '#title' => t('Stroke Color'),
    '#type' => 'textfield',
    '#default_value' => isset($format['strokeColor']) ? $format['strokeColor'] : '',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-stroke' => array('1')),
  );
  // - strokethickness - decimal number. allow for < 1 values like 0.25
  $form['format']['strokeThickness'] = array(
    '#title' => t('Stroke Thickness'),
    '#type' => 'textfield',
    '#default_value' => isset($format['strokeThickness']) ? $format['strokeThickness'] : '',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-stroke' => array('1')),
  );
  // - strokeAlpha - decimal number 0.0 - 1.0
  $form['format']['strokeAlpha'] = array(
    '#title' => t('Stroke Alpha'),
    '#type' => 'textfield',
    '#default_value' => isset($format['strokeAlpha']) ? $format['strokeAlpha'] : '',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-stroke' => array('1')),
  );
}

function sony_header_videoplayer_settings_form_validate(&$form, &$form_state) {
  // Do default validation of default elements.
  sony_header_default_settings_form_validate($form, $form_state);

  //
  $controls = array(
    'buttonColor',
    'buttonRollColor',
    'symbolColor',
    'symbolRollColor',
    'progressBarColor',
    'barColor',
  );
  $stroke = array(
    'strokeColor',
    'strokeThickness',
    'strokeAlpha',
  );
  if ($form_state['values']['attributes']['showControls']) {
    foreach ($controls as $color) {
      // If its empty skip validation since we'll just drop the values from rendering.
      if (empty($form_state['values']['format'][$color])) {
        continue;
      }

      $num = hexdec($form_state['values']['format'][$color]);
      // Make sure number is between 0 and FFFFFF.
      if (!eregi("^[0-9ABCDEFabcdef]+$", $form_state['values']['format'][$color])) {
        form_error($form['format'][$color], 'Invalid color value. Must be a hex color value without the #.');
      }

      if ($num < 0 || $num > 16777215 ) {
        form_error($form['format'][$color], 'Invalid color value.');
      }
    }
  }

  if ($form_state['values']['attributes']['stroke']) {
    // If its empty skip validation since we'll just drop the values from rendering.
    if (!empty($form_state['values']['format']['strokeColor'])) {
      $num = hexdec($form_state['values']['format']['strokeColor']);
      // Make sure number is between 0 and FFFFFF.
      if (!eregi("^[0-9ABCDEFabcdef]+$", $form_state['values']['format']['strokeColor'])) {
        form_error($form['format']['strokeColor'], 'Invalid color value. Must be a hex color value without the #.');
      }

      if ($num < 0 || $num > 16777215 ) {
        form_error($form['format']['strokeColor'], 'Invalid color value.');
      }
    }
  }
}

function sony_header_videoplayer_settings_form_submit(&$form, &$form_state) {

  $form_state['values']['attributes']['format'] = $form_state['values']['format'];
}

/**
 * Audioplayer import plugin callback.
 */
function sony_header_videoplayer_import(&$item, &$element) {

  $formatting = array();
  if (isset($element->format)) {
    foreach ($element->format->attributes() as $k => $v) {
      $formatting[$k] = (string) $v;
    }
  }

  // Store controls back to the item object.
  $item->attributes['format'] = $formatting;
}
