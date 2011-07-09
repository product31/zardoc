<?php
// $Id: FeedapiEparserTypePluginXML.class.php,v 1.1 2009/10/21 22:49:37 neclimdul Exp $

/**
 * Basic XML Type Plugin.
 */
abstract class FeedapiEparserTypePluginXML extends FeedapiEparserTypePlugin {

  protected $xml;

  /**
   * Return the global context used for namespace plugins to find their global feed information.
   *
   * @return
   * SimpleXML object.
   */
  function getGlobalContext() {
    // Many feeds will be using the root. The way simpleXML works this will
    // return the root tag as the context.
    return $this->getXML();
  }

  /**
   * Get a SimpleXML object containing the data for a feed.
   *
   * @param $feed
   * The feed to be looked up.
   * @return
   * SimpleXML object setup with the content of the feed.
   */
  protected function getXML() {

    if (!isset($this->xml)) {
      if (!defined('LIBXML_VERSION') || (version_compare(phpversion(), '5.1.0', '<'))) {
        @$this->xml = simplexml_load_string($this->source, NULL);
      }
      else {
        @$this->xml = simplexml_load_string($this->source, NULL, LIBXML_NOERROR | LIBXML_NOWARNING);
      }
    }

    return $this->xml;
  }

  /**
   * Add XML validity check.
   */
  function download() {
    parent::download();

    // Make sure we actually got valid XML.
    if ($this->getXML()) {
      return TRUE;
    }

    watchdog('FeedAPI Eparser', 'Failed to retrieve a valid XML file.', array(), WATCHDOG_ERROR);
    return FALSE;
  }
}
