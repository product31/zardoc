<?php
// $Id: media_brightcove.variables.inc,v 1.1.2.7 2010/09/01 21:30:13 aaron Exp $

/**
 * @file Contains the variables and defaults used by Media: Brightcove.
 */

/**
 * The variable namespace for Media: Brightcove.
 */
define('MEDIA_BRIGHTCOVE_NAMESPACE', 'media_brightcove__');

/**
 * This is the main URL for Brightcove.
 */
define('MEDIA_BRIGHTCOVE_MAIN_URL', 'http://www.brightcove.com/');

/**
 *  This is the URL to the API of Brightcove.
 */
define('MEDIA_BRIGHTCOVE_API_URL', 'http://developer.brightcove.com/en/');

/**
 *  This defines the version of the content data array that we serialize
 *  in emvideo_brightcove_data(). If we change the expected keys of that array,
 *  we must increment this value, which will allow older content to be updated
 *  to the new version automatically.
 */
define('MEDIA_BRIGHTCOVE_DATA_VERSION', 2);

/**
 * Brightcove status settings.
 */
define('MEDIA_BRIGHTCOVE_STATUS_UNKNOWN', 'UNKNOWN');
define('MEDIA_BRIGHTCOVE_STATUS_COMPLETE', 'COMPLETE');
define('MEDIA_BRIGHTCOVE_STATUS_ERROR', 'ERROR');


/**
 * Wrapper for variable_get() that uses the Media: Brightcove variable registry.
 *
 * @param string $name
 *  The variable name to retrieve. Note that it will be namespaced by
 *  pre-pending MEDIA_BRIGHTCOVE_NAMESPACE, as to avoid variable collisions
 *  with other modules.
 * @param unknown $default
 *  An optional default variable to return if the variable hasn't been set
 *  yet. Note that within this module, all variables should already be set
 *  in the media_brightcove_variable_default() function.
 * @return unknown
 *  Returns the stored variable or its default.
 *
 * @see media_brightcove_variable_set()
 * @see media_brightcove_variable_del()
 * @see media_brightcove_variable_default()
 */
function media_brightcove_variable_get($name, $default = NULL) {
  // Allow for an override of the default.
  // Useful when a variable is required (like $path), but namespacing still desired.
  if (!isset($default)) {
    $default = media_brightcove_variable_default($name);
  }
  // Namespace all variables
  $variable_name = MEDIA_BRIGHTCOVE_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() that uses the Media: Brightcove variable registry.
 *
 * @param string $name
 *  The variable name to set. Note that it will be namespaced by
 *  pre-pending MEDIA_BRIGHTCOVE_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 * @param unknown $value
 *  The value for which to set the variable.
 * @return unknown
 *  Returns the stored variable after setting.
 *
 * @see media_brightcove_variable_get()
 * @see media_brightcove_variable_del()
 * @see media_brightcove_variable_default()
 */
function media_brightcove_variable_set($name, $value) {
  $variable_name = MEDIA_BRIGHTCOVE_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() that uses the Media: Brightcove variable registry.
 *
 * @param string $name
 *  The variable name to delete. Note that it will be namespaced by
 *  pre-pending MEDIA_BRIGHTCOVE_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 *
 * @see media_brightcove_variable_get()
 * @see media_brightcove_variable_set()
 * @see media_brightcove_variable_default()
 */
function media_brightcove_variable_del($name) {
  $variable_name = MEDIA_BRIGHTCOVE_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the Media: Brightcove namespace.
 *
 * @param string $name
 *  Optional variable name to retrieve the default. Note that it has not yet
 *  been pre-pended with the MEDIA_BRIGHTCOVE_NAMESPACE namespace at this time.
 * @return unknown
 *  The default value of this variable, if it's been set, or NULL, unless
 *  $name is NULL, in which case we return an array of all default values.
 *
 * @see media_brightcove_variable_get()
 * @see media_brightcove_variable_set()
 * @see media_brightcove_variable_del()
 */
function media_brightcove_variable_default($name = NULL) {
  static $defaults;

  if (!isset($defaults)) {
    $defaults = array(
      // The path to the Echove class definition in echove.php.
      'echove_path' => '',

      // The description length limit imposed by Brightcove.
      'description_length' => 250,

      // Required variables to interact with the Brightcove API.
      'publisher_id' => '',
      'read_token' => '',
      'write_token' => '',

      // Brightcove player ID's for the default sizes & configurations.
      'full_player_id' => '',
      'preview_player_id' => '',

      // Status message to display for unavailable videos.
      'status_display_unavailable' => 'This video is currently unavailable. Please check back later.',
      'check_for_unavailable' => FALSE,

      'full_size_default' => TRUE,
      'default_width' => 486,
      'default_height' => 412,

      // MediaBrightcove class description for emapi class registry.
      'class_media_brightcove_description' => 'Media: Brightcove provider object.',

      // Limit number of nodes per batch page on update 6108.
      'update_get_metadata_limit' => 5,
      'cron_limit' => 5,
    );
  }

  if (!isset($name)) {
    return $defaults;
  }

  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 *
 * @param string $name
 *  The variable name to retrieve the namespaced name.
 * @return string
 *  The fully namespace variable name, prepended with
 *  MEDIA_BRIGHTCOVE_NAMESPACE.
 */
function media_brightcove_variable_name($name) {
  return MEDIA_BRIGHTCOVE_NAMESPACE . $name;
}
