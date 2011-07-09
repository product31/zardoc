<?php
// $Id$

/**
 * @file
 * file_description
 */

/**
 * Replacement for user_register() form to be used when the audience is
 * 'directed to children'.
 */
function sony_coppa_user_register() {
  $form['user_registration_help'] = array('#value' => filter_xss_admin(variable_get('user_registration_help', '')));

  $segments = sony_coppa_username_segments();
  $form['username'] = array(
    '#type' => 'fieldset',
    '#title' => t('Username'),
    '#description' => t('Choose a word from each list to create a unique username.'),
    '#tree' => 1,
  );
  $form['username']['part1'] = array(
    '#type' => 'select',
    '#options' => $segments[0],
    '#required' => TRUE,
    '#prefix' => '<div class="container-inline">',
  );
  $form['username']['part2'] = array(
    '#type' => 'select',
    '#options' => $segments[1],
    '#required' => TRUE,
    '#suffix' => '</div>',
  );

  $form['name'] = array('#type' => 'value', '#value' => '');
  $form['basename'] = array('#type' => 'value', '#value' => '');
  $form['number'] = array('#type' => 'value', '#value' => '');

  $form['pass'] = array(
    '#type' => 'password_confirm',
    '#required' => TRUE,
  );

  $form['privacy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Privacy questions'),
    '#tree' => 0,
  );

  $questions = sony_coppa_privacy_questions();
  $form['privacy']['question1'] = array(
    '#type' => 'select',
    '#title' => t('Question #1'),
    '#options' => $questions,
    '#required' => TRUE,
  );

  $form['privacy']['answer1'] = array(
    '#type' => 'textfield',
    '#title' => t('Answer'),
    '#required' => TRUE,
  );

  $form['privacy']['question2'] = array(
    '#type' => 'select',
    '#title' => t('Question #2'),
    '#options' => $questions,
    '#required' => TRUE,
  );

  $form['privacy']['answer2'] = array(
    '#type' => 'textfield',
    '#title' => t('Answer'),
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create new account'),
  );

  return $form;
}

/**
 * Validation for the custom user registration
 */
function sony_coppa_user_register_validate($form, &$form_state) {
  $values = $form_state['values'];

  if ($values['question1'] == $values['question2']) {
    form_set_error('question2', t('You must use different security questions.'));
  }

}

/**
 * Submission for the custom user registration
 */
function sony_coppa_user_register_submit($form, &$form_state) {
  $questions = sony_coppa_privacy_questions();
  $coppa_values = array(
    'pass' => $form_state['values']['pass'],
    'basename' => $form_state['values']['username']['part1'] . $form_state['values']['username']['part2'],
    'question1' => $questions[$form_state['values']['question1']],
    'question2' => $questions[$form_state['values']['question2']],
    'answer1' => $form_state['values']['answer1'],
    'answer2' => $form_state['values']['answer2'],
  );

  // Be prepared for name collisions. We might need to try several times before
  // we find an unused name.
  $counter = 0;
  do {
    $coppa_values['number'] = rand(1, 9999);
    $coppa_values['name'] = $coppa_values['basename'] . $coppa_values['number'];
    $user_data = array(
      'name' => $coppa_values['name'],
      'pass' => $coppa_values['pass'],
      'mail' => $coppa_values['name'] .'@localhost',
      'status' => 1,
    );
    $account = user_save(NULL, $user_data);
  } while ($account === FALSE && $counter < 10);

  if (!$account) {
    drupal_set_message(t("Error saving user account."), 'error');
    $form_state['redirect'] = '';
    return;
  }

  watchdog('user', 'New user: %name (%email).', array('%name' => $coppa_values['name'], '%email' => $coppa_values['mail']), WATCHDOG_NOTICE, l(t('edit'), 'user/'. $account->uid .'/edit'));

  if (user_authenticate($coppa_values)) {
    drupal_set_message(t('Registration successful. You are now logged in.'));
  }

  $coppa_values['uid'] = $account->uid;
  drupal_write_record('sony_coppa_user', $coppa_values);
  $_SESSION['sony_coppa_registration_info'] = $coppa_values;

  unset($_REQUEST['destination']);
  $form_state['redirect'] = 'user/info';
  return;
}

/**
 * Return a list of base username segments
 */
