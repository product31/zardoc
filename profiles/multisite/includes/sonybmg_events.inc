<?php

/**
 * Default labeling and weight for this profile include.
 */
function sonybmg_events_info() {
  return array(
    'name' => st('Events'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 10,
  );
}

/**
 * Required modules in order for these options to be created successfully.
 */
function sonybmg_events_modules() {
  return array('php', 'views', 'content', 'sonybmg_events', 'content_copy', 'nodecomment', 'sonybmg',
               'text', 'number', 'optionwidgets', 'nodereference', 'userreference', 'date_api',  'date', 'date_timezone',
               'votingapi', 'fivestar', 'filefield', 'imagefield', 'path', 'token', 'pathauto', 'menu');
}

/**
 * Task to complete in order to activate this segment of code.
 */
function sonybmg_events_task_list() {
  return array(
/*  'sonybmg_events_init_content_types' => array(
      'message' => st('Created content types.'),
      'weight' => 0,
    ), */
    'sonybmg_events_init_vocabulary' => array(
      'message'   => st('Created taxonomies.'),
      'weight' => 0,
    ),
/*  'sonybmg_events_init_roles' => array(
      'message' => st('Initialized roles.'),
      'weight' => 0,
    ),*/
/*  'sonybmg_events_init_menus' => array(
      'message' => st('Initialized menus.'),
      'weight' => 0,
    ), */
    'sonybmg_events_init_blocks' => array(
      'message' => st('Initialized blocks.'),
      'weight' => 0,
    ),
    'sonybmg_events_init_custom_pagers' => array(
      'message' => st('Initialized custom pagers.'),
      'weight' => 0,
    ),
/*  'sonybmg_events_init_pathauto_settings' => array(
      'message' => st('Initialized path settings.'),
      'weight' => 0,
    ), */
    'sonybmg_events_init_sample_content' => array(
      'message' => st('Initialized sample content.'),
      'weight' => 0,
    ),
  );
}


function sonybmg_events_init_blocks() {
  global $theme_key, $theme;
  if ($theme == NULL) {
    if (!isset($theme_key)) {
      init_theme();
    }
    $theme = $theme_key;
  }

  $theme = variable_get('artist_key', '_starter');
  $status = TRUE;
  $region = 'right';
  $custom = FALSE;
  $visibility = 2; //0 = show on every page except ; 1 = show only on these pages, 2 = php

  //install_add_block($module, $delta, $theme, $status, $weight, $region,
  //  $visibility = 0, $pages = '', $custom = 0, $throttle = 0, $title = '')
  
  install_add_block('views', 'events_active-block_1', $theme, $status, 0, $region,
    $visibility, '<?php
if (arg(0) == "events") {
  return true;
}

if (arg(0) == "node" && is_numeric(arg(1))) {
  $node = node_load(arg(1));
  if ($node->type == "date") {
    return true;
  }
}
?>');

  // Attendees
  install_add_block('sonybmg_events', 0, $theme, $status, 0, $region,
    $visibility, '<?php
if (arg(0) == "node" && is_numeric(arg(1))) {
  $node = node_load(arg(1));
  if ($node->type == "date") {
    return true;
  }
}
?>');

  $visibility = 1; //0 = show on every page except ; 1 = show only on these pages, 2 = php    

  // Events I will/have Attended
  //install_add_block('views', 'events_attend-block_1', $theme, $status, 0, $region,
  //  $visibility, 'user/*');
  
}

function sonybmg_events_init_vocabulary() {
  $vid = install_taxonomy_add_vocabulary('Event', array('date' => 1));
  $terms = array(
    'Concert' => '',
    'Performance' => '',
    'TV Appearance' => '',
    'Birthday' => '',
    'Release Date' => '',
  );
  
  foreach ($terms as $name => $desc) {
    install_taxonomy_add_term($vid, $name, $desc);
  }
}

/**
 * populate the fields and fivestar for the event content type.
 */
/* Content types moved to feature
function sonybmg_events_init_content_types() {
  // TODO: Move reviews into another location? They shouldn't be tied to discography.
  if (!node_get_types('type', 'review')) {
    $path = drupal_get_path('module', 'sonybmg_discography');
    install_content_copy_import_from_file($path .'/node.review.inc');
  }

  $path = drupal_get_path('module', 'sonybmg_events');
  install_content_copy_import_from_file($path .'/node.date.inc');
} */

/**
 * Path auto path settings.
 */
/* Variable now set in feature
function sonybmg_events_init_pathauto_settings() {
  variable_set('pathauto_node_date_pattern', 'event/[field_date-yyyy]/[field_date-mm]/[field_date-dd]/[title-raw]');
} */

/**
 * Generate Sample content
 */
function sonybmg_events_init_sample_content() {
  module_load_include('inc', 'node', 'node.pages');
  module_load_include('inc', 'devel', 'devel_generate');
  
  // sample event
  $node = new stdClass();
  node_object_prepare($node);
  $node->type = 'date';
  $node->uid = 1;
  $node->language = 'en';
  $node->title = 'Lorem Ipsum event';
  $node->body = '<p>Holisticly reinvent out-of-the-box meta-services for alternative catalysts for change. Interactively network scalable solutions for cross-media interfaces. Proactively streamline empowered technologies with efficient schemas.</p>';
  $node->name = 'adminn';
  $node->field_location = array();
  $node->field_location[0] = array();
  $node->field_location[0]['value'] = 'sample location, CA';
  $node->field_venue = array();
  $node->field_venue[0] = array();
  $node->field_venue[0]['value'] = 'The Sample Venue, LA., CA.';
  $node->promote = 1;
  $node->field_date = array();
  $node->field_date[0] = array();
  $node->field_date[0]['value'] = date('Y-m-d', (time() + (24 * 60 * 60))) . 'T00:00:00';
  
  /*
  $node['event'] = array();
  $node['event']['has_time'] = 1;
  $node['event']['has_end_date'] = 0;
  
  $s_time = time() + 1000;
  $e_time = $s_time + 1000;
  $starts = explode('|', date('m|d|Y|H|i', $s_time));
  $ends   = explode('|', date('m|d|Y|H|i', $e_time));
  
  $node['event']['start_exploded'] = array();
  $node['event']['start_exploded']['month'] = $starts[0];
  $node['event']['start_exploded']['day']   = $starts[1];
  $node['event']['start_exploded']['year']  = $starts[2];
  $node['event']['start_exploded']['hour']  = $starts[3];
  $node['event']['start_exploded']['minute'] = $starts[4];
  $node['event']['end_exploded'] = array();
  $node['event']['end_exploded']['month'] = $ends[0];
  $node['event']['end_exploded']['day']   = $ends[1];
  $node['event']['end_exploded']['year']  = $ends[2];
  $node['event']['end_exploded']['hour']  = $ends[3];
  $node['event']['end_exploded']['minute'] = $ends[4];
  $node['event']['timezone'] = variable_get(date_default_timezone_id, 0);
  $node['event']['start_in_dst'] = 0;
  $node['event']['end_in_dst'] = 0;
  */
  
  node_submit($node);
  node_save($node);
}


/**
 * Add role access for specific permissions
 */
/* Permissions moved to feature
function sonybmg_events_init_roles() {
  // set admin prems
  $rid = install_get_rid('administrator');
  install_add_permissions($rid, array('create date content', 'edit own date content', 'edit any date content'));
  
  // set artist perms
  $rid = install_get_rid('artist');
  install_add_permissions($rid, array('create date content', 'edit own date content', 'edit any date content'));
  
  // set moderator perms
  $rid = install_get_rid('moderator');
  install_add_permissions($rid, array('create date content', 'edit own date content', 'edit any date content'));
} */


/**
 * Create menu items for default content and views
 */
/*
function sonybmg_events_init_menus() {
  variable_set('event_overview', 'day');
  variable_set('event_taxonomy_control', 'never');
  variable_set('event_type_control', 'never');
  $pid = install_menu_create_url_alias('event', 'events');
  
  $mlid = install_menu_create_menu_item('events', 'Events', 'See events!', 'Primary Links'); 
} */

/**
 * Initialize the custom pagers
 */
function sonybmg_events_init_custom_pagers() {
  $pager = array(
    'title' => 'Events',
    'view' => 'events',
    'position' => 'top',
    'node_type' => 'date',
  );
  $pid = install_custom_pagers_add_pager($pager);
/*variable_set('events_date_pager', $pid); Variable now in feature */
}


/**
 * test function for flags
 */
/* Flag creation moved to feature
function sonybmg_events_init_custom_flags() {

  $flag = array(
    'name'         => 'signup',
    'title'        => 'signup',
    'flag_short'   => 'Add Me',
    'flag_long'    => 'I\'ll be attending',
    'unflag_short' => 'Remove Me',
    'unflag_long'  => 'I won\'t be attending',
    'roles'        => array('administrator','moderator','authenticated user'),
    'types'        => array('date'),
    'global'       => 0,
    'show_on_teaser' => 0,
    'show_on_page' => 1,
    'show_on_form' => 0,
  );
  
  install_flag_add_flag($flag); 

  // Disable the default view.
  $views_status = variable_get('views_defaults', array());
  $views_status['flag_signup'] = TRUE;
/* variable_set('views_defaults', $views_status); moved to feature */
//} 

/**
 * Initiate the site timezone
 * This function leverages the event module to istantiate the date_default_timezone_id var.
 */
/*
function sonybmg_events_init_timezone() {
  //$zones = event_zonelist('offset');
  $timezone = variable_get('date_default_timezone', 0);
  $id = 0;
  foreach ($zones as $idx => $val) {
    $arr = explode('|', $idx);
    if ($arr[1] === $timezone) {
      $id = $arr[0];
      break;
    }
  }
  
  variable_set('date_default_timezone_id', $id);
}
*/