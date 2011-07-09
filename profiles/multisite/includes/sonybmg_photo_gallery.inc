<?php
// $Id$

/**
 * @file
 * These functions bootstrap a blank database, creating all the supporting configuration
 * data needed to implement the gallery functionality.
 */

/**
 * Default labelling and weight for this profile include
 */
function sonybmg_photo_gallery_info() {
  return array(
    'name' => st('Photo Gallery'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 10,
  );
}

/**
 * Required modules in order for these options to be created successfully
 */
function sonybmg_photo_gallery_modules() {
  return array(
    'php', 
    'views', 
    'content', 
    'text',
    'optionwidgets',
    'filefield', 
    'imagefield', 
    'imageapi', 
    'imageapi_gd', 
    'imagecache', 
    'fivestar', 
    'votingapi', 
    'nodereference', 
    'userreference', 
    'date_api', 
    'date_timezone', 
    'flag',
    'sonybmg_photo_gallery',
    'token',
    'custom_pagers',

    // devel only
    //'devel',
    //'views_ui',
    //'imagecache_ui',
  );
}

/**
 * Task to complete in order to activate this segment of code
 */
function sonybmg_photo_gallery_task_list() {
  return array(
    'sonybmg_photo_gallery_init_presets' => array(
      'message'   => st('Created Photo Gallery imagecache presets.'),
      'weight' => 0,
      'show'   => FALSE,
    ),
    'sonybmg_photo_gallery_init_node_types' => array(
      'message'   => st('Created Photo Gallery content types.'),
      'weight' => 0,
      'show'   => FALSE,
    ),
    'sonybmg_photo_gallery_init_content_type_settings' => array(
      'message'   => st('Initialized Photo Gallery content type settings.'),
      'weight' => 0,
      'show'   => FALSE,
    ),
    'sonybmg_photo_gallery_init_taxonomy' => array(
      'message'   => st('Created Photo Gallery vocabulary and terms.'),
      'weight' => 0,
      'show'   => FALSE,
    ),
    'sonybmg_photo_gallery_init_custom_pagers' => array(
      'message'   => st('Created Photo Gallery custom pagers.'),
      'weight' => 0,
      'show'   => FALSE,
    ),
    'sonybmg_photo_gallery_init_roles' => array(
      'message'   => st('Created Photo Gallery roles.'),
      'weight' => 0,
      'show'   => FALSE,
    ),
    'sonybmg_photo_gallery_init_content' => array(
      'message'   => st('Created Photo Gallery sample content.'),
      'weight' => 0,
      'show'   => FALSE,
    ),
    'sonybmg_photo_gallery_init_menus' => array(
      'message'   => st('Created Photo Gallery menus.'),
      'weight' => 0,
      'show'   => FALSE,
    ),
    'sonybmg_photo_gallery_fivestar_default' => array(
      'message' => st('Set the default fivestar widget display.'),
      'weight' => 0,
    ),
    // NOTE: this was in phase 2 of the D5 hook_first_build().  might need to adjust the weight.
    'sonybmg_photo_gallery_init_blocks' => array(
      'message' => st('Created Photo Gallery blocks.'),
      'weight' => 0,
    ),
  );
}

/**
 * Install task callback to add imagecache presets
 */
function sonybmg_photo_gallery_init_presets() {
  $presets = array(
    'thumbnail' => array(
      0 => array('action' => 'imagecache_scale', 'width' => '150', 'height' => '150'),
    ),
    'preview' => array(
      0 => array('action' => 'imagecache_scale', 'width' => '583'),
    ),
    'preview_crop' => array(
      0 => array('action' => 'imagecache_scale_and_crop', 'width' => '583', 'height' => '340'),
    ),
    'preview_small' => array(
      0 => array('action' => 'imagecache_scale', 'width' => '340', 'height' => '340'),
    ),
    'icon_medium' => array(
      0 => array('action' => 'imagecache_scale_and_crop', 'width' => '60', 'height' => '60'),
    ),
    'icon_large' => array(
      0 => array('action' => 'imagecache_scale_and_crop', 'width' => '100', 'height' => '100'),
    ),
  );
  
  foreach($presets as $name => $actions) {
    install_imagecache_add_preset($name, $actions);
  }
}

/**
 * Default cck fields to be added to photos
 */
function _sonybmg_photo_gallery_cck_fields_photo() {
  $fields = array (
    0 => 
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
          0 => 
          array (
            'value' => false,
            '_error_element' => 'default_value_widget][field_verify_ownership][value',
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
      'allowed_values' => '0|n/a
  1|I have the right to distribute this photo and it does not violate the <a href="/terms">Terms of Use</a>',
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
      'default_value' => 
      array (
        0 => 
        array (
          'value' => false,
          '_error_element' => 'default_value_widget][field_verify_ownership][value',
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
    1 => 
    array (
      'label' => 'Photo',
      'field_name' => 'field_photo',
      'type' => 'image',
      'widget_type' => 'image',
      'change' => 'Change basic information',
      'weight' => '',
      'max_resolution' => '1600x1600',
      'max_filesize' => 0,
      'image_path' => 'photos',
      'file_extensions' => 'jpg jpeg png gif',
      'custom_alt' => 0,
      'custom_title' => 0,
      'description' => 'Your photo size cannot be larger than 1 MB.  If your photo is larger than 1 MB, you will receive a "photo is required" error message.  If this happens, please resize your photo and resubmit.',
      'required' => '1',
      'multiple' => '0',
      'use_default_image' => 0,
      'default_image_upload' => '',
      'default_image' => '',
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
  return $fields;
}

/**
 * Default cck fields to be added to official photos
 */
function _sonybmg_photo_gallery_cck_fields_official_photo() {
  $fields = array (
    0 => 
    array (
      'label' => 'Photo',
      'field_name' => 'field_photo',
      'type' => 'image',
      'widget_type' => 'image',
      'change' => 'Change basic information',
      'weight' => '',
      'max_resolution' => '1600x1600',
      'max_filesize' => 0,
      'image_path' => 'photos',
      'file_extensions' => 'jpg jpeg png gif',
      'custom_alt' => 0,
      'custom_title' => 0,
      'description' => 'Your photo size cannot be larger than 1 MB.  If your photo is larger than 1 MB, you will receive a "photo is required" error message.  If this happens, please resize your photo and resubmit.',
      'required' => '1',
      'multiple' => '0',
      'use_default_image' => 0,
      'default_image_upload' => '',
      'default_image' => '',
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
  return $fields;
}

/**
 * Install task callback to create photo and official photo node types
 */
function sonybmg_photo_gallery_init_node_types() {
//  module_load_include('inc', 'sonybmg_photo_gallery', 'sonybmg_photo_gallery.node_types');
//  $types = array(
//    _sonybmg_photo_gallery_photo_node_type(),
//    _sonybmg_photo_gallery_official_photo_node_type(),
//  );
//  foreach($types as $type) {
//    install_add_content_type($type['type']);
//    foreach($type['fields'] as $field) {
//      install_create_field($type['type']['type'], $field['field_name'], $field['widget_type'], $field['label'], $field);
//    }
//  }
  
  $path = drupal_get_path('module', 'sonybmg_photo_gallery');
  install_content_copy_import_from_file($path .'/node.photo.inc');
  install_content_copy_import_from_file($path .'/node.official_photo.inc');
  
  // Set flag content variables:
  variable_set('flag_content_node_type_photo', 1);
}

/**
 * Install task callback to create photo and official photo node types settings
 */
function sonybmg_photo_gallery_init_content_type_settings() {
  // initiate fivestar settings.
  // this is done separate because on node_save five star will overwrite us.
  $variable_settings = array();// just an array to loop through - not really needed with one content type.
  //populate variable settings.
  $variable_settings['photo'] = array(
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
    'comment' => 2,
    'comment_type' => 'comment',
    'comment_view' => 'nodecomments',
  );
    
  $variable_settings['official_photo'] = array(
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
    'comment' => 2,
    'comment_type' => 'comment',
    'comment_view' => 'nodecomments',
  );

  // rotate through our settings and populate the db.
  foreach ($variable_settings as $type => $data) {
    foreach($data as $key => $val) {
      variable_set($key .'_'. $type, $val);
    }
  }
}

/**
 * Install task callback to create photo gallery vocabularies and terms
 */
function sonybmg_photo_gallery_init_taxonomy() {
  if (!variable_get('sonybmg_photo_gallery_user_vocabulary', 0)) {
    $properties = array();
    $properties['module'] = 'sonybmg_photo_gallery';
    $properties['required'] = 1;
    
    $vocab = install_taxonomy_add_vocabulary(st('Gallery'), array('photo' => 1), $properties);    
    variable_set('sonybmg_photo_gallery_user_vocabulary', $vocab['vid']);

    $terms = array(
      'At the show' => 'Upload your concert photos here!',
      'You and the band' => 'Grab a shot with the band and share it online!',
      'Look-alikes' => 'Think you could be a double? See what others think...',
    );
    foreach ($terms as $name => $description) {
      install_taxonomy_add_term($vocab['vid'], $name, $description);
    }
  }

  if (!variable_get('sonybmg_photo_gallery_official_vocabulary', 0)) {
    $properties = array();
    $properties['module'] = 'sonybmg_photo_gallery';
    $properties['required'] = 1;

    $vocab = install_taxonomy_add_vocabulary(st('Official Gallery'), array('official_photo' => 1), $properties);    
    variable_set('sonybmg_photo_gallery_official_vocabulary', $vocab['vid']);

    $terms = array(
      'Candid shots' => 'Behind the scenes with the band',
      'Official glossies' => 'Official photos for the band',
    );
    foreach ($terms as $name => $description) {
      install_taxonomy_add_term($vocab['vid'], $name, $description);
    }
  }
}

/**
 * Add custom pagers for photos and official photo types.
 */
function sonybmg_photo_gallery_init_custom_pagers() {
  $pager = array(
    'title' => 'Gallery pager',
    'view' => 'photos_galleries',
    'args' => array('[term-id]'),
    'position' => 'bottom',
    'node_type' => 'photo',
  );
  $pid = install_custom_pagers_add_pager($pager);
  variable_set('sonybmg_photo_gallery_user_pager', $pid);

  /*
  $pager = array(
    'title' => 'Node pager',
    'view' => 'event_photos',
    'args' => array('[node-id]'),
    'position' => 'bottom',
    'node_type' => 'photo',
  );
  $pid = install_custom_pagers_add_pager($pager);
  variable_set('sonybmg_photo_gallery_node_pager', $pid);
  */
  
  $pager = array(
    'title' => 'Official pager',
    'view' => 'photos_official',
    'args' => array('[term-id]'),
    'position' => 'bottom',
    'node_type' => 'official_photo',
  );
  $pid = install_custom_pagers_add_pager($pager);
  variable_set('sonybmg_photo_gallery_official_pager', $pid);
}

/**
 * Add custom pagers for photos and official photo types.
 */
function sonybmg_photo_gallery_init_roles() {
  $perms = array('create photo content', 'edit own photo content', 'edit photo content', 'create official_photo content', 'edit own official_photo content', 'edit official_photo content');

  install_add_permissions(install_get_rid('administrator'), array_merge($perms, array('administer photo gallery')));
  drupal_set_message(st('Photo Gallery permissions set for administrator role.'));
  
  install_add_permissions(install_get_rid('artist'), $perms);
  drupal_set_message(st('Photo Gallery permissions set for artist role.'));
  
  install_add_permissions(install_get_rid('moderator'), $perms);
  drupal_set_message(st('Photo Gallery permissions set for moderator role.'));
  
  // Authenticated
  install_add_permissions(DRUPAL_AUTHENTICATED_RID, array('create photo content', 'edit own photo content'));
  drupal_set_message(st('Photo Gallery permissions set for authenticated role.'));
}

/**
 * Install task callback to set up blocks.
 */
function sonybmg_photo_gallery_init_blocks() {
  $module = 'sonybmg_photo_gallery';
  $theme = variable_get('artist_key', '_starter');
  $status = TRUE;
  $region = 'right';
  $custom = 0;
  $throttle = 0;

  install_add_block($module, 'galleries', $theme, $status, 1, $region, 1, 'photos', $custom, $throttle, 'Fan Photos');
  
  install_add_block($module, 'galleries_compact', $theme, $status, 2, $region, 2, '<?php
if (arg(0) == "node" && is_numeric(arg(1))) {
  $node = node_load(arg(1));
  if ($node->type == "photo" || $node->type == "official_photo") {
    return TRUE;
  }
}
?>', $custom, $throttle, 'Fan Photos');

  $header = ($theme == 'garland') ? 'content' : 'content_header';
  install_add_block($module, 'photos_pager', $theme, $status, 1, $header, 2, '<'.'?php return sonybmg_photo_gallery_block_visibility("photos_pager"); ?'.'>');

  $bottom = ($theme == 'garland') ? 'content' : 'content_bottom';
  install_add_block($module, 'official_featured', $theme, $status, -2, $bottom, 1, 'photos', $custom, $throttle, 'Official '. PHOTO_ARTIST_NAME .' Photos');
  
  install_add_block($module, 'user_featured', $theme, $status, -1, $bottom, 1, 'photos', $custom, $throttle, 'Featured '. PHOTO_ARTIST_NAME .' Fan Photo');

  install_add_block('views', 'photos_user-block_1', $theme, $status, 1, 'right', 2, '<?php return sonybmg_photo_gallery_block_visibility("photos_user-block_1"); ?>');
  
}

/**
 * Install task callback to pre-populate photo gallery with content.
 */
function sonybmg_photo_gallery_init_content() {
  global $base_url;

  // Create an official photo node
  // first create the file upload object ...
  $source = './profiles/multisite/files/official-photo.png';
  $dest = file_directory_path() .'/official_photos/';
  $file = install_upload_file($source, array(), $dest, FILE_EXISTS_RENAME, 'image/png' );
  
  // ... then create the node
  $node = new stdClass();
  $node->type = 'official_photo';
  $node->title = t('Sample official photo');
  $node->taxonomy[install_taxonomy_get_vid(st('Official Gallery'))] = install_taxonomy_get_tid('Candid shots');
  $node->field_photo = array(0 => array('fid' => $file->fid));
  $node->uid = 1;
  $node->comment = 2;
  $node->status = 1;
  $node->active = 1;
  $node->promote = 1;
  node_save($node);
 
  // Promote it to a featured photo.
  flag('flag', 'promote', 'node', $node->nid);  
  
  $terms = array('At the show', 'You and the band', 'Look-alikes');
  $vid = install_taxonomy_get_vid(st('Gallery'));
  foreach($terms as $term) {
    // Create a photo node in the 'At the show' gallery
    // first create the file upload object ...
    $source = './profiles/multisite/files/photo.png';
    $dest = file_directory_path() .'/photos/';
    $file = install_upload_file($source, array(), $dest, FILE_EXISTS_RENAME, 'image/png' );
    
    // ... then create the node
    $node = new stdClass();
    $node->type = 'photo';
    $node->title = t('Sample fan photo');
    $node->taxonomy[$vid] = install_taxonomy_get_tid($term);
    $node->field_photo = array(0 => array('fid' => $file->fid));
    $node->uid = 1;
    $node->status = 1;
    $node->active = 1;
    $node->promote = 1;
    $node->comment = 2;
    $node->moderate = 0;
    node_save($node);
  
    // Promote it to a featured photo.
    flag('flag', 'promote', 'node', $node->nid);  
  }
  
  $photos = array('Lightning', 'Mojave', 'Pier', 'Sea Mist', 'Wave');
  $vid = install_taxonomy_get_vid(st('Gallery'));
  $tid = install_taxonomy_get_tid('At the show');
  foreach($photos as $title) {
    $source = './profiles/multisite/files/photos/'. $title .'.jpg';
    $dest = file_directory_path() .'/photos/';
    $file = install_upload_file($source, array(), $dest, FILE_EXISTS_RENAME, 'image/jpeg' );
    
    // ... then create the node
    $node = new stdClass();
    $node->type = 'photo';
    $node->title = $title;
    $node->taxonomy[$vid] = $tid;
    $node->field_photo = array(0 => array('fid' => $file->fid));
    $node->uid = 1;
    $node->status = 1;
    $node->active = 1;
    $node->promote = 1;
    $node->moderate = 0;
    $node->comment = 2;
    node_save($node);
  
    // Promote it to a featured photo.
    flag('flag', 'promote', 'node', $node->nid);  
    
  }

}

/**
 * Set the default Widget display for the fivestar module.
 */
function sonybmg_photo_gallery_fivestar_default() {
  variable_set('fivestar_widget', 'sites/all/modules/contrib/fivestar/widgets/basic/basic.css');
}

/**
 * Install task callback to create menu items
 */
function sonybmg_photo_gallery_init_menus() {
  install_menu_create_menu_item('photos', 'Photos', 'Photos', 'Primary Links');
}
