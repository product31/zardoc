<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function sonybmg_events_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_flag_default_flags().
 */
function sonybmg_events_flag_default_flags() {
$flags = array();
// Exported flag: "signup".
$flags[] = array (
  'content_type' => 'node',
  'name' => 'signup',
  'title' => 'signup',
  'global' => '0',
  'types' => 
  array (
    0 => 'date',
  ),
  'flag_short' => 'Add Me',
  'flag_long' => 'I\'ll be attending',
  'flag_message' => '',
  'unflag_short' => 'Remove Me',
  'unflag_long' => 'I won\'t be attending',
  'unflag_message' => '',
  'unflag_denied_text' => '',
  'link_type' => 'toggle',
  'roles' => 
  array (
    'flag' => 
    array (
      0 => 2,
    ),
    'unflag' => 
    array (
      0 => 2,
    ),
  ),
  'show_on_page' => 1,
  'show_on_teaser' => 0,
  'show_on_form' => 0,
  'access_author' => '',
  'i18n' => 0,
  'module' => 'sonybmg_events',
  'api_version' => 2,
);
return $flags;
}

/**
 * Implementation of hook_node_info().
 */
function sonybmg_events_node_info() {
  $items = array(
    'date' => array(
      'name' => t('Date'),
      'module' => 'features',
      'description' => t('Dates have a start date and an optional end date as well as a teaser and a body. They can be extended by other modules, too.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function sonybmg_events_views_api() {
  return array(
    'api' => '2',
  );
}
