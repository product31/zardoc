<?php
// $Id: feedapi_eparser.settings.inc,v 1.10 2009/09/09 15:44:50 neclimdul Exp $

/**
 * Page callback for eparser settings wizard.
 */
function feedapi_eparser_wizard($node, $step = 'setup') {
  ctools_include('wizard');
  ctools_include('object-cache');

  // *** SETUP ARRAY multistep setup **** see docs code
  $form_info = array(
    'id' => 'feedapi_eparser_settings',
    'path' => 'node/' . $node->nid . '/eparser/%step',
    'return path' => 'node/' . $node->nid,
    'cancel path' => 'node/' . $node->nid,
    'show trail' => TRUE,
    'show back' => TRUE,
    'show cancel' => TRUE,
    'show return' => FALSE,
    'order' => array(
      'setup' => t('Setup'),
      'settings' => t('Setup Options'),
      'namespace' => t('Add Namespaces'),
//      'namespace settings' => t('Namespace Settings'),
    ),
    'forms' => array(
      'setup' => array(
        'form id' => 'feedapi_eparser_settings_setup'
      ),
      'settings' => array(
        'form id' => 'feedapi_eparser_settings_setup_settings',
      ),
      'namespace' => array(
        'form id' => 'feedapi_eparser_settings_namespace'
      ),
      'namespace settings' => array(
        'form id' => 'feedapi_eparser_settings_namespace_settings',
      ),
    ),
  );

  $form_state = array(
    '#node' => $node,
    '#record' => _feedapi_eparser_get_settings($node->nid),
  );

  return ctools_wizard_multistep_form($form_info, $step, $form_state);
}

/**
 * Ctools wizard form callback for setup settings form.
 */
function feedapi_eparser_settings_setup(&$form, &$form_state) {
  // Get feed types. Populate type options.
  $types = feedapi_eparser_get_type_plugins();
  foreach ($types as $type => $meta) {
    $feed_type_options[$type] = $meta['name'];
  }

  // Get download types. Populate download options.
  $types = feedapi_eparser_get_download_plugins();
  foreach ($types as $type => $meta) {
    $download_options[$type] = $meta['name'];
  }

  // If we've already set something for this form, use that first.
  // Useful when hitting the back button.
  if (isset($form_state['#record']->type)) {
    $default_type = $form_state['#record']->type;
    $default_download = $form_state['#record']->download;
  }
  // If they've set up this node, provide those options as a default.
  elseif (isset($form_state['#node']->eparse->type)) {
    $default_type = $form_state['#node']->eparse->type;
    $default_download = $form_state['#node']->eparse->download;
  }
  // Default options.
  else {
    $default_type = 'rss20';
    $default_download = 'drupal_http_request';
  }

  $form['download'] = array(
    '#type' => 'radios',
    '#title' => 'Download Type',
    '#options' => $download_options,
    '#default_value' => $default_download,
  );
  $form['type'] = array(
    '#type' => 'radios',
    '#title' => 'Feed Type',
    '#options' => $feed_type_options,
    '#default_value' => $default_type,
  );

  return $form;
}

/**
 * Ctools wizard submit callback for setup settings page.
 */
function feedapi_eparser_settings_setup_submit(&$form, &$form_state) {

  $form_state['#record']->nid = $form_state['#node']->nid;
  $form_state['#record']->type = $form_state['values']['type'];
  $form_state['#record']->download = $form_state['values']['download'];
  $form_state['#record']->namespaces = array();

}

/**
 * Ctools wizard form callback for setup settings form.
 */
function feedapi_eparser_settings_setup_settings(&$form, &$form_state) {

  // Setup a psuedo feed object.
  $feed = $form_state['#node']->feed;
  $feed->eparse = $form_state['#record'];

  feedapi_eparser_load_type_plugin($feed)
    ->optionsForm($form, $form_state);

  // @TODO : Download options?

  // Check if there's any options needed at this step.
  if (count($form) <= 4) {
    // @TODO : Skipping this step would be better than this cheesy msg.
    $form['msg'] = array('#value' => t('No setup options found.'));
  }
}

/**
 * Ctools wizard validate callback for setup settings form.
 */
function feedapi_eparser_settings_setup_settings_validate(&$form, &$form_state) {

  // Setup a psuedo feed object.
  $feed = $form_state['#node']->feed;
  $feed->eparse = $form_state['#record'];

  feedapi_eparser_load_type_plugin($feed)
    ->optionsFormValidate($form, $form_state);
}

/**
 * Ctools wizard submit callback for setup settings form.
 */
function feedapi_eparser_settings_setup_settings_submit(&$form, &$form_state) {

  $form_state['#record']->settings = array();

  // Setup a psuedo feed object.
  $feed = $form_state['#node']->feed;
  $feed->eparse = $form_state['#record'];

  $form_state['#record']->settings['type'] = feedapi_eparser_load_type_plugin($feed)
    ->optionsFormSubmit($form, $form_state);
}

