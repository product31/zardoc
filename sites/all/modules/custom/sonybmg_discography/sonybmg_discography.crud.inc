<?php
// $Id$

/**
 * @file
 * Create/Read/Update/Delete functions for discography data.
 */

 /**
 * Retrieves the nids of all the released albums, ordered by release date
 */
function sonybmg_discography_get_albums() {
  static $albums = array();

  if (!$albums) {
    $field = content_fields('field_release_date');
    $db_info = content_database_info($field);
    $table = $db_info['table'];

    if (module_exists('sony_global')) {
      //$result = db_query("SELECT n.nid FROM {$table} f INNER JOIN {node} n ON f.vid = n.vid WHERE n.status = 1 AND n.type = 'album' AND (n.nid = n.tnid OR n.tnid = 0) ORDER BY f.field_release_date_value DESC, nid DESC");
      $result = db_query("SELECT n.nid FROM {$table} f INNER JOIN {node} n ON f.vid = n.vid WHERE n.status = 1 AND n.type = 'album' AND (n.language = '' OR n.language = '%s') ORDER BY f.field_release_date_value DESC, nid DESC", $GLOBALS['language']->language);
    }
    else {
      $result = db_query("SELECT n.nid FROM {$table} f INNER JOIN {node} n ON f.nid = n.nid WHERE n.status = 1 ORDER BY f.field_release_date_value DESC, nid DESC");
    }
    while ($row = db_fetch_object($result)) {
      $albums[] = $row->nid;
    }
  }

  return $albums;
}

/**
 * Retrieves the nid of latest album released
 */
function sonybmg_discography_get_latest_album() {
  $albums = sonybmg_discography_get_albums();
  return array_shift($albums);
}

/**
 * Retreives the nid of the album associated with the given node or the current page
 *
 * @param $node
 *   Optional node object to find the related album. If not given the current page node will be used
 * @return nid
 */
function sonybmg_discography_get_related_album($node = NULL) {
  if (!isset($node)) {
    $node = menu_get_object('node', 1);
  }

  if ($node->type == 'album') {
    return $node->nid;
  }
  elseif ($node->type == 'track' && $node->field_album[0]['nid']) {
    return $node->field_album[0]['nid'];
  }
  elseif ($nid = sonybmg_discography_get_latest_album()) {
    return $nid;
  }
}

