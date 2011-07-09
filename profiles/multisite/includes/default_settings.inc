<?php

/**
 * This file should be used for core settings
 * and module-specific settings only.
 *
 * Most settings should be configured in inc
 * files that are appropriate to a specific
 * part of the site. However, there are some
 * cases where modules need to be configured
 * globally to affect multiple parts of the
 * site, but do not warrant their own inc file.
 *
 * In this case, create a function in this file
 * with the name default_settings_module_$module
 * and do all your configuration there. The
 * function will be automatically called on
 * installation.
 *
 */


function default_settings_info() {
  return array(
    'name' => st('Default Settings'),
    'default_value' => TRUE,
    'disabled' => TRUE,
    'weight' => -301,
  );
}

function default_settings_modules() {
  return array('dblog', 'mollom', 'wordfilter', 'views', 'views_ui', 'pathauto', 'nodecomment', 'sony_admin', 'admin', 'admin_tools' , 'extlink', 'sonybmg_analytics', 'sony_coppa', 'sonybmg_offensive', 'sonybmg_dev', 'checkbox_validate', 'legal', 'sony_register', 'feedapi', 'feedapi_node', 'sony_ads');
}

function default_settings_task_list() {
  return array(
    'default_settings_artist_info' => array(
      'message' => st('Set artist info.'),
      'weight' => -2147483647,
    ),
    'default_settings_core_set' => array(
      'message' => st('Set core settings.'),
      'weight' => -2147483646,
     ),
    'default_settings_modules_set' => array(
      'message' => st('Set module settings.'),
      'weight' => 35,
    ),
    'default_settings_nodecomment' => array(
      'message' => st('Set nodecomment settings.'),
      'weight' => 90,
    ),
    'default_settings_blocks_set' => array(
      'message' => st('Set default blocks.'),
      'weight' => 100,
    ),
    'default_settings_feedapi_setup' => array(
      'message' => st('Set up FeedAPI.'),
      'weight' => 100,
    ),
  );
}

function default_settings_nodecomment() {
  $content_types_result = db_query("SELECT type FROM {node_type}");

  while ($content_type = db_fetch_array($content_types_result)) {
    variable_set('comment_view_'. $content_type['type'], 'sonybmg_nodecomments');
  }
}

function default_settings_artist_info() {
  $form = drupal_get_form('default_settings_artist_info_form');
  if(!variable_get('artist_key', '')) {
    $output = $form;
  }
}

function default_settings_artist_info_form() {
  $artist_guess = str_replace(' Site', '', str_replace('The Official ', '', variable_get('site_name', 'Drupal')));
  $folder_guess = substr(strtolower(conf_path()), 6, 19);

  $form['artist_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Artist machine name'),
    '#default_value' => variable_get('artist_key', $folder_guess),
    '#description' => t('The machine name for the artist. This can only be 13 characters, alphanumeric and underscores. It will be used for the theme name and database setup.'),
    '#maxlength' => 13,
    '#required' => 1,
  );

  $form['artist_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Artist name'),
    '#default_value' => variable_get('artist_name', $artist_guess),
    '#description' => t('This field must only be the Artist Name. It will be used for Page Titles, Footer Links, and Album Imports.'),
    '#required' => 1,
  );

  $form['sonybmg_label'] = array(
    '#type' => 'select',
    '#title' => t('Record label'),
    '#options' => array(
      'columbia'    => t('Columbia'),
      'epic'        => t('Epic'),
      'j'           => t('J/Arista'),
      'legacy'      => t('Legacy'),
      'masterworks' => t('Masterworks'),
      'myplay'    => t('MyPlay'),
      'nashville'   => t('Nashville'),
      'rca'         => t('RCA'),
      'sonybmglatin' => t('Sony BMG Latin'),
      'sonywonder'  => t('Sony Wonder'),
      'stratmar'    => t('Strategic Marketing'),
      'victor'      => t('Victor'),
      'zomba'       => t('Zomba'),
    ),
    '#default_value' => variable_get('sonybmg_label', NULL),
    '#description' => t('Select the record label for this artist. This will be used to determine which toolbar and WebTrends code is called on each page.'),
  );

  $form['sonybmg_footer'] = array(
    '#type' => 'select',
    '#title' => t('Footer'),
    '#options' => array(
      'classical'         => t('Classical'),
      'classical_odyssey' => t('Classical / Odyssey'),
      'columbia'          => t('Columbia'),
      'columbia_legacy'   => t('Columbia / Legacy'),
      'columbia_nologo'   => t('Columbia (No Logo)'),
      'columbia_serjical' => t('Columbia / Serjical'),
      'epic'              => t('Epic'),
      'epic_b'            => t('Epic (dark background)'),
      'epic_columbia'     => t('Epic / Columbia'),
      'epic_legacy'       => t('Epic / Legacy'),
      'epic_legacy_b'     => t('Epic / Legacy (dark background)'),
      'legacy'            => t('Legacy'),
      'legacy_b'          => t('Legacy (dark background)'),
      'nologo'            => t('No logo'),
      'odyssey'           => t('Odyssey'),
      'rca'               => t('RCA'),
      'redseal'           => t('Red Seal'),
      'j-arista'          => t('J / Arista'),
      'j-arista-b'        => t('J / Arista (dark background)'),
      'victor'            => t('Victor'),
      'zomba'             => t('Zomba'),
    ),
    '#default_value' => variable_get('sonybmg_footer', NULL),
    '#description' => t('Select which label information should be displayed in the footer of each page.'),
  );

  $form['#redirect'] = FALSE;

  $form['submit'] = array('#type' => 'submit', '#value' => t('Submit'));
  return $form;
}

