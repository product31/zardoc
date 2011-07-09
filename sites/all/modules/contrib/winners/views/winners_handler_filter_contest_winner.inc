<?php
// $Id: winners_handler_filter_contest_winner.inc,v 1.1.2.1 2010/04/01 19:25:35 andrewlevine Exp $

/**
 * Filter handler for the current user
 */
class winners_handler_filter_contest_winner extends views_handler_filter_boolean_operator {
  function construct() {
    parent::construct();
    $this->value_value = t('User has won any contest');
  }

  function query() {
    $this->ensure_my_table();
    $where = "$this->table_alias.$this->real_field ";

    if (empty($this->value)) {
      $where .= 'IS NULL';
    }
    else {
      $where .= 'IS NOT NULL';
    }
    $this->query->add_where($this->options['group'], $where);
  }
}
