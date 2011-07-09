<?php

class m2_js_handler_field_album_buy_links extends views_handler_field {
  function render($values) {
    if (!m2_js_cart_enabled()) {
      return;
    }

    m2api_include('api');
    $products = m2api_product_load_references($values->nid);
    if (empty($products)) {
      return;
    }

    m2_js_add_cart_js();

    $links = array();
    foreach ($products as $product) {
      $links[] = theme('m2_js_album_link', $product->id, $product->type, t('Add'), t('In cart'));
    }

    return theme('m2_js_album_links', $links, t('Buy Now'). ' <span class="expand"> &darr;</span>');
  }
}
