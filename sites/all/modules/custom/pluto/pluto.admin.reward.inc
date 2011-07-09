<?php
// $Id$

/**
 * @file
 */

/**
 * admin/pluto/reward
 */
function pluto_admin_reward() {
  $result = db_query('SELECT * FROM {pluto_reward}');
  while ($reward = db_fetch_object($result)) {
    $rows[] = array(
      $reward->name,
      $reward->type,
      l('Edit', 'admin/pluto/reward/'. $reward->rid .'/edit', array(), drupal_get_destination()),
      l('Delete', 'admin/pluto/reward/'. $reward->rid .'/delete', array(), drupal_get_destination()),
    );
  }

  if ($rows) {
    $output = theme('table', array(), $rows);
  }
  else {
    $output = t('No rewards defined.  !create one now.', array('!create' => l('Create', 'admin/pluto/reward/add')));
  }
  return $output;
}

/**
 * Callback function for reward/add
 */
function pluto_admin_reward_add() {
  $types = pluto_reward_get_types();

  foreach ($types as $type_name => $type_info) {
    $output .= '<dt>'. l($type_info['name'], 'admin/pluto/reward/add/'. $type_name) .'</dt>';
    $output .= '<dd>'. filter_xss_admin($type_info['description']) .'</dd>';
  }

  return '<dl>'. $output .'</dl>';
}

/**
 * Reward add/edit form
 */
function pluto_admin_reward_edit($form_state, $reward = NULL) {
  $reward = (object)$reward;
  $type = pluto_reward_get_types($reward->type);
  if (!$type) {
    drupal_set_message('Pluto error: invalid reward type.', 'error');
    return array();
  }

  $form['rid'] = array(
    '#type' => 'hidden',
    '#value' => $reward->rid,
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $reward->name,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#rows' => 5,
    '#default_value' => $reward->description,
  );

  $form['type'] = array(
    '#type' => 'hidden',
    '#value' => $reward->type,
  );

  $type_form = module_invoke_all('pluto_reward', 'form', $reward);
  if ($type_form) {
    $form['data'] = $type_form;
    $form['data']['#tree'] = 1;
  }
  else {
    $form['data'] = array('#type' => 'hidden', '#value' => array());
  }

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));

  return $form;
}

/**
 * Reward add/edit form submit
 */
function pluto_admin_reward_edit_submit($form, &$form_state) {
  $reward = pluto_reward_save($form_state['values']);
  $form_state['redirect'] = 'admin/pluto/reward';
}

/**
 * Reward delete form
 */
function pluto_admin_reward_delete($form_state, $reward) {
  $form['rid'] = array('#type' => 'value', '#value' => $reward->rid);

  return confirm_form($form,
    t('Are you sure you want to delete %name', array('%name' => $reward->name)),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/pluto/reward',
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel'));
}

/**
 * Reward delete form submit
 */
function pluto_admin_reward_delete_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    pluto_reward_delete($form_state['values']['rid']);
  }

  $form_state['redirect'] =  'admin/pluto/reward';
}
