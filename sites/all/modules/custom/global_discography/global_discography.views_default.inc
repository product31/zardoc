<?php

/**
 * Implementation of hook_views_default_views().
 */
function global_discography_views_default_views() {
  /*
   * View 'global_discography'
   */
  $view = new view;
  $view->name = 'global_discography';
  $view->description = 'Translate Albums and Tracks';
  $view->tag = 'global_discography';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'field_album_cover_fid' => array(
      'label' => 'Album Cover',
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'discography_small_default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_album_cover_fid',
      'table' => 'node_data_field_album_cover',
      'field' => 'field_album_cover_fid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'title' => array(
      'label' => 'Title',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'type' => array(
      'label' => 'Type',
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'language' => array(
      'label' => 'Source',
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
      'id' => 'language',
      'table' => 'node',
      'field' => 'language',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'album' => 'album',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => 'type_op',
        'label' => 'Node: Type',
        'use_operator' => 0,
        'identifier' => 'type',
        'optional' => 1,
        'single' => 1,
        'remember' => 1,
        'reduce' => 0,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'source_translation' => array(
      'operator' => '1',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'source_translation',
      'table' => 'node',
      'field' => 'source_translation',
      'relationship' => 'none',
    ),
    'language' => array(
      'operator' => 'not in',
      'value' => array(
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
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'access administration pages',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Global Discography');
  $handler->override_option('empty', 'There are no objects satisfying the filter settings. Try changing them to get some results.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 0);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'bulk');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'field_album_cover_fid' => 'field_album_cover_fid',
      'title' => 'title',
      'type' => 'type',
      'language' => 'language',
    ),
    'info' => array(
      'field_album_cover_fid' => array(
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 1,
        'separator' => '&nbsp;',
      ),
      'type' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'language' => array(
        'sortable' => 0,
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
      'global_discography_translate_albums_action' => 'global_discography_translate_albums_action',
      'flag_nodes:9c66b6f7fa4693a8a313531764f33c8b' => 0,
      'flag_nodes:1ab203888947d12613aec06f6a2fc10d' => 0,
      'nodequeue_add_action' => 0,
      'modr8_bulk_approve' => 0,
      'node_mass_update:069c4f6e6df2752608ba0eab0bd548bf' => 0,
      'node_mass_update:84003ecc83843d323995cb7018db2fae' => 0,
      'node_mass_update:eb9b44d659ca0ee9de75f156ad3f18f9' => 0,
      'node_mass_update:ff01c04136304be19b87ce6acb1cbf4d' => 0,
      'node_mass_update:bb02076ae699b45a05b061a4542f39e0' => 0,
      'node_mass_update:7014750266664f7bbded904498ac1a26' => 0,
      'node_mass_update:ce3a1d8a7300038ec3e11ee83be79b75' => 0,
      'node_mass_update:6c9978c0db636d2682ccdc6372b3eaa9' => 0,
      'node_mass_update:46ba454f9aaeca955f4a0573ffb5b7d4' => 0,
      'node_mass_update:c2090eaffc215ec2ced9c78f92a479a2' => 0,
      'node_mass_update:7fbf73bc36ea6ac11a27ca9972248fba' => 0,
      'node_mass_update:268d31e410629c1ea008411692535d89' => 0,
      'node_mass_update:3571b4c1a0494a6461b9794cf03f4654' => 0,
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
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->override_option('path', 'admin/content/discography');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Translate Discography',
    'description' => 'Translate Discography',
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


