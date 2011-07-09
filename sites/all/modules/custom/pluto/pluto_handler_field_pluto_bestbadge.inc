<?php
/**
 * Field handler to provide simple renderer of themed badges
 */
class pluto_handler_field_pluto_bestbadge extends views_handler_field {

  function render($values) {

    $uid = $values->{$this->field_alias};

    return theme('pluto_best_badge', $uid);
  }
}
