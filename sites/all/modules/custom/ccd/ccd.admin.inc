<?php
// $Id$

/**
 * @file
 * Admin pages/forms for ConnectedCD module.
 */

/**
 * Menu callback for admin/sony/ccd
 * Displays a table of available releases.
 */
function ccd_admin_overview() {
  $rows = array();

  $result = db_query('SELECT * FROM {ccd_release}');
  while ($release = db_fetch_object($result)) {
    $ops = array(
      l(t('Edit'), 'admin/sony/ccd/edit/'. $release->id),
      l(t('Delete'), 'admin/sony/ccd/delete/'. $release->id),
    );

    $rows[] = array(
      $release->id,
      filter_xss_admin($release->name),
      l(t('Form'), 'ccd/verify/'. $release->id),
      join(' | ', $ops),
    );
  }

  $header = array(t('ID'), t('Name'), t('Verification form'), t('Operations'));

  if (!count($rows)) {
    $rows[] = array(array('colspan' => 4, 'data' => t('There are no releases defined yet.  Use the <em>Add release</em> tab to create a new release.')));
  }
  $output = theme('table', $header, $rows);

  return $output;
}

/**
 * Form callback for adding/editing a release.
 */
function ccd_admin_release_form($form_state, $release = NULL) {
  $form = array();

  $form['#release'] = $release;

  $form['id'] = array(
    '#type' => 'textfield',
    '#title' => t('Release ID'),
    '#description' => t('The release ID from the ConnectedCD system.'),
    '#size' => 10,
    '#required' => TRUE,
    '#default_value' => $release ? $release->id : '',
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('A descriptive name to identify this release throughout the site.'),
    '#maxlength' => 255,
    '#required' => TRUE,
    '#default_value' => $release ? $release->name : '',
  );
  $form['validate_error_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Validation Error'),
    '#description' => t('Where should the validation process redirect to upon error.  This should be a valid Drupal path, or left blank to use the default.'),
    '#maxlength' => 255,
    '#default_value' => $release ? $release->validate_error_path : '',
  );
  $form['validate_success_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Validation Success'),
    '#description' => t('Where should the validation process redirect to upon success.  This should be a valid Drupal path, or left blank to use the default.'),
    '#maxlength' => 255,
    '#default_value' => $release ? $release->validate_success_path : '',
  );
  $form['redeem_unauthorized_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Unauthorized redemption'),
    '#description' => t('Where should the redemption process redirect after an unauthorized redemption attempt.  This should be a valid Drupal path, or left blank to use the default.'),
    '#maxlength' => 255,
    '#default_value' => $release ? $release->redeem_unauthorized_path : '',
  );
  $form['redeem_redeemed_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Already redeemed'),
    '#description' => t('Where should the redemption process redirect to if the item has already been redeemed.  This should be a valid Drupal path, or left blank to use the default.'),
    '#maxlength' => 255,
    '#default_value' => $release ? $release->redeem_redeemed_path : '',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save release'),
  );

  return $form;
}

/**
 * Form submit handler for adding/editing a release.
 */
function ccd_admin_release_form_submit($form, &$form_state) {
  ccd_release_save($form_state['values'], ($form['#release'] && $form['#release']->id));

  $form_state['redirect'] = 'admin/sony/ccd';
}

/**
 * Form callback for deleting a release.
 */
function ccd_admin_release_delete($form_state, $release = NULL) {
  $form = array();
  $form['#release'] = $release;

  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $release->name)),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/sony/ccd',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Form submit handler for deleting a release.
 */
function ccd_admin_release_delete_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    ccd_release_delete($form['#release']);
  }

  $form_state['redirect'] = 'admin/sony/ccd';
}

