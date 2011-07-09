<?php
// $Id: FeedapiEparserTypeJSON.class.php,v 1.1 2009/10/21 22:49:37 neclimdul Exp $
/**
 * @file
 * Type handler for parsing JSON encoded content.
 *
 * Parses JSON (JavaScript Object Notation) encoded content into
 * something usable by feedapi.
 *
 */

/**
 * Eparse JSON type parsing plugin.
 */
class FeedapiEparserTypeJSON extends FeedapiEparserTypePlugin {

  protected $json;

  /**
   * Return the global context used for namespace plugins to find their global feed information.
   *
   * @return
   * PHP Object.
   */
  function getGlobalContext() {
    return $this->getJSON();
  }

  /**
   * Parse global elements.
   */
  function parseGlobal($global_context) {
    $this->feed->parsed_source->title = $this->json->title;
    $this->feed->parsed_source->timestamp = isset($this->json->published) ?
    $this->parseDate($this->json->published) : time();
  }

  /**
   * Retrieve the items collection from the feed.
   */
  function getItems() {
    $this->getJSON();
    $item_list_names = array('items', 'entries', 'entry', 'item');
    foreach ($item_list_names as $possible_name) {
      if (isset($this->json->$possible_name) && is_array($this->json->$possible_name)) {
        return $this->json->$possible_name;
      }
    }
    // Could not find an item list, return empty list
    return array();
  }


  /**
   * Parse feed items.
   */
  function parseItem(&$source_item, &$item) {
    $data = $source_item;

    foreach ((array)$data as $name => $val) {
      $item->$name = $val;
    }

    $item->options = new stdClass;
    $guid_names = array('guid', 'GUID', 'Guid', 'id', 'ID', 'Id');
    foreach ($guid_names as $possible_name) {
      if (isset($data->$possible_name) && is_scalar($data->$possible_name)) {
        $item->options->guid = (string)$data->$possible_name;
        break;
      }
    }
  }

  /**
   * Get the feed JSON object.
   */
  function getJSON() {
    if (!isset($this->json)) {
      if (!$this->download($this->feed)) {
        return FALSE;
      }
      $downloaded_string = $this->source;
      $this->json = $this->decode($downloaded_string);
    }
    return $this->json;
  }

  /**
   * Try and decode JSON.
   *
   * This function tries very hard to use other stable libraries to get
   * information. It mostly silently fails if they don't exist currently.
   */
  function decode($data) {
    // Prefer PHP 5.2's json function.
    if (function_exists('json_decode')) {
      return json_decode($data);
    }
    // Try using PEAR's JSON library.
    elseif (class_exists('Services_JSON')) {
      $value = new Services_JSON();
      return $value->decode($data);
    }
    // Try using ZEND's JSON library.
    elseif (class_exists('Zend_Json')) {
      try {
        return Zend_Json::decode($data, Zend_Json::TYPE_OBJECT);
      }
      catch (Exception $e) { }
    }
    else {
      watchdog("feedapi_eparser", "Could not find any method to decode JSON.", array(), WATCHDOG_WARNING);
      // TODO Maybe implement our own??? Scary...
    }
  }
}
