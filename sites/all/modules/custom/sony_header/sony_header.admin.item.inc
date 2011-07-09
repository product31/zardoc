<?php
// $Id$
/**
 * @file
 * Item management.
 */

function sony_header_item_preview($header_id) {
  drupal_add_css(drupal_get_path('module', 'sony_header') . '/sony_header.admin.css');
  $output = sony_header_build_breadcrumb_for_header ();
  $header = sony_header_load($header_id);
  $output .= '<div id="flash-header-admin-preview">' . theme('sony_header_flash_embed', $header, TRUE) . '</div>';

  _sony_header_include('render');
  $output .= '<pre>' . check_plain(sony_header_render_xml($header_id, FALSE)) . '</pre>';

  return $output;
}

/**
 * State aware item fetching for item wizard.
 *
 * @param mixed $item_id
 * "new" for new item or the id of the item to edit.
 * @return
 * Header item object
 */
 
function _sony_header_admin_header_item_get_settings($item_id) {

  ctools_include('object-cache');
  $item = ctools_object_cache_get('sony_header_admin_header_item', $item_id);
  if (!$item) {
    if ($item_id == 'new') {
      $item = new stdClass();
      $item->tag_id = $item_id;
      $item->header_id = isset($_GET['header_id']) ? $_GET['header_id'] : 0;
      $item->parent_id = isset($_GET['parent_id']) ? $_GET['parent_id'] : 0;
      $item->type = '';
      $item->id = '';
      $item->publish_item = 1;
      $item->attributes = array();
      $item->content = '';
    }
    else {
      $item = sony_header_item_load($item_id);
    }

    $item->locked = ctools_object_cache_test('sony_header_admin_header_item', $item_id);
  }

  return $item;
}

/**
 * Store state aware settings for item wizard.
 */
function _sony_header_admin_header_item_set_settings($item_id, $item) {
  ctools_include('object-cache');
  ctools_object_cache_set('sony_header_admin_header_item', $item_id, $item);
}

/**
 * Clear state aware settings for item wizard.
 */
function _sony_header_admin_header_item_clear_settings($item_id) {
  ctools_include('object-cache');
  ctools_object_cache_clear('sony_header_admin_header_item', $item_id);
}

/**
 * Item wizard.
 *
 * Used for editing and building items.
 *
 * @param unknown_type $item_id
 * @param unknown_type $state
 * @return unknown_type
 */
function sony_header_admin_header_item_wizard($item_id, $step = 'new') {
  ctools_include('wizard');

  $item = _sony_header_admin_header_item_get_settings($item_id);

  if (!$item || !$item->header_id) {
    return drupal_access_denied();
  }

  $header = sony_header_load($item->header_id);

  // Load parent if there is one.
  $parent = FALSE;
  if ($item->parent_id) {
    $parent = sony_header_item_load($item->parent_id);
  }
  $form_state = array(
    '#header' => $header,
    '#item' => $item,
    '#parent' => $parent,
  );

  if (!empty($item->type)) {
    ctools_include('plugins');
    $form_state['#plugin'] = ctools_get_plugins('sony_header', 'type', $item->type);
  }

  // *** SETUP ARRAY multistep setup **** see docs code
  $form_info = array(
    'id' => 'sony_header_admin_header_item_new',
    'path' => 'admin/build/sony_header/item/new/%step',
    'return path' => 'admin/build/sony_header/header/' . $item->header_id,
    'cancel path' => 'admin/build/sony_header/header/' . $item->header_id,
    'show trail' => TRUE,
    'show back' => TRUE,
    'show cancel' => TRUE,
    'show return' => FALSE,
    'order' => array(
      'new' => t('Setup'),
      'settings' => t('Options'),
    ),
    'forms' => array(
      'new' => array(
        'form id' => 'sony_header_admin_header_new'
      ),
      'settings' => array(
        'form id' => 'sony_header_admin_header_new_settings',
      ),
    ),
  );

  return ctools_wizard_multistep_form($form_info, $step, $form_state);
}

/**
 * Ctools wizard form next callback for feedapi_eparser_settings.
 */
function sony_header_admin_header_item_new_next(&$form_state) {
  _sony_header_admin_header_item_set_settings($form_state['#item']->tag_id, $form_state['#item']);
}

/**
 * Ctools wizard finish callback for new item wizard.
 */
