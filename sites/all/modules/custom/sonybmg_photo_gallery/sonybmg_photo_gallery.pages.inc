<?php
// $Id$

/**
 * @file
 * Page callback include file for sonybmg_photo_gallery module
 *
 * These functions are responsible for building specific photo gallery pages, 
 * and as such dont need to be loaded for non-photo-gallery page requests. This
 * file will be loaded automatically by the drupal menu system.
 */

function sonybmg_photo_gallery_main_page() {
  return theme('sonybmg_photo_gallery_main_page');
}

function theme_sonybmg_photo_gallery_main_page() {
  return "<!-- Photo gallery landing page -->";
}

function sonybmg_photo_gallery_supersize_page($nid) {
  $node = node_load($nid);
  if (!$node || !in_array($node->type, array('photo', 'official_photo'))) {
    return drupal_not_found();
  }

  $title = check_plain($node->title);
  $photo = $GLOBALS['base_url'] .'/'. $node->field_photo[0]['filepath'];

  $block = (object) module_invoke('block', 'block', 'view', variable_get('sonybmg_ad_sidebar_block', 4));
  $block->module = 'block';
  $block->delta = variable_get('sonybmg_ad_sidebar_block', 4);
  $block->subject = '';
  $ad1 = $block->content ? theme('block', $block) : '';

  $block = (object) module_invoke('block', 'block', 'view', variable_get('sonybmg_ad_sidebar_block', 4));
  $block->module = 'block';
  $block->delta = variable_get('sonybmg_ad_sidebar_block', 4);
  $block->subject = '';
  $ad2 = $block->content ? theme('block', $block) : '';

  print theme('sonybmg_photo_gallery_supersize_page', $photo, $title, $ad1, $ad2);
}

function theme_sonybmg_photo_gallery_supersize_page($photo, $title, $ad1, $ad2) {
  $output = <<<EOF
  <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
  <html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
  <head>
    <title>$title</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <style type="text/css">
    .block { float: left; }
    .image { clear: left; }
  </style>
  </head>
  <body>
  <div class="image">
    <img src="$photo" alt="$title" />
  </div>
  </body>
  </html>
EOF;
  return $output;
}

function sonybmg_photo_gallery_pager_ajax($nid, $count = 7) {
  $page = $_GET['page'] ? $_GET['page'] : 0;
  $event_id = $_GET['eid'];

  drupal_set_header('Content-type: text/html');
  print sonybmg_photo_gallery_pager($nid, $count, $page, $event_id);
  exit();
}

