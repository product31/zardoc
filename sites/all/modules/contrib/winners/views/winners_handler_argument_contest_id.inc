<?php
// $Id: winners_handler_argument_contest_id.inc,v 1.1.2.1 2010/04/01 19:25:35 andrewlevine Exp $

/**
 * Argument handler to accept a contest id.
 */
class winners_handler_argument_contest_id extends views_handler_argument_numeric {
  /**
   * Override the behavior of title(). Get the name of the contest.
   */
  function title_query() {
    $titles = array();
    $placeholders = implode(', ', array_fill(0, sizeof($this->value), '%d'));

    $result = db_query("SELECT wc.name FROM {winners_contests} wc WHERE wc.contest_id IN ($placeholders)", $this->value);
    while ($name = db_fetch_object($result)) {
      $titles[] = check_plain($name->name);
    }
    return $titles;
  }
}

