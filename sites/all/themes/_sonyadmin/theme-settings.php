<?php
// $Id$

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
    '_sonyadmin_color_scheme' => 'green',
  );

  // Merge the saved variables and their default values
  $settings = array_merge($defaults, $saved_settings);

  // Create the form widgets using Forms API
  $form['_sonyadmin_color_scheme'] = array(
    '#type' => 'select',
    '#title' => t('Color Scheme'),
    '#options' => array(
      'green' => t('Green'),
      'blue' => t('Blue'),
      'red' => t('Red'),
    ),
    '#default_value' => $settings['_sonyadmin_color_scheme'],
  );

  // Return the additional form widgets
  return $form;
}

