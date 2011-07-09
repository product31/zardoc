<?php
// $Id: FeedapiEparserNamespaceFeedburner.class.php,v 1.1 2009/10/21 22:49:37 neclimdul Exp $
/**
 * @file
 * Parse content from the feedburner namespace.
 */

class FeedapiEparserNamespaceFeedburner extends FeedapiEparserNamespacePlugin {
  function parseGlobal($global_context) {}

  function parseItem(&$source_item, &$item) {
    $content = $source_item->children('http://rssnamespace.org/feedburner/ext/1.0');
    $item->feedburner = $this->convertStrings(array(
      'origLink',
      'origEnclosureLink',
    ), $content);
  }
}
