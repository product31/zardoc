<?php
// $Id: FeedapiEparserNamespaceItunes.class.php,v 1.1 2009/10/21 22:49:37 neclimdul Exp $
/**
 * @file
 * Parse content from the itunes podcast namespace.
 * Useful for mirroring data from podcasts.
 */

class FeedapiEparserNamespaceItunes extends FeedapiEparserNamespacePlugin {
  function parseGlobal($global_context) {
    //
    $content = $global_context->children('http://www.itunes.com/dtds/podcast-1.0.dtd');
    $this->feed->parsed_source->itunes = $this->convertStrings(array(
      'subtitle',
      'summary',
      'author',
      'keywords',
      'owner' => array(
        'name',
        'email',
      ),
      'block',
      'explicit',
    ), $content);
    $itunes = &$this->feed->parsed_source->itunes;
    $itunes->keywords = explode(',', $itunes->keywords);
    // @todo needs some magic.
    $itunes->category = array();
    if (isset($content->image)) {
      $itunes->image = (string) $content->image->attributes()->href;
    }
  }

  function parseItem(&$source_item, &$item) {
    $content = $source_item->children('http://www.itunes.com/dtds/podcast-1.0.dtd');
    $item->itunes = $this->convertStrings(array(
      'duration',
      'subtitle',
      'summary',
      'keywords',
      'author',
      'explicit',
      'block',
    ), $content);
    $item->itunes->keywords = explode(',', $item->itunes->keywords);
  }
}
