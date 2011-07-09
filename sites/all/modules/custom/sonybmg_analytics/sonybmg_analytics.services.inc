<?php
// $Id$

/**
 * @file
 * description
 */

/**
 * Return a hashed array containing the number of user registrations within a
 * given date range, as well as the total number of registrations.

 * @param $start
 * @param $end
 * @return array
 */
function sonybmg_analytics_stats_user_registrations($start, $end = NULL) {
  $start = strtotime($start);
  $end = isset($end) ? strtotime($end) : time();

  $range = db_result(db_query('SELECT COUNT(u.uid) as `count` FROM {users} u WHERE u.created > %d AND u.created < %d', $start, $end));
  $total = db_result(db_query('SELECT COUNT(u.uid) as `count` FROM {users} u', $start, $end));

  return array(
    'range' => $range,
    'total' => $total,
  );
}

/**
 * Return a hashed array containing the number of users from various countries
 * in the given date range, as well as the total number of users.

 * @param $start
 * @param $end
 * @return array
 */
function sonybmg_analytics_stats_user_countries($start, $end = NULL) {
  $start = strtotime($start);
  $end = isset($end) ? strtotime($end) : time();
  
  $countries = array();
  $total = 0;
  $country_fid = db_result(db_query("SELECT fid FROM {profile_fields} WHERE title='Country'"));
  $result = db_query("SELECT COUNT(*) as cnt, value as country FROM {users} u LEFT JOIN {profile_values} pv ON pv.uid=u.uid AND fid=%d WHERE u.created > %d AND u.created < %d GROUP BY pv.value", $country_fid, $start, $end);
  $countries[] = array('country' => 'NONE', 'count' => 0,);
  while ($row = db_fetch_object($result)) {
    if (empty($row->country)) {
      $countries[0]['count'] += $row->cnt;
    }
    else {
      $countries[] = array('country' => $row->country, 'count' => $row->cnt,);
    }
    $total += $row->cnt;
  }
  
  return array(
    'countries' => $countries,
    'total' => $total,
  );
}

/**
 * Return a hashed array containing the number of users from various email
 * domains in the given date range, as well as the total number of users.

 * @param $start
 * @param $end
 * @return array
 */
function sonybmg_analytics_stats_user_email_domains($start, $end = NULL) {
  $start = strtotime($start);
  $end = isset($end) ? strtotime($end) : time();
  
  $domains = array();
  $total = 0;
  $result = db_query("select COUNT(*) as cnt, LOWER(SUBSTRING_INDEX(mail, '@', -1)) as domain FROM {users} u WHERE u.created > %d AND u.created < %d GROUP BY domain", $start, $end);
  $domains[] = array('domain' => 'NONE', 'count' => 0);
  while ($row = db_fetch_object($result)) {
    if (empty($row->domain)) {
      $domains[0]['count'] += $row->cnt;
    }
    else {
      $domains[] = array('domain' => $row->domain, 'count' => $row->cnt,);
    }
    $total += $row->cnt;
  }
  
  return array(
    'domains' => $domains,
    'total' => $total,
  );
}


/**
 * Return a hashed array containing the number of official and unofficial content
 * posts within the given date range. If specified, the array will split out the
 * counts by content-type.
 * 
 * @param $type_split
 *   boolean indicating whether or not you want that counts split out by content type
 * @param $start
 * @param $end
 * @return array
 */
function sonybmg_analytics_stats_content_posts($type_split = FALSE, $start = NULL, $end = NULL) {
  $start = isset($start) ? strtotime($start) : 0;
  $end = isset($end) ? strtotime($end) : time();
  
  // Find a user who is not a moderator or admin or translator or artist
  $super_roles = array(
    3, // admin
    4, // artist
    5, // moderator
    6, // translator
  );
  $uid = db_result(db_query("SELECT uid FROM {users} WHERE status=1 AND uid!=0 AND uid NOT IN 
    (SELECT uid FROM {users_roles} WHERE rid IN (%s)) ORDER BY uid DESC LIMIT 1", implode(', ', $super_roles)));
  $account = user_load(array('uid' => $uid));
  
  // Find out what types are user generated content
  $ugc_content = array();
  foreach (node_get_types() as $type => $type_data) {
    $ugc_content[$type] = node_access('create', $type, $account);
  }
  
  // Count the nodes
  $data = array();
  foreach ($ugc_content as $type => $ugc) {
    $count = db_result(db_query("SELECT COUNT(nid) FROM {node} WHERE type='%s' AND status=1 AND created > %d AND created < %d", $type, $start, $end));
    if ($type_split) {
      if ($ugc) {
        $data['unofficial'][$type] += $count;
      }
      else {
        $data['official'][$type] += $count;
      }
    }
    else {
      if ($ugc) {
        $data['unofficial'] += $count;
      }
      else {
        $data['official'] += $count;
      }
    }
  }
  return $data;
}
