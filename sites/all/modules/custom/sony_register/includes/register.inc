<?php
// $Id$

/**
 * @file
 * description
 */

/**
 * Menu callback for modal test page.
 */
function sony_register_modal_test() {
  return l('register', 'user/nojs/register', array('attributes' => array('class' => 'ctools-use-modal')));
}

/**
 * Menu callback for user/%ctools_js/register.  Handles both ajax/modal and
 * non-ajax contexts.
 */
function sony_register_ajax_register($js) {
  if ($js) {
    ctools_include('modal');
    ctools_include('ajax');

    $form_state = array(
      'ajax' => TRUE,
      'title' => t('Create a new account'),
    );
    $output = ctools_modal_form_wrapper('sony_register_user_register', $form_state);
    if (empty($output)) {
      $output[] = array(
        'command' => 'reload',
      );
    }

    ctools_ajax_render($output);
  }
  else {
    return drupal_get_form('sony_register_user_register');
  }
}

function sony_register_country_options() {
  $countries = geoip_country_values();
  asort($countries);
  unset($countries['A1']);
  unset($countries['A2']);
  unset($countries['US']);
  $countries = array('US' => 'United States') + $countries;

  return $countries;
}

/**
 * Custom user registration form.
 */
function sony_register_user_register(&$form_state) {
  $form = array();
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Choose a username'),
    '#size' => 25,
    '#validation_rules' => array(
      'uniqueUsername' => TRUE,
    ),
  );
  $form['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter your email'),
    '#size' => 25,
    '#validation_rules' => array(
      'uniqueEmail' => TRUE,
    ),
  );
  $form['pass'] = array(
    '#type' => 'password',
    '#title' => t('Choose a password'),
    '#size' => 25,
  );

  if (variable_get('sony_coppa_reac', 0)) {
    $form = sony_coppa_dob_form($form);
  }
  else {
    $form = sony_coppa_u13_form($form);
  }

  $form['country_zip'] = array(
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
  );

  $form['country_zip']['country'] = array(
    '#type' => 'select',
    '#title' => t('Where are you'),
    '#options' => sony_register_country_options(),
    '#default_value' => geoip_country_code(),
  );
  $form['country_zip']['zip'] = array(
    '#type' => 'textfield',
    '#size' => 5,
  );

  if (module_exists('legal')) {
    $default_legal_link = t('<strong>Accept</strong> !terms of Use', array('!terms' => l('Terms & Conditions', 'http://sonymusic.com/termsandconditions.html')));
    $legal = module_invoke('legal', 'user', 'register', NULL, NULL);
    $legal['legal']['#type'] = 'markup';
    $legal['legal']['legal_accept']['#title'] = t(variable_get('sony_legal_link', $default_legal_link));
    $form += $legal;
  }

  if (module_exists('mollom')) {
    // Add Mollom form protection widget.
    $form['mollom'] = array(
      '#type' => 'mollom',
      '#mode' => mollom_get_mode('user_register'),
    );
    // Add a submit handler that will clean the Mollom state as soon as the form
    // is successfully submitted.
    $form['#submit'][] = 'mollom_clean_state';
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Sign up'),
    '#weight' => 100,
  );

  // TODO: remove this and create one specifically for this form.
  $form['#after_build'][] = '_sony_register_form_user_register_after_build';

  // Since we have to add a submit handler for mollom, the normal submit
  // handler doesn't get appended automatically.  So we add it manually.
  $form['#submit'][] = 'sony_register_user_register_submit';
  return $form;
}

/**
 * Custom user registration form submit handler.
 */
function sony_register_user_register_submit($form, &$form_state) {
  user_register_submit($form, $form_state);
}

/**
 * Menu callback for user/%ctools_js/login.  Handles both ajax/modal and
 * non-ajax contexts.
 */
function sony_register_ajax_login($js) {
  if (!$js) {
    return drupal_get_form('user_login');
  }

  ctools_include('modal');
  ctools_include('ajax');

  $form_state = array(
    'ajax' => TRUE,
    'title' => t('Log in'),
  );
  $output = ctools_modal_form_wrapper('user_login', $form_state);
  
  // Empty output signals the form was submitted and passed validation.
  if (empty($output)) {
    drupal_set_message('Logging in...');
    // If there are messages for the form, render them.
    if ($messages = theme('status_messages')) {
      $html = '<div class="messages">' . $messages . '</div>';
      $output[] = ctools_modal_command_display(t('Log in'), $html);
    }
    $output[] = array('command' => 'reload');
  }

  ctools_ajax_render($output);
}

