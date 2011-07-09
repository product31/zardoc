<?php
// $Id: views_bonus_export.views.inc,v 1.3 2008/10/28 02:18:32 neclimdul Exp $
/**
 * @file
 * Views include file with views hooks.
 */

/**
 * Implementation of hook_views_plugins
 */
function views_bonus_export_views_plugins() {
  $path = drupal_get_path('module', 'views_bonus_export');
  return array(
    'style' => array(
      'views_csv' => array(
        'title' => t('CSV file'),
        'help' => t('Display the view as a comma seperated list.'),
        'path' => $path,
        'handler' => 'views_bonus_plugin_style_export_csv',
        'theme' => 'views_bonus_export_csv',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'feed',
      ),
      'views_doc' => array(
        'title' => t('DOC file'),
        'help' => t('Display the view as a doc file.'),
        'path' => $path,
        'handler' => 'views_bonus_plugin_style_export_doc',
        'theme' => 'views_bonus_export_doc',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'feed',
      ),
      'views_txt' => array(
        'title' => t('TXT file'),
        'help' => t('Display the view as a txt file.'),
        'path' => $path,
        'handler' => 'views_bonus_plugin_style_export_txt',
        'theme' => 'views_bonus_export_txt',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'feed',
      ),
      'views_xml' => array(
        'title' => t('XML file'),
        'help' => t('Display the view as a txt file.'),
        'path' => $path,
        'handler' => 'views_bonus_plugin_style_export_xml',
        'theme' => 'views_bonus_export_xml',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'feed',
      ),
    ),
  );
}

