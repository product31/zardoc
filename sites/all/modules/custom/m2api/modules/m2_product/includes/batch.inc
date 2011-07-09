<?php

function m2_product_batch_content_import_form() {
  m2api_include('api');
  ctools_include('plugins');

  if (m2api_can_connect()) {
    // Load the lists of content(products) from M2.
		$products = m2api_get_products();
		// Figure out all the m2 ids that we know about.
    $existing = array();
    $result = db_query("SELECT m2id FROM {m2api_nodes} m INNER JOIN {node} n WHERE n.language IN ('', '%s')", language_default('language'));
    while ($row = db_fetch_object($result)) {
      $existing[$row->m2id] = $row->m2id;
    }

    // Let them know how many items will be created.
    $new_products = count(array_diff_key($products, $existing));
    $totals = array(
    	format_plural(count($products), '@count products','@count products (@new new)', array('@new' => $new_products)),
    );
		//dsm($products);
    $form['help'] = array(
      '#value' => theme('item_list', $totals, t('Update the following items from the %store store?', array('%store' => m2api_get_store()))),
    );
    $form['documents'] = array(
      '#type' => 'value',
      '#value' => $products,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Import'),
    );
  }

  return $form;
}

function m2_product_batch_content_import_form_submit($form, &$form_state) {
  $values = &$form_state['values'];
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
  $form_state['redirect'] = 'admin/content/m2api/sync/products';
}


