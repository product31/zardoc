<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function sonybmg_events_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: primary-links:events
  $menu_links['primary-links:events'] = array(
    'menu_name' => 'primary-links',
    'link_path' => 'events',
    'router_path' => 'events',
    'link_title' => 'Events',
    'options' => array(
      'attributes' => array(
        'title' => 'See events!',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Events');


  return $menu_links;
}
