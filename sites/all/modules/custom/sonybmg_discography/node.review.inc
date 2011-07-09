<?php
// $Id$

/**
 * @file
 * file_description
 */

$content[type]  = array (
  'name' => 'Review',
  'type' => 'review',
  'description' => 'Reviews give a rating to another piece of content.',
  'title_label' => 'Title',
  'body_label' => 'Review',
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
  'upload' => '1',
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
    'comment' => false,
    'files' => false,
    'field_rating' => false,
  ),
  'old_type' => 'review',
  'orig_type' => 'review',
  'module' => 'node',
  'custom' => '1',
  'modified' => '1',
  'locked' => '0',
  'comment' => 0,
  'comment_default_mode' => '2',
  'comment_default_order' => '1',
  'comment_default_per_page' => '50',
  'comment_controls' => '3',
  'comment_anonymous' => 0,
  'comment_subject_field' => '0',
  'comment_preview' => '0',
  'comment_form_location' => '1',
  'node_comment' => 0,
  'node_comment_type' => 'comment',
  'node_comment_plural' => 'comments',
  'node_comment_view' => 'nodecomments',
  'node_comment_topic_review' => '1',
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
    'label' => 'Rating',
    'field_name' => 'field_rating',
    'type' => 'fivestar',
    'widget_type' => 'stars',
    'change' => 'Change basic information',
    'weight' => '-4',
    'allow_clear' => 1,
    'description' => '',
    'default_value' => 
    array (
      0 => 
      array (
        'rating' => 0,
        'target' => NULL,
        'axis' => '',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => NULL,
    'required' => 0,
    'multiple' => 0,
    'stars' => 5,
    'dynamic_target' => 'comment_target_nid',
    'php_target' => '',
    'axis' => '',
    'op' => 'Save field settings',
    'module' => 'fivestar',
    'widget_module' => 'fivestar',
    'columns' => 
    array (
      'rating' => 
      array (
        'type' => 'int',
        'unsigned' => true,
        'not null' => false,
        'sortable' => true,
      ),
      'target' => 
      array (
        'type' => 'int',
        'unsigned' => true,
        'not null' => false,
      ),
    ),
    'display_settings' => 
    array (
      'label' => 
      array (
        'format' => 'above',
      ),
      'teaser' => 
      array (
        'format' => 'default',
      ),
      'full' => 
      array (
        'format' => 'default',
      ),
      4 => 
      array (
        'format' => 'default',
      ),
    ),
  ),
);
