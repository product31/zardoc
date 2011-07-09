<?php
// $Id: FeedapiEparserNamespaceRSS20.class.php,v 1.1 2009/10/21 22:49:37 neclimdul Exp $
/**
 * @file
 * Parse RSS 2.0 data from its namespace.
 */

/**
 * Eparser RSS 2.0 namespace handler.
 */
class FeedapiEparserNamespaceRSS20 extends FeedapiEparserNamespacePlugin {

  function parseGlobal($global_context) {
    $content = $this->findContent($global_context);

    // Find what we can find.
    $this->feed->parsed_source->rss20 = $this->convertStrings(array(
      'title',
      'description',
      'link',
      'language',
      'copyright',
      'managingEditor',
      'webMaster',
      'pubDate',
      'lastBuildDate',
      'category',
      'generator',
      'docs',
      //'cloud',
      'ttl',
      'image' => array(
        'url',
        'title',
        'link',
        'width',
        'height',
        'description',
      ),
      'rating',
      // Does something maybe?
      'textInput' => array(
        'title',
        'description',
        'name',
        'link',
      ),
      //'skipHours',
      //'skipDays',
    ), $content);
  }

  function parseItem(&$source_item, &$item) {
    $content = $this->findContent($source_item);

    $data = $this->convertStrings(array(
      'title',
      'description',
      'link',
      'author',
      'comments',
      'enclosure',
      'guid',
      'pubDate',
      'source',
    ), $content);

    // Required values.
    $data->title = $this->getTitle($data->title, $data->description);
    $data->timestamp = isset($data->pubDate) ? $this->parseDate($data->pubDate) : time();
    // FeedAPI Node requires this to exist
    $data->guid = isset($data->guid) ? $data->guid : NULL;

    $additional_taxonomies = $this->parseCategories((array) $content);
    // Some legacy compatibility.
    $data->domains = $additional_taxonomies['RSS Domains'];
    $data->tags = $additional_taxonomies['RSS Categories'];

    $item->rss20 = $data;
  }

  /**
   * Figure out where the RSS data is stored.
   *
   * @param $context
   * @return
   * SimpleXML Object pointing to our rss content.
   */
  function findContent($context) {
    // In a very rare few cases, this could be actually stored using an XML namespace.
    $content = $context->children('http://backend.userland.com/RSS2');
    // Its a very very very rare case so we fall back to the basic context where
    // these items will generally show up if the namespace isn't there.
    if (empty($content)) {
      $content = $context;
    }
    return $content;
  }

  /**
   * Parse a list of categories.
   *
   * Note: This was abstracted from code in parser_common_syndication and I'm
   * not familiar with all the logic.
   * @param $context
   * @return unknown_type
   */
  function parseCategories($context) {
    $additional_taxonomies = array(
      'RSS Categories' => array(),
      'RSS Domains' => array(),
    );

    if (isset($context['category'])) {
      // SimpleXML does not parse single entries into arrays so fix it.
      if (!is_array($context['category'])) {
        $context['category'] = array($context['category']);
      }
      foreach ($context['category'] as $category) {
        $additional_taxonomies['RSS Categories'][] = (string) $category;
        if (isset($category['domain'])) {
          $domain = (string) $category['domain'];
          if (!empty($domain)) {
            if (!isset($additional_taxonomies['RSS Domains'][$domain])) {
              $additional_taxonomies['RSS Domains'][$domain] = array();
            }
            $additional_taxonomies['RSS Domains'][$domain][] = count($additional_taxonomies['RSS Categories']) - 1;
          }
        }
      }
    }

    return $additional_taxonomies;
  }
}
