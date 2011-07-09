<?php

/**
 * FAPI form callback
 */
function sony_newsletter_admin_settings_form() {
  $form['sony_newsletter_lists'] = array(
    '#tree' => TRUE,
    '#theme' => 'sony_newsletter_admin_list_form',
  );
  $i = 0;
  $newsletters = sony_newsletter_load_all();
  foreach ($newsletters as $code => $details) {
    // Put a copy of the code that's for display...
    $form['sony_newsletter_lists'][$code]['id'] = array(
      '#type' => 'item',
      '#title' => t('Code'),
      '#value' => check_plain($code),
    );
    // ...and a value one for saving.
    $form['sony_newsletter_lists'][$code]['code'] = array(
      '#type' => 'value',
      '#value' => $code,
    );
    $form['sony_newsletter_lists'][$code]['description'] = array(
      '#type' => 'textfield',
      '#title' => t('Description'),
      '#required' => TRUE,
      '#default_value' => $details['description'],
    );
    $form['sony_newsletter_lists'][$code]['default'] = array(
      '#type' => 'checkbox',
      '#title' => t('Selected by Default'),
      '#default_value' => $details['default'],
    );
    $form['sony_newsletter_lists'][$code]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => $i++,
    );
    $form['sony_newsletter_lists'][$code]['operations'] = array(
      '#type' => 'item',
      '#title' => t('Operations'),
      '#value' => l(t('Delete'), 'admin/settings/sony_newsletter/delete/' . $code),
    );
  }

  $form['paths'] = array(
    '#type' => 'fieldset',
    '#title' => t('Paths'),
  );
  $form['paths']['sony_newsletter_signup_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Sign-up page'),
    '#default_value' => variable_get('sony_newsletter_signup_path', 'newsletter/signup'),
    '#description' => t('The newsletter link block will direct users to this page to sign up for the newsletter. The default is: <kbd>newsletter/signup</kbd>'),
  );
  $form['paths']['sony_newsletter_subscribed_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Subscribed page'),
    '#default_value' => variable_get('sony_newsletter_subscribed_path', 'newsletter/subscribed'),
    '#description' => t('After subscribing to the newsletter the visitor will be redirected to this path. The default is: <kbd>newsletter/subscribed</kbd>'),
  );

  $form['signup'] = array(
    '#type' => 'fieldset',
    '#title' => t('Signup Form'),
  );
  $form['signup']['sony_newsletter_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title for list of newsletters'),
    '#default_value' => variable_get('sony_newsletter_title', 'Newsletters'),
    '#description' => t('This can be empty if you do not want a title above the list of newsletters'),
  );
  $form['signup']['sony_newsletter_newsletter_on_register'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('sony_newsletter_newsletter_on_register', 1),
    '#title' => t('Include newsletter signup on the registration form'),
  );

  $form['mobile'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mobile'),
  );
  $form['mobile']['sony_newsletter_mobile_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Code'),
    '#description' => t('Currently the only way to get this is from the <a href="!link">Form generator</a>. The ID should be similar to %id', array('!link' => url('http://subs.sonymusic.com/tools/formPreGen.action'), '%id' => 'columbia:nicoleatkins')),
    '#default_value' => variable_get('sony_newsletter_mobile_id', NULL),
  );
  $form['mobile']['sony_newsletter_mobile_on_register'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include mobile option on the registration form'),
    '#default_value' => variable_get('sony_newsletter_mobile_on_register', 0),
  );
  $form['mobile']['sony_newsletter_mobile_on_full_form'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include mobile option on the full signup form'),
    '#default_value' => variable_get('sony_newsletter_mobile_on_full_form', 0),
  );

  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('API'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['api']['sony_newsletter_api_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => variable_get('sony_newsletter_api_url', 'http://subs.sonymusic.com/app/rs/1.0/'),
  );
  $form['api']['sony_newsletter_api_login'] = array(
    '#type' => 'textfield',
    '#title' => t('Login (Partner code)'),
    '#default_value' => variable_get('sony_newsletter_api_login', 'aws-r2'),
  );
  $form['api']['sony_newsletter_api_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Shared Secret'),
    '#default_value' => variable_get('sony_newsletter_api_secret', 'rtw0$753'),
  );

  $form['#submit'][] = 'sony_newsletter_admin_settings_form_submit';
  return system_settings_form($form);
}

