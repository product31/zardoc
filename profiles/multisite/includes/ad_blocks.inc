<?php
// $Id$

/**
 * @file
 * file_description
 */
 
function ad_blocks_info() {
  return array(
    'name' => st('Advertisement Blocks'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 0,
  );
}

function ad_blocks_modules() {
  return array('block');
}

function ad_blocks_task_list() {
  return array(
    'ad_blocks_create' => array(
      'message' => st('Created advertisement blocks.'),
      'weight' => 0,
    ),
  );
}

function ad_blocks_create() {
  $theme = variable_get('artist_key', '_starter');

  // Create advertisement blocks
  $ad_top_delta = install_create_custom_block('<div style="width: 728px; height: 90px; line-height: 90px; border: #999 solid 1px;">Top Advertisement</div>', 'Ad top', 4);
  install_add_block('block', $ad_top_delta, $theme, 1, 0, 'ad_top');
  variable_set('sonybmg_ad_top_block', $ad_top_delta);
  
  $ad_bottom_delta = install_create_custom_block('<div style="width: 728px; height: 90px; line-height: 90px; border: #999 solid 1px;">Bottom Advertisement</div>', 'Ad bottom', 4);
  install_add_block('block', $ad_bottom_delta, $theme, 1, 0, 'ad_bottom');
  variable_set('sonybmg_ad_bottom_block', $ad_bottom_delta);
  
  $ad_sidebar_delta = install_create_custom_block('<div style="width: 300px; height: 280px; line-height: 280px; border: #999 solid 1px;">Sidebar Advertisement</div>', 'Ad sidebar', 4);
  install_add_block('block', $ad_sidebar_delta, $theme, 1, -8, 'right', 0, "admin*\ncalendar\n<front>");
  variable_set('sonybmg_ad_sidebar_block', $ad_sidebar_delta);
}

