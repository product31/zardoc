<?php
// $Id$

/**
 * @file
 * Context menu item.
 */

/**
 * Implementation of hook_sony_header_type().
 */
function sony_header_contextmenuitem_sony_header_type() {
  return array(
    'tag' => 'contextMenuItem',
    'content' => TRUE,
    'container' => FALSE,
    'system' => TRUE,
    'render' => 'sony_header_contextmenuitem_render',
  );
}

/**
 * Render callback for textarea element.
 */
function sony_header_contextmenuitem_render(&$xml, &$element, &$item, $plugin) {
  // Filter down the the attributes we're going to render.
  $item->attributes = array_intersect_key($item->attributes, array('href' => TRUE));

  sony_header_default_render($xml, $element, $item, $plugin);
}