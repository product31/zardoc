<?php
// $Id: views_plugin_style_rss.inc,v 1.2 2008/12/02 00:02:06 merlinofchaos Exp $
/**
 * @file
 * Contains the RSS style plugin.
 */

/**
 * Default style plugin to render an RSS feed.
 *
 * @ingroup views_style_plugins
 */
class azuki_plugin_style_rss extends views_plugin_style_rss {

  /**
   * Return an array of additional XHTML elements to add to the channel.
   *
   * @return
   *   An array that can be passed to format_xml_elements().
   */
  function get_channel_elements() {
    return array(array('xmlns:media' => 'http://search.yahoo.com/mrss/'));
  }
}
