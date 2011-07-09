<?php
// $Id: drubb.views_default.inc,v 1.1 2009/05/29 13:35:45 karens Exp $
/**
 * @file
 * Contains default views on behalf of the Drubb module.
 */

/**
 * Implementation of hook_default_view_views().
 */
$view = new view;
$view->name = 'user_draft_list';
$view->description = 'User Draft List';
$view->tag = 'draft';
$view->view_php = '';
$view->base_table = 'users';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('fields', array(
  'view_draft' => array(
    'label' => 'View Draft',
    'exclude' => 0,
    'id' => 'view_draft',
    'table' => 'drafts',
    'field' => 'view_draft',
    'relationship' => 'none',
  ),
  'node_type' => array(
    'label' => 'Node Type',
    'exclude' => 0,
    'id' => 'node_type',
    'table' => 'drafts',
    'field' => 'node_type',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'title' => array(
    'label' => 'Title',
    'exclude' => 0,
    'id' => 'title',
    'table' => 'drafts',
    'field' => 'title',
    'relationship' => 'none',
  ),
  'body' => array(
    'label' => 'Body',
    'exclude' => 1,
    'id' => 'body',
    'table' => 'drafts',
    'field' => 'body',
    'relationship' => 'none',
  ),
  'updated' => array(
    'id' => 'updated',
    'table' => 'drafts',
    'field' => 'updated',
  ),
  'cron_remove' => array(
    'label' => 'Cron Remove',
    'exclude' => 1,
    'id' => 'cron_remove',
    'table' => 'drafts',
    'field' => 'cron_remove',
    'relationship' => 'none',
  ),
  'name' => array(
    'label' => 'Name',
    'link_to_user' => 1,
    'exclude' => 1,
    'id' => 'name',
    'table' => 'users',
    'field' => 'name',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'draft_id' => array(
    'label' => 'Draft ID',
    'exclude' => 1,
    'id' => 'draft_id',
    'table' => 'drafts',
    'field' => 'draft_id',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('arguments', array(
  'uid' => array(
    'default_action' => 'default',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => 'Draft List',
    'default_argument_type' => 'user',
    'default_argument' => '',
    'validate_type' => 'none',
    'validate_fail' => 'not found',
    'break_phrase' => 0,
    'not' => 0,
    'id' => 'uid',
    'table' => 'users',
    'field' => 'uid',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => 'global $user;
                return $user->uid;',
    'validate_argument_node_type' => array(
      'poll' => 0,
      'forum' => 0,
      'image' => 0,
      'page' => 0,
      'story' => 0,
    ),
    'validate_argument_node_access' => 0,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_is_member' => 0,
    'validate_argument_vocabulary' => array(
      '4' => 0,
      '3' => 0,
      '2' => 0,
    ),
    'validate_argument_type' => 'tid',
    'validate_argument_php' => '',
    'validate_user_argument_type' => 'uid',
    'validate_user_roles' => array(
      '2' => 0,
    ),
    'validate_argument_transform' => 0,
    'validate_user_restrict_roles' => 0,
  ),
));
$handler->override_option('access', array(
  'type' => 'perm',
  'role' => array(),
  'perm' => 'access save as draft',
));
$handler->override_option('title', 'Draft List');
$handler->override_option('empty', 'There are no saved drafts.');
$handler->override_option('empty_format', '4');
$handler->override_option('use_pager', 'mini');
$handler->override_option('style_plugin', 'table');
$handler->override_option('style_options', array(
  'grouping' => '',
  'override' => 1,
  'sticky' => 0,
  'order' => 'asc',
  'columns' => array(
    'draft_id' => 'draft_id',
    'node_type' => 'node_type',
    'updated' => 'updated',
    'name' => 'name',
  ),
  'info' => array(
    'draft_id' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'node_type' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'updated' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'name' => array(
      'sortable' => 1,
      'separator' => '',
    ),
  ),
  'default' => 'name',
));
$handler = $view->new_display('page', 'Page', 'page_1');
$handler->override_option('path', 'user/%/drafts');
$handler->override_option('menu', array(
  'type' => 'tab',
  'title' => 'Drafts',
  'description' => '',
  'weight' => '1',
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'description' => '',
  'weight' => 0,
));