function sony_header_admin_header_item_new_finish(&$form_state) {
  $item = $form_state['#item'];

  _sony_header_admin_header_item_clear_settings($item->tag_id);
  sony_header_item_save($item);
  if ($form_state['clicked_button']['#value'] == t('Finish (Add child)')) {
    $form_state['redirect'] = array(
      'admin/build/sony_header/item/new',
      'parent_id=' . $item->tag_id . '&header_id=' . $item->header_id,
    );
  }
  if ($form_state['clicked_button']['#value'] == t('Finish (New sibling)')) {
    $form_state['redirect'] = array(
      'admin/build/sony_header/item/new',
      'parent_id=' . $item->parent_id . '&header_id=' . $item->header_id,
    );
  }

  if (!empty($item->id)) {
    $name = $item->id;
  }
  else {
    $name = $item->type . '-' . $item->tag_id;
  }

  drupal_set_message(t('Finished creating %tag %name.', array(
    '%tag' => $item->type,
    '%name' => $name,
  )));
}

/**
 * Ctools wizard cancel callback for new item wizard.
 */
function sony_header_admin_header_item_new_cancel($form_state) {
  _sony_header_admin_header_item_clear_settings($form_state['#item']->tag_id);
}

/**
 * Add item form callback.
 *
 * @param $form_state
 * Form state array.
 * @param $item_id
 * Item id to modify. 'new' for a new item.
 * @param $header_id
 * Optional header id. For creating new items.
 * @param $parent_id
 * Optional parent id. For creating new items as a child of an existing item.
 * @return
 * FormAPI definition array.
 */
function sony_header_admin_header_new(&$form, &$form_state) {

  $item = $form_state['#item'];

  if ($form_state['#parent']) {
    // $plugin = $form_state['#plugin'];
    ctools_include('plugins');
    $plugin = ctools_get_plugins('sony_header', 'type', $form_state['#parent']->type);

    if (!empty($plugin['children'])) {
      $elements = $plugin['children'];
    }
  }

  if (empty($elements)) {
    $elements = sony_header_get_types();
  }

  $form['type'] = array(
    '#type' => 'select',
    '#title' => 'Type',
    '#options' => array_combine($elements, $elements),
    '#default_value' => $item->type,
  );
  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => 'ID',
    '#description' => 'The id is a unique identifier useful for theming',
    '#maxlength' => 50,
    '#default_value' => $item->id,
  );
}

function sony_header_admin_header_new_validate($form, &$form_state) {

  if (strpos($form_state['values']['id'], ' ')) {
    form_error($form['id'], 'Spaces are not allowed in the ID.');
  }
}

function sony_header_admin_header_new_submit($form, &$form_state) {
  $form_state['#item']->type = $form_state['values']['type'];
  $form_state['#item']->id = $form_state['values']['id'];
}

function sony_header_admin_header_new_settings(&$form, &$form_state) {

  if ($form_state['#plugin']) {
    $form['title'] = array(
      '#prefix' => '<h2>',
      '#value' => t('Add new %title', array('%title' => $form_state['#plugin']['name'])),
      '#suffix' => '</h2>',
    );
  }

  if ($form_state['#plugin']['content']) {
    $form['content'] = array(
      '#type' => 'textarea',
      '#title' => 'Content',
      '#description' => '',
      '#default_value' => $form_state['#item']->content,
    );
  }

  $form['attributes'] = array(
    '#tree' => true,
    '#type' => 'fieldset',
    '#title' => t('Attributes'),
  );

  $return = $form['buttons']['cancel'];
  unset($form['buttons']['cancel']);
  $form['buttons']['finish'] = array(
    'new_child' => array(
      '#type' => 'submit',
      '#value' => t('Finish & Add child'),
      '#wizard type' => 'finish',
    ),
    'new_sibling' => array(
      '#type' => 'submit',
      '#value' => t('Finish & Add sibling'),
      '#wizard type' => 'finish',
    ),
  );
  $form['buttons']['cancel'] = $return;

  $func = ctools_plugin_get_function($form_state['#plugin'], 'settings form');
  if ($func) {
    $func($form, $form_state);
  }
}

function sony_header_admin_header_new_settings_validate(&$form, &$form_state) {

  $func = ctools_plugin_get_function($form_state['#plugin'], 'settings form validate');
  if ($func) {
    $func($form, $form_state);
  }
}

