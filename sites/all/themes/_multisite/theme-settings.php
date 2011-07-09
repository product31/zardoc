<?php
// $Id$

/**
 * @file
 * file_description
 */


/**
 * Implementation of THEMEHOOK_settings() function.
 *
 * @param $saved_settings
 *   array An array of saved settings for this theme.
 * @return
 *   array A form array.
 */
function phptemplate_settings($saved_settings) {
  // The default values for the theme variables. Make sure $defaults exactly
  // matches the $defaults in the template.php file.
  $defaults = array(
  );

  // Merge the saved variables and their default values
  $settings = array_merge($defaults, $saved_settings);

  $form['_multisite_reset_user_pics'] = array(
    '#type' => 'submit',
    '#value' => t('Reset default user pics'),
    '#submit' => array('sonybmg_profiles_user_picture_default_reset'),
  );

  // Return the additional form widgets
  return $form;
}