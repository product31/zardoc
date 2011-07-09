<?php
/**
* Default labeling and weight for this profile include
*/
function swfobject_info() {
  return array(
    'name' => st('Flash Blocks(Swf Object)'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 0,
  );
}

/**
 * Required modules in order for these options to be created successfully
 */
function swfobject_modules() {
  return array('swfobject');
}

/**
 * Task to complete in order to activate this segment of code
 */
function swfobject_task_list() {
  return array(
    'swfobject_settings' => array(
      'message' => st('Set default settings for SWF Object.'),
      'weight' => 0,
    ),
    'swfobject_create_blocks' => array(
      'message' => st('Created default SWFObject block.'),
      'weight' => 0,
    ),
  );
}

/**
 * Default settings for SwfObject.
 */
function swfobject_settings() {
  // Number of Flash Gallery Blocks.
  variable_set('swfobject_number', '1');
  // Debug mode.
  variable_set('swfobject_debug', 'normal');
  // On upload.
  variable_set('swfobject_replace', 'Create unique file name'); 
}

/**
 * Create default blocks
 */
function swfobject_create_blocks() {
  /*
  Do not need to create the block it is created by the panel.

  $theme = variable_get('artist_key', '_starter');
  $visibility = 1; //0 = show on every page except ; 1 = show only on these pages, 2 = php

  // will be placed in a panel so don't enable.
  install_add_block('swfobject', 1, $theme, FALSE, 0, 'content_header',
      $visibility, '<front>');
  */

  // Still need to manually set the settings though weird?
  variable_set('swfobject_name_1', 'Front Page Flash');
  variable_set('swfobject_id_1', 'homeflash');
  variable_set('swfobject_width_1', '600');
  variable_set('swfobject_height_1', '250');
  variable_set('swfobject_version_1', '8');
  variable_set('swfobject_bgcolor_1', '#000000');
  variable_set('swfobject_provide_container_1', '1');
  variable_set('swfobject_container_id_1', 'homeflash-container');
  variable_set('swfobject_container_text_1', '<a href="http://www.macromedia.com/go/getflashplayer">Get Flash Player</a>');
  variable_set('swfobject_swf_1', ''); // Provide a default flash?
}