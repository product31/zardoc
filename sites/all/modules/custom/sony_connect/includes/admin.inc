<?php
// $Id$

/**
 * @file
 * Admin page callbacks.
 */

/**
 * Menu callback and form builder for /admin/sony/connect.
 */
function sony_connect_admin_settings() {
  $form = array();
  $form['sony_connect_publishing'] = array(
    '#tree' => 1,
  );

  $types = sony_connect_publish_info();
  foreach ($types as $type_name => $type) {
    $form['sony_connect_publishing'][$type_name] = array(
      '#type' => 'fieldset',
      '#title' => $type['title'],
      '#theme' => 'sony_connect_admin_publishing_settings',
    );

    foreach ($type['subtypes'] as $subtype_name => $subtype) {
      $form['sony_connect_publishing'][$type_name][$subtype_name]['#title'] = $subtype['title'];
      $form['sony_connect_publishing'][$type_name][$subtype_name]['enabled'] = array(
        '#type' => 'checkbox',
        '#default_value' => $subtype['enabled'],
      );
      $form['sony_connect_publishing'][$type_name][$subtype_name]['message'] = array(
        '#type' => 'textarea',
        '#rows' => 2,
        '#default_value' => $subtype['message'],
        '#disabled' => !$subtype['enabled'],
      );
    }
  }

  $form['token_help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Replacement tokens'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#value' => theme('token_help'),
  );

  return system_settings_form($form);
}

/**
 * Theme the table of node/comment settings for sony_connect_admin_settings().
 */
function theme_sony_connect_admin_publishing_settings($form) {
  drupal_add_js(drupal_get_path('module', 'sony_connect') .'/js/admin.js');

  $rows = array();
  foreach (element_children($form) as $name) {
    $rows[] = array(
      $form[$name]['#title'],
      array(
        'data' => drupal_render($form[$name]['enabled']),
        'class' => 'checkbox',
      ),
      drupal_render($form[$name]['message']),
    );
  }
  $form['#value'] = theme('table', array('Type', 'Enabled', 'Message'), $rows);
  $output = drupal_render($form);
  return $output;
}

/**
 * Menu callback and form builder for /admin/sony/connect/%plugin.
 */
function sony_connect_admin_plugin_settings($form_state, $plugin) {
  $form = array();
  $plugin = sony_connect_get_network($plugin['name']);

  $form['sony_connect_network_'. $plugin['name'] .'_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => $plugin['enabled'],
  );

  $key = 'sony_connect_network_'. $plugin['name'];
  $form[$key] = sony_connect_network_invoke($plugin, 'admin_settings', $form_state);
  $form[$key]['#tree'] = 1;

  return system_settings_form($form);
}

function sony_connect_admin_appearance_settings($form_state) {
  $form = array();

  $networks = sony_connect_get_networks();
  foreach ($networks as $id => $plugin) {
    $key = 'sony_connect_login_link_icon_'. $id;
    $files = file_scan_directory($plugin['path'] .'/icons', '.*\.(gif|png|jpg)');
    $options = array();
    foreach ($files as $file) {
      $options['icons/'. $file->basename] = theme('image', $file->filename);
    }
    $form[$key] = array(
      '#type' => 'radios',
      '#title' => $plugin['title'],
      '#options' => $options,
      '#default_value' => $plugin['icon'],
    );
  }

  return system_settings_form($form);
}