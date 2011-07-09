<?php
// $Id$

/**
 * @file
 * file_description
 */

$view = new view;
$view->name = 'i18n_poll';
$view->description = '';
$view->tag = 'i18n';
$view->view_php = '';
$view->base_table = 'node';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('sorts', array(
  'created' => array(
    'order' => 'DESC',
    'granularity' => 'second',
    'id' => 'created',
    'table' => 'node',
    'field' => 'created',
    'relationship' => 'none',
  ),
));
$handler->override_option('filters', array(
  'moderate' => array(
    'operator' => '=',
    'value' => 0,
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'moderate',
    'table' => 'node',
    'field' => 'moderate',
    'relationship' => 'none',
  ),
  'status' => array(
    'operator' => '=',
    'value' => 1,
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'status',
    'table' => 'node',
    'field' => 'status',
    'relationship' => 'none',
  ),
  'type' => array(
    'operator' => 'in',
    'value' => array(
      'poll' => 'poll',
    ),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'type',
    'table' => 'node',
    'field' => 'type',
    'relationship' => 'none',
  ),
  'language' => array(
    'operator' => 'in',
    'value' => array(
      '***CURRENT_LANGUAGE***' => '***CURRENT_LANGUAGE***',
      '***NO_LANGUAGE***' => '***NO_LANGUAGE***',
    ),
    'group' => '0',
    'exposed' => FALSE,
    'expose' => array(
      'operator' => FALSE,
      'label' => '',
    ),
    'id' => 'language',
    'table' => 'node',
    'field' => 'language',
    'relationship' => 'none',
  ),
));
$handler->override_option('access', array(
  'type' => 'none',
));
$handler->override_option('title', 'Poll');
$handler->override_option('items_per_page', 1);
$handler->override_option('row_plugin', 'node');
$handler->override_option('row_options', array(
  'teaser' => 1,
  'links' => 0,
  'comments' => 0,
));
$handler = $view->new_display('block', 'Block', 'block_1');
$handler->override_option('block_description', '');
$handler->override_option('block_caching', -1);

