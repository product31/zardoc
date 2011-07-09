<?php
// $Id$
/**
 * @file
 *
 */

/**
 * Display the M2 info for a node.
 */
function m2_devel_node_page($node) {
  return m2_devel_item_details($node->m2api_document->type, $node->m2api_document->id);
}

function m2_devel_view_stores() {
  m2api_include('api');
  $stores = m2api_get_stores();
  m2api_debug($stores);

  $rows = array();
  foreach ($stores as $item) {
    $rows[] = array(
      $item->id,
      $item->name,
      $item->permalink,
    );
  }

  $header = array('id', 'name', 'permalink');
  return theme('table', $header, $rows);
}

function m2_devel_view_manifest() {
  m2api_include('api');
  $manifest = m2api_get_manifest();
  m2api_debug($manifest);

  $rows = array();
  foreach ($manifest as $item) {
    $rows[] = array(
      l($item->id, 'm2_devel/details/'. $item->type .'/'. $item->id),
      $item->type,
      $item->title,
    );
  }

  $header = array('id', 'type', 'title');
  return theme('table', $header, $rows);
}

/**
 * Helper to call an m2api_get_* function for a given type and display it's
 * results in a table.
 */
function m2_devel_view_type($type) {
  m2api_include('api');

  $func = "m2api_get_$type";
  if (!function_exists($func)) {
    return t('Cannot find a loader for @type.', array('@type' => $type));
  }

  $items = $func();
  m2api_debug($items);

  $rows = array();
  foreach ($items as $item) {
    $rows[] = array(
      l($item->id, 'm2_devel/details/'. $item->type .'/'. $item->id),
      $item->type,
      $item->title,
    );
  }

  $header = array('id', 'type', 'title');
  return theme('table', $header, $rows);
}

function m2_devel_item_details($type, $id) {
  m2api_include('api');

  $details = m2api_document_load($id, $type);
  if (empty($details)) {
    return t("Drats! We couldn't load @type @id... go blame the the m2 guys, they probably broke it.", array('@type' => $type, '@id' => $id));
  }
  m2api_process_updates($details);

  ctools_include('plugins');
  $plugins = ctools_get_plugins('m2api', 'product');
  $plurals = m2api_get_plurals();

  $rows = array();
  foreach ($details as $property => $value) {
    // If the property is a known model, provide a details link.
    if (isset($plugins[$property]) && is_numeric($value)) {
      $value = l($value, 'm2_devel/details/'. $property .'/'. $value);
    }
    // If the property is a plural of a known model, provide a list of details links.
    else if (is_array($value) && !empty($value) && !is_object($value[0]) && isset($plurals[$property])) {
      $items = array();
      foreach ($value as $id) {
        $items[] = l($id, 'm2_devel/details/'. $plurals[$property] .'/'. $id);
      }
      $value = theme('item_list', $items);
    }
    // Otherwise, cast objects and arrays to strings.
    else if (is_object($value) || is_array($value)) {
      $value = kprint_r($value, 1); //'<pre>'. htmlspecialchars(print_r($value, 1)) .'</pre>';
    }

    $rows[$property] = $value;
  }

  $output = '';
  foreach ($rows as $property => $value) {
    $output .= '<dt>'. $property .'</dt><dd>'. $value .'</dd>';
  }
  $output = '<dl>'. $output .'</dl>';

#  m2api_debug($details);
  return $output;
}

function m2_devel_item_invalidate($type, $id) {
  m2api_include('api');
  m2api_document_invalidate($id);
  drupal_set_message('document cache invalidated for document #'. $id);

  drupal_goto('m2_devel/details/'. $type .'/'. $id);
}
