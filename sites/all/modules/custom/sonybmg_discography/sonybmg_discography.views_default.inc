<?php

/**
 * Implementation of hook_views_default_views().
 */
function sonybmg_discography_views_default_views() {
  /*
   * View 'alpha_artists'
   */
  $view = new view;
  $view->name = 'alpha_artists';
  $view->description = 'Artists in alphabetical order.';
  $view->tag = 'sonybmg_discography';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title_1' => array(
      'label' => '',
      'link_to_node' => 0,
      'exclude' => 1,
      'id' => 'title_1',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
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
    'field_photo_fid' => array(
      'label' => 'Photo',
      'link_to_node' => 1,
      'label_type' => 'widget',
      'format' => '75x75_linked',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_photo_fid',
      'table' => 'node_data_field_photo',
      'field' => 'field_photo_fid',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => '',
      'link_to_taxonomy' => 0,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'term_data',
      'field' => 'name',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'title' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'glossary' => 1,
      'limit' => '1',
      'case' => 'upper',
      'path_case' => 'lower',
      'transform_dash' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'default_argument_user' => 0,
      'default_argument_fixed' => 'a',
      'default_argument_php' => '',
      'validate_argument_vocabulary' => array(),
      'validate_argument_type' => 'tid',
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'artist' => 'artist',
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
    'tid' => array(
      'operator' => 'or',
      'value' => array(),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'tid_op',
        'identifier' => 'tid',
        'label' => 'Taxonomy: Term',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 0,
      ),
      'type' => 'select',
      'vid' => '7',
      'id' => 'tid',
      'table' => 'term_node',
      'field' => 'tid',
      'hierarchy' => 0,
      'relationship' => 'none',
      'reduce_duplicates' => 0,
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
    'role' => array(),
    'perm' => '',
  ));
  $handler->override_option('cache', array(
    'type' => 'time',
    'results_lifespan' => '60',
    'output_lifespan' => '60',
  ));
  $handler->override_option('items_per_page', 36);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'grouping' => 'title_1',
    'type' => 'ul',
  ));
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->override_option('arguments', array(
    'title' => array(
      'default_action' => 'ignore',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'php',
      'validate_fail' => 'ignore',
      'glossary' => 1,
      'limit' => '1',
      'case' => 'upper',
      'path_case' => 'lower',
      'transform_dash' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'default_argument_user' => 0,
      'default_argument_fixed' => 'a',
      'default_argument_php' => '',
      'validate_argument_vocabulary' => array(
        '1' => 0,
        '5' => 0,
        '4' => 0,
        '2' => 0,
        '3' => 0,
        '6' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_php' => 'if ($argument == \'numeric\') {
                          $view->query->add_where(0, "SUBSTR(node.title, 1, 1) IN (\'1\', \'2\', \'3\', \'4\', \'5\', \'6\', \'7\', \'8\', \'9\', \'0\')");
                          return FALSE;
                        }
                        else {
                          return TRUE;
                        }',
      'override' => array(
        'button' => 'Use default',
      ),
      'default_options_div_prefix' => '',
      'validate_argument_node_type' => array(
        'poll' => 0,
        'album' => 0,
        'artist' => 0,
        'award' => 0,
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
    ),
  ));
  $handler->override_option('items_per_page', 0);
  $handler->override_option('path', 'artist_directory');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => 'Glossary',
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
  $handler = $view->new_display('attachment', 'Attachment', 'attachment');
  $handler->override_option('arguments', array(
    'title' => array(
      'default_action' => 'summary asc',
      'style_plugin' => 'unformatted_summary',
      'style_options' => array(
        'count' => 1,
        'override' => 0,
        'items_per_page' => '25',
        'inline' => 1,
        'separator' => ' | ',
      ),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'glossary' => 1,
      'limit' => '1',
      'case' => 'upper',
      'path_case' => 'lower',
      'transform_dash' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'default_argument_user' => 0,
      'default_argument_fixed' => 'a',
      'validate_argument_vocabulary' => array(),
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('attachment_position', 'before');
  $handler->override_option('inherit_arguments', 0);
  $handler->override_option('inherit_exposed_filters', FALSE);
  $handler->override_option('inherit_pager', FALSE);
  $handler->override_option('render_pager', TRUE);
  $handler->override_option('displays', array(
    'default' => 'default',
    'page' => 'page',
  ));
  $views[$view->name] = $view;

  /*
   * View 'discography_track_ratings'
   */
  $view = new view;
  $view->name = 'discography_track_ratings';
  $view->description = 'A listing of tracks and votes for a user and album.';
  $view->tag = 'sonybmg_discography';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'nid' => array(
      'label' => 'Nid',
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'field_album_nid' => array(
      'default_action' => 'empty',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'field_album_nid',
      'table' => 'node_data_field_album',
      'field' => 'field_album_nid',
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'poll' => 0,
        'album' => 0,
        'artist' => 0,
        'award' => 0,
        'blog' => 0,
        'buddy_icon' => 0,
        'comment' => 0,
        'date' => 0,
        'fan' => 0,
        'feed' => 0,
        'forum' => 0,
        'forum_reply' => 0,
        'news' => 0,
        'official_photo' => 0,
        'page' => 0,
        'photo' => 0,
        'podcast_episode' => 0,
        'podcast_series' => 0,
        'review' => 0,
        'track' => 0,
        'wallpaper' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '1' => 0,
        '7' => 0,
        '5' => 0,
        '4' => 0,
        '2' => 0,
        '3' => 0,
        '6' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_php' => '',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
        '4' => 0,
        '5' => 0,
      ),
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_node_flag_name' => '*relationship*',
      'validate_argument_node_flag_test' => 'flaggable',
      'validate_argument_node_flag_id_type' => 'id',
      'validate_argument_user_flag_name' => '*relationship*',
      'validate_argument_user_flag_test' => 'flaggable',
      'validate_argument_user_flag_id_type' => 'id',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'track' => 'track',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => 'type_op',
        'label' => 'Node: Type',
        'use_operator' => FALSE,
        'identifier' => 'type',
        'remember' => FALSE,
        'single' => TRUE,
        'optional' => TRUE,
        'reduce' => FALSE,
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
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
  $handler->override_option('items_per_page', 0);
  $views[$view->name] = $view;

  /*
   * View 'music_albums'
   */
  $view = new view;
  $view->name = 'music_albums';
  $view->description = 'Displays artist discography';
  $view->tag = 'sonybmg_discography';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'Title',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'field_album_cover_fid' => array(
      'label' => '',
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'preview_default',
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
    ),
  ));
  $handler->override_option('sorts', array(
    'field_release_date_0_value' => array(
      'order' => 'DESC',
      'id' => 'field_release_date_0_value',
      'table' => 'node_data_field_release_date_0',
      'field' => 'field_release_date_0_value',
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
    'type' => 'time',
    'results_lifespan' => '60',
    'output_lifespan' => '60',
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

  /*
   * View 'music_favorites'
   */
  $view = new view;
  $view->name = 'music_favorites';
  $view->description = 'View for bookmark: favorite tracks';
  $view->tag = 'sonybmg_discography';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'flag_content_rel' => array(
      'label' => 'Favorite',
      'required' => 1,
      'flag' => 'favorites',
      'user_scope' => 'current',
      'id' => 'flag_content_rel',
      'table' => 'node',
      'field' => 'flag_content_rel',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'title' => array(
      'label' => 'Song Title',
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_album_nid' => array(
      'label' => '',
      'link_to_node' => 1,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_album_nid',
      'table' => 'node_data_field_album',
      'field' => 'field_album_nid',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'ops' => array(
      'label' => 'Flag link',
      'exclude' => 0,
      'id' => 'ops',
      'table' => 'flag_content',
      'field' => 'ops',
      'relationship' => 'flag_content_rel',
    ),
  ));
  $handler->override_option('filters', array(
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
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
    'role' => array(),
    'perm' => '',
  ));
  $handler->override_option('cache', array(
    'type' => 'time',
    'results_lifespan' => '60',
    'output_lifespan' => '60',
  ));
  $handler->override_option('title', 'Favorite Tracks');
  $handler->override_option('use_ajax', TRUE);
  $handler->override_option('items_per_page', 40);
  $handler->override_option('use_pager', 'mini');
  $handler->override_option('style_plugin', 'table');
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $views[$view->name] = $view;

  /*
   * View 'music_tracks'
   */
  $view = new view;
  $view->name = 'music_tracks';
  $view->description = 'Album track listing';
  $view->tag = 'sonybmg_discography';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'votingapi_cache' => array(
      'label' => 'Average results',
      'required' => 0,
      'votingapi' => array(
        'value_type' => 'percent',
        'tag' => 'vote',
        'function' => 'average',
      ),
      'id' => 'votingapi_cache',
      'table' => 'node',
      'field' => 'votingapi_cache',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'field_track_number_value' => array(
      'id' => 'field_track_number_value',
      'table' => 'node_data_field_track_number',
      'field' => 'field_track_number_value',
    ),
    'nid' => array(
      'label' => 'Nid',
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'Title',
      'link_to_node' => 0,
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
    'field_audio_file_url_value' => array(
      'id' => 'field_audio_file_url_value',
      'table' => 'node_data_field_audio_file_url',
      'field' => 'field_audio_file_url_value',
    ),
    'value' => array(
      'label' => 'Average rating',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'appearance' => '',
      'exclude' => 0,
      'id' => 'value',
      'table' => 'votingapi_cache',
      'field' => 'value',
      'relationship' => 'votingapi_cache',
    ),
    'field_disc_number_value' => array(
      'label' => '',
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_disc_number_value',
      'table' => 'node_data_field_disc_number',
      'field' => 'field_disc_number_value',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'field_disc_number_value' => array(
      'order' => 'ASC',
      'id' => 'field_disc_number_value',
      'table' => 'node_data_field_disc_number',
      'field' => 'field_disc_number_value',
      'relationship' => 'none',
    ),
    'field_track_number_value' => array(
      'order' => 'ASC',
      'id' => 'field_track_number_value',
      'table' => 'node_data_field_track_number',
      'field' => 'field_track_number_value',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'field_album_nid' => array(
      'default_action' => 'empty',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => 'Track listing for %1',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'id' => 'field_album_nid',
      'table' => 'node_data_field_album',
      'field' => 'field_album_nid',
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'validate_argument_node_type' => array(
        'album' => 0,
        'blog' => 0,
        'news' => 0,
        'review' => 0,
        'track' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'track' => 'track',
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
  ));
  $handler->override_option('access', array(
    'type' => 'none',
    'role' => array(),
    'perm' => '',
  ));
  $handler->override_option('cache', array(
    'type' => 'time',
    'results_lifespan' => '60',
    'output_lifespan' => '60',
  ));
  $handler->override_option('items_per_page', 0);
  $handler->override_option('style_options', array(
    'grouping' => 'field_disc_number_value',
  ));
  $views[$view->name] = $view;

  /*
   * View 'simple_search'
   */
  $view = new view;
  $view->name = 'simple_search';
  $view->description = 'A simple search for albums geared for easy use for the user.';
  $view->tag = 'sonybmg_discography';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'album' => 'album',
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
    'field_artists_noderef_nid' => array(
      'operator' => 'or',
      'value' => array(),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'field_artists_noderef_nid_op',
        'identifier' => 'field_artists_noderef_nid',
        'label' => 'Content: Artists (field_artists_noderef)',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 0,
      ),
      'id' => 'field_artists_noderef_nid',
      'table' => 'node_data_field_artists_noderef',
      'field' => 'field_artists_noderef_nid',
      'relationship' => 'none',
      'reduce_duplicates' => 0,
    ),
    'title' => array(
      'operator' => 'contains',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'title_op',
        'identifier' => 'title',
        'label' => 'Node: Title',
        'optional' => 1,
        'remember' => 0,
      ),
      'case' => 1,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'date_filter' => array(
      'operator' => '=',
      'value' => array(
        'value' => NULL,
        'min' => NULL,
        'max' => NULL,
        'default_date' => '',
        'default_to_date' => '',
      ),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'date_filter_op',
        'identifier' => 'date_filter',
        'label' => 'Date: Date',
        'optional' => 1,
        'remember' => 0,
      ),
      'date_fields' => array(
        'node_data_field_release_date.field_release_date_value' => 'node_data_field_release_date.field_release_date_value',
      ),
      'granularity' => 'year',
      'form_type' => 'date_select',
      'default_date' => '',
      'default_to_date' => '',
      'id' => 'date_filter',
      'table' => 'node',
      'field' => 'date_filter',
      'relationship' => 'none',
    ),
    'tid' => array(
      'operator' => 'or',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'operator' => 'tid_op',
        'label' => 'Taxonomy: Term',
        'use_operator' => 0,
        'identifier' => 'tid',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
      ),
      'type' => 'select',
      'vid' => '5',
      'id' => 'tid',
      'table' => 'term_node',
      'field' => 'tid',
      'hierarchy' => 0,
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
      'reduce_duplicates' => 0,
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
  $handler->override_option('items_per_page', 20);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'type' => 'ul',
  ));
  $handler->override_option('row_plugin', 'node');
  $handler->override_option('row_options', array(
    'teaser' => 1,
    'links' => 1,
    'comments' => 0,
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'simple_search');
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
    'name' => 'navigation',
  ));
  $views[$view->name] = $view;

  /*
   * View 'track_album_buyit'
   */
  $view = new view;
  $view->name = 'track_album_buyit';
  $view->description = 'album and buy block for track nodes';
  $view->tag = 'sonybmg_discography';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'field_album_nid' => array(
      'label' => 'Album',
      'required' => 1,
      'delta' => -1,
      'id' => 'field_album_nid',
      'table' => 'node_data_field_album',
      'field' => 'field_album_nid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'field_album_cover_fid' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '%1',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 1,
      'label_type' => 'none',
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
      'relationship' => 'field_album_nid',
    ),
    'field_album_nid' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_album_nid',
      'table' => 'node_data_field_album',
      'field' => 'field_album_nid',
      'relationship' => 'none',
    ),
    'field_album_download_links_url' => array(
      'label' => 'Buy it',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_album_download_links_url',
      'table' => 'node_data_field_album_download_links',
      'field' => 'field_album_download_links_url',
      'relationship' => 'field_album_nid',
    ),
  ));
  $handler->override_option('arguments', array(
    'nid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'node',
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
        'forum' => 0,
        'forum_reply' => 0,
        'global_fan_fiction' => 0,
        'landingpage' => 0,
        'news' => 0,
        'official_photo' => 0,
        'page' => 0,
        'photo' => 0,
        'review' => 0,
        'track' => 0,
        'wallpaper' => 0,
        'wallpaper_usersubmitted' => 0,
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
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
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
        'track' => 'track',
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
  ));
  $handler->override_option('cache', array(
    'type' => 'time',
    'results_lifespan' => '60',
    'output_lifespan' => '60',
  ));
  $handler->override_option('items_per_page', 1);
  $views[$view->name] = $view;

  return $views;
}


