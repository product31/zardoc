<?php
// $Id: FeedapiEparserTypeAtom10.class.php,v 1.1 2009/10/21 22:49:37 neclimdul Exp $
/**
 * @file
 * Type handler for parsing ATOM 1.0 wrapped content.
 *
 * This plugin builds on top of the ATOM 1.0 namespace plugin collecting
 * data from the parsed_source->atom collection to populate required fields.
 */

/**
 * Eparser ATOM 1.0 type parsing plugin.
 */
class FeedapiEparserTypeAtom10 extends FeedapiEparserTypePluginXML {

  function parseGlobal($global_context) {
    $atom_data = $this->feed->parsed_source->atom;

    // Detect the title.
    $this->feed->parsed_source->title = $atom_data->title;
    // Detect the description.
    $this->feed->parsed_source->description = isset($atom_data->subtitle) ?
      $atom_data->subtitle : $atom_data->title;

    // Detect the link.
    foreach ($atom_data->link as $link) {
      if ($link->rel == 'self') {
        $link = isset($link) ? $link : "";
      }
    }

    // Get a timestamp version of the date.
    $this->feed->parsed_source->timestamp = isset($atom_data->pubDate) ?
      $this->parseDate($atom_data->pubDate) : time();

    // Parse some optional items.
    $this->feed->parsed_source->options = drupal_clone($atom_data);
  }

  /**
   * Retrieve the items collection from the xml feed.
   */
  function getItems() {
    return $this->xml->entry;
  }

  /**
   * Parse feed items.
   */
  function parseItem(&$source_item, &$item) {
    $data = $item->atom;

    // Populate body with schedule abstract
    if (isset($data->description)) {
      $body = $data->description;
    }

    // Required values.
    $item->title = $this->getTitle($data->title, $body);
    $item->description = $body;

    $item->options = drupal_clone($data);
    $item->options->original_author = (string) (!empty($this->xml->author->name) ?
      $this->xml->author->name : '');

    foreach ($data->link as $link) {
      if ($link->rel == 'self') {
        $link = isset($link) ? $link : "";
      }
    }
    $item->options->original_url = $link->href;
    $item->options->guid = $data->id;
  }

}
