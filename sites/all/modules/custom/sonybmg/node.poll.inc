<?php
$content[type] = array (
  'name' => 'Poll',
  'type' => 'poll',
  'description' => 'A <em>poll</em> is a question with a set of possible responses. A <em>poll</em>, once created, automatically provides a simple running count of the number of votes received for each response.',
  'title_label' => 'Question',
  'body_label' => '',
  'min_word_count' => 0,
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
  'comment' => 2,
  'comment_type' => '',
  'comment_view' => 'node_comments',
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
    'field_poll_image' => false,
  ),
  'old_type' => 'poll',
  'orig_type' => 'poll',
  'module' => 'poll',
  'custom' => false,
  'modified' => false,
  'locked' => true,
  'reset' => 'Reset to defaults',
);
$content[fields]  = array (
  0 =>
  array (
    'label' => 'Poll Image',
    'field_name' => 'field_poll_image',
    'type' => 'image',
    'widget_type' => 'image',
    'change' => 'Change basic information',
    'weight' => '-1',
    'max_resolution' => '1600x1600',
    'max_filesize' => 0,
    'image_path' => 'poll_images',
    'file_extensions' => 'jpg jpeg png gif',
    'custom_alt' => 0,
    'custom_title' => 0,
    'description' => 'Upload an image to be displayed with this poll.',
    'required' => 0,
    'multiple' => '0',
    'use_default_image' => 0,
    'default_image_upload' => '',
    'default_image' => '',
    'op' => 'Save field settings',
    'module' => 'imagefield',
    'widget_module' => 'imagefield',
    'columns' =>
    array (
      'fid' =>
      array (
        'type' => 'int',
        'not null' => true,
        'default' => '0',
      ),
      'title' =>
      array (
        'type' => 'varchar',
        'length' => 255,
        'not null' => true,
        'default' => '',
        'sortable' => true,
      ),
      'alt' =>
      array (
        'type' => 'varchar',
        'length' => 255,
        'not null' => true,
        'default' => '',
        'sortable' => true,
      ),
    ),
    'display_settings' =>
    array (
      'weight' => '-1',
      'parent' => '',
      'label' =>
      array (
        'format' => 'hidden',
      ),
      'teaser' =>
      array (
        'format' => 'thumbnail_default',
      ),
      'full' =>
      array (
        'format' => 'thumbnail_default',
      ),
      0 =>
      array (
        'format' => 'above',
      ),
      1 =>
      array (
        'format' => 'default',
      ),
      2 =>
      array (
        'format' => 'default',
      ),
      'token' =>
      array (
        'format' => 'default',
      ),
    ),
  ),
);
