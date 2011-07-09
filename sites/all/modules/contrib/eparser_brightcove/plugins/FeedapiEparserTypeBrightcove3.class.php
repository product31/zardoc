<?php
// $Id: FeedapiEparserTypeBrightcove3.class.php,v 1.1.2.1 2009/10/22 16:52:10 andrewlevine Exp $
/**
 * @file
 * Parses a brightcove video link out of a brightcove JSON feed to
 * be used by media_brightcove / emfield. Extends JSON type
 *
 */

/**
 * Eparse JSON type parsing plugin.
 */
class FeedapiEparserTypeBrightcove3 extends FeedapiEparserTypeJSON {

  function parseGlobal($global_context) {
    $this->feed->parsed_source->title = $this->json->name;
    $this->feed->parsed_source->id = $this->json->id;
  }

  /**
   * Retrieve the items collection from the feed.
   */
  function getItems() {
    if (isset($this->json->videos) && is_array($this->json->videos)) {
      return $this->json->videos;
    }
    // Could not find an item list, return empty list
    return array();
  }


  /**
   * Parse feed items.
   */
  function parseItem(&$source_item, &$item) {
    parent::parseItem($source_item, $item);
    if ($source_item->id) {
      $item->fake_bc_link = 'http://link.brightcove.com/services/player/bcpid00000000000?bctid=' . $source_item->id;
    }
  }
}
