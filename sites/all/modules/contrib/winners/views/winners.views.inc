<?php
// $Id: winners.views.inc,v 1.1.2.1 2010/04/01 19:25:35 andrewlevine Exp $

function winners_views_data() {
  $data = array(
    // Winners table
    'winners' => array(
      'table' => array(
        'group' => 'Winners',
        'join' => array(
          'users' => array(
            'left_field' => 'uid',
            'field' => 'uid',
          ),
        ),
      ),
      'winner_id' => array(
        'title' => t('Winner ID'),
        'help' => t('The serial ID of a winner.'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
        ),
        // Information for accepting a nid as an argument
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
          'numeric' => TRUE,
        ),
        // Information for accepting a nid as a filter
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
        ),
        // Information for sorting on a nid.
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'contest_id' => array(
        'title' => t('Contest ID'),
        'help' => t('The contest this winner won'),
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
        ),
        // Information for accepting a nid as an argument
        'argument' => array(
          'handler' => 'winners_handler_argument_contest_id',
          'numeric' => TRUE,
        ),
        // Information for accepting a nid as a filter
        'filter' => array(
          'handler' => 'winners_handler_filter_contests',
        ),
        // Information for sorting on a nid.
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      // Contest Winner
      'contest_winner' => array(
        'real field' => 'contest_id',
        'title' => t('Contest Winner'),
        'help' => t('The user has won a contest at all'),
        'filter' => array(
          'handler' => 'winners_handler_filter_contest_winner',
          'type' => 'yes-no',
        ),
      ),
      'picked' => array(
        'title' => t('Time Picked'),
        'help' => t('The time the winner was picked'),
        'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        // Information for accepting a nid as an argument
        'argument' => array(
          'handler' => 'views_handler_argument_date',
          'numeric' => TRUE,
        ),
        // Information for accepting a nid as a filter
        'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
        // Information for sorting on a nid.
        'sort' => array(
          'handler' => 'views_handler_sort_date',
        ),
      ),
    ),
    // Contests table
    'winners_contests' => array(
      'table' => array(
        'group' => 'Winners',
        'join' => array(
          'users' => array(
            'left_table' => 'winners',
            'left_field' => 'contest_id',
            'field' => 'contest_id',
          ),
        ),
      ),
      'name' => array(
        'title' => t('Contest Name'),
        'help' => t('The name of the contest.'),
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
        // Information for accepting a nid as an argument
        'argument' => array(
          'handler' => 'views_handler_argument_string',
          'numeric' => FALSE,
        ),
        // Information for accepting a nid as a filter
        'filter' => array(
          'handler' => 'views_handler_filter_string',
        ),
        // Information for sorting on a nid.
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
      'last_picked' => array(
        'title' => t('Last time picked'),
        'help' => t('The last time that a winner was picked for this contest.'),
        'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        // Information for accepting a nid as an argument
        'argument' => array(
          'handler' => 'views_handler_argument_date',
          'numeric' => TRUE,
        ),
        // Information for accepting a nid as a filter
        'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
        // Information for sorting on a nid.
        'sort' => array(
          'handler' => 'views_handler_sort_date',
        ),
      ),
    ),
  );
  return $data;
}

function winners_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'winners') . '/views',
    ),
    'handlers' => array(
      //'datasync_handler_field_status' => array('parent' => 'views_handler_field'),
      'winners_handler_filter_contests' => array('parent' => 'views_handler_filter_in_operator'),
      'winners_handler_filter_contest_winner' => array('parent' => 'views_handler_filter_boolean_operator'),
      'winners_handler_argument_contest_id' => array('parent' => 'views_handler_argument_numeric'),
    ),
  );
}
