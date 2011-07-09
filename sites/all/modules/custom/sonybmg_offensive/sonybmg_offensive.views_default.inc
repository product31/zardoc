<?php

/**
 * Implementation of hook_views_default_views().
 */
function sonybmg_offensive_views_default_views() {
  /*
   * View 'node_offensive_flags'
   */
  $view = new view;
  $view->name = 'node_offensive_flags';
  $view->description = 'List of flags on a node';
  $view->tag = 'sonybmg_offensive';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'flag_content_rel' => array(
      'label' => 'flag',
      'required' => 1,
      'flag' => 'offensive',
      'user_scope' => 'any',
      'id' => 'flag_content_rel',
      'table' => 'node',
      'field' => 'flag_content_rel',
      'relationship' => 'none',
    ),
    'uid' => array(
      'label' => 'Flag user',
      'required' => 1,
      'id' => 'uid',
      'table' => 'flag_content',
      'field' => 'uid',
      'relationship' => 'flag_content_rel',
    ),
  ));
  $handler->override_option('fields', array(
    'name' => array(
      'label' => 'Name',
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
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'uid',
    ),
    'timestamp' => array(
      'label' => 'Flagged time',
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
      'date_format' => 'large',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'timestamp',
      'table' => 'flag_content',
      'field' => 'timestamp',
      'relationship' => 'flag_content_rel',
    ),
  ));
  $handler->override_option('sorts', array(
    'timestamp' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'timestamp',
      'table' => 'flag_content',
      'field' => 'timestamp',
      'relationship' => 'flag_content_rel',
    ),
  ));
  $handler->override_option('arguments', array(
    'nid' => array(
      'default_action' => 'not found',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => 'Flags for %1',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
        '4' => 0,
        '5' => 0,
        '6' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'poll' => 0,
        'album' => 0,
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
        'review' => 0,
        'track' => 0,
        'video' => 0,
        'wallpaper' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '2' => 0,
        '1' => 0,
        '3' => 0,
        '4' => 0,
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
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'moderate content',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('empty', 'This has not been flagged');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 20);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 0,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'name' => 'name',
      'timestamp' => 'timestamp',
    ),
    'info' => array(
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'timestamp' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'node/%/offensive');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Flags',
    'description' => '',
    'weight' => '10',
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
   * View 'offensive_content'
   */
  $view = new view;
  $view->name = 'offensive_content';
  $view->description = 'Offensive Content';
  $view->tag = 'sonybmg_offensive';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'flag_count_rel' => array(
      'label' => 'offensive_count',
      'required' => 1,
      'flag' => 'offensive',
      'id' => 'flag_count_rel',
      'table' => 'node',
      'field' => 'flag_count_rel',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'flag_content_rel' => array(
      'label' => 'flag',
      'required' => 1,
      'flag' => 'offensive',
      'user_scope' => 'any',
      'id' => 'flag_content_rel',
      'table' => 'node',
      'field' => 'flag_content_rel',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'uid' => array(
      'label' => 'Flag user',
      'required' => 1,
      'id' => 'uid',
      'table' => 'flag_content',
      'field' => 'uid',
      'relationship' => 'flag_content_rel',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('fields', array(
    'name' => array(
      'label' => 'Author',
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'Title',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'type' => array(
      'label' => 'Type',
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'created' => array(
      'label' => 'Post date',
      'date_format' => 'medium',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'relationship' => 'none',
    ),
    'status' => array(
      'label' => 'Published',
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 0,
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'count' => array(
      'label' => 'Offensive Reports',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'count',
      'table' => 'flag_counts',
      'field' => 'count',
      'relationship' => 'flag_count_rel',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'name_1' => array(
      'label' => 'Flagged by',
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
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name_1',
      'table' => 'users',
      'field' => 'name',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'uid',
    ),
    'nid' => array(
      'label' => 'View',
      'alter' => array(
        'alter_text' => 1,
        'text' => 'View',
        'make_link' => 0,
        'path' => 'node/[nid]',
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
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'edit_node' => array(
      'label' => 'Edit',
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
      'text' => '',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'nid_1' => array(
      'label' => 'View flags',
      'alter' => array(
        'alter_text' => 1,
        'text' => 'Flags',
        'make_link' => 1,
        'path' => 'node/[nid_1]/offensive',
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
      'id' => 'nid_1',
      'table' => 'node',
      'field' => 'nid',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'moderate content',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Offensive Content');
  $handler->override_option('header', 'This lists all content that has been flagged as offensive. There is a separate view of <a href="offensive/unpublished">unpublished content</a>.');
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 1);
  $handler->override_option('empty', 'No content has been reported as offensive.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('use_pager', '1');
  $handler->override_option('distinct', 1);
  $handler->override_option('style_plugin', 'bulk');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'name' => 'name',
      'title' => 'title',
      'type' => 'type',
      'created' => 'created',
      'status' => 'status',
      'count' => 'count',
      'name_1' => 'name_1',
      'nid' => 'nid',
      'edit_node' => 'edit_node',
      'nid_1' => 'nid_1',
    ),
    'info' => array(
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'type' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'created' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'status' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'count' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'name_1' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'nid' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'edit_node' => array(
        'separator' => '',
      ),
      'nid_1' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => 'created',
    'execution_type' => '1',
    'display_type' => '0',
    'skip_confirmation' => 0,
    'display_result' => 1,
    'merge_single_action' => 1,
    'selected_operations' => array(
      '091c3aabc50bc2ef887476e6b87830f8' => '091c3aabc50bc2ef887476e6b87830f8',
      'e96336e879673bdfae25232d9eb1ce22' => 'e96336e879673bdfae25232d9eb1ce22',
      '5cb904f8fc918eaa69b43436cae304d2' => '5cb904f8fc918eaa69b43436cae304d2',
      '09ae6a3d4e0feb7b74eb51d675d6c77d' => '09ae6a3d4e0feb7b74eb51d675d6c77d',
      'ea3c8e5a75921b946f73bf6e9dbdb886' => 0,
      '9a0b157f567db269eae90bf073ce26e8' => 0,
      'e795c11e4b07dc1cd881d03dcbd648d5' => 0,
      '50c548dc0f69242bc4c31f724537dd5b' => 0,
      '6d1893209836a08c64f1318001dedeaf' => 0,
      'f0e8096048ca43304893bfb453c1685a' => 0,
      'ba22683fdccca49559ab54137e4508a2' => 0,
      'b67f1d720ed1805d89b81e247a7302a7' => 0,
      '6a99179e9c90e9edfb34d075fa234d78' => 0,
      '9e7c10014c1355b762534f485c1820c9' => 0,
      '3ea33dae73a849deedd536991455be98' => 0,
      'a7fdf1558dff507d3d2d556feab826ec' => 0,
      '7a3d2d5b1bb6ecb0cb811c4130452d7d' => 0,
      '132fddcb3f367a243bee632db31985c1' => 0,
      'feb13e750bd2575b1f36109233087905' => 0,
      '80a5195f877321fb32d06f3439a68628' => 0,
      '334d20af1ae7ac4b770b7ec3210b2638' => 0,
      '799e8527bbd3d99e4c8c25a8a674d264' => 0,
      'fce859fcce0e81943c3e31c20ccd68ff' => 0,
      '591b41a4f10db44fb0b09b1e25152cef' => 0,
      '0a83393b4539f3025b022822377bc5bc' => 0,
      '4df6cb87c9bbb08ebec8c757e9a0fcc7' => 0,
      'f033f40d92f0308ed6b2e3befb3a4c2a' => 0,
      '0341fcc505281031474b68c72e03a997' => 0,
      '04fc237d7d5e286e3e725163ec88a8c1' => 0,
      '10edeb21cdd1fd049751311229c5e736' => 0,
      '3864faba61f46e2b68393b7fc88fa830' => 0,
      'c6d3850086dc3c1bca4bf0625ce78c56' => 0,
      '246fdc2a4672eb371d05b48b2a7cb51e' => 0,
      '52aec7fee2070ce530da1304653ae1ec' => 0,
      '43dc1f9c05e6ba1b69e37de52ce4a33a' => 0,
      '975245dff910d26812adb69c3fe8cac9' => 0,
      '7817f754302ccc14409cae99e448cae4' => 0,
      '94a098afb1689f950d72ed4c44f8655d' => 0,
      '1dcecde02b48fdfde9628fea88920225' => 0,
      'c30ef16558b77213d0c0c0a57e43f2dc' => 0,
      '15faf15d7f591f8ef8e80238dd7c8b8c' => 0,
      'daa75f478e3093ab107e657da6620a91' => 0,
      '2178a36c0b51f3a7ea1d854780e33cc5' => 0,
      'e34b2b80ed508be19587acb5d1a080e7' => 0,
      '03b537fcae446ebc4a634dffce0cbcfc' => 0,
      '6f7871c7725f0c91c07594602f07aa72' => 0,
      '548749a939aa6334157edff3d8f69351' => 0,
      'c6db6d4ee28924020b504a5feb2bff9f' => 0,
      '95b13811ebb8a72085c486c55e37b240' => 0,
    ),
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/content/offensive');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Offensive content',
    'description' => '',
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

  /*
   * View 'unpublished_content'
   */
  $view = new view;
  $view->name = 'unpublished_content';
  $view->description = 'List of unpublished content for moderators, including \'publish\' button';
  $view->tag = 'sonybmg_offensive';
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
        'strip_tags' => 0,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'teaser' => array(
      'label' => 'Teaser',
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
        'max_length' => '200',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 1,
        'html' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'exclude' => 0,
      'id' => 'teaser',
      'table' => 'node_revisions',
      'field' => 'teaser',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => 'Name',
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
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'created' => array(
      'label' => 'Posted',
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
      'date_format' => 'small',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'nid' => array(
      'order' => 'DESC',
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'moderate content',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Unpublished Content');
  $handler->override_option('empty', 'There is no unpublished content.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 20);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'bulk');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 0,
    'sticky' => 1,
    'order' => 'asc',
    'columns' => array(
      'teaser' => 'teaser',
      'title' => 'title',
    ),
    'info' => array(
      'teaser' => array(
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
    'execution_type' => '1',
    'display_type' => '1',
    'skip_confirmation' => 0,
    'display_result' => 1,
    'merge_single_action' => 1,
    'selected_operations' => array(
      'c6d3850086dc3c1bca4bf0625ce78c56' => 'c6d3850086dc3c1bca4bf0625ce78c56',
      'ea3c8e5a75921b946f73bf6e9dbdb886' => 0,
      'acea97c21be2d2c52ed09af42d0766c6' => 0,
      '9a0b157f567db269eae90bf073ce26e8' => 0,
      'e795c11e4b07dc1cd881d03dcbd648d5' => 0,
      '50c548dc0f69242bc4c31f724537dd5b' => 0,
      '3b3573187a8f60eecaac859273a651c1' => 0,
      '6d1893209836a08c64f1318001dedeaf' => 0,
      'b1b84305a5577e311f72b6af05d64fd4' => 0,
      'ba22683fdccca49559ab54137e4508a2' => 0,
      '6a8529d398bbf16d03c2131698cd27fe' => 0,
      'b67f1d720ed1805d89b81e247a7302a7' => 0,
      '6a99179e9c90e9edfb34d075fa234d78' => 0,
      '9e7c10014c1355b762534f485c1820c9' => 0,
      '3ea33dae73a849deedd536991455be98' => 0,
      'a7fdf1558dff507d3d2d556feab826ec' => 0,
      '7a3d2d5b1bb6ecb0cb811c4130452d7d' => 0,
      '132fddcb3f367a243bee632db31985c1' => 0,
      'feb13e750bd2575b1f36109233087905' => 0,
      '334d20af1ae7ac4b770b7ec3210b2638' => 0,
      '799e8527bbd3d99e4c8c25a8a674d264' => 0,
      'fce859fcce0e81943c3e31c20ccd68ff' => 0,
      '591b41a4f10db44fb0b09b1e25152cef' => 0,
      '0a83393b4539f3025b022822377bc5bc' => 0,
      '4df6cb87c9bbb08ebec8c757e9a0fcc7' => 0,
      'f033f40d92f0308ed6b2e3befb3a4c2a' => 0,
      '0341fcc505281031474b68c72e03a997' => 0,
      '04fc237d7d5e286e3e725163ec88a8c1' => 0,
      '10edeb21cdd1fd049751311229c5e736' => 0,
      '3864faba61f46e2b68393b7fc88fa830' => 0,
      '246fdc2a4672eb371d05b48b2a7cb51e' => 0,
      '52aec7fee2070ce530da1304653ae1ec' => 0,
      'baa73ace6461fc4e3394717858952595' => 0,
      '43dc1f9c05e6ba1b69e37de52ce4a33a' => 0,
      '098f01693a564a767879a8198c52f598' => 0,
      '975245dff910d26812adb69c3fe8cac9' => 0,
      '7817f754302ccc14409cae99e448cae4' => 0,
      '94a098afb1689f950d72ed4c44f8655d' => 0,
      '1dcecde02b48fdfde9628fea88920225' => 0,
      'c30ef16558b77213d0c0c0a57e43f2dc' => 0,
      '5cb904f8fc918eaa69b43436cae304d2' => 0,
      '15faf15d7f591f8ef8e80238dd7c8b8c' => 0,
      'daa75f478e3093ab107e657da6620a91' => 0,
      '2178a36c0b51f3a7ea1d854780e33cc5' => 0,
      '1e97c6ba8028058a3a5657fbe6a6b097' => 0,
      '03b537fcae446ebc4a634dffce0cbcfc' => 0,
      '6f7871c7725f0c91c07594602f07aa72' => 0,
      '09ae6a3d4e0feb7b74eb51d675d6c77d' => 0,
      '548749a939aa6334157edff3d8f69351' => 0,
      'c6db6d4ee28924020b504a5feb2bff9f' => 0,
      '5471472ae2eedc59c992b6859d26033b' => 0,
    ),
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/content/offensive/unpublished');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Unpublished Content',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $views[$view->name] = $view;

  return $views;
}