function sony_coppa_username_segments() {
  $options = array('' => t('-- Please Select --'));

  $part1 = $options + drupal_map_assoc(array_map('trim', explode("\n", trim(variable_get('sony_coppa_registration_username_part1', '')))));
  $part2 = $options + drupal_map_assoc(array_map('trim', explode("\n", trim(variable_get('sony_coppa_registration_username_part2', '')))));

  return array($part1, $part2);
}

/**
 * Return a list of privacy questions
 */
function sony_coppa_privacy_questions() {
  $options = array('' => t('-- Please Select --'));
  $options += array_map('trim', explode("\n", trim(variable_get('sony_coppa_registration_privacy_questions', ''))));
  return $options;
}

/**
 * Replacement for user_pass() form to be used when the audience is
 * 'directed to children'.
 */
function sony_coppa_user_pass($form_state) {
  $step = (empty($form_state['storage']['step'])) ? 1 : $form_state['storage']['step'];

  switch ($step) {
    // Step 1: Enter Username
    case 1:
      $form['name'] = array(
        '#type' => 'textfield',
        '#title' => t('Username'),
        '#maxlength' => USERNAME_MAX_LENGTH,
        '#required' => TRUE,
      );
      break;

    // Step 2: Answer privacy questions
    case 2:
      $account = user_load(array('name' => $form_state['storage']['name']));
      $result = db_query('SELECT * FROM {sony_coppa_user} WHERE uid =  %d', $account->uid);
      $data = db_fetch_array($result);
      $form['privacy_data'] = array(
        '#type' => 'value',
        '#value' => $data,
      );
      $form['answer1'] = array(
        '#type' => 'textfield',
        '#title' => check_plain($data['question1']),
        '#required' => TRUE,
      );
      $form['answer2'] = array(
        '#type' => 'textfield',
        '#title' => check_plain($data['question2']),
        '#required' => TRUE,
      );
      break;

    // Step 3: Enter new password
    case 3:
      $form['pass'] = array(
        '#type' => 'password_confirm',
        '#title' => t('Enter your new password'),
        '#required' => TRUE,
      );
      break;
  }

  $form['step'] = array('#type' => 'value', '#value' => $step);
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => ($step == 3) ? t('Save new password') : t('Next'),
  );

  return $form;
}

/**
 * Validation handler for the forgot password form.
 */
function sony_coppa_user_pass_validate($form, &$form_state) {
  $values = $form_state['values'];
  $step = $values['step'];

  switch ($step) {
    case 2:
      if (($values['privacy_data']['answer1'] != $values['answer1']) ||
        ($values['privacy_data']['answer2'] != $values['answer2'])) {
        drupal_set_message(t('The answers you provided were incorrect.'), 'error');
        $form_state['rebuild'] = TRUE;
      }
      break;
  }
}

/**
 * Submit handler for the forgot password form.
 */
function sony_coppa_user_pass_submit($form, &$form_state) {
  $values = $form_state['values'];
  $step = $values['step'];

  switch ($step) {
    case 1:
      $form_state['storage']['name'] = $values['name'];
      break;

    case 2:
      $form_state['storage']['uid'] = $values['privacy_data']['uid'];
      break;

    case 3:
      // save new password
      $account = user_load(array('uid' => $form_state['storage']['uid']));
      user_save($account, array('pass' => $values['pass']));

      drupal_set_message(t('You may now log in with your new password.'));
      $form_state['redirect'] = 'user/login';
      $form_state['rebuild'] = FALSE;
      unset($form_state['storage']);
      return;
  }

  $form_state['storage']['step'] = $step + 1;
  $form_state['rebuild'] = TRUE;
}

function sony_coppa_print_info() {
  $values = $_SESSION['sony_coppa_registration_info'];
  unset($_SESSION['sony_coppa_registration_info']);

  if (empty($values)) {
    drupal_access_denied();
    return;
  }

  drupal_set_message(t('Please print this page in case you forget your information!'));

  $output = '<p>'. t('Your username is: %username', array('%username' => $values['name'])) .'</p>';
  $output .= '<p>'. t('Your password is: %password', array('%password' => $values['pass'])) .'</p>';
  $output .= '<p>'. t('Your first privacy question is:<br/>%question<br/>%answer', array('%question' => $values['question1'], '%answer' => $values['answer1'])) .'</p>';
  $output .= '<p>'. t('Your second privacy question is:<br/>%question<br/>%answer', array('%question' => $values['question2'], '%answer' => $values['answer2'])) .'</p>';

  return $output;
}