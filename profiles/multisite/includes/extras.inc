<?php

/**
 * Default labelling and weight for this profile include.
 */
function extras_info() {
  return array(
    'name' => st('Extras Section'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 10,
  );
}

/**
 * Required modules.
 */
function extras_modules() {
  return array('sonybmg_extras', 'content', 'imagefield', 'imageapi', 'imageapi_gd', 'views', 'path', 'token', 'pathauto', 'menu', 'imageapi', 'imagecache', 'imagecache_ui');
}

function extras_task_list() {
  return array(
    'extras_init_content_types' => array(
      'message' => st('Created content types.'),
      'weight' => 0,
    ),
    'extras_init_sample_content' => array(
      'message' => st('Created sample content.'),
      'weight' => 10,
    ),
    'extras_init_imagecache_presets' => array(
      'message' => st('Created imagecache presets.'),
      'weight' => 0,
    ),
    'extras_init_roles' => array(
      'message' => st('Set up permissions and roles.'),
      'weight' => 10,
    ),
    'extras_init_menu' => array(
      'message'   => st('Initialized menu.'),
      'weight' => 53,
    ),
    'extras_init_blocks' => array(
      'message'   => st('Initialized block placement.'),
      'weight' => 1000,
    ),
  );
}

/**
 * Create our content types.
 */
function extras_init_content_types() {
  $path = drupal_get_path('module', 'sonybmg_extras');
  install_content_copy_import_from_file($path .'/node.wallpaper.inc');
  install_content_copy_import_from_file($path .'/node.buddyicon.inc');
}
/**
 * Create sample buddy_icon and wallpaper content.
 */
function extras_init_sample_content() {

  $source = './profiles/multisite/files/buddy.png';
  $dest = file_directory_path() .'/buddy_icons/';
  $file = install_upload_file($source, array(), $dest, FILE_EXISTS_RENAME, 'image/png');

  $node = new stdClass();
  $node->type = 'buddy_icon';
  $node->title = st('Sample buddy icon');
  $node->field_buddy_icon = array(0 => array('fid' => $file->fid));
  $node->uid = 1;
  $node->status = 1;
  $node->active = 1;
  $node->promote = 1;

  node_save($node);
  $source = './profiles/multisite/files/wallpaper.png';
  $dest = file_directory_path() .'/wallpaper/';
  $file = install_upload_file($source, array(), $dest, FILE_EXISTS_RENAME, 'image/png');

  $node = new stdClass();
  $node->type = 'wallpaper';
  $node->title = st('Sample wallpaper');
  $node->field_wallpaper = array(0 => array('fid' => $file->fid));
  $node->uid = 1;
  $node->status = 1;
  $node->active = 1;
  $node->promote = 1;

  node_save($node);
}

/**
 * Create our imagecache presets.
 */
function extras_init_imagecache_presets() {
  $presets = array(
    '1024x768' => array(
      0 => array('action' => 'imagecache_scale', 'width' => '1024', 'height' => '768'),
      1 => array('action' => 'imagecache_crop', 'width' => '1024', 'height' => '768', 'xoffset' => 'center', 'yoffset' => 'center'),
    ),
    '800x600' => array(
      0 => array('action' => 'imagecache_scale', 'width' => '800', 'height' => '600'),
      1 => array('action' => 'imagecache_crop', 'width' => '800', 'height' => '600', 'xoffset' => 'center', 'yoffset' => 'center'),
    ),
    '1280x960' => array(
      0 => array('action' => 'imagecache_scale', 'width' => '1280', 'height' => '960'),
      1 => array('action' => 'imagecache_crop', 'width' => '1280', 'height' => '960', 'xoffset' => 'center', 'yoffset' => 'center'),
    ),
    //
    'blog' => array(
      0 => array('action' => 'imagecache_scale', 'width' => '240', 'height' => '240'),
    ),
    'blog_large' => array(
      0 => array('action' => 'imagecache_scale', 'width' => '400', 'height' => '400', 'upscale' => TRUE),
    ),
    'blog_small' => array(
      0 => array('action' => 'imagecache_scale', 'width' => '100', 'height' => '100'),
      1 => array('action' => 'imagecache_crop', 'width' => '100', 'height' => '100', 'xoffset' => 'center', 'yoffset' => 'center'),
    ),
    'discography_large' => array(
      0 => array('action' => 'imagecache_scale', 'width' => '280', 'upscale' => TRUE),
    ),
    'discography_small' => array(
      0 => array('action' => 'imagecache_scale', 'width' => '90', 'height' => '90'),
      1 => array('action' => 'imagecache_crop', 'width' => '90', 'height' => '90', 'xoffset' => 'center', 'yoffset' => 'center'),
    ),
    'block' => array(
      0 => array('action' => 'imagecache_scale', 'width' => '285', 'height' => '', 'upscale' => TRUE),
    ),
    'icon_small' => array(
      0 => array('action' => 'imagecache_scale_and_crop', 'width' => '50', 'height' => '50'),
    ),
    'icon_huge' => array(
      0 => array('action' => 'imagecache_scale_and_crop', 'width' => '160', 'height' => '160'),
    ),
  );
  foreach ($presets as $name => $actions) {
    install_imagecache_add_preset($name, $actions);
  }
}

/**
 * Enable and setup our default user pictures settings.
 */
function extras_init_menu() {
  install_menu_create_menu_item('extras', 'Extras', 'Extras', 'Primary Links', -2);
}

/**
 * Install task callback to set up blocks.
 */
function extras_init_blocks() {
  $theme = variable_get('artist_key', '_starter');
  $status = TRUE;
  $custom = 0;
  $throttle = 0;

  $bottom = ($theme == 'garland') ? 'content' : 'content_bottom';
  install_add_block('views', 'wallpaper-block_1', $theme, $status, 4, $bottom, 1, 'extras', $custom, $throttle);
  install_add_block('views', 'buddy_icons-block_1', $theme, $status, 4, 'right', 1, 'extras', $custom, $throttle);
  install_add_block('views', 'userposts-block_1', $theme, $status, 0, 'right', 1, 'blog*', $custom, $throttle);
}

/**
 * Add custom permissions.
 */
function extras_init_roles() {
  $perms = array('create wallpaper content', 'edit own wallpaper content', 'edit wallpaper content', 'create buddy_icon content', 'edit own buddy_icon content', 'edit buddy_icon content');

  install_add_permissions(install_get_rid('administrator'), $perms);
  install_add_permissions(install_get_rid('artist'), $perms);
  install_add_permissions(install_get_rid('moderator'), $perms);
  // Add our blocks

  $theme = 'garland'; // TODO: We need to pull the actual theme
  install_add_block('views', 'wallpaper-block_1', $theme, TRUE, 4, 'content', 1, 'extras', 0);
  install_add_block('views', 'buddy_icons-block_1', $theme, TRUE, 4, 'content', 1, 'extras', 0);
}
