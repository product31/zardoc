<?php
// $Id$

/**
 * @file
 * file_description
 */
 
$content[type]  = array (
  'name' => 'Official photo',
  'type' => 'official_photo',
  'description' => 'Upload official pictures.',
  'title_label' => 'Title',
  'body_label' => 'Caption',
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
  'language_content_type' => 0,
  'upload' => 1,
  'comment' => 2,
  'comment_type' => 'comment',
  'comment_view' => 'sonybmg_nodecomments',
  'usernodes_limit' => 0,
  'i18n_node' => 1,
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
    'field_photo' => false,
    'field_photographer_first' => false,
    'field_photographer_last' => false,
  ),
  'old_type' => 'official_photo',
  'orig_type' => 'official_photo',
  'module' => 'node',
  'custom' => '1',
  'modified' => '1',
  'locked' => '1',
  'fivestar' => 1,
  'fivestar_stars' => '5',
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
  'fivestar_style' => 'smart',
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
    'label' => 'Photo',
    'field_name' => 'field_photo',
    'type' => 'filefield',
    'widget_type' => 'imagefield_widget',
    'change' => 'Change basic information',
    'weight' => '-2',
    'file_extensions' => 'jpg jpeg png gif',
    'progress_indicator' => 'bar',
    'file_path' => '',
    'max_filesize_per_file' => '',
    'max_filesize_per_node' => '',
    'max_resolution' => '1600x1600',
    'min_resolution' => 0,
    'custom_alt' => 0,
    'alt' => '',
    'custom_title' => 0,
    'title_type' => 'textfield',
    'title' => '',
    'use_default_image' => 0,
    'default_image_upload' => '',
    'default_image' => '',
    'description' => 'Your photo size cannot be larger than 1 MB.  If your photo is larger than 1 MB, you will receive a "photo is required" error message.  If this happens, please resize your photo and resubmit.',
    'required' => 1,
    'multiple' => '0',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'op' => 'Save field settings',
    'module' => 'filefield',
    'widget_module' => 'imagefield',
    'columns' => 
    array (
      'fid' => 
      array (
        'type' => 'int',
        'not null' => false,
        'views' => true,
      ),
      'list' => 
      array (
        'type' => 'int',
        'size' => 'tiny',
        'not null' => false,
        'views' => true,
      ),
      'data' => 
      array (
        'type' => 'text',
        'serialize' => true,
        'views' => true,
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
        'format' => '1024x768_default',
      ),
      'full' => 
      array (
        'format' => '1024x768_default',
      ),
      4 => 
      array (
        'format' => 'image_plain',
      ),
    ),
  ),
  1 => 
  array (
    'label' => 'Photographer First Name',
    'field_name' => 'field_photographer_first',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '-1',
    'rows' => 1,
    'size' => 60,
    'description' => '',
    'default_value' => 
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_photographer_first' => 
      array (
        0 => 
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_photographer_first][0][value',
        ),
      ),
    ),
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
  2 => 
  array (
    'label' => 'Photographer Last Name',
    'field_name' => 'field_photographer_last',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => 0,
    'rows' => 1,
    'size' => 60,
    'description' => '',
    'default_value' => 
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_photographer_last' => 
      array (
        0 => 
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_photographer_last][0][value',
        ),
      ),
    ),
    'required' => 0,
    'multiple' => '0',
    'text_processing' => 0,
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
