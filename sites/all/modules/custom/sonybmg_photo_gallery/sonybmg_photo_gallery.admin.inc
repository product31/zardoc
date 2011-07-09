<?php
// $Id$

/**
 * @file
 * Admin page callback include file for sonybmg_photo_gallery module
 *
 * These functions are responsible for building the photo gallery admin pages  
 * and as such dont need to be loaded for non-photo-gallery page requests. This
 * file will be loaded automatically by the drupal menu system.
 */

/**
 * Forms API callback for the photos administration form
 */
function sonybmg_photo_gallery_settings_form() {
  $form = array();
  // preload variables for the form
  $ovid = variable_get('sonybmg_photo_gallery_official_vocabulary', 0);
  $uvid = variable_get('sonybmg_photo_gallery_user_vocabulary', 0);
  $vocabularies = array();
  $result = db_query("SELECT vid, name FROM {vocabulary} WHERE module = 'taxonomy' OR module = 'sonybmg_photo_gallery'");
  while ($vocabulary = db_fetch_object($result)) {
    $vocabularies[$vocabulary->vid] = $vocabulary->name;
  }

  $form['sonybmg_photo_gallery_official_vocabulary'] = array(
    '#type' => 'select',
    '#title' => t('Official gallery'),
    '#default_value' => $ovid,
    '#options' => $vocabularies,
    '#description' => t('The gallery to use for official photos.'),
  );

  $form['sonybmg_photo_gallery_user_vocabulary'] = array(
    '#type' => 'select',
    '#title' => t('User gallery'),
    '#default_value' => $uvid,
    '#options' => $vocabularies,
    '#description' => t('The gallery to use for user photos.'),
  );

  $form['sonybmg_photo_gallery_additional_user_links'] = array(
    '#type' => 'textarea',
    '#title' => t('Additional gallery links (compact view)'),
    '#default_value' => variable_get('sonybmg_photo_gallery_additional_user_links', NULL),
    '#description' => t('These links (one per line) will appear in the compacy list of galleries alongside the dynamic categories. Use it for links to offsite photo galleries like HotOrNot, etc.'),
  );

  $form['sonybmg_photo_gallery_additional_user_markup'] = array(
    '#type' => 'textarea',
    '#title' => t('Additional gallery links (full view)'),
    '#default_value' => variable_get('sonybmg_photo_gallery_additional_user_markup', NULL),
    '#description' => t('This HTML will appear in the gallery sidebar on the main photo page, in addition to the dynamic categories. Use it for links to offsite photo galleries like HotOrNot, etc.'),
  );

  $form['pager'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pager settings'),
    '#tree' => 0,
  );
  $form['pager']['sonybmg_photo_gallery_pager_location'] = array(
    '#type' => 'radios',
    '#title' => t('Location'),
    '#options' => array(
      'top' => t('Above the photo'),
      'bottom' => t('Below the photo'),
      'none' => t('Don\'t display the pager. Use this if you would rather display the pager block.'),
    ),
    '#default_value' => variable_get('sonybmg_photo_gallery_pager_location', 'top'),
  );
  $form['pager']['sonybmg_photo_gallery_pager_count'] = array(
    '#type' => 'select',
    '#title' => t('Number of photos per page'),
    '#options' => drupal_map_assoc(range(1, 20)),
    '#default_value' => variable_get('sonybmg_photo_gallery_pager_count', 5),
  );
  
  return system_settings_form($form);
}

