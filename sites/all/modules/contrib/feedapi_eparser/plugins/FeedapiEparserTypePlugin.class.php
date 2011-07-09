<?php
// $Id: FeedapiEparserTypePlugin.class.php,v 1.1 2009/10/21 22:49:37 neclimdul Exp $

/**
 * Basic class for Type plugins.
 *
 * Type plugins are the core of parsing a feed. They know about the structure of the
 * document and can there for parse general information and build the structures used by
 * appropriate namespace plugins to parse additional information.
 */
abstract class FeedapiEparserTypePlugin extends FeedapiEparserPluginBase {
  protected $namespace_plugins = array();

  function init(&$feed) {
    parent::init($feed);

    // Initialize parsed source variable.
    $feed->parsed_source = new stdClass();

    // Store a reference to the type plugin so namespace plugins can interact with it.
    $feed->type_plugin = &$this;

    // Find default namespace plugins and attach them.
    $def = feedapi_eparser_get_plugin_data($feed->eparse->type, 'feed_type');
    if (!empty($def['default namespaces'])) {
      foreach ($def['default namespaces'] as $namespace) {
        $this->ensureNamespace($namespace);
      }
    }

    // Attach any explicitly added namespace plugins.
    foreach ($feed->eparse->namespaces as $namespace) {
      $this->ensureNamespace($namespace);
    }
  }

  /**
   * Download and parsing a feed.
   */
  function fetch() {
    $cid = 'eparse:' . $this->feed->nid;
    if ($data = cache_get($cid)) {
      $feed_content = $data->data;
    }
    else {

      // Before anything else, make sure we download the source.
      $tmp = $this->download();
      if ($tmp !== FALSE) {
        $feed_content = $this->parse();

        // If the feed has a cache time, respect it.
        if (isset($this->feed->parsed_source->options->ttl)) {
          cache_set($cid, $this->feed->parsed_source, 'cache', time() + $this->feed->parsed_source->options->ttl);
        }
      }
      else {
        $feed_content = FALSE;
      }
    }

    return $feed_content;
  }

  /**
   * Do all the parsing magic.
   *
   * @return
   * A parsed feed object.
   */
  function parse() {
    // The global context is a bit of a hack but it should work for now...
    $global_context = $this->getGlobalContext();

    foreach ($this->namespace_plugins as $plugin) {
      $plugin->parseGlobal($global_context);
    }
    $this->parseGlobal($global_context);

    $this->feed->parsed_source->items = array();
    foreach ($this->getItems() as $item) {
      $destination_item = new stdClass();
      foreach ($this->namespace_plugins as $plugin) {
        $plugin->parseItem($item, $destination_item);
      }

      $this->parseItem($item, $destination_item);
      // Let modules alter the parsed item before returning.
      drupal_alter('eparse_parse_item', $destination_item, $item, $this->feed);

      $this->feed->parsed_source->items[] = $destination_item;
    }

    // Let modules alter the parsed source before returning.
    drupal_alter('eparse_parse_global', $this->feed->parsed_source, $global_context, $this->feed);

    return $this->feed->parsed_source;
  }

  /**
   * Ensure we have a copy of the given namespace in our namespace plugins.
   *
   * @param $namespace
   * @return unknown_type
   */
  function ensureNamespace($namespace) {
    if (!isset($this->namespace_plugins[$namespace])) {
      $this->namespace_plugins[$namespace] = feedapi_eparser_load_namespace_plugin($namespace, $this->feed);
    }
  }

  /**
   * Return the global context used for namespace plugins to find their global feed information.
   *
   * @return
   * An array.
   */
  abstract function getGlobalContext();

  /**
   * Fetch string data from some location stored on the feed object.
   *
   * @param $feed
   * The feed to download.
   * @return
   * String.
   */
  function download() {
    $feed = $this->feed;

    ctools_include('plugins');
    $download = ctools_plugin_load_function('eparse', 'download_plugins', $feed->eparse->download, 'fetch');
    if ($download) {
      $this->source = $download($feed);
      if ($this->source !== FALSE) {
        return TRUE;
      }
      $node = node_load($feed->nid);
      watchdog('FeedAPI Eparser', 'Download failed for !feed', array('!feed' => l($node->title, 'node/' . $node->nid)), WATCHDOG_ERROR);
    }
    else {
      $node = node_load($feed->nid);
      watchdog('FeedAPI Eparser', 'Failed to load download plugin for !feed.', array('!feed' => l($node->title, 'node/' . $node->nid)), WATCHDOG_ERROR);
    }
    return FALSE;
  }
}
