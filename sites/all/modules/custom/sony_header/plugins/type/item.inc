<?php
// $Id$

/**
 * @file
 *
 */

/**
 * Implementation of hook_sony_header_type().
 */
function sony_header_item_sony_header_type() {
  return array(
    'tag' => 'item',
    'content' => FALSE,
    'container' => TRUE,
    'render' => 'sony_header_item_render',
    'settings form' => 'sony_header_item_settings_form',
    'settings form validate' => 'sony_header_item_settings_form_validate',
  );
}

/**
 * Item settings form.
 */
function sony_header_item_settings_form(&$form, &$form_state) {

  $attributes = $form_state['#item']->attributes;
  $form['attributes']['tracking'] = array(
    '#type' => 'textfield',
    '#title' => t('Tracking'),
    '#default_value' => isset($attributes['tracking']) ? $attributes['tracking'] : '',
    // TODO - Get a better description
     '#description' => 'Implementation of Google Analytics in our Flash Header Tool. In the field above, enter <strong>the web property ID</strong>. This is also known as the <em>UA number</em> of your tracking code and looks like <code>UA-xxxxx-yy</code>, where the x\'s and y\'s are replaced with the numbers that correspond to your account and profile information for the object you are tracking. See <a href="/apis/analytics/docs/concepts/gaConceptsAccounts.html#webProperty" target="blank">Web Property</a> for more information.',
  );
  
  $form['attributes']['overrideTimer'] = array(
    '#type' => 'textfield',
    '#title' => 'Override Timer',
    '#default_value' => isset($attributes['overrideTimer']) ? $attributes['overrideTimer'] : '',
    '#description' => t('An integer in seconds, or the string "videoEvent" to specify that the carousel should pause/resume based on video events.'),
  );
}

/**
 * Validate item settings form.
 */
function sony_header_item_settings_form_validate(&$form, &$form_state) {

  $overrideTimer = $form_state['values']['attributes']['overrideTimer'];
  if ($overrideTimer != '' &&
      $overrideTimer != 'videoEvent' &&
      !(is_numeric($overrideTimer) && (int) $overrideTimer == $overrideTimer && $overrideTimer > 0)) {

    form_error($form['attributes']['overrideTimer'], t('Invalid timer value. It must be an integer or "videoEvent".'));
  }
}

/**
 * Render callback for config element.
 */
function sony_header_item_render(&$xml, &$element, &$item) {
  // We only want 2 attributes so filter down to just those 2.
  $item->attributes = array_intersect_key($item->attributes, array(
    'id' => TRUE,
    'tracking' => TRUE,
    'overrideTimer' => TRUE,
  ));
}
