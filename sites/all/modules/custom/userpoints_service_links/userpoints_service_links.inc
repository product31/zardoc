<?php 

/*
 * Intercept share links and award points
 */

function userpoints_service_links_share() {
  $query_string = $_SERVER['QUERY_STRING'];
  // strip out the q=share& and language prefix
  $query_string = substr($query_string, strpos($query_string, '&') + 1);
  // Award the points - implementation of hook_userpointsapi()
  global $user;
  userpoints_userpointsapi(array(
    'points' => variable_get(USERPOINTS_SERVICE_LINKS, 0),
    'uid' => $user->uid,
    'operation' => 'Sharing a link',
    'entity_id' => $user->uid,
    'entity_type' => 'user',
    'tid'         => variable_get(USERPOINTS_SERVICE_LINKS_TID, 0),
  ));
  drupal_goto($query_string);
}