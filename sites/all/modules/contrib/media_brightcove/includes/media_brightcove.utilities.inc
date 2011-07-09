<?php
// $Id: media_brightcove.utilities.inc,v 1.1.4.2 2010/09/01 21:30:13 aaron Exp $

/**
 * @file includes/media_brightcove.utilities.includes
 *
 * Utility functions for Media: Brightcove.
 */

/**
 * Read and store the raw data from Brightcove.
 *
 * @param string $code
 *  The URI or Brightcove ID.
 * @return array
 *  The array of the data as returned from Brightcove's API.
 */
function _media_brightcove_raw_data($code) {
  $code = media_brightcove_extract_id_from_uri($code);

  // Initialize the data array.
  $data = array();

  if ($token = media_brightcove_variable_get('read_token')) {
    if (!function_exists('json_decode')) {
      $json_decode_link = l('json_decode', 'http://php.net/json_decode', array('absolute' => TRUE, 'attributes' => array('target' => '_blank')));
      $error_text = "Brightcove: Could not retrieve data for video @vidId because function !json_decode doesn't exist. You need to install PHP version 5.2 or greater for the ability to retrieve Brightcove Metadata.";
      $error_vars = array(
        '@vidId' => $code,
        '!json_decode' => $json_decode_link
      );
      watchdog('media_brightcove', $error_text, $error_vars, WATCHDOG_WARNING);
    }
    else {
      // Connect and fetch a value.
      $url = url('http://api.brightcove.com/services/library', array('query' => array('command' => 'find_video_by_id', 'video_id' => $code, 'token' => $token), 'external' => TRUE));
      $result = drupal_http_request($url);

      if ($result->code != 200) {
        $error_text = 'Brightcove: HTTP error @info when fetching video data from URL !url.';
        $error_vars = array('@info' => "$result->code: $result->error", '!url' => $url);
        watchdog('media_brightcove', $error_text, $error_vars, WATCHDOG_WARNING);
      }
      else {
        $data = json_decode($result->data, TRUE);
        if (!$data) {
          watchdog('media_brightcove', 'Brightcove: Error parsing JSON from !url', array('!url' => $url), WATCHDOG_WARNING);
          // Reset data.
          $data = array();
        }
      }
    }
  }
  else {
    watchdog('media_brightcove', "No !token available for Brightcove's API.", array('!token' => l(t('read token'), 'admin/settings/media_brightcove')), WATCHDOG_WARNING);
  }

  // @TODO: Grab alternative data.
  // @see http://forum.brightcove.com/t5/General-Dev-Questions/Discover-video-still-thumbnail-without-API/td-p/6353

  // Grab the thumbnail URL from the RSS feed for the media.
//   $url = url('http://link.brightcove.com/services/link/bcpid'. $code, array('query' => array('action' => 'mrss', 'v' => '2'), 'external' => TRUE));

//   $data['media_brightcove_rss'] = emfield_request_xml('brightcove', $url, array(), !$reset, TRUE, $code);

  // Create some version control. Thus if we make changes to the data array
  // down the road, we can respect older content. If allowed by Embedded Media
  // Field, any older content will automatically update this array as needed.
  // In any case, you should account for the version if you increment it.
//     $data['emvideo_brightcove_version'] = MEDIA_BRIGHTCOVE_DATA_VERSION;

  // Set our defaults.
  global $user;
  $uri = media_brightcove_uri($code);
  $item = array(
    'uri' => $uri,
    'uid' => $user->uid,
    'status' => 1,
    'timestamp' => time(),
    'data' => serialize($data),
    'title' => isset($data['name']) ? $data['name'] : '',
    'duration' => isset($data['length']) ? round($data['length'] / 1000) : 0,
    'description' => isset($data['shortDescription']) ? $data['shortDescription'] : 0,
    'thumbnail' => $data['videoStillURL'] ? $data['videoStillURL'] : (isset($data['thumbnailURL']) ? $data['thumbnailURL'] : ''),
  );

  // Merge any stored results, overwriting the defaults.
  $results = db_query("SELECT uid, status, timestamp FROM {media_brightcove_metadata} WHERE uri = '%s'", array('uri' => $uri));
  while ($result = db_fetch_array($results)) {
    $item = array_merge($item, $result);
  }

  // We need to see if the record actually exists for the db write.
  $exists = db_result(db_query("SELECT uri FROM {media_brightcove_metadata} WHERE uri = '%s'", array('uri' => $uri)));
  drupal_write_record('media_brightcove_metadata', $item, $exists ? array('uri') : array());

  return $data;
}

/**
 * Helper function for media_brightcove_cron().
 *
 * @see media_brightcove_cron()
 */
function _media_brightcove_cron() {
  // We need to collect any metadata that is missing from node fields.
  $limit = media_brightcove_variable_get('cron_limit');
  $start = media_brightcove_variable_get('cron_start');
  $end = 0;
  $nodes = array();
  $results = db_query_range("SELECT nid, vid, field_name, delta, uri FROM {media_brightcove_fields} WHERE data_collected = 0 ORDER BY vid, field_name, delta", $start, $limit);

  // First collect any missing metadata.
  while ($result = db_fetch_object($results)) {
    $data = media_brightcove_data($result->uri, TRUE);

    // If we now have data, then load the node and add it.
    if (!empty($data)) {
      if (!isset($nodes[$result->nid])) {
        $nodes[$result->nid] = array();
      }
      // Load this revision if we haven't already.
      $nodes[$result->nid][$result->vid] = isset($nodes[$result->nid][$result->vid]) ? $nodes[$result->nid][$result->vid] : node_load($result->nid, $result->vid);
      if (isset($nodes[$result->nid][$result->vid]->{$result->field_name}[$result->delta]['value'])) {
        // Set the data for this field. Note this is only applicable to emvideo.
        $nodes[$result->nid][$result->vid]->{$result->field_name}[$result->delta]['data'] = $data;
        $nodes[$result->nid][$result->vid]->{$result->field_name}[$result->delta]['duration'] = media_brightcove_duration($result->uri);
        $nodes[$result->nid][$result->vid]->{$result->field_name}[$result->delta]['status'] = media_brightcove_video_available($result->uri);
        $nodes[$result->nid][$result->vid]->{$result->field_name}[$result->delta]['version'] = MEDIA_BRIGHTCOVE_DATA_VERSION;
      }
    }
  }

  // Now go through each revision and save it.
  foreach ($nodes as $revisions) {
    foreach ($revisions as $node) {
      // Save the newly collected data into the revision.
      node_save($node);
      // Store the current progress.
      $end = $node->vid;
      media_brightcove_variable_set('cron_start', $end);
    }
  }

  // Ensure we set back to 0 after reaching the end of it all.
  media_brightcove_variable_set('cron_start', $end);
}
