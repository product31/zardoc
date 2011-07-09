<?php
// $Id$

/**
 * @file
 * Short file description
 */

function validate_test_form() {
  $form = array();
  $form['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#maxlength' => 32,
    '#validation_rules' => array(
      'minLengthWithCharacterCount' => 2,
      'maxlength' => 32,
      'uniqueUsername' => TRUE,
    ),
    '#description' => t('This field is required and also requires a minimum length of 2 characters.'),
  );
  $form['mail'] = array(
    '#title' => t('Email address'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#maxlength' => 128,
    '#validation_rules' => array(
      'maxlength' => 128,
      'uniqueEmail' => TRUE,
    ),
    '#description' => t('This field is required and must validate as an email address.'),
  );
  $form['url'] = array(
    '#title' => t('URL'),
    '#type' => 'textfield',
    '#maxlength' => 128,
    '#validation_rules' => array(
      'url' => TRUE,
    ),
    '#description' => t('This field is not required, but if given must validate as an URL.'),
  );
  $form['num'] = array(
    '#title' => t('Favorite number'),
    '#type' => 'textfield',
    '#maxlength' => 2,
    '#validation_rules' => array(
      'number' => TRUE,
    ),
    '#description' => t('This field is not required, but if given must validate as a number.'),
  );

  $form['submit'] = array('#type' => 'submit', '#value' => t('Submit'));

  return $form;
}

