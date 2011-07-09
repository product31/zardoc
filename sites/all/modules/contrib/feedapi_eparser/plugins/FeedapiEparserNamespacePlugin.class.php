<?php
// $Id: FeedapiEparserNamespacePlugin.class.php,v 1.1 2009/10/21 22:49:37 neclimdul Exp $

/**
 * Base class for Namespace plugins.
 *
 * Namespace plugins are designed to be helper classes for type plugins. They use the
 * structure found by the type plugin and pull out compartmentalized pieces of
 * information. They derive they're name from the XML namespaces they where originally
 * implemented to support.
 */
abstract class FeedapiEparserNamespacePlugin extends FeedapiEparserPluginBase {
  protected $parsed_source;

  function init(&$feed) {
    parent::init($feed);
    // DEPRECATED - We should just use the parsed_source on the feed directly now.
    $this->parsed_source = &$this->feed->parsed_source;
  }
}
