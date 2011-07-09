<?php
// $Id$

/**
 * @file
 * Provide Sony Queued Carousels as content.
 */

/**
 * Callback function to supply a list of content types.
 */
function sony_queuedcarousel_queuedcarousel_ctools_content_types() {
  return array(
    // And this is just the administrative title.
    // All our callbacks are named according to the standard pattern and can be deduced.
    'title' => t('Queued Carousel'),
  );
}

/**
 * Return all queuedcarousel content types available.
 */
function sony_queuedcarousel_queuedcarousel_content_type_content_types() {

  $types = array();
  $result = db_query('SELECT * FROM {sony_queuedcarousel}');
  while ($queue = db_fetch_object($result)) {
    $types[$queue->queue_id] = array(
      'title' => $queue->title,
      'category' => t('Queued Carousel'),
    );
  }

  return $types;
}

/**
 * Output function for the 'queuedcarousel' content type.
 */
function sony_queuedcarousel_queuedcarousel_content_type_render($subtype, $conf) {
  $queue = sony_queuedcarousel_queue_load($subtype);
  $content->title = $queue->title;
  $content->admin_links = array(
    array(
      'title' => t('Configure carousel'),
      'alt' => 'foo',
      'href' => 'admin/build/queuedcarousel/manage/' . $subtype,
      'query' => drupal_get_destination(),
    ),
  );
  $content->content = theme('sony_queuedcarousel', $queue);

  return $content;
}
