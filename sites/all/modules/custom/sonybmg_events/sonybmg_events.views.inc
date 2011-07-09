<?php

/*
 * This function alters the events view
 * It duplicates the query that creates the view to count how many events occur are after yesterday
 * It then uses this to calculate which page of results to start from
 * This was tweaked Jan 30th 2009 by Thomas to deal with date formatting in sites that were upgraded from Drupal 5
 */

function sonybmg_events_views_query_alter (&$view, &$query) {
  if ($view->name == 'events' && arg(0) ==$view->display['page_1']->display_options['path'] && empty($_GET['page']) && empty($_GET['previous_text'])) {
    // if items_per_page is 0, dont do anything
    if(!$view->display['default']->display_options['items_per_page']) {
      return;
    }

    $new_query = drupal_clone($query);

    $date_field = $new_query->fields['node_data_field_date_field_date_value'];

    /*
     * In new D6 sites the date is stored as 2009-11-29T00:00:00
     * In sites upgraded from D5 to D6 it is 1244073600 (unix timestamp)
     * We need to check which it is for the where query
     */
    $upgraded = variable_get('upgraded_site', 'unknown');
    // $upgraded = 'unknown';
    if($upgraded == 'unknown'){
      // check format of date, and save to variables table
      $date = db_result(db_query("SELECT field_date_value FROM {content_type_date} ORDER BY nid DESC LIMIT 1"));
      if(is_numeric($date)){
        $upgraded = 'upgraded';
      } else {
        $upgraded = 'normal';
      }
      variable_set('upgraded_site', $upgraded);
    }

    if($upgraded == 'normal'){
      $new_where = 'UNIX_TIMESTAMP('. $date_field['table'] .'.'. $date_field['field'] .') >= %d';
    } else {
      $new_where = $date_field['table'] .'.'. $date_field['field'] .' >= %d';
    }

    $today = mktime(0, 0, 0, date('m'), date('d'), date('Y'));
    $yesterday = $today - (60 * 60 * 24);

    $new_query->add_where(0, $new_where, $yesterday);

    $query_sql = $query->query(TRUE);
    $replacements = module_invoke_all('views_query_substitutions', $view);
    $query_sql = str_replace(array_keys($replacements), $replacements, $query_sql);
    
    $normal_count = db_result(db_query($query_sql, $query->get_where_args()));


    $query_sql = $new_query->query(TRUE);
    $replacements = module_invoke_all('views_query_substitutions', $view);
    $query_sql = str_replace(array_keys($replacements), $replacements, $query_sql);
    
    $after_yesterday_count = db_result(db_query($query_sql, $new_query->get_where_args()));


    $page = floor(($normal_count - $after_yesterday_count)/$view->display['default']->display_options['items_per_page']);

    $_GET['page'] = (int)$page; // Change which page of the pager is shown without redirecting.
  }
}
