<?php
// $Id: winners_handler_filter_contests.inc,v 1.1.2.1 2010/04/01 19:25:35 andrewlevine Exp $

/**
 * Filter by job status
 */
class winners_handler_filter_contests extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Contest');
      $options = array();
      $result = db_query("SELECT contest_id, name FROM {winners_contests} ORDER BY name ASC");
      while ($row = db_fetch_object($result)) {
        $options[$row->contest_id] = $row->name;
      }
      $this->value_options = $options;
    }
  }
}
