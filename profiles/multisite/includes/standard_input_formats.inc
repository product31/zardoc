<?php

function standard_input_formats_info() {
  return array(
    'name' => st('Standard Input Formats'),
    'default_value' => TRUE,
    'disabled' => TRUE,
    'weight' => -14,
  );
}

function standard_input_formats_modules() {
  return array('filter_default');
}

function standard_input_formats_task_list() {
  return array(
    'standard_input_formats_create' => array(
      'message' => st('Created standard input formats.'),
      'weight' => 0,
    ),
    'standard_input_formats_update' => array(
      'message' => st('Updated standard input formats.'),
      'weight' => 0,
    ),
  );
}

function standard_input_formats_create() {
  //create new full HTML format (no filters at all)
  $fhu_id = install_add_format("Full HTML (unfiltered)");
  install_format_set_roles(array(variable_get('multisite_artist_rid', ''), variable_get('multisite_moderator_rid', ''), variable_get('multisite_administrator_rid', ''),), $fhu_id);

  $i = 1;
  variable_set('filter_default_'. $i++,
    array(variable_get('multisite_artist_rid', ''), $fhu_id));
  variable_set('filter_default_'. $i++,
    array(variable_get('multisite_moderator_rid', ''), $fhu_id));
  variable_set('filter_default_'. $i++,
    array(variable_get('multisite_administrator_rid', ''), $fhu_id));

  $default_format = variable_get('filter_default_format', 1);
  variable_set('filter_default_'. $i++,
    array(DRUPAL_ANONYMOUS_RID, $default_format));
  variable_set('filter_default_'. $i++,
    array(DRUPAL_AUTHENTICATED_RID, $default_format));

}

function standard_input_formats_update() {
  // Add necessary filters to old Full HTML.
  // TODO: Add install_get_format_id() to Install Profile API.
  // $fh_id = install_get_format_id('Full HTML');
  // TODO: add smiley or any other necessary filters to Full HTML
  // install_add_filter($fh_id, , , );
}