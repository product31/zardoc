<?php

class datasync_feedapi extends datasync_job {
  // Definitions of the different phases DataSync will run through
  // each phase should have a corresponding method
  public function phase_defs() {
    return array('fake_cron');
  }
  
  // Definition of configuration options. In this case we are
  // telling datasync to run all phases inside of database
  // transactions 
  public function config_defs() {
    return array('phase_in_transaction' => $this->phase_defs());
  }
  
  // Definition of fake_cron phase
  public function fake_cron() {
    $data = $this->extra_data();
    $feed_nid = $data['nid'];
    
    $feed = node_load($feed_nid);
    $exists = db_result(db_query("SELECT nid FROM {feedapi} WHERE nid=%d", $feed_nid));
    if ($feed_nid && $exists) {
      // Call the refresh process for each feed and store counters
      feedapi_invoke('refresh', $feed->feed, FALSE);
      watchdog("datasync", "DATASYNC_FEEDAPI: Feed %title updated.", array('%title' => $feed->title));
    }
    else {
      watchdog('datasync', "DATASYNC_FEEDAPI: Invalid feed with node id %nid", array('%nid' => $feed_nid));
      return FALSE;
    }
    
    return TRUE;
  }
}

