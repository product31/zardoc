<?php
/**
 * @file
 * Manage digital albums.
 */

$plugin = array(
  'fetch' => 'm2api_digital_album_fetch',
);

/**
 * This plugin definition can be simply deleted when we ugprade to CTools 1.3
 */
function m2api_digital_album_m2api_product() {
  return array(
    'fetch' => 'm2api_digital_album_fetch',
  );
}

function m2api_digital_album_fetch($id) {
  m2api_include('api');
  return _m2api_request('digital_album', NULL, array('id' => $id));
}
