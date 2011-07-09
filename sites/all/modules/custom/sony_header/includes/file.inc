<?php
/**
 * Some helper functions to smooth interacting with Drupal's lackluster file API.
 */

/**
 * We don't actually need a save function since this is actually handled
 * in a fairly reasonable way by core's API's. Go figure.
 */

/**
 * Missing core file object load function.
 *
 * @param $fid
 * @return unknown_type
 */
function sony_header_load_file($fid) {
  return db_fetch_object(db_query('SELECT * FROM {files} WHERE fid = %d', $fid));
}

/**
 * Missing core file delete object function.
 * @return unknown_type
 */
function sony_header_file_delete($file) {
  // Figure out what the file id is.
  if (is_object($file)) {
    $fid = $file->fid;
  }
  else {
    $fid = $file;
    $file = sony_header_load_file($fid);
  }

  // Delete the entry from the files table. We might want to try and track
  // references but... that isn't something drupal really supports. Just look
  // at all the problems the imagefield module has with this.
  db_query('DELETE FROM {files} WHERE fid = %d', $fid);

  // Remove the file from filesystem.
  file_delete($file->filepath);
}

/**
 * Submit helper function for 
 */
function sony_header_flexi_file_submit($form, $form_state, $default) {

  // Default return value.
  $return = FALSE;

  // Save new file uploads.
  $path = file_directory_path();
  if (file_check_directory($path, FILE_CREATE_DIRECTORY)) {
    $validators = array(
      'file_validate_extensions' => array($form['#file_types']),
    );

    if (!empty($form_state['upload']['delete']) && $form_state['upload']['delete']) {
      sony_header_file_delete($default['file']);
      unset($default['file']);
    }

    $file = file_save_upload($form['#source'], $validators, $path);
    if ($file) {
      $return['file'] = $file->fid;
      if (!empty($default['file'])) {
        // Try to delete the old file.
        sony_header_file_delete($default['file']);
		//drupal_set_message($file->filename . t(' has been removed'));
      }
	  // Now we neet to change the status of the file to permanent so that cron doesn't delete it 
	  file_set_status($file, FILE_STATUS_PERMANENT);
	  drupal_set_message($file->filename . t(' has been uploaded'));
      // TODO - Do we need to check and see that they tried to upload a file and it just failed?
    }
    elseif ($form_state['manual']['path']) {
      // Convert values to attributes.
      $return['path'] = $form_state['manual']['path'];

      if (!empty($default['file'])) {
        // Try to delete the old file.
        sony_header_file_delete($default['file']);
      }
    }
    elseif (isset($default['file']) && $default['file']) {
      $return = $default;
      // is there a file attached to the file?
    }
    elseif ($form['#required']) {
      drupal_set_message(t('Unable to save file. Please edit and try again or contact site administrator.'), 'error');
    }
  }
  else {
    // This shouldn't be a common error. Just a site setup problem.
    drupal_set_message(t('Unable to create storage directory. Please contact site administrator.'), 'error');
  }

  return $return;
}

/**
 * Find the file path from our goofy source array.
 *
 * @param $src
 * The goofy src array(or string).
 * @return
 * The path to a file.
 */
function sony_header_flexi_file_load(&$src) {

  $return = array();
  if (!is_array($src)) {
    // This only happens really with imports but its handy to be consistent when it happens.
    $return['path'] = $src;
  }
  elseif (!empty($src['file'])) {
    // Load of a file object because its more useful overall.
    $return['file'] = sony_header_load_file($src['file']);
  }
  else {
    $return['path'] = empty($src['path']) ? '' : $src['path'];
  }

  return $return;
}

function sony_header_flexi_file_render($src) {
  if (!empty($src['file'])) {
    // Call base path directly because url() will include localizations breaking
    // the actual path on global sites. Yuck.
    return base_path() . $src['file']->filepath;
  }

  if (!empty($src['path'])) {
    global $base_path;
    if ((strpos($src['path'], 'http') !== 0) && (strpos($src['path'], $base_path) !== 0)) {
      $src['path'] = $base_path . $src['path'];
    }
    return $src['path'];
  }

  // Should this be removed?
  if (!is_array($src)) {
    return $src;
  }

  return '';
}