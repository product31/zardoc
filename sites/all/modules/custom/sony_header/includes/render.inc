<?php
// $Id$
/**
 * @file
 * Render functionality for creating sony_header XML.
 */

/**
 * Renders a header into xml.
 *
 * @param $header_id
 * The id of a header.
 * @return unknown_type
 */
function sony_header_render_xml($header_id, $preview = FALSE) {

  $header = sony_header_load($header_id);
  
  // Setup the basic DOM elements.
  $xml = new DOMDocument();
  $xml->preserveWhitespace = false;
  $xml->formatOutput = true;
  $root = $xml->createElement('flashheader');
  $xml->appendChild($root);

  // Add required config element.
  $item = new stdClass();
  $item->type = 'config';
  $item->attributes = array(
    'cssPath' => $header->config_css,
    'fontPath' => $header->config_font,
    'embedFonts' => $header->embed_fonts ? 'true' : 'false',
    'checkPolicy' => $header->check_policy ? 'true' : 'false',
  );
  _sony_header_make_xml_item($xml, $root, (object) $item, $preview);

  // Render dynamic data.
  _sony_header_make_xml($xml, $root, $header->items, $preview);

  $item = new stdClass();
  $item->type = 'contextmenuitem';
  $item->attributes = array();
  $item->content = variable_get('site_name', 'Sony Music Artist Site');
  _sony_header_make_xml_item($xml, $root, (object) $item, $preview);

  $item = new stdClass();
  $item->type = 'contextmenuitem';
  $item->attributes = array(
    'href' => 'http://www.sonymusic.com',
  );
  $item->content = 'Copyright © ' . date("Y") . ' Sony Music Entertainment. All Rights Reserved.';
  _sony_header_make_xml_item($xml, $root, (object) $item, $preview);

  return $xml->saveXML();
}

/**
 * Run through our items and render them.
 *
 * This is semi recursive as it is run on the root as well as containers.
 *
 * @param DOMDocument $xml
 * The base DOMDocument element we're using to build our document.
 * @param DOMElement $element
 * The parent element of the new items.
 * @param array $items
 * A list of elements to iterate through and attach to the parent element.
 * @return
 * Return though $xml by reference.
 */
function _sony_header_make_xml(&$xml, $element, $items, $preview) {
  foreach ($items as $id => $item) {
    $item->attributes = isset($item->attributes) ? $item->attributes : array();
    $item->attributes = array('id' => $item->id) + $item->attributes;
    if($item->publish_item || $preview) {
      _sony_header_make_xml_item($xml, $element, $item, $preview);
    }
  }
}


/**
 * Render an XML element from a items options.
 *
 * @param DOMDocument $xml
 * The base DOMDocument element we're using to build our document.
 * @param DOMElement $parent
 * The parent element of the new items.
 * @param stdClass $items
 * An item to render and attach to the parent element.
 * @return
 * Return though $xml by reference.
 */
function _sony_header_make_xml_item(&$xml, $parent, $item, $preview) {
  static $funcs, $plugins;

  if (!$plugins) {
    ctools_include('plugins');
    $plugins = ctools_get_plugins('sony_header', 'type');
    foreach ($plugins as $name => $plugin) {
      $funcs[$name] = ctools_plugin_get_function($plugin, 'render');
    }
  }

  if (!isset($item->type)) {
    throw new Exception('Missing type on element');
  }

  $element = $xml->createElement($plugins[$item->type]['tag']);

  if (isset($funcs[$item->type])) {
    $funcs[$item->type]($xml, $element, $item, $plugins[$item->type]);
  }

  if ($plugins[$item->type]['container'] && !empty($item->items)) {
    // render all the sub items.
    _sony_header_make_xml($xml, $element, $item->items, $preview);
  }

  // Add attributes to the new element.
  if (isset($item->attributes)) {
    foreach ($item->attributes as $name => $value) {
      $attribute = $xml->createAttribute($name);
      $attribute->appendChild(
        $xml->createTextNode($value)
      );
      $element->appendChild($attribute);
    }
  }
  $parent->appendChild($element);
}

/**
 * Default render callback.
 */
function sony_header_default_render(&$xml, &$element, &$item, $plugin) {

  // Render content into item if content exists.
  if ($plugin['content'] && !empty($item->content)) {
    $element->appendChild(
      $xml->createTextNode($item->content)
    );
  }
}
