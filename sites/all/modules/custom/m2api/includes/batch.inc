<?php

function m2api_batch_content_import_form(&$form_state) {
  m2api_include('api');

  if (m2api_can_connect()) {
    $types = m2api_node_types();

    // Figure out all the m2 ids that we know about.
    $existing = array();
    $args = array_keys($types);
    $result = db_query("SELECT m.nid, m.m2id FROM {m2api_nodes} m INNER JOIN {node} n WHERE n.type IN (". db_placeholders($args, 'varchar') .") AND (n.nid = n.tnid OR n.tnid = 0)", $args);
    while ($row = db_fetch_object($result)) {
      $existing[$row->m2id] = $row->nid;
    }

    // Load the lists of content from M2 and compute how many new nodes would
    // be created.
    $documents = array();
    $totals = array();
    foreach ($types as $node_type => $document_types) {
      $d = array();
      foreach ($document_types as $document_type) {
        if ($result = m2api_document_fetch_all($document_type)) {
          $d += $result;
        }
      }
     $totals[$node_type] = format_plural(count($d), "@count $node_type", "@count {$node_type}s (@new new)", array('@new' => count(array_diff_key($d, $existing))));
      $documents += $d;
    }

    $form['help'] = array(
      '#value' => theme('item_list', $totals, t('Update the following items from the %store store?', array('%store' => m2api_get_store()))),
    );
    $form['documents'] = array(
      '#type' => 'value',
      '#value' => array_values($documents),
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update'),
    );
  }

  return $form;
}

function m2api_batch_content_import_form_submit($form, &$form_state) {
  $values =& $form_state['values'];

  $batch = array(
    'operations' => array(
      array('m2api_batch_content_import_operation', array($values['documents'])),
    ),
    'finished' => 'm2api_batch_content_import_finished',
    'title' => t('Updating from M2'),
    'file' => drupal_get_path('module', 'm2api') .'/includes/batch.inc',
  );

  batch_set($batch);

  // Redirection takes place as usual.
  $form_state['redirect'] = 'admin/content/m2api/sync';
}

function m2api_batch_content_import_operation($documents, &$context) {
  m2api_include('api');

  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = count($documents);
  }

  $limit = 10;
  while($context['sandbox']['progress'] < $context['sandbox']['max'] && $limit > 0) {
    $document = $documents[$context['sandbox']['progress']];
    // Reload the document so we get the _status property set.
    $document = m2api_document_load($document->id, $document->type);
    if ($document !== FALSE) {
      m2api_process_updates($document);
    }
    $context['sandbox']['progress']++;
    $limit--;
  }

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

function m2api_batch_content_import_finished($success, $results, $operations) {
  if ($success) {
    // TODO should note how many albums and tracks were created. Need to get
    // those into the $results.
    drupal_set_message(t('Sync finished successfully.'));
  }
  else {
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
    drupal_set_message($message, 'error');
  }

}
