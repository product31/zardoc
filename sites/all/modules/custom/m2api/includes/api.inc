<?php
// $Id$
/**
 * @file
 * Functions for abstracting making requests to the m2 api.
 *
 * TODO document funcitons better.
 * TODO These methods should probably do a better job of validating their input.
 *
 */

// Constant for the current version of the API. This part of the request building process.
define('M2API_VERSION', 'v1');

/**
 * Make an API request.
 *
 * A standardized API request, handles default requests against the M2 Rest API.
 *
 * @param $method
 *   String
 * @param $store
 *   String with store name. NULL uses the site's store name. Empty omits the
 *   store name.
 * @param $query
 *   Array with additional arguments to the request.
 * @param $bypass_cache
 *   Boolean indicating that cached data should not be used to fufill the
 *   request.
 * @return
 */
function _m2api_request($method = '', $store = NULL, $query = array(), $bypass_cache = FALSE) {
  $url = variable_get('m2api_api_url', 'http://api.stage.sonymusicdigital.com/');

  // Distinguish between a NULL value (giving the default store) and empty
  // string (no store):
  if (is_null($store)) {
    $store = m2api_get_store();
  }

  $path = '';
  if ($store) {
    $path .= $store . '/';
  }
  $path .= 'api/' . M2API_VERSION . '/' . $method;

  // Just hack this in rather than munging the function sig any further.
  if (isset($query['id'])) {
    $path .= '/' . $query['id'];
    unset($query['id']);
  }

  // Force key to the front of the query.
  $defaults = array(
    'key' => variable_get('m2api_api_key', '109177db7055de2e42958238572b4454'),
    'current_country' => 'US',
  );
  $query = array_merge($defaults, $query);

  $url = url($url . $path, array('external' => TRUE, 'query' => $query));

  // Now that we've got the URL check for a cached value.
  $cid = 'm2_request:' . md5($url);
  if (!$bypass_cache) {
    $cache = cache_get($cid, 'cache');
    if ($cache && !empty($cache->data)) {
      return $cache->data;
    }
  }

  $request = drupal_http_request($url);

  if ($request && $request->code == 200) {
    $response = json_decode($request->data);
    // If caching is enabled and it's a valid response store it for 1 minute.
    if (!$bypass_cache && $response) {
      cache_set($cid, $response, 'cache', time() + 60);
    }
    return $response;
  }

  $error_msg = 'Recieved error code %error_code %error_msg requesting %url';
  $error_variables = array(
    '!url' => $url,
    '%url' => $url,
    '%error_code' => $request->code,
    '%error_msg' => $request->error,
  );
  watchdog('M2API', $error_msg, $error_variables, WATCHDOG_ERROR);
  // Hack in the error so it can be seen.
  // @warning this could be a possible XSS or the worst sort if the url is some
  // how hijacked. Its terribly useful for debuging though.
  m2api_admin_message('<p>'. $error_msg . '</p><iframe src="!url" width="600" height="80"></iframe>', $error_variables, 'error');

  return FALSE;
}

/**
 * Request all objects of a type from M2.
 */
function _m2api_request_all($plural_type, $store = NULL, $arguments = array()) {
  $per_page = 500;
  $page = 1;
  $arguments += array('per_page' => $per_page);
  $documents = array();
  do {
    $arguments['page'] = $page;
    $data = _m2api_request($plural_type, $store, $arguments);
    if ($data == FALSE) {
      m2api_admin_message('Failed loading page %page of %types so no results were returned.', array('%types' => $plural_type, '%page' => $page), 'error');
      return FALSE;
    }
    foreach ($data->results as $document) {
      $documents[$document->id] = $document;
    }
    $page++;
  } while (count($data->results) >= $per_page);
  return $documents;
}

/**
 * Test the connection to the M2 server.
 *
 * @return
 *   Boolean indicating success.
 */
function m2api_can_connect() {
  $response = _m2api_request('tracks', NULL, array('per_page' => 1));
  if ($response === FALSE) {
    m2api_admin_message('Could not connect to an M2 server using these settings.', array(), 'error');
    return FALSE;
  }
  if (isset($response->error)) {
    m2api_admin_message('Could not connect to the store. M2 says error: @error', array('@error' => $response->error), 'error');
    return FALSE;
  }
  return TRUE;
}

/**
 * Get a listing of stores.
 *
 * @return unknown_type
 */
function m2api_get_stores() {
  return _m2api_request_all('stores', '');
}

/**
 * Get a manifest listing.
 */
