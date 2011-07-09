<?php
// $Id: views-bonus-export-csv.tpl.php,v 1.1 2008/10/08 05:50:10 neclimdul Exp $
/**
 * @file views-view-table.tpl.php
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $rows: An array of row items. Each row is an array of content
 *   keyed by field ID.
 * - $header: an array of haeaders(labels) for fields.
 * - $themed_rows: a array of rows with themed fields.
 * - $items:
 * - $seperator: The seperator used to seperate fields. generally comma's but
 *   sometimes people use other values in CSVs.
 * @ingroup views_templates
 */

foreach ($items as $count => $item_row):
  if ($options['quote']) echo '"';
  print implode($seperator, $item_row);
  if ($options['quote']) echo '"';
  echo "\r\n";
endforeach;
