<?php

/**
 * Field handler to provide simple renderer of themed badges
 */
class pluto_handler_field_pluto_badges extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
    $this->additional_fields['name'] = 'name';
  }

  function render($values) {

    $uid = $values->{$this->field_alias};

    return theme('pluto_badges', $uid);
  }
}
