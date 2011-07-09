<?php

function broserver_admin_settings() {
  $options = array(
    '' => t('None'),
  );
  
  $files = file_scan_directory(drupal_get_path('module', 'broserver') . '/config/', 'config.php$');
  foreach ($files as $absolute => $file) {
    $bro = NULL;
    require_once $absolute;
    if (isset($bro)) {
      $options[$bro->id] = $bro->description;
    }
  }

  $form['bro_config'] = array(
    '#type' => 'select',
    '#title' => t('BRO configuration'),
    '#options' => $options,
    '#default_value' => variable_get('bro_config', ''),
  );
  
  return system_settings_form($form);
}
