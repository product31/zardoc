<?php
// $Id$

/**
 * @file
 * Defines m2 lyrics CCK field.
 */

/**
 * Implementation of hook_theme().
 */
function m2_theme($existing, $type, $theme, $path) {
  $themes = array(
    'm2_quicksearch' => array(
      'arguments' => array('element' => NULL),
    ),
    'm2_formatter_default' => array(
      'arguments' => array('element' => NULL),
    ),
    'm2_formatter_devel' => array(
      'arguments' => array('element' => NULL),
    ),
  );

  return $themes;
}

/**
 * Implementation of hook_field_info().
 */
function m2_field_info() {
  $fields = array(
    'm2' => array(
      'label' => t('M2 document'),
      'description' => t('Store a reference to an M2 document in the database.'),
    ),
  );

  // Create fields for each of the plugins that want one.
  $plugins = m2_load_plugins();
  foreach ($plugins as $name => $plugin) {
    $id = 'm2_'. $name;
    if (isset($plugin['cck']) && is_array($plugin['cck'])) {
      $fields[$id] = $plugin['cck'];
    }
  }

  return $fields;
}

/**
 * Implementation of hook_field_settings().
 */
function m2_field_settings($op, $field) {
  switch ($op) {
    case 'form':
      $plugins = m2_load_plugins();
      foreach ($plugins as $key => $plugin) {
        $options[$plugin['name']] = array();
        if (is_array($plugin['index'])) {
          foreach ($plugin['index'] as $index => $title) {
            $index = $key .'-'. $index;
            $options[$plugin['name']][$index] = $title;
          }
        }
      }
      $form = array();
      $form['document_type'] = array(
        '#type' => 'select',
        '#title' => t('Document type and search field'),
        '#options' => $options,
        '#required' => TRUE,
        '#default_value' => $field['document_type'] === '' ? '' : $field['document_type'],
        '#description' => t('Select the document type and search field for this field.'),
      );
      return $form;

    case 'save':
      return array('document_type');

    case 'database columns':
      $columns['m2id'] = array('type' => 'int', 'not null' => FALSE, 'unsigned' => TRUE);
      $columns['document'] = array('type' => 'text', 'size' => 'big', 'not null' => FALSE);
      return $columns;

    case 'views data':
      break;
  }
}

/**
 * Implementation of hook_field().
 */
function m2_field($op, &$node, $field, &$items, $teaser, $page) {
  switch ($op) {
    case 'validate':
      if (is_array($items)) {
        foreach ($items as $delta => $item) {
          $error_element = isset($item['_error_element']) ? $item['_error_element'] : '';
          if (is_array($item) && isset($item['_error_element'])) unset($item['_error_element']);
          if (!empty($item['m2id'])) {
            // Fetch the document by id, then validate that it is the correct
            // document type.
            $document = m2_document_load($item['m2id']);
            list($plugin_name, $search_field) = explode('-', $field['document_type']);
            $plugin = m2_load_plugins($plugin_name);
            if ($plugin['class'] != $document->class) {
              form_set_error($error_element, t('Invalid document type specified in the %field field.', array('%field' => $element['#title'])));
            }
          }
        }
      }
      return $items;
    case 'presave':
      // save each document to the database as a json encoded string.
      foreach ($items as $delta => $item) {
        if ($item['m2id']) {
          $items[$delta]['document'] = json_encode(m2_document_load($item['m2id']));
        }
        else {
          $items[$delta]['document'] = NULL;
        }
      }
      break;

    case 'load':
      if (empty($items)) {
        return array();
      }
      foreach ($items as $delta => $item) {
        // Despite hook_content_is_empty(), CCK still doesn't filter out
        // empty items from $op = 'load', so we need to do that ourselves.
        //if (empty($item['m2id']) || !($document = m2_document_load($item['m2id']))) {
        if (empty($item['m2id'])) {
          unset($items[$delta]);
        }
        else {
          $items[$delta]['document'] = json_decode($items[$delta]['document']);
        }
      }
      return array($field['field_name'] => $items);

    case 'sanitize':
      // TODO: it seems like i should be doing something here.
      break;
  }
}

/**
 * Implementation of hook_content_is_empty().
 */
