<?php
/**
* Default labelling and weight for this profile include
*/
function friendlist_info() {
  return array(
    'name' => st('Friend List'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 0,
  );
}

function friendlist_task_list() {
  return array(
    'friendlist_create_relationship' => array(
      'message' => st('Created friendship relationship.'),
      'weight' => 10,
    ),
  );
}

/**
 * Required modules in order for these options to be created successfully
 */
function friendlist_modules() {
  return array('friendlist_api', 'friendlist_ui', 'friendlist_views', 'sonybmg_profiles');
}

function friendlist_create_relationship() {
  module_load_include('module', 'friendlist_api');
  module_load_include('module', 'friendlist_ui');
  
  // Create a new relationship type for 'buddy'.
  $buddy_terms = _friendlist_buddylist_translation();
  $name = $buddy_terms['@buddy'];
  $plural = $buddy_terms['@buddies'];

  // This is a two-way, active relationship.
  $rtid = friendlist_api_relation_type_add($name, $plural, TRUE, TRUE);
  variable_set('sonybmg_friendlist_buddy_rtid', $rtid->rtid);
  
  // Create some permissions
  install_add_permissions(DRUPAL_AUTHENTICATED_RID, array('have relationships with friendlist'));

  // Disable the Friendlist default views (TRUE is disabled).
  $views_status = variable_get('views_defaults', array());
  $views_status['friendlist_manage_oneway'] = TRUE;
  $views_status['friendlist_manage_twoway'] = TRUE;
  $views_status['friendlist_public_oneway'] = TRUE;
  $views_status['friendlist_public_twoway'] = TRUE;
  variable_set('views_defaults', $views_status);
}

/**
 * Returns an array of common translation placeholders.
 *
 * This function is duplicated from buddylist.module, because buddylist.module
 * cannot currently be enabled due to its incompatibility with 6.x.
 */
function _friendlist_buddylist_translation() {
  $translations = array(
    '@buddy' => t('buddy'),
    '@Buddy' => t('Buddy'),

    '@buddylist' => t('buddylist'),
    '@Buddylist' => t('Buddylist'),

    '@buddies' => t('buddies'),
    '@Buddies' => t('Buddies'),

    '@buddyof' => t('buddy of'),
    '@Buddyof' => t('Buddy of'),
  );
  return variable_get('buddylist_translation', $translations);
}
