<?php
// $Id$

/**
 * @file
 * file_description
 */

/**
 * Registered user reports.
 */
function sonybmg_analytics_reports_users() {
  $from = strtotime('1 year ago');
  $to = time();
  $max = db_result(db_query('SELECT COUNT(u.uid) as `count` FROM {users} u GROUP BY FROM_UNIXTIME(u.created, "%%Y-%%m") ORDER BY `count` DESC LIMIT 1'));
  $sql = 'SELECT FROM_UNIXTIME(u.created, "%%b %%Y") as `label`, COUNT(u.uid) as `count` FROM {users} u WHERE u.created > %d AND u.created < %d GROUP BY `label` ORDER BY u.created ASC';
  $title = t('User registrations');

  $dates = array();
  $result = db_query($sql, $from, $to);
  while ($row = db_fetch_array($result)){
    $dates[$row['label']] = $row['count'];
  }

  $i = 0;
  $chart['#data'] = array();
  foreach($dates as $label => $count) {
    // zero values break the continuity of line graphs, so we use a decimal instead.
    //$count = isset($dates[$label]) ? (int)$dates[$label] : 0.5;
    $chart['#data'][] = $count;
    $chart['#mixed_axis_labels'][CHART_AXIS_X_BOTTOM][0][] = chart_mixed_axis_label($label);
    $chart['#shape_markers'][] = array('t'. $count, '000000', 0, $i++, 10);
  }
  // add a marker to each data point
  $chart['#shape_markers'][] = array('o', '000000', 0, -1, 5);

  $chart['#line_styles'][] = chart_line_style(2);
  $chart['#chart_id']   = 'sonybmg_users';
  $chart['#title']      = chart_title($title);
  $chart['#type']       = CHART_TYPE_LINE;
  $chart['#size']       = chart_size(950, 315);
  $chart['#grid_lines'] = chart_grid_lines(20, 20, 1, 5);
  if($dates) {
    $chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0][] = chart_mixed_axis_range_label(0, $max);
    $chart['#adjust_resolution'] = array('#adjust' => TRUE, '#max' => $max);
  }

  $output = chart_render($chart, array('width' => $chart['#size']['#width'], 'height' => $chart['#size']['#height']));

  $output .= sonybmg_analytics_reports_users_geoip();
  return $output;
}

/**
 * GeoIP users
 */
function sonybmg_analytics_reports_users_geoip() {
  if (!module_exists('geoip')) {
    return;
  }

  $chart = array(
    '#georange' => 'world',
  );
  $title = t('Users by location');
  $countries = array();
  $result = db_query('SELECT hostname FROM {sessions} GROUP BY uid');
  while ($row = db_fetch_array($result)){
    $cc = geoip_country_code($row['hostname']);
    if ($cc) {
      $countries[$cc]++;
    }
  }
  arsort($countries);

  $chart['#data'] = array();
  $chart['#countries'] = array();
  foreach($countries as $cc => $num) {
    $chart['#data'][] = $num;
    $chart['#countries'][] = $cc;
    $chart['#mixed_axis_labels'][CHART_AXIS_X_BOTTOM][0][] = chart_mixed_axis_label($cc);
  }

  $chart['#chart_id']   = 'sonybmg_users_geoip';
  $chart['#title']      = chart_title($title);
  $chart['#type']       = CHART_TYPE_MAP;
  $chart['#size']       = chart_size(440, 220);
  $chart['#data_colors'] = array('EEEEEE', 'DDE1FA', '1B2364');

  $output = chart_render($chart, array('width' => $chart['#size']['#width'], 'height' => $chart['#size']['#height']));

  $chart['#chart_id'] = 'sonybmg_users_geoip_bar';
  $chart['#type'] =     CHART_TYPE_BAR_V;
  $chart['#size']       = chart_size(950, 315);
  $bars = floor($chart['#size']['#width'] / (27));
  $chart['#data'] = array_slice($chart['#data'], 0, $bars, TRUE);
  $chart['#mixed_axis_labels'][CHART_AXIS_X_BOTTOM][0] = array_slice($chart['#mixed_axis_labels'][CHART_AXIS_X_BOTTOM][0], 0, $bars, TRUE);

  $output .= chart_render($chart, array('width' => $chart['#size']['#width'], 'height' => $chart['#size']['#height']));

  return $output;
}

/**
 * Content post reports
 */
function sonybmg_analytics_reports_content_posts() {
  module_load_include('inc', 'sonybmg_analytics', 'sonybmg_analytics.services');
  $data = sonybmg_analytics_stats_content_posts(TRUE);
 
  $output .= "<h2>" . t('Official Content') . "</h2>\n";
  $chart['#data'] = array();
  $max = 0;
  $max_num = 0;
  foreach($data['official'] as $type => $num) {
    $max = max($max, !$num ? 0 : round(log($num),2));
    $max_num = max($max_num, $num);
    $chart['#data'][] = !$num ? 0 : round(log($num),2);
    $chart['#mixed_axis_labels'][CHART_AXIS_X_BOTTOM][0][] = chart_mixed_axis_label($type);
  }
  $y_top = ceil($max);
  foreach(range(0, $y_top) as $y_ax) {
    $pct = !$y_ax ? 0 : round(100*$y_ax/$max);
    $chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0][] = chart_mixed_axis_label(round(exp($y_ax)), $pct);
  }
  $chart['#chart_id'] = 'sonybmg_content_posts_official';
  //$chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0][] = chart_mixed_axis_range_label(0, $max);
  $chart['#adjust_resolution'] = array('#adjust' => TRUE, '#max' => $max);
  $chart['#line_styles'][] = chart_line_style(2);
  $chart['#grid_lines'] = chart_grid_lines(20, 20, 1, 5);
  $chart['#type'] =     CHART_TYPE_BAR_V;
  $chart['#size']       = chart_size(950, 315);
  $chart['#bar_size'] = array('#size' => 20, '#spacing' => 30);
  $output .= chart_render($chart, array('width' => $chart['#size']['#width'], 'height' => $chart['#size']['#height']));

  $chart = array();

  $output .= "<h2>" . t('Unofficial Content') . "</h2>\n";
  $chart['#data'] = array();
  $max = 0;
  $max_num = 0;
  foreach($data['unofficial'] as $type => $num) {
    $max = max($max, !$num ? 0 : round(log($num),2));
    $max_num = max($max_num, $num);
    $chart['#data'][] = !$num ? 0 : round(log($num),2);
    $chart['#mixed_axis_labels'][CHART_AXIS_X_BOTTOM][0][] = chart_mixed_axis_label($type);
  }
  $y_top = ceil($max);
  foreach(range(0, $y_top) as $y_ax) {
    $pct = !$y_ax ? 0 : round(100*$y_ax/$max);
    $chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0][] = chart_mixed_axis_label(round(exp($y_ax)), $pct);
  }
  $chart['#chart_id'] = 'sonybmg_content_posts_unofficial';
  //$chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0][] = chart_mixed_axis_range_label(0, $max);
  $chart['#adjust_resolution'] = array('#adjust' => TRUE, '#max' => $max);
  $chart['#line_styles'][] = chart_line_style(2);
  $chart['#grid_lines'] = chart_grid_lines(20, 20, 1, 5);
  $chart['#type'] =     CHART_TYPE_BAR_V;
  $chart['#size']       = chart_size(950, 315);
  $chart['#bar_size'] = array('#size' => 20, '#spacing' => 30);
  $output .= chart_render($chart, array('width' => $chart['#size']['#width'], 'height' => $chart['#size']['#height']));
  
  return $output;
}
