<?php

/**
 * Theme a network profile picture with a favicon overlay.
 */
function theme_sony_connect_profile_picture($network, $nuid) {
  drupal_add_css(drupal_get_path('module', 'sony_connect') .'/sony_connect.css');

  if (!is_array($network)) {
    $network = sony_connect_get_network($network);
  }

  $profile = sony_connect_load_profile($network['name'], $nuid);

  if (isset($profile['picture'])) {
    $img = theme('image', $profile['picture'], '', '', NULL, FALSE);
  }

  $favicon = theme('image', $network['path'] .'/'. $network['favicon'], $network['title']);

  return '<div class="sony-connect-picture">'. $img . $favicon .'</div>';
}