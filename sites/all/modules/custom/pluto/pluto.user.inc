<?php
/**
 * Menu callback for /membership
 * Redirect to the latest membership node, taking language into consideration.
 */
function pluto_membership_about() {
  $nid = variable_get('pluto_about_nid', NULL);

  if ($nid) { drupal_goto('node/'. $nid, NULL, NULL, 301); }
}
?>