<?php
// $Id: FeedapiEparserTypeTwitter.class.php,v 1.2 2010/01/05 20:41:16 tomot Exp $ 

/**
 * @file
 * Parses a status update out of a Twitter xml feed.
 * Extends xml type.
 */

/**
 * Eparse xml type parsing plugin.
 */
class FeedapiEparserTypeTwitter extends FeedapiEparserTypePluginXML {

  function parseGlobal($global_context) {}

  /**
   * Retrieve the items collection from the feed.
   */
  function getItems() {
    return $this->xml->xpath('//status');
  }


  /**
   * Parse feed items.
   */
  function parseItem(&$source_item, &$item) {
    // parent::parseItem($source_item, $item);
    $tmp = $this->convertStrings(array('id', 'created_at', 'text', 'source', 'truncated', 'in_reply_to_status_id'), $source_item);
    if ($tmp->id) {
      $item->options->guid = $tmp->id;
      // Convert Twitter's "created at" to a timestamp
      $item->options->timestamp = strtotime($tmp->created_at);
      foreach ((array)$tmp as $key => $val) {
        $item->$key = $val;
      }
      // Feedapi expects the description to be there to generate teaser. See line 314 of feedapi_node.module
      $item->description = $item->text;
      // @todo add rest of xml as seen at http://twitter.com/statuses/user_timeline/14923080.xml
    }
  }
}
