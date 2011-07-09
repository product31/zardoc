<?php
// $Id$
/**
 * @file
 *
 */

function sony_header_admin_header_paste() {
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
  '#default_value' => isset($header->language) ? $header->language : $lang->language,
  '#description' => t('Select a language.'),
);
  
   $form['xml'] = array(
    '#type' => 'textarea',
    '#title' => t('XML'),
	'#description' => t('Paste the XML of this Flash Header instance.'),
	'#rows' => 5,
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
function sony_header_admin_header_paste_submit(&$form, &$form_state) {
  $header =  sony_header_paste($form_state['values']['xml'],$form_state['values']['name'], $form_state['values']['title']);
  sony_header_save($header);
}
