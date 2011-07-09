<?php
// $Id$

/**
 * @file
 *   Globalnews administration section.
 */

/**
 * Ctools multistep form wizard.
 */
function globalnews_wizard() {
  // Merlin hints that there's a better way to figure out the step.
  $step = arg(4);
  // Required includes for the multistep form wizard.
  ctools_include('wizard');
  ctools_include('object-cache');

  // The setup array for the multistep form.
  $form_info = array(
    'id' => 'globalnews_basic',
    'path' => "admin/content/globalnews/settings/%step",
    'show trail' => TRUE,
    'show back' => TRUE,
    'show cancel' => TRUE,
    'show return' => FALSE,
    'next text' => 'Configure',
    'next callback' =>  'globalnews_basic_add_subtask_next',
    'finish callback' => 'globalnews_basic_add_subtask_finish',
    'return callback' => 'globalnews_basic_add_subtask_finish',
    'cancel callback' => 'globalnews_basic_add_subtask_cancel',
    'order' => array(
      'create' => t('Step 1: Select region'),
      'deploy' => t('Step 2: Subscribe to news'),
    ),
    'forms' => array(
      'create' => array(
        'form id' => 'globalnews_add_form',
      ),
      'deploy' => array(
        'form id' => 'globalnews_deployment_form',
      ),
    ),
  );

  // Set up the form for multistep.
  $form_state = array(
    'cache name' => NULL,
  );
  // No matter the step, you will load your values from the callback page.
  $globalnews = globalnews_basic_get_page_cache(NULL);
  if (!$globalnews) {
    // Set form to the first step since we have no data.
    $step = current(array_keys($form_info['order']));
    $globalnews = new stdClass();
    // Set the storage object so its ready for whatever comes next.
    ctools_object_cache_set('globalnews_basic', $form_state['cache name'], $globalnews);
  }
  // This is where we will store all form data.
  $form_state['globalnews_obj'] = $globalnews;
  // This is the function call that makes the multistep form wizard work.
  $output = ctools_wizard_multistep_form($form_info, $step, $form_state);
  return $output;
}

/**
 * First step of the globalnews multistep form.
 *
 * All forms within this wizard will take $form, and $form_state by reference.
 * Note that the form doesn't have a return value.
 */
function globalnews_add_form(&$form, &$form_state) {
  ctools_include('dependent');
  global $user;
  // Load every enabled language if the user is an administrator only.
  if (in_array('administrator', $user->roles)) {
    $options = i18n_language_list();
  }
  else {
    $options = i18n_access_load_permissions($user->uid);
  } 

  $globalnews = &$form_state['globalnews_obj'];
  // Display the language configuration select box.
  $form['globalnews'] = array(
    '#type' => 'fieldset',
    '#title' => t('Region Settings'),
    '#description' => t('Configure Global News subscriptions.'),
  );
  $form ['globalnews']['region'] = array(
    '#type' => 'select',
    '#title' => t('Global Region'),
    '#required' => 1,
    '#options' => $options,
    '#default_value' => $globalnews->region,
    '#description' => t('Select your region.'),
  );
  // Build a list of languages the languages subscribed to each.
  $form['current'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global News Subscriptions'),
    '#weight' => 1010,
    '#description' => t('Current Global News subscriptions by region.'),
  );
  // Load the subsribers for each language and unset any with no subscribers.
  // @todo This seems like a very inefficient way to do this. We should find
  // a way to not store empty values so we dont have to unset them later.
  foreach ($options as $language_code => $language_name) {
    $subscription = array();
    $subscriptions = globalnews_load_subscriptions($language_code);
     foreach ($subscriptions as $key => $value) {
       if (empty($value)) {
         unset($subscriptions[$language_name]);
         }
       }
       // Replace language codes with language names.
       foreach ($subscriptions as $code => $name) {
         $subscription[] = globalnews_get_language_name($subscriptions[$code]);
       }
       // Remove any languages with no subscibers so they are not displayed
       // as empty values.
       foreach ($subscription as $key => $value) {
         if (empty($value)) {
           unset($subscription[$key]);
         }
       }
    // Add the subscription overview element to the form. Display a different
    // message for languages with no subscribers.
    $form['current'][$language_code] = array(
      '#type' => 'item',
      '#title' => !empty($subscription) ? t('@region is currently subscribed to global news from the following regions: ' . implode(', ', $subscription), array('@region' => $language_name)) : t('@region is not subscribed to any global news', array('@region' => $language_name)) ,
      '#description' => $language_code . ' Global News subscriptions.',
      );

   }
  $form_state['no buttons'] = TRUE;
}

/**
 * Helper function for language name replacements.
 *
 * @todo See if there is a way to do this without hitting the database. This
 *   function name is misleading. We should load all the names at once into a
 *   static variable then replace language codes from the values loaded into
 *   that static variable instead of going back to the db.
 */
function globalnews_get_language_name($langcode) {
  $subscription = db_result(db_query("SELECT name FROM {languages} WHERE language = '%s'", $langcode));
  return $subscription;
}

