<?php
// $Id$
/**
 * @file
 * Functions needed to manage queues.
 */

/**
 * Queue list page callback.
 */
function sony_queuedcarousel_queue_list_page() {

  $output = '';
  $rows = array();
  $headers = array('Name', 'Operations');

  $result = db_query('SELECT * FROM sony_queuedcarousel'); // @todo Enumerate fields.
  while ($row = db_fetch_array($result)) {
    $operations = array(
      l('Settings', 'admin/build/queuedcarousel/manage/' . $row['queue_id']),
      l('Manage', 'admin/build/queuedcarousel/manage/' . $row['queue_id'] . '/list'),
      l('Add', 'admin/build/queuedcarousel/manage/' . $row['queue_id'] . '/add'),
      l('Delete', 'admin/build/queuedcarousel/manage/' . $row['queue_id'] . '/delete'),
    );

    $rows[] = array(
      $row['name'],
      implode(' | ', $operations),
    );
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => 'No rows found', 'colspan' => 2));
  }

  $output .= theme('table', $headers, $rows);

  return $output;
}

function sony_queuedcarousel_queue_edit($form_state, $queue) {

  if ($queue == 'new') {
    $queue = new stdClass();
  }

  if (!is_object($queue)) {
    $queue = sony_queuedcarousel_queue_load($queue);
  }
  $form['#queue'] = $queue;

  $form['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#description' => t('A system name for the carousel. This will be used when creating the CSS ID and for administration links. May only contain alphanumeric characters or underscores and must be unique.'),
    '#default_value' => isset($queue->name) ? $queue->name : '',
  );
  $form['title'] = array(
    '#title' => t('Title'),
    '#type' => 'textfield',
    '#description' => t('A descriptive title. If provided, this will be used as a title when displaying the carousel.'),
    '#default_value' => isset($queue->title) ? $queue->title : '',
  );

  $form['conf']['#tree'] = TRUE;
  $form['conf']['auto'] = array(
    '#title' => t('Delay'),
    '#type' => 'textfield',
    '#size' => 3,
    '#description' => t('Number of seconds between automated rotation. If set to 0, the carousel will have no automated rotation, only manual navigation.'),
    '#default_value' => isset($queue->conf['auto']) ? $queue->conf['auto'] : 3,
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['#redirect'] = 'admin/build/queuedcarousel';

  return $form;
}

function sony_queuedcarousel_queue_edit_validate($form, &$form_state) {
  // Test uniqueness of name:
  if (preg_match("/[^A-Za-z0-9_]/", $form_state['values']['name'])) {
    form_error($form['name'], t('Name must be alphanumeric or underscores only.'));
  }
  else {
    $query = "SELECT pid FROM {panels_queuedcarousel} WHERE name = '%s'";
    if (!empty($form['#queue']->pid) && is_numeric($form['#queue']->pid)) {
      $query .= ' AND pid != ' . $form['#queue']->pid;
    }
    if (db_result(db_query($query, $form_state['values']['name']))) {
      form_error($form['name'], t('Panel name must be unique.'));
    }
  }

}

function sony_queuedcarousel_queue_edit_submit(&$form, &$form_state) {

  $queue = $form['#queue'];
  $queue->title = $form_state['values']['title'];
  $queue->name = $form_state['values']['name'];
  $queue->conf = $form_state['values']['conf'];
  sony_queuedcarousel_queue_save($queue);
}

function sony_queuedcarousel_queue_delete_confirm(&$form_state, $queue) {
  if (!is_object($queue)) {
    $queue = sony_queuedcarousel_queue_load($queue);
  }
  $form['#queue'] = $queue;
  $form['#redirect'] = 'admin/build/queuedcarousel';
  return confirm_form($form,
    t('Are you sure you want to delete the queue "@name"?', array('@name' => $queue->name)),
    !empty($_GET['destination']) ? $_GET['destination'] : 'admin/build/queuedcarousel',
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel')
  );
}

function sony_queuedcarousel_queue_delete_confirm_submit(&$form, &$form_state) {
  sony_queuedcarousel_queue_delete($form['#queue']);
}


/**
 * Settings for queuedcarousel panels.
 */
function sony_queuedcarousel_settings() {
  panels_load_include('common');
  return drupal_get_form('panels_common_settings', 'sony_queuedcarousel');
}
