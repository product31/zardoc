<?php

class m2_js_handler_field_product_price extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['m2id'] = 'm2id';
  }
  function render($values) {
    if (!m2_js_cart_enabled() || empty($values->{$this->aliases['m2id']})) {
      return;
    }
    m2_js_add_cart_js();
    return theme('m2_js_track_price', $values->{$this->aliases['m2id']});
  }
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }
}
