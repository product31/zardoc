<?php
/**
 * @file
 * Create our default content types that don't necessarily fit elsewhere.
 */
function default_content_types_info() {
  return array(
    'name' => st('Default Content Types'),
    'default_value' => TRUE,
    'disabled' => TRUE,
    'weight' => -10,
  );
}

/**
 * Required modules.
 */
function default_content_types_modules() {
  return array('content', 'content_copy', 'text', 'views', 'pathauto', 'poll', 'filefield', 'imagefield', 'emfield', 'emvideo');
}

/**
 * Task list.
 */
function default_content_types_task_list() {
  return array(
    'default_content_types_page' => array(
      'message' => st('Created page content type.'),
      'weight' => 0,
    ),
    'default_content_types_poll' => array(
      'message' => st('Created poll content type.'),
      'weight' => 1,
    ),
    'default_content_types_page_block' => array(
      'message' => st('Set up page sidebar content block.'),
      'weight' => 5,
    ),
  );
}

/**
 * Create our page content type and fields.
 */
function default_content_types_page() {
  $path = drupal_get_path('module', 'sonybmg');
  install_content_copy_import_from_file($path .'/node.page.inc');
  install_content_copy_import_from_file($path .'/node.landingpage.inc');
}

function default_content_types_poll() {
  $path = drupal_get_path('module', 'sonybmg');
  
  install_content_copy_import_from_file($path .'/node.poll.inc', 'poll');
  variable_set('pathauto_node_poll_pattern', 'poll/[title-raw]');  
}

/**
 * Set up our block for the sidebar content field.
 */
function default_content_types_page_block() {
  $module = 'sonybmg';
  $theme = variable_get('artist_key', '_starter');
  $status = TRUE;
  $region = 'right';

  install_add_block($module, 10, $theme, $status, 0, $region, 1, '');
}
