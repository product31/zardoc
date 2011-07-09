<?php
// $Id: FeedapiEparserTypeViewsBonus.class.php,v 1.1 2009/10/23 18:10:50 neclimdul Exp $
/**
 * @file
 * Example type parser using Views Bonus XML Feeds.
 */

/**
 * Eparser Views Bonus XML type parsing plugin.
 *
 * This extends FeedapiEparserTypePluginXML to get some helpful functions.
 */
class FeedapiEparserTypeViewsBonus extends FeedapiEparserTypePluginXML {

  /**
   * This function returns that global context.
   *
   * This is required by type plugins and returns the context for
   * finding out global information about the feed like the title, etc.
   */
  function getGlobalContext() {
    // This is the same as the parent function so its only here for clarity.
    return $this->getXML();
  }

  /**
   * This function should return an array of feed items.
   */
  function getItems() {
    return $this->xml->xpath('//node');
  }

  /**
   * Parse and global information like the title of the feed.
   *
   * Views bonus doesn't really provide any global fields that would be
   * parsed here so this implementation is pretty sparse.
   */
  function parseGlobal($global_context) {
    // This is how we add information directly to the parsed source.
    $this->feed->parsed_source->title = 'Views Bonus Feed';
  }

  /**
   * Parse individual items for a feed.
   *
   * @param $source_item
   * One of the items, unmodified, from getItems()
   * @param $item
   * This is the item we're building up to store in the final parsed object.
   */
  function parseItem(&$source_item, &$item) {
    // As a type plugin there are certain responsibilities parseItem has.
    // Every item is expected to have a title, description, timestamp
    // and an options object.

    // Since this is a very simple plugin that doesn't actualy know much
    // about the view being exported we guess and provide a default.

    //
    $item->title = isset($item->views_bonus->title) ? $item->views_bonus->title : 'Views bonus feed item';
    $item->description = isset($item->views_bonus->body) ? $item->views_bonus->body : 'Views bonus feed item';

    // This tends to works out pretty well as a value for the options array.
    $item->options = $item->views_bonus;
  }
}
