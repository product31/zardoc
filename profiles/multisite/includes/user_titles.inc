<?php
// $Id$

/**
 * @file
 * file_description
 */

function user_titles_info() {
  return array(
    'name' => st('User Titles'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 0,
  );
}

function user_titles_modules() {
  return array('user_titles');
}

function user_titles_task_list() {
  return array(
    'user_titles_create' => array(
      'message' => st('Created default titles and settings.'),
      'weight' => 0,
    ),
  );
}

function user_titles_create() {
  $tid = 1;

  $titles = array(
    array(
      'title' => 'Newbie',
      'value' => 0,
    ),
    array(
      'title' => 'Fan',
      'value' => 5,
    ),
    array(
      'title' => 'Big Fan',
      'value' => 15,
    ),
    array(
      'title' => 'Super Fan',
      'value' => 50,
    ),
    array(
      'title' => 'Mega Fan',
      'value' => 100,
    ),
  );
  
  db_query("TRUNCATE {user_titles}");
  foreach ($titles as $title) {
    db_query("INSERT INTO {user_titles} (title, value) VALUES ('%s', %d)", $title['title'], $title['value']);
  }

  $types = array(
    'forum',
    'forum_reply',
  );

  variable_set('user_titles_types', $types);
}
