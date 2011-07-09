<?php
/**
 * @file
 * Manage full_tracks.
 */

$plugin = array(
  'fetch' => 'm2api_full_track_fetch',
);

/**
 * This plugin definition can be simply deleted when we ugprade to CTools 1.3
 */
function m2api_full_track_m2api_product() {
  return array(
    'fetch' => 'm2api_full_track_fetch',
  );
}

function m2api_full_track_fetch($id) {
  m2api_include('api');
  return _m2api_request('full_track', NULL, array('id' => $id));
}
