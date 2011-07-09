<?php

/**
 * Implementation of hook_strongarm().
 */
function sonybmg_events_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_date';
  $strongarm->value = 0;

  $export['comment_anonymous_date'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_date';
  $strongarm->value = '3';

  $export['comment_controls_date'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_date';
  $strongarm->value = 0;

  $export['comment_date'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_date';
  $strongarm->value = '4';

  $export['comment_default_mode_date'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_date';
  $strongarm->value = '1';

  $export['comment_default_order_date'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_date';
  $strongarm->value = '50';

  $export['comment_default_per_page_date'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_date';
  $strongarm->value = '1';

  $export['comment_form_location_date'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_date';
  $strongarm->value = '1';

  $export['comment_preview_date'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_date';
  $strongarm->value = '1';

  $export['comment_subject_field_date'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'events_date_pager';
  $strongarm->value = '3';

  $export['events_date_pager'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'flag_content_node_type_photo';
  $strongarm->value = 1;

  $export['flag_content_node_type_photo'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_date';
  $strongarm->value = '0';

  $export['language_content_type_date'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_date';
  $strongarm->value = array(
    '0' => 'status',
    '1' => 'promote',
  );

  $export['node_options_date'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_date_pattern';
  $strongarm->value = 'event/[field_date-yyyy]/[field_date-mm]/[field_date-dd]/[title-raw]';

  $export['pathauto_node_date_pattern'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_date';
  $strongarm->value = '1';

  $export['upload_date'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'views_defaults';
  $strongarm->value = array(
    'friendlist_manage_oneway' => TRUE,
    'friendlist_manage_twoway' => TRUE,
    'friendlist_public_oneway' => TRUE,
    'friendlist_public_twoway' => TRUE,
    'flag_favorite' => TRUE,
    'flag_favorites' => TRUE,
    'flag_signup' => TRUE,
    'flag_promote' => TRUE,
    'flag_bookmarks' => TRUE,
    'flag_offensive' => TRUE,
  );

  $export['views_defaults'] = $strongarm;
  return $export;
}
