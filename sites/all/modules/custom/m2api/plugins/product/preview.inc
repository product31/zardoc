<?php
/**
 * @file
 * Manage previewss.
 */

$plugin = array(
  'fetch' => 'm2api_preview_fetch',
);

/**
 * This plugin definition can be simply deleted when we ugprade to CTools 1.3
 */
function m2api_preview_m2api_product() {
  return array(
    'fetch' => 'm2api_preview_fetch',
  );
}

function m2api_preview_fetch($id) {
  m2api_include('api');
  return _m2api_request('preview', NULL, array('id' => $id));
}
