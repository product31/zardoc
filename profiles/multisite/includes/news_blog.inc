<?php
//TODO views_rss for news_blog feeds

function news_blog_info() {
  return array(
    'name' => st('News and Blog'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 10,
  );
}

function news_blog_modules() {
  return array('php', 'views', 'content', 'sonybmg', 'service_links');
}

function news_blog_task_list() {
  return array(
    'news_blog_content_types' => array(
      'message' => st('Created news and blog content types.'),
      'weight' => 0,
    ),
    'news_blog_content_type_settings' => array(
      'message'   => st('Initialized content type settings.'),
      'weight' => 0,
    ),
    'news_blog_dummy_content' => array(
      'message' => st('Created dummy content.'),
      'weight' => 0,
    ),
    'news_blog_service_links' => array(
      'message' => st('Configured service links.'),
      'weight' => 0,
    ),
    'news_blog_menu' => array(
      'message' => st('Created news menu item.'),
      'weight' => 0,
    ),
  );
}

function news_blog_content_types() {
  $path = drupal_get_path('module', 'sonybmg');
  install_content_copy_import_from_file($path .'/node.blog.inc');
  install_content_copy_import_from_file($path .'/node.news.inc');
}

/**
 * Initialize the custom content type settings
 */
function news_blog_content_type_settings() {
  $variable_settings = array();
  $variable_settings['blog'] = array(
    'node_comment' => 2,
    'comment_type' => 'comment',
    'comment_view' => 'nodecomments',
    'comment_default_mode' => '2',
    'comment_subject_field' => '0',
  );

  $variable_settings['news'] = array(
    'node_comment' => 2,
    'comment_type' => 'comment',
    'comment_view' => 'nodecomments',
    'comment_default_mode' => '2',
    'comment_subject_field' => '0',
  );

  // rotate through our settings and populate the db.
  foreach ($variable_settings as $ct => $data) {
    foreach($data as $var => $val) {
      variable_set($var .'_'. $ct, $val);
    }// end - foreach
  }// end - foreach
}


function news_blog_dummy_content() {
  module_load_include('inc', 'node', 'node.pages');
  module_load_include('inc', 'devel', 'devel_generate');

  $node = new stdClass();
  $node->type = 'blog';
  node_object_prepare($node);
  $node->status = 1;
  $node->title = devel_create_greeking(rand(1, 10), TRUE);
  $node->body = devel_create_content();
  $node->teaser = node_teaser($node->body);
  $node->promote = 1;
  $node->uid = 1;
  $node->filter = variable_get('filter_default_format', 1);
  $node->format = FILTER_FORMAT_DEFAULT;
  $node->language = '';
  $node->created = time();

  node_save($node);
  $contentids[$node->type] = $node->nid;

  $node = new stdClass();
  $node->type = 'news';
  node_object_prepare($node);
  $node->status = 1;
  $node->title = devel_create_greeking(rand(1, 10), TRUE);
  $node->body = devel_create_content();
  $node->teaser = node_teaser($node->body);
  $node->promote = 1;
  $node->uid = 1;
  $node->filter = variable_get('filter_default_format', 1);
  $node->format = FILTER_FORMAT_DEFAULT;
  $node->language = '';
  $node->created = time();

  node_save($node);
  $contentids[$node->type] = $node->nid;


  // Create sample comments for each type. 
  foreach ($contentids as $type => $contentid) {
    $node = new stdClass();
    $node->type = 'comment';
    node_object_prepare($node);
    $node->uid = 1;
    $node->title = devel_create_greeking(rand(1, 10), TRUE);
    $node->body = devel_create_content();
    $node->teaser = node_teaser($node->body);
    $node->filter = variable_get('filter_default_format', 1);
    $node->format = FILTER_FORMAT_DEFAULT;
    $node->language = '';
    $node->promote = 1;
    $node->created = time();

    $node->comment_target_nid = $contentid;
    $node->comment_target_cid = 0;

    node_save($node);
  }
}

function news_blog_service_links() {
  $everyone_perms = array('access service links');
  $admin_perms = array('access service links', 'administer service links');

  install_add_permissions(install_get_rid('anonymous user'), $everyone_perms);
  install_add_permissions(install_get_rid('authenticated user'), $everyone_perms);
  install_add_permissions(install_add_role('artist'), $admin_perms);
  install_add_permissions(install_add_role('moderator'), $admin_perms);

  variable_set('service_links_node_types', drupal_map_assoc(array('blog', 'news', 'official_photo', 'photo')));
  variable_set('service_links_show_delicious', 1);
  variable_set('service_links_show_digg', 1);
  variable_set('service_links_show_reddit', 1);
  variable_set('service_links_show_magnoliacom', 1);
  variable_set('service_links_show_newsvine', 1);
  variable_set('service_links_show_facebook', 1);
  variable_set('service_links_show_google', 1);
  variable_set('service_links_show_yahoo', 1);
  variable_set('service_links_show_yahoo_buzz', 1);
  variable_set('service_links_in_links', '3');
  variable_set('service_links_in_node', '0');
  variable_set('service_links_style', '3');
}

/**
 * Move menu item from navigation to primary links.
 */
function news_blog_menu() {
  install_menu_create_menu_item('news', 'News and Blog', $description = '', 'primary-links', $plid = 0, $weight = 0, 'views');
}