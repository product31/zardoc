<?php
// $Id: FeedapiEparseNamespaceFeedburner.inc,v 1.1 2009/08/14 03:15:40 neclimdul Exp $
/**
 * @file
 * Parse content from the feedburner namespace.
 */

class FeedapiEparseNamespaceFeedburner extends FeedapiEparserNamespacePlugin {
  function parseGlobal($global_context) {}

  function parseItem(&$xml_item, &$item) {
    $content = $xml_item->children('http://rssnamespace.org/feedburner/ext/1.0');
    $item->feedburner = $this->convertStrings(array(
      'origLink',
      'origEnclosureLink',
    ), $content);
  }
}