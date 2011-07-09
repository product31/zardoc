<?php
// $Id: FeedapiEparseTypeAtom10.inc,v 1.2 2009/08/17 21:59:38 neclimdul Exp $
/**
 * @file
 * Type handler for parsing ATOM 1.0 wrapped content.
 *
 * This plugin builds on top of the ATOM 1.0 namespace plugin collecting
 * data from the parsed_source->atom collection to populate required fields.
 */

/**
 * Eparse ATOM 1.0 type parsing plugin.
 */
class FeedapiEparseTypeAtom10 extends FeedapiEparserTypePluginXML {

  function parseGlobal() {
    $atom_data = $this->parsed_source->atom;

    // Detect the title.
    $this->parsed_source->title = $atom_data->title;
    // Detect the description.
    $this->parsed_source->description = isset($atom_data->subtitle) ?
      $atom_data->subtitle : $atom_data->title;

    // Detect the link.
    foreach ($atom_data->link as $link) {
      if ($link->rel == 'self') {
        $link = isset($link) ? $link : "";
      }
    }

    // Get a timestamp version of the date.
    $this->parsed_source->timestamp = isset($this->pubDate) ?
      $this->parseDate($this->pubDate) : time();

    // Parse some optional items.
    $this->parsed_source->options = drupal_clone($atom_data);
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
  function parseItem(&$xml_item, &$item) {
    $data = $item->atom;

    // Populate body with schedule abstract
    if (isset($data->description)) {
      $body = $data->description;
    }

    // Required values.
    $item->title = $this->getItemTitle($data->title, $body);
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
