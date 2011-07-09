<?php

/**
 * Implementation of hook_views_default_views().
 */
function sonybmg_profiles_views_default_views() {
  /*
   * View 'buddylist'
   */
  $view = new view;
  $view->name = 'buddylist';
  $view->description = 'An approximation of the old buddylist module view.';
  $view->tag = 'sonybmg_profiles';
  $view->view_php = '';
  $view->base_table = 'friendlist_relations';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'requestee_id' => array(
      'label' => 'Requestee',
      'required' => 0,
      'id' => 'requestee_id',
      'table' => 'friendlist_relations',
      'field' => 'requestee_id',
      'relationship' => 'none',
    ),
    'requester_id' => array(
      'label' => 'Requester',
      'required' => 0,
      'id' => 'requester_id',
      'table' => 'friendlist_relations',
      'field' => 'requester_id',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'picture' => array(
      'label' => '',
      'exclude' => 0,
      'id' => 'picture',
      'table' => 'users',
      'field' => 'picture',
      'relationship' => 'requestee_id',
    ),
    'name' => array(
      'label' => '',
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'requestee_id',
    ),
  ));
  $handler->override_option('arguments', array(
    'uid' => array(
      'default_action' => 'empty',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
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
      'relationship' => 'requester_id',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'poll' => 0,
        'album' => 0,
        'blog' => 0,
        'buddy_icon' => 0,
        'comment' => 0,
        'date' => 0,
        'fan' => 0,
        'forum_reply' => 0,
        'landingpage' => 0,
        'news' => 0,
        'official_photo' => 0,
        'page' => 0,
        'photo' => 0,
        'review' => 0,
        'track' => 0,
        'wallpaper' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_php' => '',
      'validate_argument_vocabulary' => array(
        '2' => 0,
        '1' => 0,
        '3' => 0,
        '4' => 0,
      ),
      'validate_argument_type' => 'tid',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'time',
    'results_lifespan' => '60',
    'output_lifespan' => '60',
  ));
  $handler->override_option('title', 'Friend List');
  $handler->override_option('empty', 'This user doesn\'t have any friends yet.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 20);
  $handler->override_option('use_pager', '1');
  $handler->override_option('use_more', 1);
  $handler->override_option('style_plugin', 'grid');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'columns' => '5',
    'alignment' => 'horizontal',
  ));
  $handler = $view->new_display('page', 'Buddy List', 'page_1');
  $handler->override_option('path', 'buddylist');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $views[$view->name] = $view;

  /*
   * View 'user_activity'
   */
  $view = new view;
  $view->name = 'user_activity';
  $view->description = 'This view will display the user\'s blog, reviews and comments.';
  $view->tag = 'sonybmg_profiles';
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
  $handler->override_option('arguments', array(
    'uid' => array(
      'default_action' => 'empty',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => 'My Reviews & Blog',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'empty',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'album' => 0,
        'blog' => 0,
        'buddy_icon' => 0,
        'comment' => 0,
        'date' => 0,
        'fan' => 0,
        'forum' => 0,
        'forum_reply' => 0,
        'news' => 0,
        'official_photo' => 0,
        'page' => 0,
        'photo' => 0,
        'review' => 0,
        'track' => 0,
        'wallpaper' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '1' => 0,
        '4' => 0,
        '2' => 0,
        '3' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'blog' => 'blog',
        'comment' => 'comment',
        'review' => 'review',
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
  ));
  $handler->override_option('access', array(
    'type' => 'none',
    'role' => array(),
    'perm' => '',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('empty', 'This user does not have any reviews or blogs.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 3);
  $handler->override_option('use_pager', 'mini');
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('row_plugin', 'node');
  $handler->override_option('row_options', array(
    'teaser' => 1,
    'links' => 1,
  ));
  $views[$view->name] = $view;

  return $views;
}


