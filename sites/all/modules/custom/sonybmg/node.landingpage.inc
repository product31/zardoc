<?php
// $Id$

/**
 * @file
 * file_description
 */

$content[type]  = array (
  'name' => 'Landing Page',
  'type' => 'landingpage',
  'description' => '',
  'title_label' => 'Title',
  'body_label' => 'Body',
  'min_word_count' => '0',
  'help' => '',
  'node_options' =>
  array (
    'status' => true,
    'promote' => true,
    'sticky' => false,
    'revision' => false,
    'moderate' => false,
  ),
  'language_content_type' => '0',
  'upload' => 1,
  'comment' => '0',
  'comment_type' => 'comment',
  'comment_view' => 'nodecomments',
  'usernodes_limit' => '0',
  'i18n_node' => '1',
  'i18nsync_nodeapi' =>
  array (
    'author' => false,
    'status' => false,
    'promote' => false,
    'moderate' => false,
    'sticky' => false,
    'revision' => false,
    'parent' => false,
    'taxonomy' => false,
    'files' => false,
    'field_css' => false,
  ),
  'old_type' => 'landingpage',
  'orig_type' => '',
  'module' => 'node',
  'custom' => '1',
  'modified' => '1',
  'locked' => '0',
  'fivestar' => 0,
  'fivestar_stars' => 5,
  'fivestar_labels_enable' => 1,
  'fivestar_label_0' => 'Cancel rating',
  'fivestar_label_1' => 'Poor',
  'fivestar_label_2' => 'Okay',
  'fivestar_label_3' => 'Good',
  'fivestar_label_4' => 'Great',
  'fivestar_label_5' => 'Awesome',
  'fivestar_label_6' => 'Give it @star/@count',
  'fivestar_label_7' => 'Give it @star/@count',
  'fivestar_label_8' => 'Give it @star/@count',
  'fivestar_label_9' => 'Give it @star/@count',
  'fivestar_label_10' => 'Give it @star/@count',
  'fivestar_style' => 'average',
  'fivestar_text' => 'dual',
  'fivestar_title' => 1,
  'fivestar_feedback' => 1,
  'fivestar_unvote' => 0,
  'fivestar_position_teaser' => 'hidden',
  'fivestar_position' => 'below',
);
$content[fields]  = array (
  0 =>
  array (
    'label' => 'CSS',
    'field_name' => 'field_css',
    'type' => 'text',
    'widget_type' => 'text_textarea',
    'change' => 'Change basic information',
    'weight' => '-3',
    'rows' => '5',
    'size' => 60,
    'description' => '',
    'default_value' =>
    array (
      0 =>
      array (
        'value' => '',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => NULL,
    'required' => 0,
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'op' => 'Save field settings',
    'module' => 'text',
    'widget_module' => 'text',
    'columns' =>
    array (
      'value' =>
      array (
        'type' => 'text',
        'size' => 'big',
        'not null' => false,
        'sortable' => true,
      ),
    ),
    'display_settings' =>
    array (
      'label' =>
      array (
        'format' => 'hidden',
      ),
      'teaser' =>
      array (
        'format' => 'hidden',
      ),
      'full' =>
      array (
        'format' => 'hidden',
      ),
    ),
  ),
);
$content[extra]  = array (
  'title' => '-5',
  'body_field' => '-4',
  'menu' => '-2',
);

