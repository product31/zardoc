<?php

/**
 * Prepreprocess function for page.tpl.php.
 */
function _starter_preprocess_page(&$vars) {

}

/**
 * Preprocess function for all node.tpl.php files.
 */
function _starter_preprocess_node(&$vars) {
  // Add any needed variables.
  switch ($vars['node']->type) {
    case 'album':
      break;
    case 'track':
      break;
  }
}

/**
 * Override of theme_breadcrumb(). Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */
function _starter_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb) && strlen(drupal_get_title()) > 0) {
    $breadcrumb[] = drupal_get_title();
    return '<div class="breadcrumb">'. implode(' » ', $breadcrumb) .'</div>';
  }
}