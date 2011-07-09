<?php

/**
 * Implementation of hook_views_data()
 */
function pluto_views_data() {
  // ----------------------------------------------------------------
  // users table

  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.
  $data['pluto_users']['table']['group']  = t('Pluto');
  
  // join to the users table
  $data['pluto_users']['table']['join'] = array(
    'users' => array(
      'table' => 'users', // pluto_users is an alias, so this is the real name of the table
      'left_field' => 'uid',
      'field' => 'uid',
      'type' => 'INNER', // we're joining the user table to itself, so always going to be both
    ),
  );
  
  $data['pluto_users']['badges'] = array(
    'real field' => 'uid',
    'title' => t('Badges'),
    'help' => t("The user's badges, if any."), // The help that appears on the UI,
    // Information for displaying the uid
    'field' => array(
      'handler' => 'pluto_handler_field_pluto_badges',
      'click sortable' => FALSE,
    ),
  );
  
  $data['pluto_users']['bestbadge'] = array(
    'real field' => 'uid',
    'title' => t('Rank Badge'),
    'help' => t("The user's 'rank' badge."), // The help that appears on the UI,
    // Information for displaying the uid
    'field' => array(
      'handler' => 'pluto_handler_field_pluto_bestbadge',
      'click sortable' => FALSE,
    ),
  );
  
  $data['pluto_users']['badgesnobest'] = array(
    'real field' => 'uid',
    'title' => t('Badge (without rank badge)'),
    'help' => t("The user's badges, without the rank badge (use in conjunction with the Rank Badge field)."), // The help that appears on the UI,
    // Information for displaying the uid
    'field' => array(
      'handler' => 'pluto_handler_field_pluto_badgesnobest',
      'click sortable' => FALSE,
    ),
  );

  // ----------------------------------------------------------------
  // pluto userpoints table
  
  $data['pluto_userpoints'] = array(
    'table' => array(
      'group' => t('Pluto'),
      'join' => array(
        'users' => array(
          'left_field' => 'uid',
          'field' => 'uid',
        ),
      ),
    ),
    'total_points' => array(
      'title' => t('Total !Points', userpoints_translation()),
      'help' => t('The total userpoints for a user'),
      'field' => array('handler' => 'views_handler_field'),
      'filter' => array('handler' => 'views_handler_filter_numeric'),
      'sort' => array('handler' => 'views_handler_sort'),
    ),
    'monthly_points' => array(
      'title' => t('Monthly !Points Total', userpoints_translation()),
      'help' => t('The total userpoints for a month'),
      'field' => array('handler' => 'views_handler_field'),
      'filter' => array('handler' => 'views_handler_filter_numeric'),
      'sort' => array('handler' => 'views_handler_sort'),
    ),
  );

  return $data;
  
}

/**
 * Implementation of hook_views_handlers() to register all of the basic handlers
 * views uses.
 */
function pluto_views_handlers() {
  return array(
    'handlers' => array(
      'pluto_handler_field_pluto_badges' => array(
        'parent' => 'views_handler_field',
      ),
      'pluto_handler_field_pluto_bestbadge' => array(
        'parent' => 'views_handler_field',
      ),
      'pluto_handler_field_pluto_badgesnobest' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}