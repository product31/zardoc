<?php
// $Id$

/**
 * @file
 * Page callbacks for ccd.module.
 */

function ccd_verify_form($form_state, $release) {
  $form['#release'] = $release;
  $form['key'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter your key'),
    '#size' => 10,
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  drupal_set_title($release->name);

  return $form;
}

function ccd_verify_form_submit($form, &$form_state) {
  ccd_verify($form_state['values']['key'], $form['#release']->id);
}

function ccd_verify_success($release) {
  drupal_set_message(t('%name key verified successfully', array('%name' => $release->name)));
  if ($_SESSION['ccd'][$release->id]['meta_download']) {
    $_SESSION['ccd'][$release->id]['inline_download'] = $_SESSION['ccd'][$release->id]['meta_download'];
  }
  ccd_redirect('validate_success_path', $release);
}

function ccd_verify_error($release) {
  // unset the session var.
  unset($_SESSION['ccd'][$release->id]);

  drupal_set_message(t('There was an error verifying your %name key', array('%name' => $release->name)));
  ccd_redirect('validate_error_path', $release);
}

function ccd_redeem_form() {
  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter the download ID'),
    '#size' => 10,
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function ccd_redeem_form_submit($form, &$form_state) {
  $form_state['redirect'] = ccd_redeem($form_state['values']['id'], 0, TRUE);
}

function ccd_redeem_unauthorized($release) {
  $session = &$_SESSION['ccd'][$release->id];

  if ($session['destination']) {
    //ccd_set_path('validate_success_path', $release, $session['destination']);
    $session['meta_download'] = $session['q'];
    drupal_goto('ccd/verify/'. $release->id);
  }
  else {
    drupal_set_message(t('Unauthorized redemption'));
    ccd_redirect('validate_redeem_unauthorized', $release);
  }
}

function ccd_redeem_redeemed($release) {
  drupal_set_message(t('This media has already been downloaded.'));
  ccd_redirect('validate_redeem_redeemed', $release);
}

