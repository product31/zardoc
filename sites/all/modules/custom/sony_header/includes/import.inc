<?php

function _sony_header_header_import($name, $title, $language, $xml) {

  $header = new stdClass();
  $header->name = $name;
  $header->title = $title;
  $header->language = $language;

  foreach ($xml as $tag => $element) {
    if ($tag == 'config') {
      $header->config_css['path'] = (string) $element->attributes()->cssPath;
      $header->config_font['path'] = (string) $element->attributes()->fontPath;
      $header->embed_fonts= (string) $element->attributes()->embedFonts;
      $header->check_policy = (string) $element->attributes()->checkPolicy;
      break;
    }
  }

  // $header->items = array();
  $header->items = _sony_header_header_import_items($xml);

  return $header;
}

function _sony_header_header_import_items(&$xml) {
  static $tags;

  // Initialize a list of valid tags.
  if (!isset($tags)) {
    // Get a list of tags.
    ctools_include('plugins');
    $plugins = ctools_get_plugins('sony_header', 'type');
    foreach ($plugins as $type => $plugin) {
      // We don't want system plugins and config will be handled by the header import.
      if (!$plugin['system'] && $type != 'config') {
        $tags[$plugin['tag']] = $plugin;
      }
    }
  }

  // Iterate through the XML elements and find items.
  $items = array();
  foreach ($xml as $tag => $element) {

    // These are simpleXML elements so we could probably limit the items with XPath or something...
    // This is a simple solution for now though.
    if (isset($tags[$tag])) {
      $item = new stdClass();
      $item->id = '';
      $item->type = $tags[$tag]['name'];
      $item->content = (string) $element;
      $item->weight = 0;

      // Copy attributes into the attributes array.
      foreach ($element->attributes() as $k => $v) {
        // Special handling for id.
        if ($k == 'id') {
          $item->id = (string) $v;
        }
        else {
          $item->attributes[$k] = (string) $v;
        }
      }

      $sub_items = _sony_header_header_import_items($element);
      if (!empty($sub_items)) {
        $item->items = $sub_items;
      }

      $func = ctools_plugin_get_function($tags[$tag], 'import');
      if ($func) {
        $func($item, $element);
      }

      $items[] = $item;
    }
  }

  return $items;
}
