<?php
//$Id$
/**
 * @file
 * Create/Read/Update/Delete functions for sonybmg_events data.
 */
 
/**
 * Attendee load function
 *
 * @param $node
 *   The node to check against.
 * @return
 *   An array containing the returned values.
 */
function sonybmg_events_attendees_load($node) {
  static $sonybmg_event_attendees = array();
  $return = array();
  
  if (isset($sonybmg_event_attendees['nid_' . $node->nid])) {
    $return = $sonybmg_event_attendees['nid_' . $node->nid];
  } else {
    $result = db_query("SELECT uid FROM {flag_content} WHERE content_id = %d ORDER BY timestamp $order", $node->nid);
    
    // populate return
    while ($row = db_fetch_array($result)) {
      $return[] = $row['uid'];
    }
    
    $sonybmg_event_attendees['nid_' . $node->nid] = $return;
  }
  
  return $return;
}


/**
 * Return the number of attendees for an event node
 */
function sonybmg_events_attendees_count($nid) {
  $flag_counts = flag_get_counts('node', $nid);
  return isset($flag_counts['signup']) ? $flag_counts['signup'] : 0;
}