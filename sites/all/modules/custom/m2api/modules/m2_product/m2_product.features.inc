<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function m2_product_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function m2_product_node_info() {
  $items = array(
    'm2_product' => array(
      'name' => t('M2 Product'),
      'module' => 'features',
      'description' => t('to store artists generic products and product groups'),
      'has_title' => '1',
      'title_label' => t('Product name'),
      'has_body' => '1',
      'body_label' => t('Description'),
      'min_word_count' => '0',
      'help' => t('TODO: Create some nice text for the product submission form.'),
    ),
  );
  return $items;
}
