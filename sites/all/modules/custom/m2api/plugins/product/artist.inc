<?php
/**
 * @file
 * Manage artistss.
 */

$plugin = array(
  'fetch' => 'm2api_artist_fetch',
);

/**
 * This plugin definition can be simply deleted when we ugprade to CTools 1.3
 */
function m2api_artist_m2api_product() {
  return array(
    'fetch' => 'm2api_artist_fetch',
  );
}

function m2api_artist_fetch($id) {
  m2api_include('api');
  return _m2api_request('artist', NULL, array('id' => $id));
}
