<?php
/**
 * @file
 * Create our "biography" page.
 */
function pages_poll_info() {
  return array(
    'name' => st('Poll Content Type and Sample Poll'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 5,
  );
}

/**
 * Required modules.
 */
function pages_poll_modules() {
  return array('poll', 'content', 'pathauto', 'imagefield');
}

function pages_poll_task_list() {
  return array(
    'pages_poll_default_poll' => array(
      'message' => st('Created default poll.'),
      'weight' => 5,
    ),
  );
}

/**
 * Generate help page.
 */
function pages_poll_default_poll() {
  module_load_include('inc', 'node', 'node.pages');

  $node = new stdClass();
  $node->type = 'poll';
  node_object_prepare($node);
  $node->status = 1;
  $node->title = t('What is your favorite track on the new album?');
  /*
  $node->body = pages_poll_content();
  $node->teaser = node_teaser($node->body);
  */
  $node->promote = 1;
  $node->uid = 1;
  $node->filter = variable_get('filter_default_format', 1);
  $node->format = 3;
  $node->language = '';

  // Custom poll fields
  $node->choice = array(
    array(
      'chtext' => 'Track 1',
      'chvotes' => 0,
      'chorder' => 0,
    ),
    array(
      'chtext' => 'Track 2',
      'chvotes' => 0,
      'chorder' => 1,
    ),
    array(
      'chtext' => 'Bonus Track 1',
      'chvotes' => 0,
      'chorder' => 2,
    ),
  );
  $node->allowvotes = true;
  $node->vote = -1;
  $node->runtime = 0;
  $node->active = 1;
  
  node_save($node);
}
