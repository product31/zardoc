<?php
// $Id$

/**
 * @file
 * Sony Canonical Admin Functions
 */

/**
 * Implements hook_admin().
 */
function sony_canonical_admin() {

  $filters = _sony_canonical_load_filters(TRUE);

  $options = array();
  foreach ($filters as $name => $filter) {
    $options[ $name ] = $filter['name'];
  }

  $form['sony_canonical_default_filters'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Default Canonical filter options'),
    '#options' => $options,
    '#default_value' => variable_get( 'sony_canonical_default_filters', array())
  );

  return system_settings_form($form);

}