function m2api_get_manifest($query = array(), $store = NULL) {
  return _m2api_request_all('manifest', $store, $query);
}

/**
 * Get all of the store's albums.
 */
function m2api_get_albums() {
  return m2api_document_fetch_all('album');
}

/**
 * Get all of the store's tracks.
 */
function m2api_get_tracks() {
  return m2api_document_fetch_all('track');
}

/**
 * Get a organized list of tracks.
 */
function _m2api_get_sorted_tracks() {
  foreach (m2api_get_tracks() as $track) {
    $tracks[$track->album][$track->disc_number][$track->track_number] = $track;
  }
  return $tracks;
}

/**
 * Get a list of all products (generic_physical_product and product_group).
 */
function m2api_get_products($store = NULL) {
  return _m2api_request_all('generic_physical_products', $store) +
    _m2api_request_all('product_groups', $store);
}

/**
 * Load an M2 document from cache or the API.
 *
 * @param $id
 *   The M2 document ID.
 * @param $type
 *   The M2 document type or FALSE on error.
 */
function m2api_document_load($id, $type = NULL) {
  $now = time();
  $cache = m2api_document_get_cache($id);
  $hash = ($cache) ? $cache->hash : '';

  // If it's still valid cached data, use it.
  if ($cache && $cache->expire >= $now) {
    $document = unserialize($cache->data);
    $document->_cached = TRUE;
  }
  // Otherwise load from M2.
  else {
    $document = m2api_document_fetch($id, $type);
    if ($document === FALSE || empty($document->id) || empty($document->type)) {
      return FALSE;
    }

    m2api_document_set_cache($document, $now);
  }

  // FIXME: Since the only hash value is stored with the document cache we can't
  // detect changes. The hash should be stored in {m2api_node} so we can check
  // for divergences of {m2api_node} and {m2_api_document_cache}. Disabling the
  // hash checking for now.
  $hash = 'DISABLED';

  // Add the extra join to ensure there's actually a matching node.
  $row = db_fetch_object(db_query("SELECT m.nid, c.hash FROM {m2api_nodes} m
    INNER JOIN {node} n ON m.nid = n.nid
    LEFT JOIN {m2api_document_cache} c ON m.m2id = c.m2id
    WHERE m.m2id = %d", $document->id));
  if (empty($row->nid)) {
    $document->_status = M2API_DOCUMENT_STATUS_NEW;
  }
  else if ($hash != $row->hash) {
    $document->_status = M2API_DOCUMENT_STATUS_CHANGED;
  }
  else {
    $document->_status = M2API_DOCUMENT_STATUS_UNCHANGED;
  }

  return $document;
}

function m2api_document_fetch($id, $type = NULL) {
  if (empty($type)) {
    // If there's no type, load it as a generic document.
    $result = _m2api_request('documents', '', array('id' => $id));
  }
  else {
    $arguments = array('id' => $id);

    // If we've got a type use the plugin to load it, this is prefered since
    // the plugins may expand certain fields.
    $plugin = ctools_get_plugins('m2api', 'product', $type);
    if (!empty($plugin['expand'])) {
      $arguments['expand'] = $plugin['expand'];
    }

    $result = _m2api_request($type, NULL, $arguments);
  }

  if (empty($result)) {
    m2api_admin_message('Could not fetch document id: %id type: %type from M2. The site may be down or you might need to configure the M2 API module.', array('%id' => $id, '%type' => $type ? $type : 'N/A'), 'error');
    return FALSE;
  }
  if (isset($result->error)) {
    m2api_admin_message('There was an error fetching document id: %id type: %type.<br />M2 Error: @error', array('%id' => $id, '%type' => $type ? $type : 'N/A', '@error' => $result->error), 'error');
    return FALSE;
  }

  $document = $result->results[0];
  $document->_cached = FALSE;

  return $document;
}

/**
 * Fetch and cache all documents of a type.
 *
 * This requires that the type's plugin offer a fetch_all method.
 *
 * @param $type
 */
function m2api_document_fetch_all($type) {
  $plugin = ctools_get_plugins('m2api', 'product', $type);

  $arguments = array();
  if (!empty($plugin['expand'])) {
    $arguments['expand'] = $plugin['expand'];
  }

  $documents = _m2api_request_all($type, NULL, $arguments);
  if ($documents !== FALSE) {
    // This is a bit quirky but it lets us easily get all the documents into
    // the cache for m2api_document_load().
    $now = time();
    foreach ($documents as $document) {
      m2api_document_set_cache($document, $now);
    }
  }

  return $documents;
}

function m2api_document_get_cache($id) {
  $cache = db_fetch_object(db_query('SELECT * FROM {m2api_document_cache} WHERE m2id = %d', $id));
  return $cache;
}

function m2api_document_set_cache($document, $now) {
  // Only cache if TTL is not empty.  This allows a plugin to set the TTL to 0.
  $plugin = ctools_get_plugins('m2api', 'product', $document->type);
  if (!empty($plugin['cache_ttl'])) {
    db_query('DELETE FROM {m2api_document_cache} WHERE m2id = %d', $document->id);

    $row = array(
      'm2id' => $document->id,
      'type' => $document->type,
      'data' => $document,
      'expire' => $now + $plugin['cache_ttl'],
      'hash' => m2api_document_hash($document),
    );
    drupal_write_record('m2api_document_cache', $row);

    $document->_cached = TRUE;
  }
}

function m2api_document_hash($doc) {
  $plugin = ctools_get_plugins('m2api', 'product', $doc->type);
  $hash_fields = array('id', 'type') + (isset($plugin['hash_fields']) ? $plugin['hash_fields'] : array());

  $hash_array = array();
  foreach ($hash_fields as $field) {
    $hash_array[$field] = $doc->{$field};
  }

  $hash = md5(serialize($hash_array));
  return $hash;
}

function m2api_process_updates($doc) {
  switch ($doc->_status) {
    case M2API_DOCUMENT_STATUS_NEW:
      // Allow plugin to respond.
      $func = ctools_plugin_load_function('m2api', 'product', $doc->type, 'insert');
      if ($func) {
        $func($doc);
      }
      break;

    case M2API_DOCUMENT_STATUS_CHANGED:
      // Allow plugin to respond.
      $func = ctools_plugin_load_function('m2api', 'product', $doc->type, 'update');
      if ($func) {
        $node = m2api_document_node_load($doc->id);
        $func($doc, $node);
      }
      break;

    case M2API_DOCUMENT_STATUS_UNCHANGED:
      break;
  }
}

/**
 * Returns an array of plural type names mapped to the singular plugin name.
 * This can be useful to match what Ruby does with active record.
 */
function m2api_get_plurals() {
  static $plurals;

  if (!isset($plurals)) {
    $plugins = ctools_get_plugins('m2api', 'product');
    $plurals = array();
    foreach ($plugins as $name => $plugin) {
      if (!empty($plugin['plural'])) {
        $plurals[$plugin['plural']] = $name;
      }
    }
  }

  return $plurals;
}

function m2api_document_node_load($m2id) {
  $nid = db_result(db_query("SELECT m.nid FROM {m2api_nodes} m INNER JOIN {node} n ON m.nid = n.nid WHERE m.m2id = %d AND n.language IN ('', '%s')", $m2id, language_default('language')));
  if ($nid) {
    return node_load($nid);
  }
  return FALSE;
}

function m2api_document_invalidate($m2id) {
  db_query('UPDATE {m2api_document_cache} SET expire = 0, hash = "" WHERE m2id = %d', $m2id);
}

function m2api_product_create_reference($nid, $m2id, $type) {
  db_query("REPLACE INTO {m2api_nodes_products} (nid, m2id, type) VALUES (%d, %d, '%s')", $nid, $m2id, $type);
}

function m2api_product_remove_reference($nid, $m2id) {
  db_query('DELETE FROM {m2api_nodes_products} WHERE nid = %d AND m2id = %d', $nid, $m2id);
}

function m2api_product_remove_all_references($nid) {
  db_query('DELETE FROM {m2api_nodes_products} WHERE nid = %d', $nid);
}

function m2api_product_load_references($nid) {
  $ret = array();
  $result = db_query('SELECT m2id AS id, type FROM {m2api_nodes_products} WHERE nid = %d', $nid);
  while ($row = db_fetch_object($result)) {
    $ret[$row->id] = $row; // m2api_document_load($row->id, $row->type);
  }
  return $ret;
}

/**
 * Load the settings for a product plugin.
 *
 * @param $type
 *   Plugin name.
 *
 * @return
 *   An array or FALSE for invalid $type values.
 */
function m2api_get_product_settings($type) {
  $plugins = ctools_get_plugins('m2api', 'product');
  if (!isset($plugins[$type])) {
    return FALSE;
  }

  $settings = variable_get('m2api_product_settings', array());
  $plugin_settings = isset($settings[$type]) ? $settings[$type] : array();
  $plugin_settings += $plugins[$type]['default_settings'];

  return $plugin_settings;
}