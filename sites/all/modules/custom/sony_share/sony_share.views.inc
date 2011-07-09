<?php
// $Id:

/**
 * @file
 * Provide views data and handlers for custom_teasers_views.module
 */

/**
 * Implementation of hook_views_data().
 */
function sony_share_views_data() {
  // We're registering the 'custom_teasers' table.
  $data['node']['sony_share'] = array(
    'title' => t('Sony Share'),
    'help' => t('Display links to social sharing websites like Digg, del.icio.us, reddit, Technorati etc..'),
    'field' => array(
      'handler' => 'sony_share_handler_field_sony_share',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function sony_share_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'sony_share'),
    ),
    'handlers' => array(
      'sony_share_handler_field_sony_share' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}
