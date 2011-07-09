<?php
// $Id$

/**
 * @file
 * These are the exports from the content type export UI.  
 * Each is wrapped in a function that returns the entire $content array
 */

/**
 * Content type definition for 'photo' node type
 */
function _sonybmg_photo_gallery_photo_node_type() {
  $content['type']  = array (
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
    'language_content_type' => '0',
    'comment' => '2',
    'comment_type' => 'comment',
    'comment_view' => 'nodecomments',
    'old_type' => 'photo',
    'orig_type' => 'photo',
    'module' => 'node',
    'custom' => '1',
    'modified' => '1',
    'locked' => '1',
    'event_nodeapi' => 'never',
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
    'fivestar_unvote' => 1,
    'fivestar_position_teaser' => 'hidden',
    'fivestar_position' => 'hidden',
  );
  $content['fields']  = array (
    0 => 
    array (
      'label' => 'Photo',
      'field_name' => 'field_photo',
      'type' => 'image',
      'widget_type' => 'imagefield_widget',
      'change' => 'Change basic information',
      'weight' => '-4',
      'file_extensions' => 'jpg gif png',
      'file_path' => 'photos',
      'file_widgets' => 
      array (
        'filefield_generic' => 
        array (
          'enabled' => 1,
          'weight' => 1,
        ),
      ),
      'description' => 'Your photo size cannot be larger than 1 MB.  If your photo is larger than 1 MB, you will receive a "photo is required" error message.  If this happens, please resize your photo and resubmit. jpg, png and gif only',
      'required' => '1',
      'multiple' => '0',
      'force_list' => 1,
      'file_formatters' => 
      array (
        'filefield_generic' => 
        array (
          'enabled' => 1,
          'weight' => 1,
        ),
      ),
      'module' => 'imagefield',
      'widget_module' => 'imagefield',
      'columns' => 
      array (
        'fid' => 
        array (
          'type' => 'int',
          'not null' => false,
        ),
        'description' => 
        array (
          'type' => 'varchar',
          'length' => 255,
          'not null' => false,
          'sortable' => true,
        ),
        'list' => 
        array (
          'type' => 'int',
          'size' => 'tiny',
          'not null' => false,
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
          'format' => 'thumbnail_linked',
        ),
        'full' => 
        array (
          'format' => 'preview_default',
        ),
        4 => 
        array (
          'format' => 'default',
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
      'weight' => '-1',
      'description' => '',
      'default_value_widget' => 
      array (
        'field_verify_ownership' => 
        array (
          'value' => false,
          '_error_element' => 'default_value_widget][field_verify_ownership][value',
        ),
      ),
      'default_value_php' => '',
      'required' => '1',
      'multiple' => '0',
      'min' => '',
      'max' => '',
      'prefix' => '',
      'suffix' => '',
      'allowed_values' => "0|n/a\n1|I have the right to distribute this photo and it does not violate the <a href=\"/terms\">Terms of Use</a>",
      'allowed_values_php' => '',
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
  
  return $content;
}

/**
 * Content type definition for 'official_photo' node type
 */
function _sonybmg_photo_gallery_official_photo_node_type() {
  $content['type']  = array (
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
    'comment' => 2,
    'comment_type' => '',
    'comment_view' => 'nodecomments',
    'old_type' => 'official_photo',
    'orig_type' => 'official_photo',
    'module' => 'node',
    'custom' => '1',
    'modified' => '1',
    'locked' => '1',
    'event_nodeapi' => 'never',
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
  $content['fields']  = array (
    0 => 
    array (
      'label' => 'Photo',
      'field_name' => 'field_photo',
      'type' => 'image',
      'widget_type' => 'imagefield_widget',
      'change' => 'Change basic information',
      'weight' => '',
      'file_extensions' => 'jpg gif png',
      'file_path' => 'official_photos',
      'file_widgets' => 
      array (
        'filefield_generic' => 
        array (
          'enabled' => 1,
          'weight' => 1,
        ),
      ),
      'description' => 'Your photo size cannot be larger than 1 MB.  If your photo is larger than 1 MB, you will receive a "photo is required" error message.  If this happens, please resize your photo and resubmit. jpg, png and gif only',
      'required' => '1',
      'multiple' => '0',
      'force_list' => 1,
      'file_formatters' => 
      array (
        'filefield_generic' => 
        array (
          'enabled' => 1,
          'weight' => 1,
        ),
      ),
      'module' => 'imagefield',
      'widget_module' => 'imagefield',
      'columns' => 
      array (
        'fid' => 
        array (
          'type' => 'int',
          'not null' => false,
        ),
        'description' => 
        array (
          'type' => 'varchar',
          'length' => 255,
          'not null' => false,
          'sortable' => true,
        ),
        'list' => 
        array (
          'type' => 'int',
          'size' => 'tiny',
          'not null' => false,
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
          'format' => 'thumbnail_linked',
        ),
        'full' => 
        array (
          'format' => 'preview_default',
        ),
        4 => 
        array (
          'format' => 'default',
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
      'weight' => '',
      'rows' => 1,
      'description' => '',
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
    2 => 
    array (
      'label' => 'Photographer Last Name',
      'field_name' => 'field_photographer_last',
      'type' => 'text',
      'widget_type' => 'text_textfield',
      'change' => 'Change basic information',
      'weight' => '',
      'rows' => 1,
      'description' => '',
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
      'default_value_php' => '',
      'required' => '0',
      'multiple' => '0',
      'text_processing' => 0,
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
  );
  
  return $content;
}
