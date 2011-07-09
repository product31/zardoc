<?php
// $Id$
/**
 * @file
 * Administration pages
 */

/**
 * Page callback for admin listing.
 */
 
function sony_header_admin_list() {
   $registeredHeaders =  sony_header_return_regions();

  $results = db_query('SELECT header_id, name, title, language, config_css, config_font FROM {sony_header}');
  $i = 0;
  $rows = array();
  drupal_add_js(drupal_get_path('module', 'sony_header') . '/js/sony_header.admin.js');
  drupal_add_css(drupal_get_path('module', 'sony_header') . '/sony_header.admin.css');
  while ($row = db_fetch_array($results)) {
    $ops = array(
      l('Preview', 'admin/build/sony_header/header/' . $row['header_id'] . '/preview'),
      l('Edit', 'admin/build/sony_header/header/' . $row['header_id'] . '/edit'),
      l('Manage', 'admin/build/sony_header/header/' . $row['header_id'] . '/manage'),
      l('Delete', 'admin/build/sony_header/header/' . $row['header_id'] . '/delete'),

    );

    $rows[] = array(
      l($row['title'].'-'.$row['language'], 'admin/build/sony_header/header/' . $row['header_id']),
      sony_header_return_region_name($row['name'], $registeredHeaders),
      l('XML', 'sony_header/xml/' . $row['header_id']),
      theme('sony_header_operations', $ops),
    );
  }

  if (empty($rows)) {
    $rows[] = array(array(
      'data' => t('No flash headers found.'),
      'colspan' => 3,
    ));
  }

  $output = '';
  $output .= 'The table below lists all the instances of the Flash Header available on this site. For those that are available, please click on the "Operations" link  to <ol><li>Preview a Flash Header</li><li>Edit a particular instance</li><li>Manage the items / resources that is contained within the instance</li><li>Delete this instance</li></ol> If an instance is not available, please import on through the "Import" tab or create a new one, through the "new" tab.<hr/>';
  $output .= theme('table', array('Title', 'Designated to Block:','', 'Operations'), $rows);

  return $output;
}
