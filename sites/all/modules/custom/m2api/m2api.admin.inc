<?php

function m2api_admin_settings() {
  m2api_include('api');

  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('API'),
    '#weight' => -1,
  );
  $form['api']['m2api_api_url'] = array(
    '#type' => 'radios',
    '#title' => t('Endpoint URL'),
    '#options' => array(
      'http://api.stage.sonymusicdigital.com/' => t('Stage - api.stage.sonymusicdigital.com'),
      'http://api.sonymusicdigital.com/' => t('Live - api.sonymusicdigital.com'),
    ),
    '#default_value' => variable_get('m2api_api_url', 'http://api.stage.sonymusicdigital.com/'),
  );
  $form['api']['m2api_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Key'),
    '#default_value' => variable_get('m2api_api_key', '109177db7055de2e42958238572b4454'),
  );
  $stores = array('' => t('- Select one -'));
  foreach (m2api_get_stores() as $store) {
    $stores[$store->permalink] = check_plain("$store->name ($store->permalink)");
  }
  $form['api']['m2api_default_store'] = array(
    '#type' => 'select',
    '#title' => t('Store Id'),
    '#options' => $stores,
    '#default_value' => variable_get('m2api_default_store', ''),
    '#description' => t("You'll need to ask the M2 guys what this is."),
  );
  $form['api']['status'] = array(
    '#type' => 'item',
    '#title' => t('Manifest summary'),
    '#value' => t('Unable to connect to M2'),
    '#after_build' => array('_m2api_admin_settings_test_manifest'),
    '#weight' => 99,
  );

  $form['m2api_product_settings'] = array(
    '#tree' => TRUE,
  );

  foreach (ctools_get_plugins('m2api', 'product') as $name => $plugin) {
    if ($function = ctools_plugin_get_function($plugin, 'settings_form')) {
      $form['m2api_product_settings'][$name] = array(
        '#type' => 'fieldset',
        '#title' => t('%type settings', array('%type' => drupal_ucfirst(strtr($name, '_', ' ')))),
      );
      $settings = m2api_get_product_settings($name);
      $form['m2api_product_settings'][$name] += (array) $function($settings);
    }
  }

  $form['m2api_debug_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Debugging'),
    '#default_value' => variable_get('m2api_debug_mode', TRUE),
  );

  return system_settings_form($form);
}

function _m2api_admin_settings_test_manifest($form_element, $form_state) {
  m2api_include('api');
  $response = _m2api_request('object_counts');
  if ($response === FALSE){
    drupal_set_message(t('Could not connect to an M2 server using these settings.'), 'error');
  }
  elseif (isset($response->error)) {
    drupal_set_message(t('Could not load a manifest for this store. M2 says error: @error', array('@error' => $response->error)), 'error');
  }
  elseif (isset($response->meta->totals)) {
    $types = m2api_node_types();
    $totals = array();
    foreach ($types as $doc_types) {
      foreach ($doc_types as $doc_type) {
        $count = empty($response->meta->totals->{$doc_type}) ? 0 : (int) $response->meta->totals->{$doc_type};
        $totals[$doc_type] = format_plural($count, '@count @doc_type', '@count @doc_types', array('@doc_type' => strtr($doc_type, '_', ' ')));
      }
    }
    $form_element['#value'] = theme('item_list', $totals);
  }

  return $form_element;
}