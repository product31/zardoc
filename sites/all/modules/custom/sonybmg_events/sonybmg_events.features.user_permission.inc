<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function sonybmg_events_user_default_permissions() {
  $permissions = array();

  // Exported permission: create date content
  $permissions['create date content'] = array(
    'name' => 'create date content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'artist',
      '2' => 'moderator',
    ),
  );

  // Exported permission: edit any date content
  $permissions['edit any date content'] = array(
    'name' => 'edit any date content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'artist',
      '2' => 'moderator',
    ),
  );

  // Exported permission: edit own date content
  $permissions['edit own date content'] = array(
    'name' => 'edit own date content',
    'roles' => array(
      '0' => 'administrator',
      '1' => 'artist',
      '2' => 'moderator',
    ),
  );

  return $permissions;
}
