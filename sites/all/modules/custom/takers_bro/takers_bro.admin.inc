<?php

function takers_bro_admin_settings_form() {
  $form['takers_bro_autoshow'] = array(
    '#type' => 'select',
    '#title' => t('Automatically Open'),
    '#default_value' => variable_get('takers_bro_autoshow', NULL),
    '#options' => array(
      NULL => t('Never'),
      'once' => t('Once'),
      'always' => t('Always (useful when testing)'),
    ),
  );
  $form['takers_bro_duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Autoshow duration'),
    '#default_value' => variable_get('takers_bro_duration', 6),
    '#description' => t('When automatically showing the BRO keep it open for this many seconds.')
  );

  return system_settings_form($form);
}