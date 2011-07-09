<?php
// Windows is always like "we'll be like unix but make it obnoxious hidden and hard!"

/**
 * Implementation of hook_views_plugins().
 */
function azuki_views_plugins() {
  $path = drupal_get_path('module', 'azuki') . '/views';
  $tmp = array(
    'display' => array(
      'azuki_feed' => array(
        'title' => t('Azuki Feed'),
        'help' => t('Display the view as a feed, such as an RSS feed.'),
        'handler' => 'views_plugin_display_feed',
        'parent' => 'page', // so it knows to load the page plugin .inc file
        'uses hook menu' => TRUE,
        'use ajax' => FALSE,
        'use pager' => TRUE,
        'accept attachments' => FALSE,
        'admin' => t('Feed'),
        'help topic' => 'display-feed',
        'path' => drupal_get_path('module', 'views') . '/plugins',
      ),
    ),
    'style' => array(
      'azuki_rss' => array(
        'title' => t('Azuki RSS Feed'),
        'help' => t('Generates a Media RSS feed from a view, appropriate for use with the Azuki mobile platform.'),
        'handler' => 'azuki_plugin_style_rss',
        'uses row plugin' => TRUE,
        'parent' => 'rss',
        'type' => 'azuki_feed',
        'path' => $path,
        'theme' => 'azuki_rss',
        'theme path' => $path,
        //'help topic' => 'style-rss',
      ),
    ),
    'row' => array(
      'azuki_row' => array(
        'title' => t('Azuki RSS'),
        'help' => t('Output the node according to Azuki RSS specs.'),
        'handler' => 'azuki_plugin_row_rss',
        'parent' => 'node_rss',
        'path' => $path,
        'theme' => 'azuki_node_rss',
        'theme path' => $path,
        'base' => array('node'), // only works with 'node' as base.
        'uses options' => TRUE,
        'type' => 'azuki_feed',
      ),
    ),
  );
  // dpm($tmp);
  return $tmp;
}
