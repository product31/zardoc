<?php

/**
 * Default labeling and weight for this profile include.
 */
function i18n_info() {
  return array(
    'name' => st('Internationalization'),
    'default_value' => TRUE,
    'disabled' => TRUE,
    'weight' => -10,
  );
}

/**
 * Required modules.
 */
function i18n_modules() {
  return array(
    'locale',
    'translation', 
    'menu',
    'taxonomy',
    'i18n', 
    'i18nstrings', 
    'i18nblocks', 
    'i18ncontent', 
    'i18npoll', 
    'i18nprofile', 
    'i18nviews', 
    'i18nsync', 
    'i18nmenu', 
    'i18ntaxonomy',
    'geoip',
    'sony_global', 
  );
} 

function i18n_task_list() {
  return array(
    'i18n_variables' => array(
      'message' => st('Set up default settings.'),
      'weight' => 0,
    ),
  );
}

/**
 * Set our default i18n settings.
 */
function i18n_variables() {
  // Don't use i18n's rewriting for display.
  variable_set('i18n_selection_mode', 'off');
}
