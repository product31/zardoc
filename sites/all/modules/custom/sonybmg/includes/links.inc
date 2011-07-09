<?php

/**
 * Theme function for 'default' text field formatter.
 */
function theme_sonybmg_formatter_links_dropdown($element) {
  // dsm($element);
  $links = array();
  foreach (element_children($element) as $key) {
    $links[] = theme('link_formatter_default', $element[$key]);
  }
  return theme('sonybmg_dropdown_links', $links);
}

function theme_sonybmg_dropdown_links($links = array(), $title = '', $attributes = array()) {
  // Add in defaults.
  $attributes += array('class' => '');

  foreach ($links as $i => $link) {
    if (empty($link)) {
      unset($links[$i]);
    }
  }
  if (empty($links)) {
    return;
  }

  $path = drupal_get_path('module', 'sonybmg');
  drupal_add_js($path .'/includes/links/links.js');
  drupal_add_css($path .'/includes/links/links.css');

  $output = '<h3>'. $title .'</h3>';
  $output .= '<ul><li>'. join('</li><li>', $links) .'</li></ul>';

  $attributes['class'] .= ' links-dropdown-list';
  return '<div '. drupal_attributes($attributes) .'>'. $output .'</div>';
}