/**
 * Sort the lists before system_settings_form_submit() saves them.
 */
function sony_newsletter_admin_settings_form_submit($form, &$form_state) {
  if (!empty($form_state['values']['sony_newsletter_lists'])) {
    uasort($form_state['values']['sony_newsletter_lists'], '_sony_newsletter_list_sort');
  }
}

/**
 * Comparison callback for sorting the lists.
 */
function _sony_newsletter_list_sort($a, $b) {
  if ($a['weight'] == $b['weight']) {
    return 0;
  }
  return ($a['weight'] < $b['weight']) ? -1 : 1;
}

function theme_sony_newsletter_admin_list_form($form, $b = null) {
  drupal_add_tabledrag('sony-newsletter-list-table', 'order', 'sibling', 'sort');
  $header = array('', t('Code'), t('Description'), t('Selected by default'), t('Weight'), t('Operations'));
  $rows = array();
  foreach (element_children($form) as $code) {
    $form[$code]['weight']['#attributes']['class'] = 'sort';
    unset(
      $form[$code]['id']['#title'],
      $form[$code]['description']['#title'],
      $form[$code]['default']['#title'],
      $form[$code]['weight']['#title'],
      $form[$code]['operations']['#title']
    );
    $rows[] = array(
      'class' => 'draggable',
      'data' => array(
        '',
        drupal_render($form[$code]['id']),
        drupal_render($form[$code]['description']),
        drupal_render($form[$code]['default']),
        drupal_render($form[$code]['weight']),
        drupal_render($form[$code]['operations']),
      ),
    );
  }
  if (empty($rows)) {
    $rows[] = array(array('colspan' => 6, 'data' => '<em>' . t('There are no lists. You could add or import one.') . '</em>'));
  }

  return theme('table', $header, $rows, array('id' => 'sony-newsletter-list-table')) . drupal_render($form);
}

/**
 * FAPI form callback
 * Add a newsletter
 */
function sony_newsletter_add_form(&$form_state, $action = 'add', $newsletter = NULL) {
  $form['code'] = array(
    '#type' => 'textfield',
    '#title' => t('Code'),
    '#required' => TRUE,
  );
  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#required' => TRUE,
  );
  $form['default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Selected by Default'),
    '#description' => t('Should this newsletter be ticked by default when someone goes to the subscription block/page?'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );
  $form['#redirect'] = 'admin/settings/sony_newsletter';

  return $form;
}

function sony_newsletter_add_form_submit($form, &$form_state) {
  sony_newsletter_save(array(
    'code' => $form_state['values']['code'],
    'description' => $form_state['values']['description'],
    'default' => $form_state['values']['default'],
  ));
  drupal_set_message(t('The %code newsletter has been saved.', array('%code' => $form_state['values']['code'])));
}

/**
 * Menu callback -- ask for confirmation of deletion
 */
function sony_newsletter_delete_confirm_form(&$form_state, $newsletter) {
  $form['newsletter'] = array(
    '#type' => 'value',
    '#value' => $newsletter,
  );

  return confirm_form($form,
    t('Are you sure you want to delete %name - %description?', array('%name' => $newsletter['code'], '%description' => $newsletter['description'])),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/settings/sony_newsletter/edit/'. $newsletter['code'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Execute deletion.
 */
function sony_newsletter_delete_confirm_form_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    sony_newsletter_delete($form_state['values']['newsletter']['code']);
    drupal_set_message(t('Newsletter %code deleted', array('%code' => $form_state['values']['newsletter']['code'])));
  }

  $form_state['redirect'] = 'admin/settings/sony_newsletter';
}