/**
 * Submit handler for globalnews add form.
 *
 * Generally, you will never save data here -- you will simply add values to the
 * yet to be saved ctools_cache object. Saving happens at the end, within the
 * $form_info['finish callback'];
 */
function globalnews_add_form_submit(&$from, &$form_state) {
  $globalnews = &$form_state['globalnews_obj'];
  $globalnews->region = $form_state['values']['region'];
}

/**
 * The final step of the globalnews multistep form. This is where territoies
 * sign up for globalnews feeds.
 */
function globalnews_deployment_form(&$form, &$form_state) {
  $globalnews = &$form_state['globalnews_obj'];
  $options = i18n_language_list();
  $default = globalnews_load_subscriptions($globalnews->region);
  $form['gregion'] = array(
  '#type' => 'item',
  '#title' => t('Select subscriptions for') . ' ' . globalnews_get_language_name($globalnews->region),
  '#default_value' => $globalnews->region,
  );
  // List all global news feeds available for subscription.
  foreach ($options as $language => $langcode) {
    $form['global'] = array(
      '#type' => 'fieldset',
      '#title' => ' Global News Feeds',
      '#description' => t("Choose from any of these available news feeds."),
      '#prefix' => '<div>',
      '#suffix' => '</div>',
      '#tree' => TRUE,
      );
    $form['global'][$langcode] = array(
      '#type' => 'checkboxes',
      '#options' => $options,
      '#default_value' => !empty($default) ? $default : array(),
      '#process' => array('expand_checkboxes', 'ctools_dependent_process'),
      '#dependency' =>  array('edit-region' => $langcode),
      '#prefix' => '<div id ="edit-global-' . $langcode . '-wrapper">',
      '#suffix' => '</div>',
    );
   drupal_add_js('$(document).ready(function(){$("#edit-global-' . str_replace(array('][', '_', ' '), '-', $langcode) . '-' . $globalnews->region . '-wrapper").hide();});', 'inline');
  }
  $form_state['no buttons'] = TRUE;
}


/**
 * Submit handler for the final step of the global news subscriptions
 * multistep form.
 */
function globalnews_deployment_form_submit(&$form, &$form_state) {
  $languages = i18n_language_list();
  foreach ($languages as $language => $langcode) {
     // Set the language code in a form state variable.
    if (!empty($form_state['values']['global'])) {
      $form_state['globalnews_obj']->$langcode = $form_state['values']['global'][$langcode];
    }
  }
}

/**
 * Callback generated when the add page process is finished.
 *
 * This is where subscriptions are written into the globalnews table.
 */
function globalnews_basic_add_subtask_finish(&$form_state) {
  global $user;
  $globalnews = &$form_state['globalnews_obj'];
  $languages = i18n_language_list();
  $region = $globalnews->region;
  foreach ($languages as $language => $langcode) {
    if (!empty($globalnews->$langcode)) {
      $langs = ($globalnews->$langcode);
      db_query("DELETE FROM {globalnews} WHERE region = '%s'", $region);
      db_query("INSERT INTO {globalnews} (region, langs) VALUES ('%s', '%s')", $region, implode(', ', $langs));
      foreach ($langs as $key => $sub) {
        if (empty($sub)) {
          unset($langs[$key]);
        }
      }
      foreach ($langs as $language_code => $language_name) {
        $lang[] = globalnews_get_language_name($langs[$language_code]);
      }
      drupal_set_message(t('%globalnews_languages successfully configured to recieve news from %territories.', array('%globalnews_languages' => globalnews_get_language_name($globalnews->region), '%territories' => implode(', ', $lang))));
      watchdog('globalnews', 'Username %name subscribed %region to newsfeeds from %langs.', array('%name' => $user->name, '%region' => $globalnews->region, '%langs' => implode(', ', $langs)), WATCHDOG_NOTICE);
    }
  }
  // Clear the cache.
  ctools_object_cache_clear('globalnews_basic', $form_state['cache name']);
  $form_state['redirect'] = 'admin/content/globalnews/settings';
}

/**
 * Callback for the proceed step.
 */
function globalnews_basic_add_subtask_next(&$form_state) {
  $globalnews = &$form_state['globalnews_obj'];
  $globalnews->region = $form_state['values']['region'];
  $cache = ctools_object_cache_set('globalnews_basic', $form_state['cache name'], $globalnews);
}

/**
 * Callback generated when the 'cancel' button is clicked.
 * All we do here is clear the cache.
 */
function globalnews_basic_add_subtask_cancel(&$form_state) {
  // Update the cache with changes.
  ctools_object_cache_clear('globalnews_basic', $form_state['cache name']);
  $form_state['redirect'] = 'admin/content/globalnews/settings';
  drupal_set_message(t('Canceled.'));
}

/**
 * Remove an item from the object cache.
 */
function  globalnews_basic_clear_page_cache($name) {
  ctools_object_cache_clear('globalnews_basic', $name);
}

/**
 * Get the cached changes to a given task handler.
 */
function globalnews_basic_get_page_cache($name) {
  $cache = ctools_object_cache_get('globalnews_basic', $name);
  return $cache;
}