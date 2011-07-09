<?php

function scratch_info() {
  if($_SERVER['HTTP_HOST'] != 'scratch.rs.gdb-dev.com' && $_SERVER['HTTP_HOST'] != 'scratch') {
    return array();
  }
  return array(
    'name' => st('Scratch setup'),
    'default_value' => TRUE,
    'disabled' => TRUE,
    'weight' => -9999,
  );
}

function scratch_modules() {
  return array('update', 'cvs_deploy', 'coder', 'simpletest', 'scratch');
}

function scratch_task_list() {
  return array(
    '_scratch_init_settings' => array(
      'message' => st('Scratch configuration settings'),
      'weight' => 0,
    ),
  );
}

