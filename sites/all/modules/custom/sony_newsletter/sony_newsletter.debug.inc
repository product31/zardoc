<?php

/**
 * Returns a table containing status of all subscriptions for currently logged in user
 */
function sony_newsletter_subscriptions() {
  global $user;

  $sony_newsletter = sony_newsletter_request_instance($user->mail);
  $lists = $sony_newsletter->subscriptionStatus();

  $rows = array();
  foreach($lists as $list_id => $status) {
    $rows[] = array(
      array('data' => $list_id, 'header' => TRUE),
      $status,
    );
  }

  return theme('table', NULL, $rows);
}

function sony_newsletter_test_form($form_state) {
  module_load_include('inc', 'sony_newsletter', 'sony_newsletter.helpers');

  if (empty($form_state['values'])) {
    // Warn them that we use devel for output.
    if (!module_exists('devel')) {
      drupal_set_message(t('Need to enable the devel module to use this.'), 'error');
    }

    $form_state['values'] = array(
      'list_code' => sony_newsletter_get_default(),
      'email' => '',
      'with_demo' => 0,
      'demographics' => array(
        'first_name' => '',
        'country' => module_exists('geoip') ? geoip_country_code() : NULL,
        'zip_postal_code' => '',
        'coppa_dob' => array('day' => 1, 'month' => 1, 'year' => 1980),
      ),
    );
  }

  $form['list_code'] = array(
    '#type' => 'textfield',
    '#title' => t('List Code'),
    '#required' => TRUE,
    '#default_value' => $form_state['values']['list_code'],
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#required' => TRUE,
    '#default_value' => $form_state['values']['email'],
  );

  $form['demographics'] = array(
    '#type' => 'fieldset',
    '#title' => t('Demographics'),
    '#tree' => 1,
  );
  $form['demographics']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Full Name'),
    '#default_value' => $form_state['values']['demographics']['first_name'],
  );
  $form['demographics']['country'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#options' => _sony_newsletter_country_lookup(),
    '#default_value' => $form_state['values']['demographics']['country'],
  );
  $form['demographics']['zip_postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal Code'),
    '#size' => 10,
    '#default_value' => $form_state['values']['demographics']['zip_postal_code'],
  );
  $form['demographics']['coppa_dob'] = array(
    '#type' => 'coppa_dob',
    '#title' => t('Date of birth'),
    '#element_validate' => array('sony_newsletter_copy_coppa_dob_value'),
    '#default_value' => $form_state['values']['demographics']['coppa_dob'],
  );

  $debug = array('submission' => t('Submission'), 'request' => t('Request'), 'result' => t('Result'));
  foreach ($debug as $key => $title) {
    if (isset($form_state['storage'][$key])) {
      $form[$key] = array(
        '#type' => 'item',
        '#title' => $title,
        '#value' => kprint_r($form_state['storage'][$key], TRUE),
      );
    }
  }

  $form['subscribe'] = array(
    '#type' => 'submit',
    '#value' => t('Subscribe'),
  );
  $form['unsubscribe'] = array(
    '#type' => 'submit',
    '#value' => t('Unsubscribe'),
  );
  $form['status'] = array(
    '#type' => 'submit',
    '#value' => t('Status'),
  );

  return $form;
}

# Handy for debugging the $form.
#function sony_newsletter_test_form_validate($form, &$form_state) {
#  dsm($form);
#}

function sony_newsletter_test_form_submit($form_id, &$form_state) {
  $form_state['storage'] = array();

  $request = sony_newsletter_request_instance($form_state['values']['email']);
  $form_state['storage']['request'] = $request;

  switch($form_state['values']['op']) {
    case t('Subscribe'):
      // Pull out the coppa_dob since sony_newsletter_copy_coppa_dob_value()
      // should have copied it to the birth_* values.
      $form_state['storage']['submission'] = $form_state['values']['demographics'];
      unset($form_state['storage']['submission']['coppa_dob']);

      $form_state['storage']['result'] = $request->subscribe($form_state['values']['list_code'], $form_state['storage']['submission']);
      break;

    case t('Unsubscribe'):
      $form_state['storage']['result'] = $request->unsubscribe($form_state['values']['list_code']);
      break;

    case t('Status'):
      $form_state['storage']['result'] = $request->subscriptionStatus();
      break;
  }
}
