<?php
//TODO views_rss for news_blog feeds
/**
 * Default labelling and weight for this profile include
 **/
function sonybmg_fans_info() {
  return array(
    'name' => st('Why I\'m A Fan'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 10,
  );
}//end - function

/**
 * Required modules in order for these options to be created successfully
 **/
function sonybmg_fans_modules() {
  return array('usernodes', 'sonybmg_fans', 'nodequeue', 'content');
}//end - function

/**
 * Task to complete in order to activate this segment of code
 **/
function sonybmg_fans_task_list() {
  return array(
    'sonybmg_fans_init_content_types' => array(
      'message'   => st('Created fan content type.'),
      'weight' => 0,
    ),
    'sonybmg_fans_init_roles' => array(
      'message'   => st('Initialize fan roles.'),
      'weight' => 0,
    ),
    'sonybmg_fans_init_nodequeue_and_content' => array(
      'message'   => st('Create fans nodequeue.'),
      'weight' => 0,
    ),
    'sonybmg_fans_init_blocks' => array(
      'message'   => st('Initialize fans blocks.'),
      'weight' => 0,
    ),
  );
}//end - function


function sonybmg_fans_init_blocks() {
  global $theme_key;
  if ($theme == NULL) {
    if (!isset($theme_key)) {
      init_theme();
    }
    $theme = $theme_key;
  }

  $theme = variable_get('artist_key', '_starter');
  $status = TRUE;
  $region = 'right';
  $custom = FALSE;
  $visibility = 1; //0 = show on every page except ; 1 = show only on these pages, 2 = php

  // The default "Why I'm A Fan" block.
  install_add_block('sonybmg_fans', 0, $theme, $status, 0, $region,
    $visibility, '<front>'); 
}

/**
 * populate the fields and fivestar for the fan content type.
 */
function sonybmg_fans_init_content_types() {
  $path = drupal_get_path('module', 'sonybmg_fans');
  install_content_copy_import_from_file($path .'/node.fan.inc');
}

/**
 * Set up a nodequeue.
 */
function sonybmg_fans_init_nodequeue_and_content() {
  // Content!
  module_load_include('inc', 'node', 'node.pages');
  
  // sample event
  $node = new stdClass();
  node_object_prepare($node);
  $node->type = 'fan';
  // The default member uid and name
  $node->uid = 5;
  $node->name = 'member';
  $node->language = 'en';
  $node->title = 'I love SONY!';
  $node->body = '<p>I love Sony, and this artist. Also, the Bob Dylan site is pretty cool.</p>';
  
  node_submit($node);
  node_save($node);

  module_load_include('inc', 'sonybmg_fans', 'nodequeue.fans');
  sonybmg_fans_install_nodequeue($node->nid);
}

/**
 * Add role access for specific permissions
 */
function sonybmg_fans_init_roles() {
  // set admin perms
  $rid = install_get_rid('administrator');
  install_add_permissions($rid, array('create fan content', 'edit own fan content', 'edit any fan content',
    'administer nodequeue', 'manipulate all queues', 'manipulate queues'));
  
  $rid = install_get_rid('moderator');
  install_add_permissions($rid, array('create fan content', 'edit own fan content', 'edit any fan content',
    'administer nodequeue', 'manipulate queues'));
  
  // Set prefs for all users.
  $rid = install_get_rid('authenticated user');
  install_add_permissions($rid, array('create fan content', 'edit own fan content'));

}// end - function
