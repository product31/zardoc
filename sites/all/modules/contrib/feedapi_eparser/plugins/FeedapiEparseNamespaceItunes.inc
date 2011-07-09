<?php
// $Id: FeedapiEparseNamespaceItunes.inc,v 1.2 2009/08/17 21:59:38 neclimdul Exp $
/**
 * @file
 * Parse content from the itunes podcast namespace.
 * Useful for mirroring data from podcasts.
 */

class FeedapiEparseNamespaceItunes extends FeedapiEparserNamespacePlugin {
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

  function parseItem(&$xml_item, &$item) {
    $content = $xml_item->children('http://www.itunes.com/dtds/podcast-1.0.dtd');
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