function default_settings_artist_info_form_submit($form, &$form_state) {
  variable_set('artist_key', $form_state['values']['artist_key']);
  variable_set('artist_name', $form_state['values']['artist_name']);
  variable_set('sonybmg_label', $form_state['values']['sonybmg_label']);
  variable_set('sonybmg_footer', $form_state['values']['sonybmg_footer']);
}

function default_settings_core_set() {
  variable_set('clean_url', 1);
  variable_set('site_frontpage', 'home');
  variable_set('file_directory_temp', '/tmp');
  variable_set('date_default_timezone', -18000);
  variable_set('date_default_timezone_name', 'America/New_York');
  variable_set('upload_list_default', 0);

  // Setup files directory.
  $artist_name = variable_get('artist_key', '');
  $artist_dir = 'sites/'. $artist_name;
  if (!empty($artist_name) && !is_dir($artist_dir)) {
    mkdir($artist_dir);
    chmod($artist_dir, 0755);
  }
  $files_dir = $artist_dir .'/files';
  if (!is_dir($files_dir)) {
    mkdir($files_dir);
    chmod($files_dir, 0755);
  }

  variable_set('file_directory_path', $files_dir);

 /* TODO FINISH
  $new_roles = array(variable_get('multisite_artist_rid', 0), variable_get('multisite_moderator_rid', 0), variable_get('multisite_administrator_rid', 0));
  // Filtered HTML (all)
  install_format_set_roles(1, array_merge(array(1, 2, 3), $new_roles));
  // Full HTML (Admin, Artist, Moderator)
  install_format_set_roles(3, $new_roles);
  // Create the Full HTML no breaks role (Admin, Artist, Moderator)
  profile_helper_add_input_format('Full HTML no breaks', array(3, 4, 5));
  */
}

function default_settings_modules_set() {
  $modules = module_list(TRUE, FALSE);
  foreach ($modules as $module) {
    $func = "default_settings_module_$module";
    //run the module setup function if it exists
    if (function_exists($func)) {
      $func();
    }
  }
}

/**
 * Module specific settings for NodeComment module.
 */
function default_settings_module_nodecomment() {
  // Display comment submission form below post or comments.
  variable_set('comment_form_location', 1);
}

/**
 * Module specific settings for Fivestar module.
 */
function default_settings_module_fivestar() {
  variable_set('fivestar_allow_cancel', FALSE);
  //content-type-specific five-star settings should
  //be set in the appropriate inc files
}

/**
 * Module specific settings for Flag module.
 */
function default_settings_module_flag() {
  // Delete the "bookmark" flag.
  $flag = flag_get_flag('bookmarks');
  $flag->delete();
}

/**
 * Module specific setting for Administrative Menu module
 */
