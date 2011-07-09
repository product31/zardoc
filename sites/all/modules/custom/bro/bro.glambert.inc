<?php

function bro_glambert_import() {
  $rid = 7;

  $content = file_get_contents(drupal_get_path('module', 'bro') .'/glambert.txt');
  $emails = explode("\n", $content);

  $found = 0;
  foreach($emails as $email) {
    $uid = db_result(db_query('SELECT uid FROM {users} WHERE mail ="%s"', $email));
    if ($uid) {
      $count = db_result(db_query('SELECT uid FROM {users_roles} WHERE uid = %d AND rid = %d', $uid, $rid));
      if ($count == 0) {
        drupal_set_message('adding ' . $email .' (uid: '. $uid .') to chatter role');
        db_query("INSERT INTO {users_roles} (uid, rid) VALUES (%d, %d)", $uid, $rid);
      }
      $found++;
    }
  }
  dsm('found '. $found .'/'. count($emails));
}
