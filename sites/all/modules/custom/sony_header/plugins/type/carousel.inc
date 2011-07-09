<?php
// $Id$

/**
 * @file
 * Carousel element type.
 */

/**
 * Implementation of hook_sony_header_type().
 */
function sony_header_carousel_sony_header_type() {
  return array(
    'tag' => 'carousel',
    'content' => FALSE,
    'container' => TRUE,
    // Use the default render for now. We don't need to do anything fancy.
    'render' => 'sony_header_carousel_render',
    'settings form' => 'sony_header_carousel_settings_form',
    'settings form submit' => 'sony_header_carousel_settings_form_submit',
    'import' => 'sony_header_carousel_import',
    'children' => array('item'),
  );
}

function sony_header_carousel_render(&$xml, &$element, &$item) {
  // $item->attributes['src'] = $item->attributes[];
  $controls = array();
  if ($item->attributes['useControls'] == 'true') {
    $controls['prev'] = $item->attributes['controls']['control_left'];
    $controls['next'] = $item->attributes['controls']['control_right'];
  }
  $type = isset($item->attributes['controls']['control']) ? $item->attributes['controls']['control'] : array();
  $format = isset($item->attributes['controls']['format']) ? $item->attributes['controls']['format'] : array();

  // Clear out some stuff.
  unset($item->attributes['controls']);

  if (!$item->attributes['autoRotate']) {
    unset($item->attributes['defaultTimer']);
  }

  foreach ($controls as $location => $control) {
    // If disabled, skip rendering.
    if (!empty($control['disable'])) {
      continue;
    }

    $attributes = array(
      'id' => $location,
      'type' => $type,
      'x' => $control['attributes']['x'],
      'y' => $control['attributes']['y'],
      'transition' => $control['attributes']['transition'],
    );

    $nav = $xml->createElement('control');

    if (FALSE !== array_search($type, array('swf', 'image'))) {
      _sony_header_include('file');

      $attributes['src'] = sony_header_flexi_file_render(sony_header_flexi_file_load($control['src']));
    }

    // Add attributes to the new element.
    foreach ($attributes as $name => $value) {
      $attribute = $xml->createAttribute($name);
      $attribute->appendChild(
        $xml->createTextNode($value)
      );
      $nav->appendChild($attribute);
    }

    $element->appendChild($nav);
  }

  if ($type == 'default') {
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
}

function sony_header_carousel_settings_form(&$form, &$form_state) {
  // Provide all the default options.
  sony_header_default_settings_form($form, $form_state);
  ctools_include('dependent');

  // Extra: autoRotate='true' defaultTimer='9' useControls='false'
  $attributes = $form_state['#item']->attributes;

  $default = isset($attributes['autoRotate']) ? $attributes['autoRotate'] : 'true';
  if ($default === 'false') $default = false;
  $form['attributes']['autoRotate'] = array(
    '#title' => 'Auto rotate',
    '#type' => 'checkbox',
    '#default_value' => $default,
  );
  $options = array_keys(array_fill(1, 30, 'foo')); // foo gets tossed by array_keys.
  $options = array_combine($options, $options);
  $form['attributes']['defaultTimer'] = array(
    '#title' => 'Default timer',
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => isset($attributes['defaultTimer']) ? $attributes['defaultTimer'] : '9',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-autoRotate' => array('1')),
  );
  $default = isset($attributes['useControls']) ? $attributes['useControls'] : 'false';
  if ($default === 'false') $default = false;
  $form['attributes']['useControls'] = array(
    '#title' => 'Use Controls',
    '#type' => 'checkbox',
    '#default_value' => $default,
  );

  $form['controls'] = array(
    '#title' => 'Controls',
    '#type' => 'fieldset',
    '#tree' => TRUE,
    // Trigger processing.
    '#input' => TRUE,
    // Wrapper controls.
    '#id' => 'carousel-controls',
    '#prefix' => '<div><div id="carousel-controls">',
    '#suffix' => '</div></div>',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-attributes-useControls' => array('1')),
    'control' => array(
      '#title' => t('Control Type'),
      '#type' => 'select',
      '#options' => array(
        'default' => t('Default'),
        'swf' => t('SWF'),
        'image' => t('Image'),
      ),
      '#default_value' => isset($attributes['controls']['control']) ? $attributes['controls']['control'] : 'disabled',
    ),
    'format' => array(
      '#title' => t('Format'),
      // Collapse fieldsets sometimes to make things easier to read?
      '#type' => 'fieldset',
      '#input' => TRUE,
      '#id' => "carousel-format",
      '#prefix' => '<div><div id="carousel-format">',
      '#suffix' => '</div></div>',
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array("edit-controls-control" => array('default')),
      'buttonColor' => array(
        '#title' => t('Button Color'),
        '#description' => t('Hex color value of the button.'),
        '#type' => 'textfield',
        '#size' => 6,
        '#default_value' => isset($attributes['controls']['format']['buttonColor']) ? $attributes['controls']['format']['buttonColor'] : '',
      ),
      'buttonRollColor' => array(
        '#title' => t('Button Roll Color'),
        '#description' => t('Hex color value of the button on hover.'),
        '#type' => 'textfield',
        '#size' => 6,
        '#default_value' => isset($attributes['controls']['format']['buttonRollColor']) ? $attributes['controls']['format']['buttonRollColor'] : '',
      ),
      'symbolColor' => array(
        '#title' => t('Symbol Color'),
        '#description' => t('Hex color value of the button symbol.'),
        '#type' => 'textfield',
        '#size' => 6,
        '#default_value' => isset($attributes['controls']['format']['symbolColor']) ? $attributes['controls']['format']['symbolColor'] : '',
      ),
      'symbolRollColor' => array(
        '#title' => t('Symbol Roll Color'),
        '#description' => t('Hex color value of the button symbol on hover.'),
        '#type' => 'textfield',
        '#size' => 6,
        '#default_value' => isset($attributes['controls']['format']['symbolRollColor']) ? $attributes['controls']['format']['symbolRollColor'] : '',
      ),
    ),
  );

  $form['controls']['control_left'] = array(
    '#title' => t('Left Control'),
    '#type' => 'fieldset',
    'disable' => array(),
    'attributes' => array(),
    'src' => array(),
  );
  $form['controls']['control_right'] = array(
    '#title' => t('Right Control'),
    '#type' => 'fieldset',
    'disable' => array(),
    'attributes' => array(),
    'src' => array(),
  );

  foreach (array('control_left', 'control_right') as $id) {
    $defaults = $attributes['controls'][$id];
    $default_attributes = isset($defaults['attributes']) ? $defaults['attributes'] : array();

    $form['controls'][$id]['disable'] = array(
      '#title' => t('Disable'),
      '#type' => 'checkbox',
      '#default_value' => isset($defaults['disable']) ? $defaults['disable'] : '',
    );

    sony_header_default_settings_form_items($form['controls'][$id]['attributes'], $default_attributes);
    // We only want 2 attributes so filter down to just those 2.
    $form['controls'][$id]['attributes'] = array_intersect_key($form['controls'][$id]['attributes'], array(
      'wrapper_prefix' => TRUE,
      'wrapper_suffix' => TRUE,
      'x' => TRUE,
      'y' => TRUE,
      'transition' => TRUE,
    ));

    $css_id = str_replace('_', '-', $id);
    $form['controls'][$id]['attributes']['wrapper_prefix'] = array(
      '#id' => 'default-attributes-' . $css_id,
      '#type' => 'markup',
      '#value' => '<div><div id="default-attributes-' . $css_id . '" class="clear-block default-attributes">',
      '#input' => TRUE,
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array(
        "edit-controls-$css_id-disable" => array(0),
      ),
    );

    $form['controls'][$id]['src'] = array(
      '#type' => 'sony_header_flexi_file',
      '#title' => 'Source',
      '#id' => 'carousel-' . $css_id,
      '#prefix' => '<div><div id="carousel-' . $css_id . '">',
      '#suffix' => '</div></div>',
      '#process' => array('ctools_dependent_process', 'expand_sony_header_flexi_file'),
      '#dependency' => array(
        "edit-controls-$css_id-disable" => array(0),
        'edit-controls-control' => array('swf', 'image'),
      ),
      '#dependency_count' => 2,
      '#default_value' => $defaults['src'],
    );

    $form['controls'][$id]['attributes']['wrapper_suffix']['#value'] = '</div></div>';
  }
}

/**
 * Carousel settings submit callback.
 *
 * Convert checkboxes into usable values.
 */
function sony_header_carousel_settings_form_submit(&$form, &$form_state) {
  if ($form_state['values']['attributes']['autoRotate']) {
    $form_state['values']['attributes']['autoRotate'] = 'true';
  }
  else {
    $form_state['values']['attributes']['autoRotate'] = 'false';
  }

  if ($form_state['values']['attributes']['useControls']) {
    $form_state['values']['attributes']['useControls'] = 'true';
  }
  else {
    $form_state['values']['attributes']['useControls'] = 'false';
  }

  // Store control data. Just stash it in the attributes and fix it in the render hook.
  _sony_header_include('file');
  $defaults = isset($form_state['#item']->attributes['control_left']['src']) ?  $form_state['#item']->attributes['control_left']['src'] : array();
  $form_state['values']['controls']['control_left']['src'] = sony_header_flexi_file_submit(
    $form['controls']['control_left']['src'],
    $form_state['values']['controls']['control_left']['src'],
    $defaults);

  $defaults = isset($form_state['#item']->attributes['control_right']['src']) ?  $form_state['#item']->attributes['control_right']['src'] : array();
  $form_state['values']['controls']['control_right']['src'] = sony_header_flexi_file_submit(
    $form['controls']['control_right']['src'],
    $form_state['values']['controls']['control_right']['src'],
    $defaults);
  // TODO - Probably need to delete files if they move to default or disabled.

  $form_state['values']['attributes']['controls'] = $form_state['values']['controls'];
}

/**
 * Carousel import plugin callback.
 */
function sony_header_carousel_import(&$item, &$element) {

  $controls = array();
  if (isset($element->control)) {

    // A set of key/value pairs to translate the expected id's to the attribute ids.
    $control_keys = array('next' => 'control_left', 'prev' => 'control_right');

    // Iterate through the control items found in the xml and convert them to the expected attribute array.
    foreach ($element->control as $control_element) {
      $control = array();
      $control['attributes'] = array();
      foreach ($control_element->attributes() as $k => $v) {
        $control['attributes'][$k] = (string) $v;
      }

      // ID is special so clear it out of the attributes.
      $control['id'] = $control['attributes']['id'];
      unset($control['attributes']['id']);

      // Type is only stored in one place(on the controls array) since it has to be equal.
      $controls['control'] = $control['attributes']['type'];
      unset($control['attributes']['type']);

      // Provide expected src values.
      if (isset($control['attributes']['src'])) {
        $control['src'] = array('path' => $control['attributes']['src']);
        unset($control['attributes']['src']);
      }
      else {
        $control['src'] = array();
      }

      $id = $control_keys[$control['id']];
      $controls[$id] = $control;
    }
  }

  $controls['format'] = array();
  if (isset($element->format)) {
    foreach ($element->format->attributes() as $k => $v) {
      $controls['format'][$k] = (string) $v;
    }
  }

  // Store controls back to the item object.
  $item->attributes['controls'] = $controls;
}
