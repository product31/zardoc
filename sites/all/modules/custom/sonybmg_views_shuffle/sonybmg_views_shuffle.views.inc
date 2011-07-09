<?php
/**
 * @file sonybmg_views_shuffle.views.inc
 * @author Scott Nelson of This by Them <scott@thisbythem.com>
 */


function sonybmg_views_shuffle_views_plugins() {
  return array(
    'style' => array(
      'sony_shuffle_list' => array(
        'title' => t('Sony Shuffle'),
        'help' => t('Displays rows as a shuffleable HTML list.'),
        'path' => drupal_get_path('module', 'views') . '/plugins',
        'handler' => 'views_plugin_style_list',
        'theme' => 'sonybmg_views_shuffle_list',
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'help topic' => 'style-list',
      ),
    ),
  );
}