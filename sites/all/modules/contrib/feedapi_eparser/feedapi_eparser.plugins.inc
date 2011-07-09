<?php
// $Id: feedapi_eparser.plugins.inc,v 1.40 2009/09/02 22:58:55 neclimdul Exp $
/**
 * @file
 * Functions related to our plugin functionality.
 */

/**
 * CTools plugin information callback for type plugins.
 *
 * @return
 * An array of information about the plugin api.
 */
function eparse_ctools_plugin_type_plugins() {
  return array(
    // This is cacheable.
    'cache' => TRUE,
    // Provide additional default values for definition arrays.
    'defaults' => array(
      'name' => '',
      'description' => '',
      // System plugins are used for inheritance and are not visible in the UI.
      'system' => FALSE,
      // This is used by FeedAPI as the feed type.
      'type' => 'XML feed',
    ),
  );
}

/**
 * CTools plugin information callback for namespace plugins.
 *
 * @return
 * An array of information about the plugin api.
 */
function eparse_ctools_plugin_namespace_plugins() {
  return array(
    // This is cacheable.
    'cache' => TRUE,
    // Provide additional default values for definition arrays.
    'defaults' => array(
      'name' => '',
      'description' => '',
      'system' => FALSE,
    ),
  );
}

/**
 * CTools plugin information callback for namespace plugins.
 *
 * @return
 * An array of information about the plugin api.
 */
function eparse_ctools_plugin_download_plugins() {
  return array(
    // This is cacheable.
    'cache' => TRUE,
    // Provide additional default values for definition arrays.
    'defaults' => array(
      'name' => '',
      'description' => '',
    ),
  );
}

function feedapi_eparser_fetch_http_request($feed) {
  $url = $feed->url;
  if (valid_url($url, TRUE)) {
    // Handle password protected feeds.
    $url_parts = parse_url($url);
    $password = $username = NULL;
    if (!empty($url_parts['user'])) {
      $password = $url_parts['pass'];
      $username = $url_parts['user'];
    }
  }

  $headers = array();
  $result = drupal_http_request($url, $headers);
  if (isset($result->error) || empty($result->data)) {
    return FALSE;
  }
  return $result->data;
}

/**
 * Implementation of hook_eparse_type_plugins().
 */
function feedapi_eparser_eparse_type_plugins() {
  $base_path = drupal_get_path('module', 'feedapi_eparser') . '/plugins';
  return array(
    'base' => array(
      'name' => 'Type Base',
      'description' => 'This plugin is not actually used other than as a parent for other plugins.',
      'handler' => 'FeedapiEparserTypePlugin',
      'system' => TRUE,
      'path' => $base_path,
    ),
    'json' => array(
      'name' => 'JSON Base',
      'description' => 'This plugin is not normally used other than as a parent for other plugins.',
      'handler' => array(
        'class' => 'FeedapiEparserTypeJSON',
        'parent' => 'base',
      ),
      'type' => 'JSON Feed',
      'system' => TRUE,
      'path' => $base_path,
    ),
    'xml' => array(
      'name' => 'XML Base',
      'description' => 'This plugin is not actually used other than as a parent for other plugins.',
      'handler' => array(
        'class' => 'FeedapiEparserTypePluginXML',
        'parent' => 'base',
      ),
      'system' => TRUE,
      'path' => $base_path,
    ),
    'rss20' => array(
      'name' => 'RSS 2.0',
      'description' => 'Parse data from an RSS 2.0 Feed.',
      'handler' => array(
        'class' => 'FeedapiEparserTypeRSS20',
        'parent' => 'xml',
      ),
      'default namespaces' => array('rss20'),
      'path' => $base_path,
    ),
    'atom' => array(
      'name' => 'Atom',
      'description' => 'Parse data from an Atom Feed.',
      'handler' => array(
        'class' => 'FeedapiEparserTypeAtom10',
        'parent' => 'xml',
      ),
      'parent' => 'xml',
      'default namespaces' => array('atom10'),
      'path' => $base_path,
    ),
  );
}

/**
 * Implementation of hook_eparse_download_plugins().
 */
function feedapi_eparser_eparse_download_plugins() {
  return array(
    'drupal_http_request' => array(
      'name' => 'Drupal HTTP Request',
      'description' => 'Uses Drupal\'s Http Request function to fetch feeds.',
      'fetch' => 'feedapi_eparser_fetch_http_request',
    ),
  );
}

/**
 * Implementation of hook_eparse_namespace_plugins().
 */
