<?php
$content[type]  = array (
  'name' => 'Page',
  'type' => 'page',
  'description' => 'Static pages like biographies, discography, or other informational pages. These pages do not normally have comments enabled.',
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
  'language_content_type' => 0,
  'comment' => 0,
  'comment_type' => '',
  'comment_view' => '',
  'usernodes_limit' => 0,
  'i18n_node' => 1,
  'old_type' => 'page',
  'orig_type' => 'page',
  'module' => 'node',
  'custom' => '0',
  'modified' => '0',
  'locked' => '1',
  'reset' => 'Reset to defaults',
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
    'label' => 'Sidebar content',
    'field_name' => 'field_sidebar_content',
    'type' => 'text',
    'widget_type' => 'text_textarea',
    'change' => 'Change basic information',
    'weight' => '2',
    'rows' => '20',
    'size' => 60,
    'description' => 'Content in this field will appear in a sidebar next to the page content.',
    'default_value_widget' =>
    array (
      'field_sidebar_content' =>
      array (
        0 =>
        array (
          'value' => '',
          'format' => 1,
          '_error_element' => 'default_value_widget][field_sidebar_content][0][value',
        ),
      ),
    ),
    'default_value_php' => '',
    'required' => '0',
    'multiple' => '0',
    'text_processing' => '1',
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
      'format' =>
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
        'value' => '',
        'format' => 1,
        '_error_element' => 'default_value_widget][field_sidebar_content][0][value',
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
