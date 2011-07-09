<?php
/**
 * @file
 * Manage cds.
 */

$plugin = array(
  'fetch' => 'm2api_compact_disc_fetch',
);

/**
 * This plugin definition can be simply deleted when we ugprade to CTools 1.3
 */
function m2api_compact_disc_m2api_product() {
  return array(
    'fetch' => 'm2api_compact_disc_fetch',
  );
}

function m2api_compact_disc_fetch($id) {
  m2api_include('api');
  return _m2api_request('compact_disc', NULL, array('id' => $id));
}