function sony_newsletter_artist_search_form($form_state) {
  $form['help'] = array(
    '#type' => 'item',
    '#value' => t("Search for an artist by name or <a href='!url'>view non-artist lists</a>.", array('!url' => url('admin/settings/sony_newsletter/artist_lists/0'))),
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Artist Name'),
    '#default_value' => isset($form_state['values']['name']) ? $form_state['values']['name'] : '',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );
  if (!empty($form_state['values']['name'])) {
    if (!empty($form_state['values']['artists'])) {
      $headers = array(t('ID'), t('Artist'));
      $rows = array();
      foreach ($form_state['values']['artists'] as $id => $name) {
        $rows[] = array(l($id, 'admin/settings/sony_newsletter/artist_lists/' . $id), check_plain($name));
      }
      $artists = theme('table', $headers, $rows);
    }
    $form['artists'] = array(
      '#type' => 'item',
      '#title' => t('Search results'),
      '#value' => empty($artists) ? t('No matches found.') : $artists,
    );
  }
  return $form;
}

function sony_newsletter_artist_search_form_submit($form_id, &$form_state) {
  $request = sony_newsletter_request_instance();
  $form_state['values']['artists'] = $request->findArtists($form_state['values']['name']);
  $form_state['rebuild'] = TRUE;
}

function sony_newsletter_artist_list_form($form_state, $artist_id) {
  $form['id'] = array(
    '#type' => 'item',
    '#title' => t('Artist ID'),
    '#value' => check_plain($artist_id),
  );

  $request = sony_newsletter_request_instance();
  $server_lists = $request->getArtistLists($artist_id);
  $local_lists = sony_newsletter_load_all();
  $mailing_ids = array();
  $rows = array();
  foreach ($server_lists['mailing'] as $id => $list) {
    if (empty($local_lists[$id])) {
      $mailing_ids[$id] = $id;
    }
  }
  $form['mailing'] = array(
    '#type' => 'value',
    '#value' => $server_lists['mailing'],
  );
  $form['mailing_ids'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Import'),
    '#options' => $mailing_ids,
  );
  $form['mobile'] = array(
    '#type' => 'value',
    '#value' => $server_lists['mobile'],
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
    '#access' => !empty($server_lists['mailing']) || !empty($server_lists['mobile']),
  );

  $form['#theme'] = 'sony_newsletter_artist_list_form';

  return $form;
}

function sony_newsletter_artist_list_form_submit($form_id, &$form_state) {
  foreach (array_filter($form_state['values']['mailing_ids']) as $id) {
    if (isset($form_state['values']['mailing'][$id])) {
      $list = array(
        'code' => $id,
        'description' => $form_state['values']['mailing'][$id]['description'],
        'default' => FALSE,
      );
      sony_newsletter_save($list);
      drupal_set_message(t('The %code newsletter has been saved.', array('%code' => $id)));
    }
  }
  $form_state['redirect'] = 'admin/settings/sony_newsletter';
}

function theme_sony_newsletter_artist_list_form($form) {
  $output = drupal_render($form['id']);

  unset($form['mailing_ids']['#title']);
  $header = array(theme('table_select_header_cell'), t('ID'), t('Description'), t('Client'), t('Label'));
  $rows = array();
  foreach ($form['mailing']['#value'] as $key => $list) {
    unset($form['mailing_ids'][$key]['#title']);
    $rows[] = array(
      isset($form['mailing_ids'][$key]) ? drupal_render($form['mailing_ids'][$key]) : t('Done'),
      check_plain($key),
      check_plain($list['description']),
      check_plain($list['client']),
      check_plain($list['label']),
    );
  }
  if (!$rows) {
    $rows[] = array(array('colspan' => 5, 'data' => '<em>'. t('None found.') .'</em>'));
  }
  $output .= theme('table', $header, $rows, array(), t('Mailing Lists'));

  $header = array('', t('ID'), t('Description'), t('Partner'));
  $rows = array();
  foreach ($form['mobile']['#value'] as $key => $list) {
    $rows[] = array(
      '',
      check_plain($key),
      check_plain($list['description']),
      check_plain($list['partner']),
    );
  }
  if (!$rows) {
    $rows[] = array(array('colspan' => 4, 'data' => '<em>'. t('None found.') .'</em>'));
  }
  $output .= theme('table', $header, $rows, array(), t('Mobile Lists'));

  return $output . drupal_render($form);
}