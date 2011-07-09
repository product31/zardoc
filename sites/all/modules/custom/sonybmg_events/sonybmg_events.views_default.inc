<?php

/**
 * Implementation of hook_views_default_views().
 */
function sonybmg_events_views_default_views() {
  $views = array();

  // Exported view: events
  $view = new view;
  $view->name = 'events';
  $view->description = 'The events of the day.';
  $view->tag = 'events,date,calendar';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'flag_count_rel' => array(
      'label' => 'counter',
      'required' => 0,
      'flag' => 'signup',
      'id' => 'flag_count_rel',
      'table' => 'node',
      'field' => 'flag_count_rel',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'field_date_value' => array(
      'label' => 'Date',
      'link_to_node' => 1,
      'label_type' => 'widget',
      'format' => 'short',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_date_value',
      'table' => 'node_data_field_date',
      'field' => 'field_date_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_location_value' => array(
      'label' => 'City',
      'link_to_node' => 1,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_location_value',
      'table' => 'node_data_field_location',
      'field' => 'field_location_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_venue_value' => array(
      'label' => '',
      'link_to_node' => 1,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_venue_value',
      'table' => 'node_data_field_venue',
      'field' => 'field_venue_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'count' => array(
      'label' => 'Attendees',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'count',
      'table' => 'flag_counts',
      'field' => 'count',
      'relationship' => 'flag_count_rel',
    ),
    'comment_count' => array(
      'label' => 'Reviews',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'comment_count',
      'table' => 'node_comment_statistics',
      'field' => 'comment_count',
      'relationship' => 'none',
    ),
    'field_venue_notes_value' => array(
      'label' => 'Notes',
      'link_to_node' => 1,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_venue_notes_value',
      'table' => 'node_data_field_venue_notes',
      'field' => 'field_venue_notes_value',
      'relationship' => 'none',
    ),
    'field_ticket_sales_url_value' => array(
      'label' => 'Tickets',
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_ticket_sales_url_value',
      'table' => 'node_data_field_ticket_sales_url',
      'field' => 'field_ticket_sales_url_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'sticky' => array(
      'order' => 'ASC',
      'id' => 'sticky',
      'table' => 'node',
      'field' => 'sticky',
      'relationship' => 'none',
    ),
    'field_date_value' => array(
      'order' => 'ASC',
      'id' => 'field_date_value',
      'table' => 'node_data_field_date',
      'field' => 'field_date_value',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'date' => 'date',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
    'role' => array(),
    'perm' => '',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Tour Info');
  $handler->override_option('header', 'To participate in  dTb ticket pre-sales, simply sign up for The Derek Trucks Band Fan Community.  It\'s free to sign up, and you receive special ticket access in advance of the  general public for select shows.

To review ongoing  ticket pre-sales, to purchase tickets, or to sign up for the dTb Fan  Community, <a href="http://www.dtbtickets.musictoday.com/ ">click here</a>

<a href="/events/feed" class="feed-icon"><img src="/misc/feed.png" alt="Syndicate content" title="Syndicate content" width="16" height="16" /></a>');
  $handler->override_option('header_format', '2');
  $handler->override_option('header_empty', 0);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler = $view->new_display('page', 'Events', 'page_1');
  $handler->override_option('items_per_page', 0);
  $handler->override_option('use_pager', '0');
  $handler->override_option('path', 'events');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('style_plugin', 'rss');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'node_rss');
  $handler->override_option('row_options', array(
    'item_length' => 'default',
  ));
  $handler->override_option('path', 'events/feed');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array(
    'page_1' => 'page_1',
    'block_1' => 'block_1',
    'default' => 0,
  ));
  $handler->override_option('sitename_title', FALSE);
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('fields', array(
    'field_date_value' => array(
      'label' => 'Date',
      'link_to_node' => 1,
      'label_type' => 'widget',
      'format' => 'short',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_date_value',
      'table' => 'node_data_field_date',
      'field' => 'field_date_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_location_value' => array(
      'label' => 'City',
      'link_to_node' => 1,
      'label_type' => 'custom',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_location_value',
      'table' => 'node_data_field_location',
      'field' => 'field_location_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_venue_value' => array(
      'label' => '',
      'link_to_node' => 1,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_venue_value',
      'table' => 'node_data_field_venue',
      'field' => 'field_venue_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Tour');
  $handler->override_option('header', 'Latest Tour Information');
  $handler->override_option('header_format', '1');
  $handler->override_option('footer', '<div class="more"><a href="/events" class="more">MORE TOUR INFO</a></div>');
  $handler->override_option('footer_format', '1');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);

  $views[$view->name] = $view;

  return $views;
}
