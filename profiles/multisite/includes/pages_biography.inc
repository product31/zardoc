<?php
/**
 * @file
 * Create our "biography" page.
 */
function pages_biography_info() {
  return array(
    'name' => st('Biography Section'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 0,
  );
}

/**
 * Required modules.
 */
function pages_biography_modules() {
  return array('menu', 'token', 'content', 'pathauto');
}

function pages_biography_task_list() {
  return array(
    'pages_biography_biography_page' => array(
      'message' => st('Created biography page section'),
      'weight' => 0,
    ),
    'pages_biography_menu' => array(
      'message' => st('Create biography menu item'),
      'weight' => 0,
    ),
  );
}

/**
 * Generate bio page.
 */
function pages_biography_biography_page() {

  $node = array(
    'type' => 'page',
    'uid' => 3,
    'language' => 'en',
    'title' => st('Biography'),
    'body' => st('Insert some text here for your band\'s biography page. <strong>HTML is okay!</strong>'),
    'path' => 'biography',
    'format' => 2,
    'field_sidebar_content' => array(
      '0' => array(
        'value' => pages_biography_default_sidebar_content(),
        'format' => 2,
      ),
    ),
  );
  
  $node = (object) $node;
  node_save($node);
}

/**
 * Our default sidebar content.
 */
function pages_biography_default_sidebar_content() {
  $output = '<div class="block" id="bio-pic"><img src="[336x336 band image]" class="reflected" />';
  $output .= 'THE BAND (left to right): <a href="/user/[bandmember1]">Band Member 1</a>, <a href="/user/[bandmember2]">Band Member 2</a>, <a href="/user/[bandmember3]">Band Member 3</a>';
  $output .= '<div class="photocredit">Photo by [photographer]</div></div>';
  $output .= '<div class="block" id="bio-members"><h2 class="title">BAND MEMBER BLOGS</h2><ul>';
  $output .= '<li><a href="user/[bandmember1]">[Band Member 1]</a>: [Lead Vocals]</li>';
  $output .= '<li><a href="user/[bandmember2]">[Band Member 2]</a>: [Drums]</li>';
  $output .= '<li><a href="user/[bandmember3]">[Band Member 3]</a>: [Guitar]</li>';
  $output .= '</ul></div>';

  $output .= '<div id="bio-links"><h2 class="title">Links</h2><ul>';
  $output .= '<li><a href="http://myspace.com/[bandname]">[Band] at MySpace</a></li>';
  $output .= '<li><a href="http://en.wikipedia.org/wiki/[bandname]">[Band] at Wikipedia</a></li>';
  $output .= '</ul></div>';

  return $output;
}

/**
 * Create menu item.
 */
function pages_biography_menu() {
  $path = drupal_get_normal_path('biography');
  install_menu_create_menu_item($path, 'Bio', NULL, 'Primary Links', 0, 2);
}
