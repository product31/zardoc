<?php
// $Id: splashpage_redirect.admin.inc,v 1.1.2.1 2010/02/11 21:13:03 andrewlevine Exp $

function splashpage_redirect_admin_settings() {
  $form = array();
  $form['splashpage_redirect_splashpage_src_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect from'),
    '#default_value' => variable_get('splashpage_redirect_splashpage_src_path', ''),
    '#size' => 60,
    '#maxlength' => SPLASHPAGE_REDIRECT_URL_MAX_LENGTH,
    '#description' => t("Enter the Drupal system path you want to add the redirect to. Enter <front> if you want to redirect from the front page and nothing if you don't want to redirect at all."),
  );
  $form['splashpage_redirect_splashpage_dst_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect to'),
    '#default_value' => variable_get('splashpage_redirect_splashpage_dst_url', ''),
    '#size' => 60,
    '#maxlength' => SPLASHPAGE_REDIRECT_URL_MAX_LENGTH,
    '#description' => t("Enter the Drupal system path or absolute URL you want to add the redirect to. Enter <front> if you want to redirect to the front page. If you want to redirect to an absolute URL, make sure you include it in full (including the protocol)."),
  );
  $options = array('off' => t('Never Redirect'), '0' => t('Always Redirect'));
  $options = array_merge($options, drupal_map_assoc(range(1, 10), 'splashpage_redirect_format_x_views'));
  $form['splashpage_redirect_authenticated_views'] = array(
    '#type' => 'select',
    '#title' => t('Redirect authenticated users after'),
    '#default_value' => variable_get('splashpage_redirect_authenticated_views','off'),
    '#options' => $options,
    '#description' => t('Redirect authenticated users from "Redirect from" to "Redirect to" after this many page views'),
  );
  $form['splashpage_redirect_anonymous_views'] = array(
    '#type' => 'select',
    '#title' => t('Redirect anonymous users after'),
    '#default_value' => variable_get('splashpage_redirect_anonymous_views','off'),
    '#options' => $options,
    '#description' => t('Redirect anonymous users from "Redirect from" to "Redirect to" after this many page views'),
  );
  return system_settings_form($form);
}

function splashpage_redirect_format_x_views($x) {
  return format_plural($x, t('1 view'), t('@count views'));
}