/**
 * Ctools wizard form callback for namespace settings form.
 */
function feedapi_eparser_settings_namespace(&$form, &$form_state) {

  $namespace_options = _feedapi_eparser_find_namespaces($form_state['#record']->type);

  if (!empty($namespace_options)) {
    $default_namespaces = array();
    if (isset($form_state['#node']->eparse->namespaces)) {
      $default_namespaces = $form_state['#node']->eparse->namespaces;
    }

    $form['namespaces'] = array(
      '#type' => 'checkboxes',
      '#title' => 'Additional namespaces',
      '#description' => 'The feed type plugin will parse default data out of the feed. Additional namespaces provide some additional locations for informations to be found using the XML namespaces.',
      '#options' => $namespace_options,
      '#default_value' => $default_namespaces,
    );
  }
  else {
    $form['namespaces'] = array(
      '#value' => t('There are no namespace plugins for the selected type plugin.'),
    );
  }

  return $form;
}

/**
 * Ctools wizard submit callback for namespace settings page.
 */
function feedapi_eparser_settings_namespace_submit(&$form, &$form_state) {

  $form_state['#record']->namespaces = !empty($form_state['values']['namespaces']) ?
    array_filter(array_values($form_state['values']['namespaces'])) :
    array();
}

/**
 * Ctools wizard form callback for namespace settings form.
 */
function feedapi_eparser_settings_namespace_settings(&$form, &$form_state) {

  dpm("implement me!");
  return;
  $type = $form_state['#record']->type;
  $type_plugin = feedapi_eparser_load_type_plugin($type);
  $type_plugin->optionsForm($form, $form_state);

  // Check if there's any options needed at this step.
  if (empty($form)) {
    // @TODO : Skipping this step would be better than this cheesy msg.
    $form['msg'] = array('#value' => t('No setup options found.'));
  }
}

/**
 * Ctools wizard validate callback for namespace settings form.
 */
function feedapi_eparser_settings_namespace_settings_validate(&$form, &$form_state) {
  dpm("implement me!");
  return;
  $type = $form_state['#record']->type;
  $type_plugin = feedapi_eparser_load_type_plugin($type);
  $type_plugin->optionsFormValidate($form, $form_state);
}

/**
 * Ctools wizard submit callback for namespace settings form.
 */
function feedapi_eparser_settings_namespace_settings_submit(&$form, &$form_state) {
  dpm("implement me!");
  return;
  $type = $form_state['#record']->type;
  $type_plugin = feedapi_eparser_load_type_plugin($type);
  $type_plugin->optionsFormSubmit($form, $form_state);
}


/**
 * Ctools wizard form next callback for feedapi_eparser_settings.
 */
function feedapi_eparser_settings_next(&$form_state) {

  _feedapi_eparser_set_settings($form_state['#node']->nid, $form_state['#record']);
}

/**
 * Ctools wizard form finish callback for feedapi_eparser_settings.
 */
function feedapi_eparser_settings_finish(&$form_state) {

  // To update or not update. That is the question.
  $update = isset($form_state['#node']->eparse->type) ? array('nid') : array();

  drupal_write_record('feedapi_eparser_node', $form_state['#record'], $update);
  _feedapi_eparser_clear_settings($form_state['#node']->nid);

  // Update the feed type to something useful in the database.
  $def = feedapi_eparser_get_plugin_data($form_state['#record']->type, 'feed_type');
  db_query("UPDATE {feedapi} SET feed_type = '%s' WHERE nid = %d",
    $def['type'], $form_state['#node']->nid);
}

/**
 * Ctools wizard form finish callback for feedapi_eparser_settings.
 */
function feedapi_eparser_settings_cancel(&$form_state) {

  _feedapi_eparser_clear_settings($form_state['#node']->nid);
}

function _feedapi_eparser_find_namespaces($type) {
  // Find namespace plugins get .
  foreach (feedapi_eparser_get_namespace_plugins() as $namespace => $plugin) {
    $namespaces[$namespace] = $plugin['name'];
  }

  // Remove namespaces that are required by the feed type.
  $types = feedapi_eparser_get_type_plugins();
  if (!empty($types[$type]['default namespaces'])) {
    foreach ($types[$type]['default namespaces'] as $namespace) {
      unset($namespaces[$namespace]);
    }
  }

  return $namespaces;
}



function _feedapi_eparser_set_settings($nid, $settings) {
  ctools_include('object-cache');
  ctools_object_cache_set('feedapi_eparser_settings', $nid, $settings);
}

function _feedapi_eparser_get_settings($nid) {
  ctools_include('object-cache');
  $cache = ctools_object_cache_get('feedapi_eparser_settings', $nid);

  if (!$cache) {
    $cache = new stdClass();
    $cache->locked = ctools_object_cache_test('feedapi_eparser_settings', $nid);
  }

  return $cache;
}

function _feedapi_eparser_clear_settings($nid) {
  ctools_include('object-cache');
  ctools_object_cache_clear('feedapi_eparser_settings', $nid);
}