function m2_content_is_empty($item, $field) {
  if (empty($item['m2id'])) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Implementation of hook_field_formatter_info().
 */
function m2_field_formatter_info() {
  return array(
    'default' => array(
      'label' => t('Default'),
      'field types' => array_keys(m2_field_info()),
      'multiple values' => CONTENT_HANDLE_CORE,
    ),
    'devel' => array(
      'label' => t('Devel output'),
      'field types' => array_keys(m2_field_info()),
      'multiple values' => CONTENT_HANDLE_CORE,
    ),
  );
}

/**
 * Theme function for 'default' text field formatter.
 */
function theme_m2_formatter_default($element) {
  $item = $element['#item'];
  return check_plain($item['m2id']);
}

/**
 * Theme function for 'devel' text field formatter.
 */
function theme_m2_formatter_devel($element) {
  $item = $element['#item'];
  return '<pre>'. check_plain(print_r($item['document'], 1)) .'</pre>';
}

/**
 * Implementation of hook_widget_info().
 *
 * Here we indicate that the content module will handle
 * the default value and multiple values for these widgets.
 *
 * Callbacks can be omitted if default handing is used.
 * They're included here just so this module can be used
 * as an example for custom modules that might do things
 * differently.
 */
function m2_widget_info() {
  return array(
    'm2_quicksearch' => array(
      'label' => t('M2 Search'),
      'field types' => array_keys(m2_field_info()),
      'multiple values' => CONTENT_HANDLE_CORE,
      'callbacks' => array(
        'default value' => CONTENT_CALLBACK_DEFAULT,
      ),
    ),
  );
}

/**
 * Implementation of FAPI hook_elements().
 *
 * Any FAPI callbacks needed for individual widgets can be declared here,
 * and the element will be passed to those callbacks for processing.
 *
 * Drupal will automatically theme the element using a theme with
 * the same name as the hook_elements key.
 *
 * Autocomplete_path is not used by m2_widget but other widgets can use it
 * (see nodereference and userreference).
 */
function m2_elements() {
  return array(
    'm2_quicksearch' => array(
      '#input' => TRUE,
      '#columns' => array('m2id', 'document'), '#delta' => 0,
      '#process' => array('m2_quicksearch_process'),
      '#filter_value' => FILTER_FORMAT_DEFAULT,
      '#autocomplete_path' => 'm2/autocomplete',
    ),
  );
}

/**
 * Implementation of hook_widget_settings().
 */
function m2_widget_settings($op, $widget) {
  switch ($op) {
    case 'form':
      $form = array();
      return $form;

    case 'save':
      return array();

  }
}

/**
 * Implementation of hook_widget().
 *
 * Attach a single form element to the form. It will be built out and
 * validated in the callback(s) listed in hook_elements. We build it
 * out in the callbacks rather than here in hook_widget so it can be
 * plugged into any module that can provide it with valid
 * $field information.
 *
 * Content module will set the weight, field name and delta values
 * for each form element. This is a change from earlier CCK versions
 * where the widget managed its own multiple values.
 *
 * If there are multiple values for this field, the content module will
 * call this function as many times as needed.
 *
 * @param $form
 *   the entire form array, $form['#node'] holds node information
 * @param $form_state
 *   the form_state, $form_state['values'][$field['field_name']]
 *   holds the field's form values.
 * @param $field
 *   the field array
 * @param $items
 *   array of default values for this field
 * @param $delta
 *   the order of this item in the array of subelements (0, 1, 2, etc)
 *
 * @return
 *   the form item for a single element for this field
 */
function m2_widget(&$form, &$form_state, $field, $items, $delta = 0) {
  $element = array(
    '#type' => $field['widget']['type'],
    '#default_value' => isset($items[$delta]) ? $items[$delta] : '',
    '#value_callback' => 'm2_quicksearch_value',
  );
  return $element;
}

/**
 * Process an individual element.
 *
 * Build the form element. When creating a form using FAPI #process,
 * note that $element['#value'] is already set.
 *
 * The $fields array is in $form['#field_info'][$element['#field_name']].
 */
function m2_quicksearch_process($element, $edit, $form_state, $form) {
  $field_key = $element['#columns'][0];
  $delta = $element['#delta'];
  $element['m2id'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($element['#value']['m2id']) ? $element['#value']['m2id'] : NULL,
    '#autocomplete_path' => 'm2/autocomplete/'. $element['#field_name'],

    // The following values were set by the content module and need
    // to be passed down to the nested element.
    '#title' => $element['#title'],
    '#description' => $element['#description'],
    '#required' => $element['#required'],
    '#field_name' => $element['#field_name'],
    '#type_name' => $element['#type_name'],
    '#delta' => $element['#delta'],
    '#columns' => $element['#columns'],
  );
  if (empty($element[$field_key]['#element_validate'])) {
    $element[$field_key]['#element_validate'] = array();
  }
  array_unshift($element[$field_key]['#element_validate'], 'm2_autocomplete_validate');

  $element['document'] = array(
    '#type' => 'value',
    '#value' => isset($element['#value']['document']) ? $element['#value']['document'] : NULL,
  );

  // Used so that hook_field('validate') knows where to flag an error.
  $element['_error_element'] = array(
    '#type' => 'value',
    '#value' => implode('][', array_merge($element['#parents'], array($field_key))),
  );

  return $element;
}

/**
 * Value for a nodereference autocomplete element.
 *
 * Substitute in the node title for the node nid.
 */
function m2_quicksearch_value($element, $edit = FALSE) {
  $field_key  = $element['#columns'][0];
  if (!empty($element['#default_value'][$field_key])) {
    $m2id = $element['#default_value'][$field_key];
    $document = m2_document_load($m2id);
    $value = $document->title;
    $value .= ' [m2id:'. $m2id .']';
    return array($field_key => $value);
  }
  return array($field_key => NULL);
}

/**
 * FAPI theme for an individual text elements.
 *
 * The textfield or textarea is already rendered by the
 * textfield or textarea themes and the html output
 * lives in $element['#children']. Override this theme to
 * make custom changes to the output.
 *
 * $element['#field_name'] contains the field name
 * $element['#delta]  is the position of this element in the group
 */
function theme_m2_quicksearch($element) {
  return $element['#children'];
}