function default_settings_module_admin_menu() {
  $perms = array('access administration menu');
  install_add_permissions(install_add_role('artist'), $perms);
  install_add_permissions(install_add_role('moderator'), $perms);
}

/**
 * Module specific setting for Mollom module
 */
function default_settings_module_mollom() {
  $perms = array('post with no checking');
  install_add_permissions(install_get_rid('authenticated user'), $perms);
  install_add_permissions(install_add_role('artist'), $perms);
  install_add_permissions(install_add_role('moderator'), $perms);
}


/**
 * Module specific setting for Word Filter module
 */
function default_settings_module_wordfilter() {
  $perms = array('administer words filtered');
  install_add_permissions(install_add_role('artist'), $perms);
  install_add_permissions(install_add_role('moderator'), $perms);

  db_query("INSERT INTO {filters} (format, module, delta, weight) VALUES (1, 'wordfilter', 0, 10)");
  db_query("INSERT INTO {wordfilter} values
  ('1','asshole','a**hole','0'),
  ('2','bitch','b****','0'),
  ('3','cock','c***','0'),
  ('4','cunt','c***','0'),
  ('5','dickhead','d***head','0'),
  ('6','fuck','f***','0'),
  ('7','kyke','[Slur Deleted]','0'),
  ('8','kike','[Slur Deleted]','0'),
  ('9','nigger','[Slur Deleted]','0'),
  ('10','fag','[Slur Deleted]','0'),
  ('11','dyke','[Slur Deleted]','0'),
  ('12','shit','s***','0')");
}

/**
 * Module specific settings for pathauto
 */
function default_settings_module_pathauto() {
  variable_set('pathauto_update_action', 2);

  variable_set('pathauto_node_pattern', '');

  variable_set('pathauto_node_album_pattern', 'music/[title-raw]');
  variable_set('pathauto_node_blog_pattern', 'blog/[title-raw]');
  //variable_set('pathauto_node_comment_pattern', 'comment/[title-raw]');
  variable_set('pathauto_node_news_pattern', 'news/[title-raw]');
  variable_set('pathauto_node_page_pattern', '[title-raw]');
  variable_set('pathauto_node_poll_pattern', 'poll/[title-raw]');
  variable_set('pathauto_node_track_pattern', 'music/[field_album-title-raw]/[title-raw]');
  variable_set('pathauto_node_date_pattern', 'event/[field_date-yyyy]/[field_date-mm]/[field_date-dd]/[title-raw]');
  //variable_set('pathauto_node_reply_pattern', 'reply/[title-raw]');
  variable_set('pathauto_node_official_photo_pattern', 'official-photos/[nid]');
  variable_set('pathauto_node_photo_pattern', 'photos/[title-raw]');
  variable_set('pathauto_node_review_pattern', '');
  variable_set('pathauto_node_wallpaper_pattern', 'wallpaper/[nid]');
  variable_set('pathauto_node_applytofeeds', '');
  variable_set('pathauto_taxonomy_pattern', 'category/[vocab-raw]/[catpath-raw]');

  variable_set('pathauto_user_pattern', 'users/[user-raw]');

}

/**
 * Module specific settings for extlink
 */

function default_settings_module_extlink() {
  variable_set('extlink_target', '_blank');
  variable_set('extlink_class', 0);
  variable_set('extlink_mailto_class', 0);
  variable_set('extlink_subdomains', 0);
}
/**
 * Disable the existing blocks.
 */
function default_settings_blocks_set() {
  $theme = variable_get('artist_key', '_starter');
  // User login block.
  install_add_block('user', '0', $theme, FALSE, 0, '');
  // Navigation block.
  install_add_block('user', '1', $theme, FALSE, 0, '');
  // Powered by Drupal block :(
  install_add_block('user', '1', $theme, FALSE, 0, '');
}

/**
 * Setup FeedAPI
 */
function default_settings_feedapi_setup() {
  if (is_array(variable_get('feedapi_settings_feed', FALSE))) {
    $settings = variable_get('feedapi_settings_feed', FALSE);
    $settings['parsers']['feedapi_eparser']['enabled'] = 1;
    $settings['parsers']['feedapi_eparser']['weight'] = "-5";
    variable_set('feedapi_settings_feed', $settings);
  }
}
