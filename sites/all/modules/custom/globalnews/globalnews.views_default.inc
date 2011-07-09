<?php

// $Id$

/**
 * @file
 *   Globalnews default views include.
 */

/**
 * Implementation of hook_views_default_views().
 */
function globalnews_views_default_views() {
  /*
   * View 'globalnews_moderation'.
   */
  $view = new view;
  $view->name = 'globalnews_moderation';
  $view->description = 'News articles awaiting approval';
  $view->tag = 'globalnews';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'Title',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'body' => array(
      'label' => 'Body',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 1,
        'max_length' => '50',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'body',
      'table' => 'node_revisions',
      'field' => 'body',
      'relationship' => 'none',
    ),
    'edit_node' => array(
      'label' => 'Edit link',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'text' => '',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'language' => array(
      'default_action' => 'summary asc',
      'style_plugin' => 'default_summary',
      'style_options' => array(
        'count' => 1,
        'override' => 0,
        'items_per_page' => '25',
      ),
      'wildcard' => 'all',
      'wildcard_substitution' => 'Global Regions with News Pending News Approval',
      'title' => '%1 Global News Awaiting Approval',
      'breadcrumb' => '',
      'default_argument_type' => 'php',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'id' => 'language',
      'table' => 'node',
      'field' => 'language',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '6' => 0,
        '4' => 0,
        '5' => 0,
        '3' => 0,
      ),
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'poll' => 0,
        'album' => 0,
        'banner' => 0,
        'block' => 0,
        'blog' => 0,
        'buddy_icon' => 0,
        'comment' => 0,
        'date' => 0,
        'fan' => 0,
        'feed' => 0,
        'forum' => 0,
        'forum_reply' => 0,
        'landingpage' => 0,
        'news' => 0,
        'official_photo' => 0,
        'page' => 0,
        'photo' => 0,
        'product' => 0,
        'review' => 0,
        'track' => 0,
        'video' => 0,
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
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_node_flag_name' => '*relationship*',
      'validate_argument_node_flag_test' => 'flaggable',
      'validate_argument_node_flag_id_type' => 'id',
      'validate_argument_user_flag_name' => '*relationship*',
      'validate_argument_user_flag_test' => 'flaggable',
      'validate_argument_user_flag_id_type' => 'id',
      'validate_argument_php' => '',
    ),
    'language_1' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'php',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'id' => 'language_1',
      'table' => 'node',
      'field' => 'language',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '6' => 0,
        '4' => 0,
        '5' => 0,
        '3' => 0,
      ),
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => 'global $user;
$all = \'all\';
$options = i18n_access_load_permissions($user->uid);
$count=count($options);
if ($count == 1) {
$language = array();
foreach($options as $option){
$language[]=$option;
}
if ($language[0] != \'NEUTRAL\') {
return $language[0];
}
else {
return $all;
}
}
else {
return;
}
',
      'validate_argument_node_type' => array(
        'poll' => 0,
        'album' => 0,
        'banner' => 0,
        'block' => 0,
        'blog' => 0,
        'buddy_icon' => 0,
        'comment' => 0,
        'date' => 0,
        'fan' => 0,
        'feed' => 0,
        'forum' => 0,
        'forum_reply' => 0,
        'landingpage' => 0,
        'news' => 0,
        'official_photo' => 0,
        'page' => 0,
        'photo' => 0,
        'product' => 0,
        'review' => 0,
        'track' => 0,
        'video' => 0,
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
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_node_flag_name' => '*relationship*',
      'validate_argument_node_flag_test' => 'flaggable',
      'validate_argument_node_flag_id_type' => 'id',
      'validate_argument_user_flag_name' => '*relationship*',
      'validate_argument_user_flag_test' => 'flaggable',
      'validate_argument_user_flag_id_type' => 'id',
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'moderate' => array(
      'operator' => '=',
      'value' => '1',
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
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'news' => 'news',
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
    'type' => 'role',
    'role' => array(
      '6' => 6,
      '5' => 5,
      '3' => 3,
    ),
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Regions with Global News Pending Approval');
  $handler->override_option('items_per_page', 0);
  $handler->override_option('style_plugin', 'bulk');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'title' => 'title',
      'body' => 'body',
      'edit_node' => 'edit_node',
    ),
    'info' => array(
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'body' => array(
        'separator' => '',
      ),
      'edit_node' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
    'execution_type' => '2',
    'display_type' => '1',
    'hide_select_all' => 0,
    'skip_confirmation' => 0,
    'display_result' => 1,
    'merge_single_action' => 1,
    'selected_operations' => array(
      'modr8_bulk_approve' => 'modr8_bulk_approve',
      'flag_nodes:9c66b6f7fa4693a8a313531764f33c8b' => 0,
      'nodequeue_add_action' => 0,
      'node_mass_update:069c4f6e6df2752608ba0eab0bd548bf' => 0,
      'node_mass_update:84003ecc83843d323995cb7018db2fae' => 0,
      'node_mass_update:ff01c04136304be19b87ce6acb1cbf4d' => 0,
      'node_mass_update:6ace511cf8ccad8698fbb659375b4294' => 0,
      'node_mass_update:d1a59cb3f99bdac899ef8e055eb0fa44' => 0,
      'node_mass_update:7f68adda8cc74d1a61d53f3d0491712d' => 0,
      'node_mass_update:ce3a1d8a7300038ec3e11ee83be79b75' => 0,
      'node_mass_update:f5fca66aaa4c68f11e2c1305d4493e86' => 0,
      'node_mass_update:268d31e410629c1ea008411692535d89' => 0,
      'node_mass_update:dc2febb20bb2dd6e9521ef6a9c3e092d' => 0,
      'node_mass_update:b6500cb09f9baa1a3d4c7fee0a53b0c3' => 0,
      'node_mass_update:1f0ac016bcdc10e2f961993c4e09a619' => 0,
      'node_mass_update:54cb1006a818a6cf33d0287ae4f78c9f' => 0,
      'node_mass_update:88cf0fd753cede1a693768df99a61ed7' => 0,
      'node_assign_owner_action' => 0,
      'modr8_bulk_deny' => 0,
      'views_bulk_operations_delete_node_action' => 0,
      'flag_nodes:f72d1e527ee7919cf5b1ae4e7c4941c4' => 0,
      'node_mass_update:a27b9efabcd054685a549378b174ad11' => 0,
      'system_message_action' => 0,
      'token_actions_message_action' => 0,
      'sonybmg_enable_comments' => 0,
      'views_bulk_operations_action' => 0,
      'views_bulk_operations_script_action' => 0,
      'flag_node_action' => 0,
      'flag_nodes:1ab203888947d12613aec06f6a2fc10d' => 0,
      'node_make_sticky_action' => 0,
      'node_make_unsticky_action' => 0,
      'node_mass_update:c4d3b28efb86fd703619a50b74d43794' => 0,
      'modr8_bulk_moderate' => 0,
      'views_bulk_operations_fields_action' => 0,
      'views_bulk_operations_taxonomy_action' => 0,
      'views_bulk_operations_argument_selector_action' => 0,
      'node_promote_action' => 0,
      'flag_nodes:9c92acbeaeb2ac2b272c9b212ef10401' => 0,
      'node_mass_update:14de7d028b4bffdf2b4a266562ca18ac' => 0,
      'node_mass_update:9c585624b9b3af0b4687d5f97f35e047' => 0,
      'node_publish_action' => 0,
      'token_actions_goto_action' => 0,
      'system_goto_action' => 0,
      'emfield_operations_reload' => 0,
      'flag_nodes:174f0b389fed788c321cee22d3d257d0' => 0,
      'nodequeue_remove_action' => 0,
      'flag_nodes:1a6b07342f962e3c5d91174ec13fdfe2' => 0,
      'node_unpromote_action' => 0,
      'node_mass_update:8ce21b08bb8e773d10018b484fe4815e' => 0,
      'flag_nodes:a35437ea90330f1b7e0b0cc9f0f0cebd' => 0,
      'sonybmg_offensive_mollom_delete_action' => 0,
      'sonybmg_offensive_mollom_unpublish_action' => 0,
      'sonybmg_offensive_undo_offensive_action' => 0,
      'node_save_action' => 0,
      'system_send_email_action' => 0,
      'token_actions_send_email_action' => 0,
      'global_discography_translate_albums_action' => 0,
      'flag_nodes:44858eeba48bb1106d0359543ab9435b' => 0,
      'node_mass_update:0ccad85c1ebe4c9ceada1aa64293b080' => 0,
      'sonybmg_offensive_remove_offensive_action' => 0,
      'node_unpublish_action' => 0,
      'node_unpublish_by_keyword_action' => 0,
      'pathauto_node_update_alias_multiple:620e193b20ba9caa374fea9ca0ad38f0' => 0,
    ),
    'views_bulk_operations_fields_action' => array(
      'php_code' => 0,
      'display_fields' => array(
        '_all_' => '_all_',
      ),
    ),
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/content/moderation/news');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Global News Moderation',
    'description' => 'News Articles Pending Approval',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $views[$view->name] = $view;

  return $views;
}


