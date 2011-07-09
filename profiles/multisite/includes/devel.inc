<?php

/**
 * Default labelling and weight for this profile include
 **/
function devel_info() {
  return array(
    'name' => st('Developer tools'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => -1,
  );
}

/**
 * Required modules in order for these options to be created successfully
 */
function devel_modules() {
  return array('devel');
}