function sony_header_admin_header_new_settings_submit(&$form, &$form_state) {
  $func = ctools_plugin_get_function($form_state['#plugin'], 'settings form submit');
  if ($func) {
    $func($form, $form_state);
  }

  $form_state['#item']->attributes = $form_state['values']['attributes'];
  $form_state['#item']->content = isset($form_state['values']['content']) ? $form_state['values']['content'] : '';
}

/**
 * Edit item form callback.
 *
 * @param unknown_type $form_state
 * @param $id
 * Item ID.
 * @return
 * FormAPI array.
 */
function sony_header_admin_header_edit_item($form_state, $id) {
  $item = sony_header_item_load($id);
  // change the title of the document
  ctools_include('plugins');
  $header = sony_header_load($item->header_id);

  sony_header_build_breadcrumb_for_item ($item);

  $parent = FALSE;
  if ($item->parent_id) {
    $parent = sony_header_item_load($item->parent_id);
  }

  $form_state = array(
    '#header' => $header,
    '#item' => $item,
    '#plugin' => ctools_get_plugins('sony_header', 'type', $item->type),
    '#parent' => $parent,
  );

  $form = array();
  $form['breadcrumb'] = array (
   '#type' => 'markup',
   '#value' => ($header_id == 'new')? sony_header_build_breadcrumb_for_header() : sony_header_build_breadcrumb_for_header($header),
   '#weight' => -16,
  );
  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => 'ID',
    '#description' => 'The id is a unique identifier useful for  theming',
    '#maxlength' => 50,
    '#weight' => -1000,
    '#default_value' => $item->id,
  );
     $form['publish_item'] = array(
    '#title' => t('Published'),
    '#type' => 'checkbox',
    '#default_value' => $item->publish_item,
     '#description' => t('If this box is checked, the item is live.'),
  );
  if ($form_state['#plugin']['content']) {
    $form['content'] = array(
      '#type' => 'textarea',
      '#title' => 'Content',
      '#description' => '',
      '#default_value' => $item->content,
    );
  }
  $form['attributes'] = array(
    '#tree' => true,
    '#type' => 'fieldset',
    '#title' => t('Attributes'),
  );

  $func = ctools_plugin_get_function($form_state['#plugin'], 'settings form');
  if ($func) {
    $func($form, $form_state);
  }

  $form['save'] = array(
    '#type' => 'submit',
    '#weight' => 100,
    '#value' => t('Save and Return to Manage'),
  );
  return $form;
}

/**
 * Edit form validate callback.
 *
 * @param $form
 * @param $form_state
 * @return
 * No return. Sets message to provide feedback. 
 */
function sony_header_admin_header_edit_item_validate($form, &$form_state) {
  $func = ctools_plugin_get_function($form_state['#plugin'], 'settings form validate');
  if ($func) {
    $func($form, $form_state);
  }
}

/**
 * Edit form submit callback.
 *
 * @param $form
 * @param $form_state
 * @return
 * No return. Sets message to provide feedback.
 */
function sony_header_admin_header_edit_item_submit($form, &$form_state) {

  $func = ctools_plugin_get_function($form_state['#plugin'], 'settings form submit');
  if ($func) {
    $func($form, $form_state);
  }

  $item = drupal_clone($form_state['#item']);
  $item->header_id = $form_state['#header']->header_id;
  $item->id = $form_state['values']['id'];
  $item->publish_item = $form_state['values']['publish_item'];
  $item->content = isset($form_state['values']['content']) ? $form_state['values']['content'] : '';
  $item->attributes = $form_state['values']['attributes'];

  switch(sony_header_item_save($item)) {
    case SAVED_NEW:
      // If this ever happens there's actually probably a really big problem
      // somewhere but its probably better to not fail confusingly and instead
      // let the mistake be fixed in the manage interface
      break;

    case SAVED_UPDATED:
      //drupal_set_message(t( $item->id.' successfully updated with '.$item->publish_item));
      break;

    default:
      break;
  }

  // If editing, go back to listing page.
  $form_state['redirect'] = 'admin/build/sony_header/header/' . $form_state['#header']->header_id;
}

/**
 * Delete item form callback.
 *
 * @param $form_state
 * @param $item_id
 * @return
 * FormAPI Array
 */
