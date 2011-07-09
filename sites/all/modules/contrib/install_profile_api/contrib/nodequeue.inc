<?php
// $Id$

/*
 * @file
 * Support for creating nodequeues programatically in an install profile.
 */

/**
 * Creates a new nodequeue programmatically.
 *
 * @param string $title The title of the nodequeue.
 * @param string $subqueue_title The title of this queue's subqueue.
 * @param int $size How many nodes may be in this nodequeue at one time?
 * @param bool $reverse Should this queue show its content in reverse to admins?
 * @param string $link The text to show admins to add a node to this queue.
 * @param string $link_remove The text to show admins to remove a node from this queue.
 * @param array $roles An array where values describe what roles may edit this nodequeue. The role must first have the 'manipulate queues' permission.
 * @param array $types An array where values describe what node types this nodequeue should allow.
 * @param string $owner The module which owns this nodequeue. Defaults to 'nodequeue'.
 * @param bool $show_in_links Show this nodequeue in links? Defaults to TRUE. 
 * @param bool $show_in_tab Show this nodequeue in tabs? Defaults to TRUE.
 * @param bool $show_in_ui Show this nodequeue in the UI? Defaults to TRUE.
 * @param bool $reference Defaults to FALSE.
 * @param array $subqueues Any subqueues that reference this queue. Defaults to array().
 * 
 * @return int $qid The qid of the new nodequeue, or FALSE if an error occured.
 */
function install_nodequeue_add_nodequeue($title, $subqueue_title, $size, $reverse, $link, $link_remove, $roles, $types, $owner = 'nodequeue', $show_in_links = TRUE, $show_in_tab = TRUE, $show_in_ui = TRUE, $reference = FALSE, $subqueues = array()) {
  // Check error conditions.
  if (empty($title)) {
    return FALSE;
  }
  if (!is_array($types)) {
    return FALSE;  
  }
  
  // Put in reasonable defaults elsewhere.
  if (intval($size) < 0) {
    $size = 0;
  }
  if (empty($link)) {
    $link = 'Feature this';
  }
  if (empty($link_remove)) {
    $link_remove = 'Unfeature this';
  }
  if (!is_array($roles)) {
    $roles = array();
  }
  
  // Convert our two arrays to match what would be in a real $form_state passed to nodequeue_edit_queue_form_submit().
  foreach ($roles as $value) {
    $converted_roles[$value] = $value;
  }
  foreach ($types as $value) {
    $converted_types[$value] = $value;
  }
  
  // Let's programatically rebuild $form_state, from which $form_state['values'] is used to make a new nodequeue.
  $form_state = array();
  $form_state['values'] = array();
  $form_state['values']['title'] = $title;
  $form_state['values']['subqueue_title'] = $subqueue_title;
  $form_state['values']['size'] = $size;
  $form_state['values']['reverse'] = $reverse;
  $form_state['values']['link'] = $link;
  $form_state['values']['link_remove'] = $link_remove;
  $form_state['values']['roles'] = $converted_roles;
  $form_state['values']['types'] = $converted_types;
  $form_state['values']['owner'] = $owner;
  $form_state['values']['show_in_links'] = $show_in_links;
  $form_state['values']['show_in_tab'] = $show_in_tab;
  $form_state['values']['show_in_ui'] = $show_in_ui;
  $form_state['values']['reference'] = $reference;
  $form_state['values']['subqueues'] = $subqueues;

  // This next part modified from nodequeue.module, nodequeue_edit_queue_form_submit() function.
  $queue = (object) $form_state['values'];
  // fix checkboxes
  $queue->roles = array_keys(array_filter($queue->roles));
  $queue->types = array_keys(array_filter($queue->types));

  // Modified from the module - this will always be a new queue.
  $queue->new = TRUE;

  // Modify show_in_links based on whether or not links are available.
  $queue->show_in_links = !empty($queue->link) && !empty($queue->link_remove);

  nodequeue_api_queue_form_submit($queue, $form_state);

  $qid = nodequeue_save($queue); // sets $queue->qid if needed.

  nodequeue_api_queue_form_submit_finish($queue, $form_state);

  nodequeue_check_subqueue_sizes($queue);  
  // And thus ends the code cribbed from nodequeue.module.
    
  return $qid;
}
