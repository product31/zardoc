<?php
// $Id$

/**
 * @file
 * Implements a FeedAPI mapper on behalf of the ImageField module.
 * @link http://drupal.org/project/imagefield
 */

/**
 * Implementation of hook_feedapi_mapper().
 */
function imagefield_feedapi_mapper($op, $node, $field_name, $feed_element = array(), $sub_field = '') {
  if (strpos($field_name, 'field_') !== 0
    || !($field = feedapi_mapper_content_is_cck_type($field_name, array('filefield')))
    || $field['widget']['module'] != 'imagefield') {
    // Not an imagefield field.
    return;
  }
  switch ($op) {
  case 'describe':
    return t('Maps image URLs to CCK ImageFields. The image will be downloaded and saved as a local file. You can choose whether to keep the original file name or use a hash value of the URL. The latter is better for images that are returned by scripts (like getimage.php?foo=), otherwise they would all be saved as "getimage.php".');

  case 'list':
    $sub_fields = array(
      'original' => t('Original file name'),
      'md5' => t('Hashed URL'),
    );
    return $sub_fields;

  case 'map':
    if ($feed_element) {
      $field = content_fields($field_name);
      $items = (array)$node->$field_name;
      foreach ((array)$feed_element as $element) {
        $url = NULL;
        if (is_array($element)) {
          // is this an options->enclosure-media->type array
          if (valid_url($element['link'])) {
            $url = $element['link'];
          }
          elseif (valid_url($element['player'])) {
            $url = $element['player'];
          }
        }
        elseif (is_string($element) && valid_url($element)) {
          // not sure when this would be called but for completeness
          $url = $element;
        }
        if ($url
          && $file = _feedapi_mapper_imagefield_file_insert($url, $sub_field, $field)) {
          // Always add as last, Image Field takes care of deleting the
          // first image for non-multiple fields.
          $items[] = $file;
          // update the file status in the database
          field_file_save($node, $file);
          if (!$field['multiple']) {
            break; // too late if $items isn't empty???
          }
        }
      }
      $node->$field_name = $items;
    }
    return $node;
  }
}

function _feedapi_mapper_imagefield_file_insert($url, $filename_option, $field) {
  global $user;
  static $blacklist;

  if (!isset($blacklist)) {
    // The blacklist is an associative array consisting of an MD5 fingerprint
    // and keyed by file size.
    $blacklist = variable_get('imagefield_mapper_blacklist', array());
  }

  // Download the image.
  $result = drupal_http_request($url);
  if ($result->code != 200) {
    return FALSE;
  }

  // Check for blacklisted image.
  //$filesize = strlen($result->data);
  $filesize = $result->headers['Content-Length']; // is there a case where Content-Length is not set???
  if (isset($blacklist[$filesize]) && md5($result->data) == $blacklist[$filesize]) {
    return FALSE;
  }

  // Build the filename.
  $mime_type = $result->headers['Content-Type'];
  $filename = _feedapi_mapper_imagefield_get_filename($filename_option, $url, $mime_type);
  if (!$filename) {
    return FALSE;
  }
  $filepath = file_directory_temp() .'/'. $filename;

  // Avoid creating dupes while updating.
  if ($uid && db_result(db_query("SELECT fid FROM {files} WHERE uid = %d AND filename = '%s' AND filesize = %d", $uid, $filename, $filesize))) {
    return FALSE;
  }

  // write the temporary file
  $fp = fopen($filepath, 'w');
  fwrite($fp, $result->data, $filesize);
  fclose($fp);

  // Allow tokenized paths.
  $widget_image_path = $field['widget']['file_path'];
  if (function_exists('token_replace')) {
    $widget_image_path = token_replace($widget_image_path, 'user', $user);
  }

  // ensure the destination exists and create it
  $dest = file_create_path($widget_image_path);
  if (!file_check_directory($dest, FILE_CREATE_DIRECTORY) && !mkdir($dest, 0775, true)) {
    watchdog('feedapi_mapper', 'Failed to create imagefield directory: %dir', array('%dir' => $dest), WATCHDOG_ERROR);
    return false;
  }
  return field_file_save_file($filepath, array(), $dest . '/' . $filename);
}

/**
 * Get local filename from image URL.
 *
 * @param $filename_option
 *   The selected filename generation option.
 * @param $url
 *   The feed URL.
 * @param &$mime_type
 *   The MIME type of the downloaded image.
 * @return
 *   The local filename or FALSE if the file was no image.
 */
function _feedapi_mapper_imagefield_get_filename($filename_option, $url, &$mime_type) {
  // Figure out the proper file extension from the MIME type.
  static $types = array(
    'image/gif' => '.gif',
    'image/jpeg' => '.jpg',
    'image/png' => '.png',
    'image/psd' => '.psd',
    'image/bmp' => '.bmp',
    'image/tiff' => '.tif',
    'image/jp2' => '.jp2',
    'image/iff' => '.iff',
    'image/vnd.wap.wbmp' => '.wbmp',
    'image/xbm' => '.xbm',
    'image/vnd.microsoft.icon' => '.ico',
  );
  if (!isset($types[$mime_type])) {
    return FALSE;
  }

  $ext = $types[$mime_type];

  // Create filename.
  switch ($filename_option) {
  case 'original':
    $components = parse_url($url);
    $filename = basename($components['path']);
    if (strrchr($filename, '.') != $ext) {
      $filename .= $ext;
    }
    return $filename;

  case 'md5':
    return md5($url) . $ext;
  }
}
