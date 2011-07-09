<?php
// $Id: FeedapiEparserNamespaceViewsBonus.class.php,v 1.1 2009/10/23 18:10:50 neclimdul Exp $
/**
 * @file
 * Example namespace parser using views bonus xml feeds.
 */

/**
 * Eparser Views Bonus XML type parsing plugin.
 *
 * This extends FeedapiEparserTypePluginXML to get some helpful functions.
 */
class FeedapiEparserNamespaceViewsBonus extends FeedapiEparserNamespacePlugin {

  /**
   * Parse and global information like the title of the feed.
   *
   * Views bonus doesn't really provide any global fields that would be
   * parsed here so this implementation is pretty sparse.
   */
  function parseGlobal($global_context) {
    // This is how we add information directly to the parsed source.
    // $this->feed->parsed_source->title = 'Views Bonus Feed';

    // Generally you will want to namespace this information so it does
    // not collide with other plugins. see parseItem for an example.
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
    // Normally you could use this little helper to convert a bunch of
    // things to strings. Since views bonus' xml doesn't actually have a
    // set schema its less useful.
    $data = $this->convertStrings(array(
      'title',
      ), $source_item);

    // Views bonus feed is very simple. Just store everything in an object.
    foreach ($source_item as $key => $value) {
      // Make sure we convert everything to strings. SimpleXML objects
      // don't always behave well if you treat them as strings.
      $key = (string) $key;
      $data->$key = (string) $value;
    }

    // FeedAPI Node expects these 2 values to be set.
    // This is supopse to be a unique URL pointing to the post. If it is
    // no unique, FeedAPI Node will likely update the previous node
    // instead of creating a new node like you expect.
    $data->original_url = md5(serialize($data));
    // This is suppose to be a uniquely identifying value.
    $data->guid = isset($data->nid) ? $data->nid : md5(serialize($data));

    // FeedAPI expects this to be set and will through notices if it isn't.
    $data->timestamp = isset($data->created) ? $data->created : time();

    // You're going to want to store your information in some sort of
    // unique property on the item so you don't colide with another plugin.
    $item->views_bonus = $data;
  }
}
