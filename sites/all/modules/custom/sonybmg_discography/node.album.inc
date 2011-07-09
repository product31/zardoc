<?php
// $Id$

/**
 * @file
 * file_description
 */
 
$content[type]  = array (
  'name' => 'Album',
  'type' => 'album',
  'description' => 'An album by the artist.',
  'title_label' => 'Album title',
  'body_label' => 'Description',
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
    'field_artist' => false,
    'field_album_site_url' => false,
    'field_album_video_url' => false,
    'field_album_cover' => false,
    'field_band_member' => false,
    'field_release_date' => false,
    'field_producer' => false,
    'field_label' => false,
    'field_album_download_links' => false,
    'field_liner_notes' => false,
  ),
  'old_type' => 'album',
  'orig_type' => 'album',
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
  'node_comment_type' => 'review',
  'node_comment_plural' => 'comments',
  'node_comment_view' => 'nodecomments',
  'node_comment_topic_review' => '1',
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
  'fivestar_style' => 'average',
  'fivestar_text' => 'dual',
  'fivestar_title' => 1,
  'fivestar_feedback' => 0,
  'fivestar_unvote' => 0,
  'fivestar_position_teaser' => 'hidden',
  'fivestar_position' => 'below',
);
$content[fields]  = array (
  0 => 
  array (
    'label' => 'Artist',
    'field_name' => 'field_artist',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '-4',
    'rows' => 1,
    'size' => 60,
    'description' => '',
    'default_value' => 
    array (
      0 => 
      array (
        'value' => '',
        '_error_element' => 'default_value_widget][field_artist][0][value',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => NULL,
    'required' => 1,
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
  1 => 
  array (
    'label' => 'Album site URL',
    'field_name' => 'field_album_site_url',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '-3',
    'rows' => 1,
    'size' => 60,
    'description' => '',
    'default_value' => 
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_album_site_url' => 
      array (
        0 => 
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_album_site_url][0][value',
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
    'label' => 'Album video URL',
    'field_name' => 'field_album_video_url',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '-2',
    'rows' => 1,
    'size' => 60,
    'description' => '',
    'default_value' => 
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_album_video_url' => 
      array (
        0 => 
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_album_video_url][0][value',
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
  3 => 
  array (
    'label' => 'Band Members',
    'field_name' => 'field_band_member',
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
      'field_band_member' => 
      array (
        0 => 
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_band_member][0][value',
        ),
      ),
    ),
    'required' => 1,
    'multiple' => '1',
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
  4 => 
  array (
    'label' => 'Album Cover',
    'field_name' => 'field_album_cover',
    'type' => 'filefield',
    'widget_type' => 'imagefield_widget',
    'change' => 'Change basic information',
    'weight' => 0,
    'file_extensions' => 'jpg jpeg png gif',
    'progress_indicator' => 'bar',
    'file_path' => '',
    'max_filesize_per_file' => '',
    'max_filesize_per_node' => '',
    'max_resolution' => 0,
    'min_resolution' => 0,
    'custom_alt' => 0,
    'alt' => '',
    'custom_title' => 0,
    'title_type' => 'textfield',
    'title' => '',
    'use_default_image' => 0,
    'default_image_upload' => '',
    'default_image' => '',
    'description' => '',
    'required' => 0,
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
        'format' => 'image_plain',
      ),
      'full' => 
      array (
        'format' => 'image_plain',
      ),
      4 => 
      array (
        'format' => 'image_plain',
      ),
    ),
  ),
  5 => 
  array (
    'label' => 'Release Date',
    'field_name' => 'field_release_date',
    'type' => 'date',
    'widget_type' => 'date_select',
    'change' => 'Change basic information',
    'weight' => '2',
    'default_value' => 'blank',
    'default_value2' => 'same',
    'default_value_code' => '',
    'default_value_code2' => '',
    'input_format' => 'Y-m-d H:i:s',
    'input_format_custom' => '',
    'year_range' => '-50:+3',
    'increment' => '1',
    'advanced' => 
    array (
      'label_position' => 'above',
      'text_parts' => 
      array (
        'year' => 0,
        'month' => 0,
        'day' => 0,
        'hour' => 0,
        'minute' => 0,
        'second' => 0,
      ),
    ),
    'label_position' => 'above',
    'text_parts' => 
    array (
    ),
    'description' => '',
    'required' => 1,
    'multiple' => '0',
    'repeat' => 0,
    'todate' => '',
    'granularity' => 
    array (
      'year' => 'year',
      'month' => 'month',
      'day' => 'day',
    ),
    'default_format' => '',
    'tz_handling' => 'none',
    'timezone_db' => 'America/New_York',
    'op' => 'Save field settings',
    'module' => 'date',
    'widget_module' => 'date',
    'columns' => 
    array (
      'value' => 
      array (
        'type' => 'varchar',
        'length' => 20,
        'not null' => false,
        'sortable' => true,
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
  6 => 
  array (
    'label' => 'Producers',
    'field_name' => 'field_producer',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '3',
    'rows' => 1,
    'size' => 60,
    'description' => '',
    'default_value' => 
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_producer' => 
      array (
        0 => 
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_producer][0][value',
        ),
      ),
    ),
    'required' => 0,
    'multiple' => '1',
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
  7 => 
  array (
    'label' => 'Label',
    'field_name' => 'field_label',
    'type' => 'text',
    'widget_type' => 'optionwidgets_select',
    'change' => 'Change basic information',
    'weight' => '5',
    'description' => '',
    'default_value' => 
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_label' => 
      array (
        'value' => '',
      ),
    ),
    'required' => 0,
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => 'Columbia|Columbia
    Epic|Epic
    J/Arista|J/Arista
    Legacy Recordings|Legacy Recordings
    Masterworks
    Nashville|Nashville
    Provident|Provident
    RCA|RCA
    Sony Wonder|Sony Wonder
    Zomba|Zomba',
    'allowed_values_php' => '',
    'op' => 'Save field settings',
    'module' => 'text',
    'widget_module' => 'optionwidgets',
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
  8 => 
  array (
    'label' => 'Album download links',
    'field_name' => 'field_album_download_links',
    'type' => 'link',
    'widget_type' => 'link',
    'change' => 'Change basic information',
    'weight' => '6',
    'description' => 'Enter URLs and link text for purchasing this song\'s album from a Music Download Service. ',
    'default_value' => 
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_album_download_links' => 
      array (
        0 => 
        array (
          'url' => '',
          'title' => '',
        ),
      ),
    ),
    'required' => 0,
    'multiple' => '1',
    'url' => 0,
    'title' => 'required',
    'title_value' => '',
    'enable_tokens' => 0,
    'display' => 
    array (
      'url_cutoff' => '80',
    ),
    'attributes' => 
    array (
      'target' => 'default',
      'rel' => '',
      'class' => '',
    ),
    'op' => 'Save field settings',
    'module' => 'link',
    'widget_module' => 'link',
    'columns' => 
    array (
      'url' => 
      array (
        'type' => 'varchar',
        'length' => 255,
        'not null' => false,
        'sortable' => true,
      ),
      'title' => 
      array (
        'type' => 'varchar',
        'length' => 255,
        'not null' => false,
        'sortable' => true,
      ),
      'attributes' => 
      array (
        'type' => 'text',
        'size' => 'medium',
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
  9 => 
  array (
    'label' => 'Liner Notes',
    'field_name' => 'field_liner_notes',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '7',
    'rows' => 1,
    'size' => 60,
    'description' => '',
    'default_value' => 
    array (
    ),
    'default_value_php' => '',
    'default_value_widget' => 
    array (
      'field_liner_notes' => 
      array (
        0 => 
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_liner_notes][0][value',
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
);
