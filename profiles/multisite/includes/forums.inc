<?php

function forums_info() {
  return array(
    'name' => st('Forums'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 0,
  );
}

function forums_modules() {
  return array('menu', 'taxonomy', 'views', 'nodecomment', 'nodeforum', 'sonybmg_forum');
}