function feedapi_eparser_eparse_namespace_plugins() {
  $base_path = drupal_get_path('module', 'feedapi_eparser') . '/plugins';
  return array(
    'base' => array(
      'name' => 'Base Namespace Plugin',
      'description' => 'iTunes podcast feed information.',
      'handler' => 'FeedapiEparserNamespacePlugin',
      'system' => TRUE,
      'path' => $base_path,
    ),
    'itunes' => array(
      'url' => 'http://www.itunes.com/dtds/podcast-1.0.dtd',
      'name' => 'iTunes',
      'description' => 'iTunes podcast feed information.',
      'handler' => array(
        'class' => 'FeedapiEparserNamespaceItunes',
        'parent' => 'base',
      ),
      'path' => $base_path,
    ),
    'feedburner' => array(
      'url' => 'http://rssnamespace.org/feedburner/ext/1.0',
      'name' => 'Feedburner',
      'description' => 'Additional information added by feedburner with information like original media urls.',
      'handler' => array(
        'class' => 'FeedapiEparserNamespaceFeedburner',
        'parent' => 'base',
      ),
      'path' => $base_path,
    ),
    'rss10_content' => array(
      'url' => 'http://web.resource.org/rss/1.0/modules/content/',
      'name' => 'RSS 1.0 - Content',
      'description' => "RSS Content namespace contains extra items and most importantly the encoded field.",
      'handler' =>  array(
        'class' => 'FeedapiEparserNamespaceRSS10Content',
        'parent' => 'base',
      ),
      'path' => $base_path,
    ),
    'rss20' => array(
      'url' => 'http://backend.userland.com/RSS2',
      'name' => 'RSS 2.0',
      'description' => "Seldom used RSS 2.0 namespace. Should only really be explicitly added if RSS 2.0 data is embeded in another feed type and you really know what you're doing.",
      'handler' =>  array(
        'class' => 'FeedapiEparserNamespaceRSS20',
        'parent' => 'base',
      ),
      'path' => $base_path,
    ),
    'atom10' => array(
      'url' => 'http://www.ietf.org/rfc/rfc4287.txt',
      'name' => 'Atom 1.0',
      'description' => "Atom content.",
      'handler' =>  array(
        'class' => 'FeedapiEparserNamespaceAtom10',
        'parent' => 'base',
      ),
      'path' => $base_path,
    ),
  );
}

/**
 * Build a list of namespace plugins.
 *
 * @see feedapi_eparser_get_namespace_plugins().
 *
 * @param $system
 * Toggle filtering out system objects. If TRUE system plugins will be included.
 * @return
 * An array of namespace plugins.
 */
function _feedapi_eparser_get_namespace_plugins($system = FALSE) {
  ctools_include('plugins');
  $plugins = ctools_get_plugins('eparse', 'namespace_plugins');
  if ($system) {
    return $plugins;
  }
  return array_filter($plugins, '_feedapi_eparser_system_filter');
}

/**
 * Build a list of download plugins.
 *
 * @see feedapi_eparser_get_download_plugins().
 * @return
 * An array of namespace plugins.
 */
function _feedapi_eparser_get_download_plugins() {
  ctools_include('plugins');
  return ctools_get_plugins('eparse', 'download_plugins');
}

/**
 * Build a list of feed_type plugins.
 *
 * @see feedapi_eparser_get_feed_type_plugins().
 *
 * @param $system
 * Toggle filtering out system objects. If TRUE system plugins will be included.
 * @return
 * Array of plugins.
 */
function _feedapi_eparser_get_type_plugins($system = FALSE) {
  ctools_include('plugins');
  $plugins = ctools_get_plugins('eparse', 'type_plugins');
  if ($system) {
    return $plugins;
  }
  return array_filter($plugins, '_feedapi_eparser_system_filter');
}

/**
 * Filter callback to remove filter plugins from a plugin list.
 */
function _feedapi_eparser_system_filter($plugin) {
  return !$plugin['system'];
}

function feedapi_eparser_get_plugin_data($name, $type) {
  static $plugins = array();

  if (!isset($plugins[$type])) {
    switch ($type) {
      case 'feed_type':
        $plugins[$type] = _feedapi_eparser_get_type_plugins();
        break;
      case 'download':
        $plugins[$type] = _feedapi_eparser_get_download_plugins();
        break;
      case 'namespaces':
        $plugins[$type] = _feedapi_eparser_get_namespace_plugins();
        break;
      default:
        return FALSE;
    }
  }

  return $plugins[$type][$name];
}

/**
 * Basic Plugin Interface.
 *
 * These are the methods that are required to be implemented by any
 * plugin class. This includes both Type plugins and Namespace plugins.
 *
 * The feed object:
 * Plugins have access to a feed object which is used for as a context
 * for storage and settings. If the plugin has properly inherited
 * FeedapiEparserPluginBase or a class inheriting it, the feed object
 * will be available at $this->feed.
 *
 * The feed object built on top of the FeedAPI feed object so can use
 * any settings provided by the FeedAPI or one its modules that have
 * been appropriately attached.
 *
 * It also contains a parsed_source property that is used for
 * aggregating the final value returned to FeedAPI. It is shared so
 * especially for namespace plugins, it is a good idea to keep your data
 * namespaced in some way so it does not colide with another plugin.
 */
interface FeedapiEparserPluginInterface {
  /**
   * Initializes a plugin.
   *
   * This called early on in the creation after the constructor and
   * after the feed object has been setup. You should generally
   * call parent::init($feed); first so that any classes you're
   * inheriting from can do their setup.
   *
   * @param $feed
   * A feed object. This is cloned of the FeedAPI feed object.
   * @return
   * No return.
   */
  function init(&$feed);

