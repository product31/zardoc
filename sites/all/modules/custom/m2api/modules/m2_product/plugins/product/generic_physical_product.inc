<?php
/**
 * @file
 * Manage generic_physical_products.
 */

$plugin = array(
  'insert' => 'm2_product_generic_physical_product_insert',
  'update' => 'm2_product_generic_physical_product_update',
  'hash_fields' => array('title', 'short_description_html', 'long_description_html', 'upc', 'stock_info', 'pricing', 'graphic'),
);

/**
 * This plugin definition can be simply deleted when we ugprade to CTools 1.3
 */
function m2_product_generic_physical_product_m2api_product() {
  return array(
    'insert' => 'm2_product_generic_physical_product_insert',
    'update' => 'm2_product_generic_physical_product_update',
    'hash_fields' => array('title', 'short_description_html', 'long_description_html', 'upc', 'stock_info', 'pricing', 'graphic'),
  );
}

function m2_product_generic_physical_product_insert($doc) {
  $node = new stdClass();
  $node->type = 'm2_product';
  $node->body = '';
  $node->teaser = node_teaser($node->body);
  $node->language = language_default('language');
  $node->uid = 1;

  module_load_include('inc', 'node', 'node.pages');
  node_object_prepare($node);

  _m2_product_generic_physical_product_node_data($doc, $node);
  node_save($node);
}

function m2_product_generic_physical_product_update($doc, &$node) {
  _m2_product_generic_physical_product_node_data($doc, $node);
  node_save($node);
}

/**
 * This should be done after a full node load or on a new node after running
 * it through node_object_prepare().
 */
function _m2_product_generic_physical_product_node_data($doc, &$node) {
  $node->title = $doc->title;
  $node->m2api_document = $doc;

  if (!empty($doc->long_description_html->en)) {
    $node->body = $doc->long_description_html->en;
  }
  elseif (!empty($doc->short_description_html->en)) {
    $node->body = $doc->short_description_html->en;
  }

  // TODO: it might make sense to check for changes to the image...
  if (empty($node->field_m2_product_image[0]['fid']) && !empty($doc->graphic)) {
    // Check that it's a valid image and determine the file type.
    $info = getimagesize($doc->graphic);
    $extensions = array(IMG_GIF => 'gif', IMG_JPG => 'jpg', IMG_PNG => 'png');
    if ($info && $extensions[$info[2]]) {
      // Get a temporary filename.
      $temp_path = file_directory_temp() ."/{$doc->id}.{$extensions[$info[2]]}";
      // Download the image to a temporary file...
      if (copy($doc->graphic, $temp_path)) {
        // ...then move it to the files directory.
        module_load_include('inc', 'filefield', 'field_file');
        $file = field_file_save_file($temp_path, array(), file_directory_path());
        $file->data = array();
        $file->list = 0;
        $node->field_m2_product_image[0] = $file;
      }
    }
  }

  if (!empty($doc->stock_info[0]->availability_date)) {
    $datetime = $doc->stock_info[0]->availability_date . 'T00:00:00';
    $timezone_name = 'America/New_York';
    $timezone = timezone_open($timezone_name);

    $node->field_m2_available_date[0] = array(
      'value' => $datetime,
      'timezone' => $timezone_name,
      'offset' => timezone_offset_get($timezone, date_create($datetime, $timezone)),
    );
  }
}
