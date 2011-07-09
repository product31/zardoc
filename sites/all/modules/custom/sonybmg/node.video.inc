<?php
$content['type']  = array (
  'name' => 'Video',
  'type' => 'video',
  'description' => 'Post videos from youtube, brightcove or other video providers',
  'title_label' => 'Title',
  'body_label' => '',
  'min_word_count' => '0',
  'help' => '',
  'node_options' =>
  array (
    'status' => true,
    'promote' => false,
    'sticky' => false,
    'revision' => false,
    'moderate' => false,
  ),
  'language_content_type' => '2',
  'upload' => '0',
  'usernodes_limit' => '0',
  'i18n_node' => '3',
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
    'field_video' => false,
    'field_progressive_url' => false,
  ),
  'old_type' => 'video',
  'orig_type' => '',
  'module' => 'node',
  'custom' => '1',
  'modified' => '1',
  'locked' => '0',
  'comment' => 0,
  'comment_default_mode' => '4',
  'comment_default_order' => '1',
  'comment_default_per_page' => '50',
  'comment_controls' => '3',
  'comment_anonymous' => 0,
  'comment_subject_field' => '1',
  'comment_preview' => '0',
  'comment_form_location' => '0',
  'node_comment' => '2',
  'node_comment_type' => 'review',
  'node_comment_plural' => 'comments',
  'node_comment_view' => 'nodecomments',
  'node_comment_topic_review' => '0',
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
  'fivestar_feedback' => 1,
  'fivestar_unvote' => 0,
  'fivestar_position_teaser' => 'hidden',
  'fivestar_position' => 'below',
  'feedapi' =>
  array (
    'enabled' => 0,
    'refresh_on_create' => 0,
    'update_existing' => 1,
    'skip' => 0,
    'items_delete' => '0',
    'parsers' =>
    array (
      'feedapi_eparser' =>
      array (
        'enabled' => 0,
        'weight' => '0',
      ),
    ),
    'processors' =>
    array (
      'feedapi_node' =>
      array (
        'enabled' => 0,
        'weight' => '0',
        'content_type' => 'poll',
        'input_format' => '1',
        'author' => 'adminn',
        'language' => '',
        'node_date' => 'feed',
        'promote' => '3',
        'x_dedupe' => '0',
      ),
    ),
  ),
);
$content['fields']  = array (
  0 =>
  array (
    'label' => 'Video',
    'field_name' => 'field_video',
    'type' => 'emvideo',
    'widget_type' => 'emvideo_textfields',
    'change' => 'Change basic information',
    'weight' => '-4',
    'providers' =>
    array (
      'brightcove3' => true,
      'youtube' => true,
      0 => 1,
      'archive' => false,
      'bliptv' => false,
      'dailymotion' => false,
      'google' => false,
      'guba' => false,
      'imeem' => false,
      'lastfm' => false,
      'livevideo' => false,
      'metacafe' => false,
      'myspace' => false,
      'revver' => false,
      'sevenload' => false,
      'spike' => false,
      'tudou' => false,
      'twistage' => false,
      'ustream' => false,
      'ustreamlive' => false,
      'vimeo' => false,
      'voicethread' => false,
      'yahoomusic' => false,
      'zzz_custom_url' => false,
    ),
    'video_width' => '480',
    'video_height' => '385',
    'video_autoplay' => '',
    'preview_width' => '480',
    'preview_height' => '385',
    'preview_autoplay' => '',
    'thumbnail_width' => '200',
    'thumbnail_height' => '154',
    'thumbnail_default_path' => '',
    'thumbnail_link_title' => 'See video',
    'description' => '',
    'default_value' =>
    array (
      0 =>
      array (
        'embed' => '',
        'value' => '',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => NULL,
    'required' => 0,
    'multiple' => '0',
    'op' => 'Save field settings',
    'module' => 'emvideo',
    'widget_module' => 'emvideo',
    'columns' =>
    array (
      'embed' =>
      array (
        'type' => 'text',
        'size' => 'big',
        'not null' => false,
        'sortable' => true,
      ),
      'value' =>
      array (
        'type' => 'varchar',
        'length' => 255,
        'not null' => false,
        'sortable' => true,
      ),
      'provider' =>
      array (
        'type' => 'varchar',
        'length' => 255,
        'not null' => false,
        'sortable' => true,
      ),
      'data' =>
      array (
        'type' => 'text',
        'size' => 'big',
        'not null' => false,
        'sortable' => false,
      ),
      'version' =>
      array (
        'description' => 'The version of the provider\'s data.',
        'type' => 'int',
        'unsigned' => true,
        'not null' => true,
        'default' => 0,
      ),
      'duration' =>
      array (
        'description' => 'Store the duration of a video in seconds.',
        'type' => 'int',
        'unsigned' => true,
        'not null' => true,
        'default' => 0,
      ),
    ),
    'display_settings' =>
    array (
      'weight' => '-4',
      'parent' => '',
      'label' =>
      array (
        'format' => 'hidden',
      ),
      'teaser' =>
      array (
        'format' => 'video_thumbnail',
        'exclude' => 0,
      ),
      'full' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      4 =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      2 =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      3 =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
  1 =>
  array (
    'label' => 'Progressive Download URL',
    'field_name' => 'field_progressive_url',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '1',
    'rows' => 5,
    'size' => '400',
    'description' => '',
    'default_value' =>
    array (
      0 =>
      array (
        'value' => '',
        '_error_element' => 'default_value_widget][field_progressive_url][0][value',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' =>
    array (
      'field_progressive_url' =>
      array (
        0 =>
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_progressive_url][0][value',
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
        'views' => true,
      ),
    ),
    'display_settings' =>
    array (
      'weight' => '1',
      'parent' => '',
      2 =>
      array (
        'format' => 'hidden',
        'exclude' => 1,
      ),
      3 =>
      array (
        'format' => 'hidden',
        'exclude' => 1,
      ),
      4 =>
      array (
        'format' => 'hidden',
        'exclude' => 1,
      ),
      'label' =>
      array (
        'format' => 'hidden',
      ),
      'teaser' =>
      array (
        'format' => 'hidden',
        'exclude' => 1,
      ),
      'full' =>
      array (
        'format' => 'hidden',
        'exclude' => 1,
      ),
      'token' =>
      array (
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
  ),
);
$content['extra']  = array (
  'title' => '-5',
  'language' => '0',
  'menu' => '-3',
);

