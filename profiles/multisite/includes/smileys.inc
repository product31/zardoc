<?php
/**
* Default labelling and weight for this profile include
*/
function smileys_info() {
  return array(
    'name' => st('Smileys(Emoticons)'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 0,
  );
}

/**
 * Required modules in order for these options to be created successfully
 */
function smileys_modules() {
  return array('smileys');
}

/**
 * Task to complete in order to activate this segment of code
 */
function smileys_task_list() {
  return array(
    'smileys_add_format' => array(
      'message' => st('Added Smileys filter to the default format.'),
      'weight' => 0,
    ),
  );
}

/**
 * Add smileys filter to the default format.
 */
function smileys_add_format() {
  // Get the default format.
  $fid = variable_get('filter_default_format', 1);

  // Add smileys filter to default format.
  install_add_filter($fid, 'smileys', 0, 10);
}
