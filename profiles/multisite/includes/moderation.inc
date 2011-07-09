<?php
/**
 * Default labeling and weight for this profile include
 **/
function moderation_info() {
  return array(
    'name' => st('Moderation'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 50,
  );
}

/**
 * Required modules in order for these options to be created successfully
 **/
function moderation_modules() {
  return array('modr8', 'taxonomy', 'modr8_taxonomy');
}

/**
 * Task to complete in order to activate this segment of code
 **/
function moderation_task_list() {
  return array(
    'moderation_init_modr8_variables' => array(
      'message' => st('Initialized modr8 variables.'),
      'weight' => 0,
    ),
    'moderation_init_modr8_perms' => array(
      'message' => st('Initialized modr8 permissions.'),
      'weight' => 0,
    ),
  );
}

/**
 * Initialize modr8 variables
 **/
function moderation_init_modr8_variables() {
  variable_set('modr8_nodes_per_page', '50');
  variable_set('modr8_default_option', 'approve');
  variable_set('modr8_send_approve', 1);
  variable_set('modr8_send_deny', 1);
  variable_set('modr8_send_noact', 1);
  variable_set('node_options_photo', array('status', 'moderate'));
}

/**
  * Initialize modr8 variables
  **/
function moderation_init_modr8_perms() {
  $perms = array('moderate content');
  install_add_permissions(install_add_role('artist'), $perms);
  install_add_permissions(install_add_role('moderator'), $perms);
}