  /**
   * Parse the global context of a feed.
   *
   * This is where things like the title and description of the feed are
   * set. This may not do a whole lot for a lof of feeds if they only
   * have items.
   *
   * @param $global_context
   * This is the global context. IE the base of the feed.
   */
  function parseGlobal($global_context);

  /**
   * Parse a single item from the feed.
   *
   * @param $source_item
   * This is the source item object.
   * @param $item
   * This is a destination item used to aggregate return values.
   */
  function parseItem(&$source_item, &$item);

  /*
   * Optional functions:
   *
   * These functions are related to form callbacks to provide options.
   */
   function optionsForm(&$form, &$form_state);
   function optionsFormSubmit(&$form, &$form_state);
   function optionsFormValidate(&$form, &$form_state);
}

/**
 * Base class providing generalized utility functions to parsers.
 */
abstract class FeedapiEparserPluginBase implements FeedapiEparserPluginInterface {

  /**
   * Store a reference to the feed object.
   */
  protected $feed;

  function init(&$feed) {
    $this->feed = &$feed;
  }

  /**
   * Blank options forms callbacks are provided here so they are
   * optional for plugins to implement.
   */

  function optionsForm(&$form, &$form_state) {
  }

  function optionsFormValidate(&$form, &$form_state) {
  }

  function optionsFormSubmit(&$form, &$form_state) {
  }

  /**
   * parseGlobal and parseItem have no implementation here to force parsers to implement
   * them. There is at the minimum what they must implement to be functional.
   */

  /*********************************************************************
   * Helper methods
   ********************************************************************/

  /**
   * Parse a date comes from a feed.
   *
   * @param $date_string
   *  The date string in various formats.
   * @return
   *  The timestamp of the string or the current time if can't be parsed
   */
  function parseDate($date_str) {
    static $time;
    if (!isset($time)) {
      $time = time();
    }

    $parsed_date = strtotime($date_str);
    if ($parsed_date === FALSE || $parsed_date == -1) {
      $parsed_date = $this->parseW3CDTF($date_str);
    }
    return $parsed_date === FALSE ? $time-- : $parsed_date;
  }

  /**
   * Parse the W3C date/time format, a subset of ISO 8601.
   *
   * PHP date parsing functions do not handle this format.
   * See http://www.w3.org/TR/NOTE-datetime for more information.
   * Originally from MagpieRSS (http://magpierss.sourceforge.net/).
   *
   * @param $date_str
   *   A string with a potentially W3C DTF date.
   * @return
   *   A timestamp if parsed successfully or FALSE if not.
   */
  function parseW3CDTF($date_str) {
    if (preg_match('/(\d{4})-(\d{2})-(\d{2})T(\d{2}):(\d{2})(:(\d{2}))?(?:([-+])(\d{2}):?(\d{2})|(Z))?/', $date_str, $match)) {
      list($year, $month, $day, $hours, $minutes, $seconds) = array($match[1], $match[2], $match[3], $match[4], $match[5], $match[6]);
      // Calculate the epoch for current date assuming GMT.
      $epoch = gmmktime($hours, $minutes, $seconds, $month, $day, $year);
      if ($match[10] != 'Z') { // Z is zulu time, aka GMT
        list($tz_mod, $tz_hour, $tz_min) = array($match[8], $match[9], $match[10]);
        // Zero out the variables.
        if (!$tz_hour) {
          $tz_hour = 0;
        }
        if (!$tz_min) {
          $tz_min = 0;
        }
        $offset_secs = (($tz_hour * 60) + $tz_min) * 60;
        // Is timezone ahead of GMT?  If yes, subtract offset.
        if ($tz_mod == '+') {
          $offset_secs *= -1;
        }
        $epoch += $offset_secs;
      }
      return $epoch;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Convert strings from formats like simpleXML objects to strings.
   *
   * Helps by patching large groups of conversions. Drupal array love...
   *
   * TODO - Allow some way to force certain keys to exist.
   * TODO - Allow some way to force keys to be multiple values. SimpleXML sucks at these sort of things.
   *
   * @param $map
   * An array of elements in the context.
   * @param $context
   * A simpleXML object that is our current context
   * @return
   * An object containing the converted strings.
   */
  function convertStrings($map, $context) {
    $return = new stdClass;
    foreach ($map as $key => $item) {
      if (is_array($item) && isset($context->$key)) {
        $return->$key = $this->convertStrings($item, $context->$key);
      }
      elseif (!is_array($item) && isset($context->$item)) {
        $return->$item = (string) $context->$item;
      }
    }
    return (object) $return;
  }

  /**
   * Make sure we have a title.
   *
   * We always need a title in FeedAPI but not all feeds actually have one. This helps by creating one out
   * of the first 3 words of the body.
   * @param $title
   * The title, possibly empty.
   * @param $body
   * The body of the content.
   */
  function getTitle($title, $body) {
    if (empty($title) && !empty($body)) {
      // Explode to words and use the first 3 words.
      $words = preg_split("/[\s,]+/", $body);
      $title = $words[0] . ' ' . $words[1] . ' ' . $words[2];
    }
    return $title;
  }
}

