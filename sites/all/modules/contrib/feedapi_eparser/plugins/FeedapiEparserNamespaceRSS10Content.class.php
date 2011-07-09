<?php
// $Id: FeedapiEparserNamespaceRSS10Content.class.php,v 1.1 2009/10/21 22:49:37 neclimdul Exp $
/**
 * @file
 * Parses RSS 1.0 content module data from its namespace.
 */

/**
 * Eparser RSS 1.0 namespace content module handler.
 */
class FeedapiEparserNamespaceRSS10Content extends FeedapiEparserNamespacePlugin {

  function parseGlobal($global_context) {
    $content = $this->findContent($global_context);

    // Find what we can find.
    $this->feed->parsed_source->rss10_content = $this->convertStrings(array(
      'encoded',
    ), $content);
  }

  function parseItem(&$source_item, &$item) {
    $content = $this->findContent($source_item);

    $data = $this->convertStrings(array(
      'encoded',
    ), $content);

    $item->rss10_content = $data;
  }

  /**
   * Return where the RSS data is stored.
   *
   * @param $context
   * @return
   * SimpleXML Object pointing to our rss content.
   */
  function findContent($context) {
    return $context->children('http://purl.org/rss/1.0/modules/content/');
  }
}