function sony_header_admin_header_delete_item(&$form_state, $item_id) {
  $form = array();
  $item = sony_header_item_load($item_id);
  $form['#item'] = $item;
  $form['breadcrumb'] = array (
   '#type' => 'markup',
   '#value' => sony_header_build_breadcrumb_for_header(),
   '#weight' => -16,
  );
  $form['#redirect'] = 'admin/build/sony_header/header/' . $item->header_id . '/manage';

  if (!empty($item->id)) {
    $name = $item->id;
  }
  else {
    $name = $item->type . '-' . $item->tag_id;
  }
  $msg = '<p>' .
    t('Deleting %name will delete the header and all of its items. This can not be undone. Are you sure you want to do this?', array(
        '%name' => $name)) .
      '</p>';

  return confirm_form($form,
    t('Are you sure you want to delete %name', array('%name' => $name)),
      'admin/build/sony_header/' . $item->header_id . '/manage',
    $msg,
    t('Delete'),
    t('Cancel'));
}

/**
 * Delete item form submit callback.
 *
 * @param $form
 * @param $form_state
 * @return
 */
function sony_header_admin_header_delete_item_submit($form, &$form_state) {
  sony_header_item_delete($form['#item']);
}

/**
 * Default render callback.
 * @return unknown_type
 */
function sony_header_default_settings_form(&$form, &$form_state) {
  sony_header_default_settings_form_items($form['attributes'], $form_state['#item']->attributes);
}

function sony_header_default_settings_form_items(&$form, $defaults) {
  drupal_add_css(drupal_get_path('module', 'sony_header') . '/sony_header.admin.css');
    
  $form['wrapper_prefix'] = array(
    '#type' => 'markup',
    '#value' => '<div class="clear-block default-attributes">',
  );

  $form['x'] = array(
    '#title' => t('X = Horizontal'),
    '#type' => 'textfield',
    '#default_value' => isset($defaults['x']) ? $defaults['x'] : 0,
    '#size' => 2,
	'#description' => t('The horizontal distance, in pixels, from the upper left hand corner.' ),
  );
  $form['y'] = array(
    '#title' => t('Y = Vertical'),
    '#type' => 'textfield',
    '#default_value' => isset($defaults['y']) ? $defaults['y'] : 0,
    '#size' => 2,
	'#description' => t('The vertical distance, in pixels, from the upper left hand corner.' ),
  );
  $form['z'] = array(
    '#title' => t('Z = Stack Order'),
    '#type' => 'textfield',
    '#default_value' => isset($defaults['z']) ? $defaults['z'] : 0,
	'#description' => t('Elements with lower number will be below (underneath) elements with higher numbers.' ),
    '#size' => 2,
  );
  $form['delay'] = array(
    '#title' => 'Delay',
    '#type' => 'textfield',
    '#default_value' => isset($defaults['delay']) ? $defaults['delay'] : 0,
	'#description' => t('How much time, in seconds, do you want this element to pause before being seen?' ),
    '#size' => 2,
  );
  $form['transition'] = array(
    '#title' => 'Transition',
    '#type' => 'select',
    '#options' => array('alpha' => 'alpha'),
    '#default_value' => isset($defaults['transition']) ? $defaults['transition'] : 'alpha',
	'#description' => t('At this time, we only have an alpha fade. We created this option because we plan on adding more in the future.' ),
    // '#size' => 10,
  );
  $form['wrapper_suffix'] = array(
    '#type' => 'markup',
    '#value' => '</div>',
  );
}

function sony_header_default_settings_form_validate(&$form, &$form_state) {

  if (isset($form_state['values']['attributes']['z']) && $form_state['values']['attributes']['z'] != 0) {
    $z = $form_state['values']['attributes']['z'];
    if ($z < 0) {
      form_error($form['attributes']['z'], t('Z values must be positive.'));
    }
    else {
      $max_z = _sony_header_validate_z($form_state['#header']->items, $z);
      if ($max_z !== FALSE) {
        form_error($form['attributes']['z'], t('Z value is too high. Suggested value: %z', array('%z' => $max_z + 1)));
      }
    }
  }
}

function sony_header_build_breadcrumb_for_item ($item){
	$breadcrumb = array();
    $breadcrumb[] = l(t('Home'), '<front>');
    $breadcrumb[] = l(t('Administer'), 'admin/');
	$breadcrumb[] = l(t('Site building'), 'admin/build');
	$breadcrumb[] = l(t('Flash Headers'), 'admin/build/sony_header');
	$breadcrumb[] = l(t('Manage Header'), 'admin/build/sony_header/header/'.$item->header_id.'/manage');
    // Set Breadcrumbs
    drupal_set_breadcrumb($breadcrumb);
	  if ($item->id){
	   drupal_set_title(t('Edit '). '"'.$item->id.'"');
       }
}