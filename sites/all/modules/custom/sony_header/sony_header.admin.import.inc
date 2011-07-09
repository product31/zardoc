<?php
// $Id$
/**
 * @file
 *
 */

function sony_header_admin_header_import() {
  $lang = variable_get('language_default', '');
  $form = array();
  $regions = sony_header_return_regions();  
  $form['name'] = array(
        '#type' => 'select',
    '#title' => t('Block Name'),
    '#required' => 1,
    '#options' => $regions,
    '#default_value' => isset($header->name) ? $header->name : 'flash_header',
        '#description' => t('Assign this Flash header to a block region.'),
  );
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
	'#description' => t('Enter the title of this Flash Header instance.'),
	'#weight' => -15,
  );
  $form ['language'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#required' => 1,
    '#options' => locale_language_list(),
    '#default_value' => isset($lang->language) ? $lang->language : 'en',
    '#description' => t('Select a language.'),
);

  // Detect available templates.
  $templates = file_scan_directory('./' . drupal_get_path('theme', variable_get('theme_default', 'garland')) . '/header_templates', '\.xml$');
  if (empty($templates)) {
    drupal_set_message(t('There is not a flash header for this theme. You can place it in %path.', array(
      '%path' => drupal_get_path('theme', variable_get('theme_default', 'garland')) . '/header_templates',
    )), 'warning');
  }
  $templates += file_scan_directory('./' . drupal_get_path('module', 'sony_header') . '/templates', '\.xml$');
  $form['#templates'] = $templates;

  $options = array();
  foreach ($templates as $key => $template) {
    $options[$key] = $template->name;
  }
  $form['template'] = array(
    '#type' => 'select',
    '#options' => $options,
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['#redirect'] = 'admin/build/sony_header';
  return $form;
}

/**
 * Admin import form FAPI submit callback.
 */
function sony_header_admin_header_import_submit(&$form, &$form_state) {
  $upload = FALSE;
  if ($upload) {
    //
  }
  else {
    $file = $form['#templates'][$form_state['values']['template']];
  }

  // Fetch a header object from the supplied header file.
  $header = sony_header_import($file, $form_state['values']['name'], $form_state['values']['title'], $form_state['values']['language']);
  sony_header_save($header);
}
