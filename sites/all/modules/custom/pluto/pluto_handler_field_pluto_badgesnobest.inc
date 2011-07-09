<?php

/**
 * Field handler to provide simple renderer of themed badges
 */
class pluto_handler_field_pluto_badgesnobest extends views_handler_field {

  function render($values) {

    $uid = $values->{$this->field_alias};

    return theme('pluto_badges', $uid, TRUE);
  }
}
