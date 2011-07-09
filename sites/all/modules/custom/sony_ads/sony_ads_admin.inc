<?php

function sony_ads_settings_form() {
  $form = array();
  $form['sony_ads_sitename'] = array(
    '#type' => 'textfield',
    '#title' => t('Ad Sitename'),
    '#default_value' => variable_get('sony_ads_sitename', ''),
    '#size' => 60,
    '#maxlength' => 64,
    '#description' => t('Sitename that will be passed to the ads. Please only use letters numbers and .'),
  );
  $form['sony_ads_ham_exclude'] = array(
    '#type' => 'textarea',
    '#title' => t('Exclude HAM on these pages'),
    '#default_value' => variable_get('sony_ads_ham_exclude', "videos\nvideos/*\nvideo/*\nadmin\nadmin/*\ndevel/*\nsonybmg_dev\nsonybmg_dev/*"),
    '#cols' => 60,
    '#rows' => 5,
    // Description taken from block module
    '#description' => t('Enter one page per line as Drupal paths. The \'*\' character is a wildcard. Example paths are blog for the blog page and blog/* for every personal blog. @front is the front page.', array('@front' => '<front>')),
  );
  $form['freewheel_account'] = array(
    '#type' => 'fieldset',
    '#title' => t('Freewheel Account Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['freewheel_account']['sony_ads_fw_network_id'] = array(
    '#type' => 'textfield',
    '#title' => t('FreeWheel Network ID'),
    '#default_value' => variable_get('sony_ads_fw_network_id', '61017'),
    '#size' => 60,
    '#maxlength' => 64,
    '#description' => t('Network ID that is passed into FreeWheel Javascript. Should always be a positive integer.'),
  );
  $form['freewheel_account']['sony_ads_fw_server_hex'] = array(
    '#type' => 'textfield',
    '#title' => t('FreeWheel Server Hex'),
    '#default_value' => variable_get('sony_ads_fw_server_hex', 'ee59'),
    '#size' => 60,
    '#maxlength' => 64,
    '#description' => t('Server Hex that is passed into FreeWheel Javascript. Consists of a combination of digits and letters from A to E'),
  );
  $form['freewheel_account']['sony_ads_fw_network_root'] = array(
    '#type' => 'textfield',
    '#title' => t('FreeWheel Network Root'),
    '#default_value' => variable_get('sony_ads_fw_network_root', 'sonymusic_live'),
    '#size' => 60,
    '#maxlength' => 64,
    '#description' => t('Network root that is passed into FreeWheel Javascript.'),
  );
  return system_settings_form($form);
}