<?php
// $Id: views_natural_sort.admin.inc,v 1.2 2009/05/12 18:46:22 neclimdul Exp $
/**
 * @file
 * Callbacks for managing Views Natural Sort.
 */

/**
 * Form callback for Views Natural Sort settings page..
 *
 * Allows rebuilding index but should also allow things like limiting what node
 * types are indexed and cck text field index options.
 */
function views_natural_sort_settings_form() {
  $form = array();

  $form['rebuild'] = array(
    '#type' => 'submit',
    '#value' => t('Rebuild title index'),
    '#submit' => array('views_natural_sort_rebuild_index_submit'),
  );

  return $form;
}

/**
 * Submit handler that triggers the rebuild_index batch.
 */
function views_natural_sort_rebuild_index_submit() {
  $batch = array(
    'operations' => array(
      array('views_natural_sort_rebuild_index', array()),
    ),
    'finished' => 'views_natural_sort_rebuild_index_finished',
    'file' => drupal_get_path('module', 'views_natural_sort') . '/views_natural_sort.admin.inc',
  );

  batch_set($batch);
}

/**
 * Batch API callback for rebuild_index.
 */
function views_natural_sort_rebuild_index(&$context) {
  // Alias sandbox for easier referencing.
  $sandbox = &$context['sandbox'];

  // Initialize our context.
  if (!isset($sandbox['max'])) {
    $sandbox['progress'] = 0;
    $sandbox['max'] = db_result(db_query('SELECT MAX(nid) FROM {node}'));
    $sandbox['total'] = db_result(db_query('SELECT COUNT(nid) FROM {node} WHERE nid <= %d', $sandbox['max']));
    $sandbox['current'] = 0;
    $context['results']['nodes'] = 0;
  }

  $results = db_query_range('SELECT nid, title FROM {node} WHERE nid > %d AND nid <= %d', $sandbox['current'], $sandbox['max'], 0, 10);

  $title = '';
  while($row = db_fetch_object($results)) {
    _views_natural_sort_store_node($row);
    ++$sandbox['progress'];
    $sandbox['current'] = $row->nid;
    $title = $row->title;
    ++$context['results']['nodes'];
  }

  $context['message'] = t('Processing node %title', array('%title' => $title));

  $context['finished'] = $sandbox['progress'] / $sandbox['total'];
}

/**
 * Finished callback for rebuild_index batch.
 */
function views_natural_sort_rebuild_index_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('Index update has completed.'));
    drupal_set_message(t('Indexed %count.', array(
      '%count' => format_plural($results['nodes'], '1 node', '@count nodes'),
    )));
  }
}
