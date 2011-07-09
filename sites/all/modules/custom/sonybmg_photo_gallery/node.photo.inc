<?php
// $Id$

/**
 * @file
 * file_description
 */
 
$content[type]  = array (
  'name' => 'Photo',
  'type' => 'photo',
  'description' => 'Upload your pictures.',
  'title_label' => 'Title',
  'body_label' => 'Caption',
  'min_word_count' => '0',
  'help' => '',
  'node_options' => 
  array (
    'status' => true,
    'moderate' => true,
    'promote' => false,
    'sticky' => false,
    'revision' => false,
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
    'field_verify_ownership' => false,
  ),
  'old_type' => 'photo',
  'orig_type' => 'photo',
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
    'weight' => '-4',
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
    'label' => 'Copyright holder',
    'field_name' => 'field_verify_ownership',
    'type' => 'number_integer',
    'widget_type' => 'optionwidgets_onoff',
    'change' => 'Change basic information',
    'weight' => '-3',
    'description' => '',
    'default_value' => 
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_verify_ownership' => 
      array (
        'value' => false,
      ),
    ),
    'required' => 1,
    'multiple' => '0',
    'min' => '',
    'max' => '',
    'prefix' => '',
    'suffix' => '',
    'allowed_values' => '0|n/a
1|I have the right to distribute this photo and it does not violate the <a href="http://sonymusic.com/termsandconditions.html">Terms of Use</a>',
    'allowed_values_php' => '',
    'op' => 'Save field settings',
    'module' => 'number',
    'widget_module' => 'optionwidgets',
    'columns' => 
    array (
      'value' => 
      array (
        'type' => 'int',
        'not null' => false,
        'sortable' => true,
      ),
    ),
    'display_settings' => 
    array (
      4 => 
      array (
        'format' => 'hidden',
      ),
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
