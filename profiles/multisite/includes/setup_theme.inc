<?php
/**
 * @file
 * Create our default content types that don't necessarily fit elsewhere.
 */
function setup_theme_info() {
  return array(
    'name' => st('Configure theme'),
    'default_value' => TRUE,
    'disabled' => TRUE,
    'weight' => -300,
  );
}

/**
 * Task list.
 */
function setup_theme_task_list() {
  return array(
    'setup_theme_create_theme' => array(
      'message' => st('Created site theme.'),
      'weight' => -2147483647,
    ),
    'setup_theme_set_theme' => array(
      'message' => st('Set the site theme.'),
      'weight' => -2147483646,
    ),
    'setup_theme_set_variables' => array(
      'message' => st('Set theme variables.'),
      'weight' => 1,
    ),
  );
}

/**
 * Create a new theme based off the _starter theme.
 */
function setup_theme_create_theme() {
  // Note: install_profile_api is unable to actually enable a newly created
  // theme due to static caches in Drupal 6, use a manual SQL approach instead.
  $artist_short = variable_get('artist_key', '_starter');
  $artist = variable_get('artist_name', 'Artist theme');
  $replace_short = '_starter';

  $source_theme_root = 'sites/all/themes';
  $source_theme_dir = $source_theme_root .'/'. $replace_short;

  $site_dir = 'sites/'.$artist_short;
  $dest_theme_root = 'sites/'.$artist_short .'/themes';
  $dest_theme_dir = $dest_theme_root. '/'. $artist_short;

  // Check if a theme by the name of the artist already exists.
  if (!is_dir($dest_theme_dir)) {

    // Create the entire tree if necessary.
    if (mkdir($dest_theme_dir, 0755, TRUE)) {

      // Copy the template theme to a new theme and remove any VCS folders.
      multisite_copy_files($source_theme_dir, $dest_theme_dir, array('.svn', 'CVS'));
      drupal_set_message(st('Theme <b>%theme</b> created from the Multsite starter theme.', array('%theme' => $artist_short)));

      // Update template.php file.
      multisite_file_replace($dest_theme_dir .'/template.php', $replace_short, $artist_short);

      // Update the _starter.info file.
      $find = array(
        'Multisite Starter Theme',
        'The starter theme that is duplicated for all new multisites.',
      );
      $replace = array(
        $artist_short,
        $artist_short .' site theme.',
      );
      rename($dest_theme_dir .'/'. $replace_short .'.info', $dest_theme_dir .'/'. $artist_short .'.info');
      multisite_file_replace($dest_theme_dir ."/". $artist_short .".info", $find, $replace);
    }
    else {
      drupal_set_message(st('Could not create the theme folder at @dir, check permissions', array('@dir' => $dest_theme_dir)));
    }
  }
  else {
    drupal_set_message(st('Theme <b>%theme</b> already exists. No new theme created.', array('%theme' => $artist_short)), 'warning');
  }
}

/**
 * Enable the site theme.
 */
function setup_theme_set_theme() {
  $artist_short = variable_get('artist_key', '_starter');
  $theme_dir = 'sites/'. $artist_short .'/themes/'. $artist_short;

  // Check to make sure that a theme exists where we expect it.
  if (file_exists($theme_dir .'/'. $artist_short .'.info')) {
    // Enable theme.
    install_default_theme($artist_short);
    install_disable_theme('garland');
  }
}

/**
 * Set theme variables variables.
 */
function setup_theme_set_variables() {
  // Setup theme.
  $theme_info = theme_get_settings();

  // Build a list of content types that do not have a "submitted by" line.
  $no_title_types = array(
    'album',
    'buddy_icon',
    'date',
    'official_photo',
    'page',
    'track',
    'wallpaper',
  );

  foreach ($no_title_types as $type) {
    $theme_info['toggle_node_info_'. $type] = 0;
  }

  $form_state = array('values' => $theme_info);

  // Save theme specific settings.
  drupal_execute('system_theme_settings', $form_state);

  // Clear theme caches.
  system_theme_data();
}