<?php
// $Id$

/**
 * @file
 * file_description
 */

$content[type]  = array (
  'name' => 'Track',
  'type' => 'track',
  'description' => 'A track on an album.',
  'title_label' => 'Title',
  'body_label' => '',
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
  'comment' => 2,
  'comment_type' => 'review',
  'comment_view' => 'nodecomments',
  'old_type' => 'track',
  'orig_type' => 'track',
  'module' => 'node',
  'custom' => '1',
  'modified' => '1',
  'locked' => '0',
  'event_nodeapi' => 'never',
  'fivestar' => 1,
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
  'fivestar_feedback' => 0,
  'fivestar_unvote' => 0,
  'fivestar_position_teaser' => 'hidden',
  'fivestar_position' => 'below',
);
$content[fields]  = array (
  0 =>
  array (
    'label' => 'Album',
    'field_name' => 'field_album',
    'type' => 'nodereference',
    'widget_type' => 'nodereference_select',
    'change' => 'Change basic information',
    'weight' => '-4',
    'description' => 'Associate this track with an album.',
    'default_value_widget' =>
    array (
      'field_album' =>
      array (
        0 =>
        array (
          'nid' => '',
          '_error_element' => 'default_value_widget][field_album][nid][nid',
        ),
      ),
    ),
    'default_value_php' => '',
    'required' => '1',
    'multiple' => '0',
    'referenceable_types' =>
    array (
      1 => 1,
      0 => 1,
      'album' => 'album',
      'blog' => false,
      'buddy_icon' => false,
      'comment' => false,
      'event' => false,
      'forum' => false,
      'news' => false,
      'official_photo' => false,
      'page' => false,
      'photo' => false,
      'forum_reply' => false,
      'review' => false,
      'track' => false,
      'wallpaper' => false,
    ),
    'advanced_view' => '--',
    'advanced_view_args' => '',
    'module' => 'nodereference',
    'widget_module' => 'nodereference',
    'columns' =>
    array (
      'nid' =>
      array (
        'type' => 'int',
        'unsigned' => true,
        'not null' => false,
      ),
    ),
    'default_value' =>
    array (
      0 =>
      array (
        'nid' => '',
        '_error_element' => 'default_value_widget][field_album][nid][nid',
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
    'label' => 'Disc Number',
    'field_name' => 'field_disc_number',
    'type' => 'number_integer',
    'widget_type' => 'number',
    'change' => 'Change basic information',
    'weight' => '-3',
    'description' => 'If this is part of a multiple disc compilation, list the disc number here.',
    'default_value_widget' =>
    array (
      'field_disc_number' =>
      array (
        0 =>
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_disc_number][0][value',
        ),
      ),
    ),
    'default_value_php' => '',
    'required' => '0',
    'multiple' => '0',
    'min' => '',
    'max' => '',
    'prefix' => '',
    'suffix' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'module' => 'number',
    'widget_module' => 'number',
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
    'label' => 'Track Number',
    'field_name' => 'field_track_number',
    'type' => 'number_integer',
    'widget_type' => 'number',
    'change' => 'Change basic information',
    'weight' => '-2',
    'description' => '',
    'default_value_widget' =>
    array (
      'field_track_number' =>
      array (
        0 =>
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_track_number][0][value',
        ),
      ),
    ),
    'default_value_php' => '',
    'required' => '1',
    'multiple' => '0',
    'min' => '',
    'max' => '',
    'prefix' => '',
    'suffix' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'module' => 'number',
    'widget_module' => 'number',
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
    'label' => 'Audio File URL',
    'field_name' => 'field_audio_file_url',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '-1',
    'rows' => 1,
    'size' => 60,
    'description' => 'Enter a complete URL to a an audio file to be used in the site player. Audio files must be .swf format.',
    'default_value_widget' =>
    array (
      'field_audio_file_url' =>
      array (
        0 =>
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_audio_file_url][0][value',
        ),
      ),
    ),
    'default_value_php' => '',
    'required' => '0',
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
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
    'label' => 'Lyrics',
    'field_name' => 'field_lyrics',
    'type' => 'text',
    'widget_type' => 'text_textarea',
    'change' => 'Change basic information',
    'weight' => '',
    'rows' => '10',
    'size' => 60,
    'description' => '',
    'default_value_widget' =>
    array (
      'field_lyrics' =>
      array (
        0 =>
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_lyrics][0][value',
        ),
      ),
    ),
    'default_value_php' => '',
    'required' => '0',
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
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
  5 =>
  array (
    'label' => 'Song download links',
    'field_name' => 'field_song_download_links',
    'type' => 'link',
    'widget_type' => 'link',
    'change' => 'Change basic information',
    'weight' => '',
    'description' => 'Enter URLs and link text for purchasing this individual song from a Music Download Service.',
    'default_value_widget' =>
    array (
      'field_song_download_links' =>
      array (
        0 =>
        array (
          'url' => '',
          'title' => '',
        ),
      ),
    ),
    'default_value_php' => '',
    'required' => '0',
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
  6 =>
  array (
    'label' => 'Track video URL',
    'field_name' => 'field_track_video_url',
    'type' => 'text',
    'widget_type' => 'text_textfield',
    'change' => 'Change basic information',
    'weight' => '-2',
    'rows' => 1,
    'size' => 60,
    'description' => '',
    'default_value_widget' =>
    array (
      'field_album_video_url' =>
      array (
        0 =>
        array (
          'value' => '',
          '_error_element' => 'default_value_widget][field_track_video_url][0][value',
        ),
      ),
    ),
    'default_value_php' => '',
    'required' => '0',
    'multiple' => '0',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
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
    'label' => 'Gracenote Lyrics',
    'field_name' => 'field_gracenote_lyrics',
    'type' => 'm2_music_lyrics',
    'widget_type' => 'm2_quicksearch',
    'change' => 'Change basic information',
    'weight' => '1',
    'description' => '',
    'default_value' =>
    array (
      0 =>
      array (
        'm2id' => '',
        'document' => NULL,
        '_error_element' => 'default_value_widget][field_gracenote_lyrics][0][m2id',
      ),
    ),
    'default_value_php' => '',
    'default_value_widget' => NULL,
    'required' => 0,
    'multiple' => '0',
    'document_type' => 'music_lyrics-artist_title',
    'op' => 'Save field settings',
    'module' => 'm2',
    'widget_module' => 'm2',
    'columns' =>
    array (
      'm2id' =>
      array (
        'type' => 'int',
        'not null' => false,
        'unsigned' => true,
      ),
      'document' =>
      array (
        'type' => 'text',
        'size' => 'big',
        'not null' => false,
      ),
    ),
    'display_settings' =>
    array (
      'weight' => '1',
      'parent' => '',
      'label' =>
      array (
        'format' => 'above',
      ),
      'teaser' =>
      array (
        'format' => 'lyrics',
        'exclude' => 0,
      ),
      'full' =>
      array (
        'format' => 'lyrics',
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
);

