<?php

function sony_meta_admin_page() {
  $result = db_query('SELECT * FROM {sony_meta} ORDER BY title');
  while ($row = db_fetch_object($result)) {
    $all_languages = language_list();  
    $current_language = $all_languages[$row->language];
    $url = url($row->path, array('language' => $current_language));
    $rows[] = array(
      $row->title,
      $row->keywords,
      $row->description,
      $row->path,
      $row->language,
      '<a href="' . $url . '">' . t('View/Edit') . '</a>',
      l(t('Delete'), 'sony_meta/delete/' . $row->mid),
    );
  }
  $header = array(t('Title'), t('Keywords'), t('Description'), t('Path'), t('Language'), t('Edit'), t('Delete'));
  $page = theme('table', $header, $rows);
  return $page;
}

/*
 * Delete custom meta
 */
 
function sony_meta_delete($form_state, $meta) {
  $form['#meta'] = $meta;
  return confirm_form($form, t('Are you sure you want to delete custom meta information from %meta-path?', array('%meta-path' => $meta->path)), 'admin/settings/meta', '', t('Delete'), t('Cancel'));
}

function sony_meta_delete_submit($form, &$form_state) {
  $meta = $form['#meta'];
  
  // redirect user to page they just deleted meta from
  $form_state['redirect'] = $meta->path;
  
  db_query('DELETE FROM {sony_meta} WHERE mid = %d LIMIT 1', $meta->mid);
  drupal_set_message(t('Meta deleted'));
  // Clear the page and block caches.
  cache_clear_all();
}

function sony_meta_google_admin_page() {

  $form = array();
  $form['sony_meta_google_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Webmaster Code'),
    '#default_value' => variable_get('sony_meta_google_code', NULL),
    '#size' => 120,
    '#maxlength' => 120,
  );

  return system_settings_form($form);
}
