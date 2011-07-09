<?php

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _sonybmg_events_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _sonybmg_events_user_default_permissions() {
  $permissions = array();

  // Exported permission: create date content
  $permissions[] = array(
    'name' => 'create date content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'artist',
      '2' => 'moderator',
    ),
  );

  // Exported permission: edit any date content
  $permissions[] = array(
    'name' => 'edit any date content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'artist',
      '2' => 'moderator',
    ),
  );

  // Exported permission: edit own date content
  $permissions[] = array(
    'name' => 'edit own date content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'artist',
      '2' => 'moderator',
    ),
  );

  return $permissions;
}

/**
 * Helper to implementation of hook_strongarm().
 */
function _sonybmg_events_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'events_date_pager';
  $strongarm->value = '774';

  $export['events_date_pager'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'flag_content_node_type_photo';
  $strongarm->value = 1;

  $export['flag_content_node_type_photo'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_date_pattern';
  $strongarm->value = 'event/[field_date-yyyy]/[field_date-mm]/[field_date-dd]/[title-raw]';

  $export['pathauto_node_date_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'views_defaults';
  $strongarm->value = array(
    'flag_offensive' => TRUE,
    'flag_favorites' => TRUE,
    'friendlist_manage_oneway' => TRUE,
    'friendlist_manage_twoway' => TRUE,
    'friendlist_public_oneway' => TRUE,
    'friendlist_public_twoway' => TRUE,
  );

  $export['views_defaults'] = $strongarm;
  return $export;
}
