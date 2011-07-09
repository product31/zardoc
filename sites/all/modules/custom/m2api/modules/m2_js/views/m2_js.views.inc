<?php

/**
 * Implementation of hook_views_data_alter().
 */
function m2_js_views_data_alter(&$views) {
  $views['m2api_nodes']['product_button'] = array(
    'title' => t('JS Track Product Button'),
    'help' => t('Add/Remove button for M2 products.'),
    'field' => array(
      'real field' => 'm2id',
      'handler' => 'm2_js_handler_field_product_button',
    ),
  );
  $views['m2api_nodes']['product_price'] = array(
    'title' => t('JS Track Product Price'),
    'help' => t('Price for M2 products.'),
    'field' => array(
      'real field' => 'm2id',
      'handler' => 'm2_js_handler_field_product_price',
    ),
  );

  $views['node']['m2_buy_album'] = array(
    'title' => t('JS Album Buy Dropdown Links'),
    'help' => t('Drop down links for M2 buy alubm links.'),
    'field' => array(
      'real field' => 'nid',
      'group' => t('M2'),
      'handler' => 'm2_js_handler_field_album_buy_links',
    ),
  );
}

function m2_js_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'm2_js') . '/views',
    ),
    'handlers' => array(
      'm2_js_handler_field_product_button' => array('parent' => 'views_handler_field'),
      'm2_js_handler_field_product_price' => array('parent' => 'views_handler_field'),
      'm2_js_handler_field_album_buy_links' => array('parent' => 'views_handler_field'),
    ),
  );
}
