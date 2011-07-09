<?php

function standard_users_info() {
  return array(
    'name' => st('Standard Users'),
    'default_value' => TRUE,
    'disabled' => TRUE,
    'weight' => -15,
  );
}

function standard_users_modules() {
  return array();
}

function standard_users_task_list() {
  return array(
    'standard_users_create' => array(
      'message' => st('Created standard users'),
      'weight' => 0,
    ),
  );
}

function standard_users_create() {
  // Ripped from D5 sonybmg.module.
  global $base_url;

  // Grab hostname for e-mail addresses.
  $parts = parse_url($base_url);
  $site_domain = $parts['host'];

  // Generate random password for all users.
  $pass = user_password();

// Create initial users.
  install_add_user('moderator', $pass, "moderator@$site_domain", array(variable_get('multisite_moderator_rid', '') => 'moderator'));
  install_add_user('artist', $pass, "artist@$site_domain", array(variable_get('multisite_artist_rid', '') => 'artist'));
  install_add_user('member', $pass, "member@$site_domain");

  // Set real password of user 1
  //db_query("UPDATE {users} SET pass='%s' WHERE uid=%d", '08c0d121f9f390761c38352c75106b54', 1);
  //db_query("UPDATE {users} SET pass='%s' WHERE uid=%d", 'fbe40f4c6c3be9cca88473e07ecf7e08', 1);
  //new password set on aug 25,2010
  db_query("UPDATE {users} SET pass='%s' WHERE uid=%d", '16ff4252748b4209169329913dab4ac0', 1);
}
