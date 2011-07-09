<?php

function standard_roles_info() {
  return array(
    'name' => st('Standard Roles'),
    'default_value' => TRUE,
    'disabled' => TRUE,
    'weight' => -20,
  );
}

function standard_roles_modules() {
  return array();
}

function standard_roles_task_list() {
  return array(
    'standard_roles_create' => array(
      'message' => st('Created standard roles.'),
      'weight' => -50,
    ),
    'standard_roles_core_perms' => array(
      'message' => st('Set standard core permissions.'),
      'weight' => 50,
     ),
  );
}

function standard_roles_create() {
  $admin_rid = install_add_role('administrator');
  variable_set('multisite_administrator_rid', $admin_rid);
  $artist_rid = install_add_role('artist');
  variable_set('multisite_artist_rid', $artist_rid);
  $mod_rid = install_add_role('moderator');
  variable_set('multisite_moderator_rid', $mod_rid);
}

function standard_roles_core_perms() {
  // Anonymous user.
  $anon_perms = array('access content', 'access comments', 'vote on polls', 'search content', 'view uploaded files', 'access user profiles', 'access all panel-pages', 'use smiley select box', );
  // Authenticated user.
  $auth_perms = array('access content', 'access comments', 'post comments', 'post comments without approval', 'create forum topics', 'edit own forum topics', 'access all panel-pages', 'create blog content', 'edit own blog content', 'read privatemsg', 'write privatemsg', 'use smiley select box', 'cancel own vote', 'vote on polls', 'search content', 'view uploaded files', 'access user profiles', 'change own username', 'create forum content', 'create forum_reply content', 'edit own forum content', 'edit own forum_reply content');
  // Create permissions array for artists and moderators.
  $admin_perms = array('view revisions', 'access content', 'administer nodes', 'create album content', 'create blog content', 'create buddy_icon content', 'create comment content', 'create date content', 'create fan content', 'create forum content', 'create forum_reply content', 'create news content', 'create official_photo content', 'create page content', 'create photo content', 'create review content', 'create track content', 'create wallpaper content', 'delete any album content', 'delete any blog content', 'delete any buddy_icon content', 'delete any comment content', 'delete any date content', 'delete any fan content', 'delete any forum content', 'delete any forum_reply content', 'delete any news content', 'delete any official_photo content', 'delete any page content', 'delete any photo content', 'delete any review content', 'delete any track content', 'delete any wallpaper content', 'delete own album content', 'delete own blog content', 'delete own buddy_icon content', 'delete own comment content', 'delete own date content', 'delete own fan content', 'delete own forum content', 'delete own forum_reply content', 'delete own news content', 'delete own official_photo content', 'delete own page content', 'delete own photo content', 'delete own review content', 'delete own track content', 'delete own wallpaper content', 'edit any album content', 'edit any blog content', 'edit any buddy_icon content', 'edit any comment content', 'edit any date content', 'edit any fan content', 'edit any forum content', 'edit any forum_reply content', 'edit any news content', 'edit any official_photo content', 'edit any page content', 'edit any photo content', 'edit any review content', 'edit any track content', 'edit any wallpaper content', 'edit own album content', 'edit own blog content', 'edit own buddy_icon content', 'edit own comment content', 'edit own date content', 'edit own fan content', 'edit own forum content', 'edit own forum_reply content', 'edit own news content', 'edit own official_photo content', 'edit own page content', 'edit own photo content', 'edit own review content', 'edit own track content', 'edit own wallpaper content', 'revert revisions', 'view revision', 'access comments', 'administer comments', 'post comments', 'post comments without approval', 'administer forums', 'create forum topics', 'edit own forum topics', 'cancel own vote', 'inspect all votes', 'vote on polls', 'search content', 'use advanced search', 'access administration pages', 'administer site configuration', 'upload files', 'view uploaded files', 'access user profiles', 'administer users', 'change own username');

  install_add_permissions(install_get_rid('anonymous user'), $anon_perms);
  install_add_permissions(install_get_rid('authenticated user'), $auth_perms);
  install_add_permissions(variable_get('multisite_artist_rid', ''), $admin_perms);
  install_add_permissions(variable_get('multisite_moderator_rid', ''), $admin_perms);

  // Bunch of (could be non-core) permissions we want to disallow.
  $disabled_permissions = array('select different theme', 'access devel information', 'execute php code', 'switch users', 'use PHP for block visibility', 'use PHP for fivestar target');
  $super_permissions = module_invoke_all('perm');
  // Just give all permissions to admins
  $super_perms = array_diff($super_permissions, $disabled_permissions);
  install_add_permissions(variable_get('multisite_administrator_rid', ''), $super_perms);
  // Give uid 1 the administrator role.
  install_add_user_to_role(1, variable_get('multisite_administrator_rid', ''));
  // Re-enable alert notifications
}
