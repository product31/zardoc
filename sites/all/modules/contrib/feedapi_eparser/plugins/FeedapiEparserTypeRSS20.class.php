<?php
// $Id: FeedapiEparserTypeRSS20.class.php,v 1.1 2009/10/21 22:49:37 neclimdul Exp $
/**
 * @file
 * Type handler for parsing RSS 2.0 wrapped content.
 *
 * This plugin builds on top of the RSS 2.0 namespace plugin for parsing almost
 * all content. It is automatically added by the eparse plugin system.
 */

/**
 * Eparser RSS 2.0 type parsing plugin.
 */
class FeedapiEparserTypeRSS20 extends FeedapiEparserTypePluginXML {

  function getGlobalContext() {
    return $this->getXML()->channel;
  }

  function parseGlobal($global_context) {
    $rss_data = $this->feed->parsed_source->rss20;

    // Detect the title.
    $this->feed->parsed_source->title = isset($rss_data->title) ? $rss_data->title : "";
    // Detect the description.
    $this->feed->parsed_source->description = isset($rss_data->description) ?
      $rss_data->description : "";

    // Detect the link.
    $this->feed->parsed_source->link = isset($rss_data->link) ? $rss_data->link : "";

    // Parse some optional items.
    $this->feed->parsed_source->options = $rss_data;

    // Get a timestamp version of the date.
    $this->feed->parsed_source->timestamp = isset($rss_data->pubDate) ?
      $this->parseDate($rss_data->pubDate) : time();
  }

  function getItems() {
    return $this->xml->xpath('//item');
  }

  /**
   * Parse our RSS 2.0 information out of our items.
   *
   * Some funky stuff goes on here. We need a body for our content but RSS
   * doesn't require that a description be attached. So we have to look in
   * description and title. However, some feed creators also put the content
   * in non standard locations like content:encoded(just encoded on some
   * versions of php).
   *
   * NOTE: I believe the content:encoded searching could be deprecated in favor of
   * an rss 1.0 content namespace plugin.
   */
  function parseItem(&$source_item, &$item) {
    // Get children for current namespace.
    $data = $item->rss20;

    // Track down something good to put in the description.
    if (isset($data->description)) {
      $body = $data->description;
    }
    // Some sources use content:encoded as description i.e. PostNuke PageSetter module.
    if (isset($item->encoded)) {  // content:encoded for PHP < 5.1.2.
      $encoded = (string) $item->encoded;
      if (strlen($body) < strlen($encoded)) {
        $body = $encoded;
      }
    }
    else {
      // content:encoded for PHP >= 5.1.2.
      $content = $source_item->children('http://purl.org/rss/1.0/modules/content/');

      if (isset($content->encoded)) {
        $encoded = (string) $content->encoded;
        if (strlen($body) < strlen($encoded)) {
          $body = $encoded;
        }
      }
    }

    // Standards require that the title be set if there is no description so
    // we'll finally fall back on that.
    if (!isset($body)) {
      $body = $data->title;
    }

    // Required values.
    $item->title = $this->getTitle($data->title, $body);
    $item->description = $body;

    $item->options = $data;

    // Some legacy compatibility.
    $item->options->original_author = (string) (!empty($this->xml->channel->title) ?
      $this->xml->channel->title : '');
    $item->options->original_url = $data->link;
  }
}
