<?php
// $Id$
/**
 * @file
 * Page callbacks for the language section of the sony_global module.
 */

/**
 * A list of known languages used in the sony multisite global platform.
 *
 * @param $langcode (optional)
 * @return
 *   If $langcode is provided, return info about that language.  Otherwise
 *   returns an array of all known languages.
 */
function sony_global_known_languages($langcode = NULL) {
  static $custom_languages;
  if (!isset($custom_languages)) {
    $custom_languages = parse_ini_file(drupal_get_path('module', 'sony_global') .'/countries.ini', TRUE);
  }

  if ($langcode) {
    return $custom_languages[$langcode];
  }

  return $custom_languages;
}

/**
 * Install one of the known languages.
 *
 * @param $langcode
 */
function sony_global_known_language_install($langcode) {
  $installed_languages = language_list();

  $custom_language = sony_global_known_languages($langcode);
  $name = $custom_language['name'];
  $native = isset($custom_language['native']) ? $custom_language['native'] : $name;
  $direction = isset($custom_language['direction']) ? $custom_language['direction'] : LANGUAGE_LTR;
  $prefix = $custom_language['prefix'];

  if (!isset($installed_languages[$langcode])) {
    locale_inc_callback('locale_add_language', $langcode, $name, $native, $direction, NULL, $prefix, FALSE, FALSE);
    drupal_set_message(t('Installed language: %language', array('%language' => $name)));

    // install geoip-language mappings for this language
    $mappings = geoip_language_mappings();
    if (isset($custom_language['geoip'])) {
      foreach ($custom_language['geoip'] as $country) {
        if (!isset($mappings[$country])) {
          geoip_language_mapping_create($country, $langcode);
          drupal_set_message(t('Installed GeoIP Language mapping for %country -> %langcode', array('%country' => $country, '%langcode' => $langcode)));
        }
        else {
          drupal_set_message(t('Skipped GeoIP Language mapping for %country -> %langcode because it is already enabled for %other_country',
            array('%country' => $country, '%langcode' => $langcode, '%other_country' => $mappings[$country])));
        }
      }
    }
  }

  sony_global_language_variables_update();
}

/**
 * Update currently installed langauges to match the info provided by
 * sony_global_known_languages().
 */
function sony_global_update_languages() {
  $custom_languages = sony_global_known_languages();
  $installed_languages = language_list();

  foreach ($custom_languages as $langcode => $custom_language) {
    //extract($custom_language);
    $name = $custom_language['name'];
    $native = isset($custom_language['native']) ? $custom_language['native'] : $name;
    $direction = isset($custom_language['direction']) ? $custom_language['direction'] : LANGUAGE_LTR;
    $prefix = $custom_language['prefix'];

    if (isset($installed_languages[$langcode])) {
      db_query("UPDATE {languages} SET name = '%s', native = '%s', prefix = '%s', direction = %d WHERE language = '%s'", $name, $native, $prefix, $direction, $langcode);
      drupal_set_message(t('Updated language: %language', array('%language' => $name)));
    }
  }

  // set en (US) weight to -1.
  db_query("UPDATE {languages} SET weight = -1 WHERE language = 'en'");

  // Clear locale cache.
  locale_inc_callback('_locale_invalidate_js');
  cache_clear_all('locale:', 'cache', TRUE);

  return;
}

/**
 * Languages list, with enabled and weight elements.
 */
function sony_global_languages_form(&$form_state) {
  $languages = language_list('language', TRUE);

  $form['languages']['#tree'] = 1;

  foreach ($languages as $langcode => $language) {
    $form['languages'][$langcode]['#language'] = $language;
    $form['languages'][$langcode]['enabled'] = array(
      '#type' => 'checkbox',
      '#default_value' => $language->enabled,
    );
    $form['languages'][$langcode]['weight'] = array(
      '#type' => 'weight',
      '#delta' => 10,
      '#default_value' => $language->weight,
    );
  }

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save changes'), '#weight' => 10);
  $form['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update languages'),
    '#weight' => 11,
    '#submit' => array('sony_global_update_languages'),
  );

  return $form;
}

/**
 * Theme the languages list as a table and enable draggable weights.
 */
function theme_sony_global_languages_form($form) {
  drupal_add_tabledrag('sony-global-languages', 'order', 'sibling', 'language-weight');

  $headers = array(
    array('data' => t('Enabled'), 'class' => 'checkbox'),
    t('English Name'),
    t('Native Name'),
    t('Prefix'),
    t('Weight'),
    t('Operations'),
  );

  foreach (element_children($form['languages']) as $langcode) {
    $language = $form['languages'][$langcode]['#language'];

    $form['languages'][$langcode]['weight']['#attributes']['class'] = 'language-weight';

    $row = array(
      array('data' => drupal_render($form['languages'][$langcode]['enabled']), 'class' => 'checkbox'),
      sony_global_flag_icon($language) .' '. $language->name,
      $language->native,
      $language->prefix,
      drupal_render($form['languages'][$langcode]['weight']),
      l(t('Re-import translations'), 'admin/global/languages/import/'. $langcode),
    );

    $rows[] = array(
      'data' => $row,
      'class' => 'draggable',
    );
  }

  $output = theme('table', $headers, $rows, array('id' => 'sony-global-languages'));
  $output .= drupal_render($form);

  return $output;
}

/**
 * Update enabled and weights for languages
 */
function sony_global_languages_form_submit($form, &$form_state) {
  foreach ($form_state['values']['languages'] as $langcode => $values) {
    db_query("UPDATE {languages} SET weight = %d, enabled = %d WHERE language = '%s'", $values['weight'], $values['enabled'], $langcode);
  }

  sony_global_language_variables_update();
}

/**
 * Add a known language/country
 */
function sony_global_language_add(&$form_state) {
  $installed_languages = language_list();

  $options = array();
  foreach (sony_global_known_languages() as $langcode => $language) {
    if (!isset($installed_languages[$langcode])) {
      $options[$langcode] = $language['name'];
    }
  }

  $form = array();

  $form['langcode'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#default_value' => key($options),
    '#options' => $options,
    '#required' => TRUE,
    '#description' => t('Select the desired language and click the <em>Add language</em> button. (Use the <em>Custom language</em> options if your desired language does not appear in this list.)'),
  );

  $form['submit'] = array('#type' => 'submit', '#value' => t('Add language'));
  return $form;
}

/**
 * Submit handler for sony_global_language_add().
 */
function sony_global_language_add_submit($form, &$form_state) {
  $langcode = $form_state['values']['langcode'];
  sony_global_known_language_install($langcode);

  $language = sony_global_known_languages($langcode);
  if (!isset($language['base'])) {
    $language['base'] = drupal_substr($langcode, 0, 2);
  }

  if ($batch = _sony_global_locale_batch_by_language($langcode)) {
    batch_set($batch);
  }

  $form_state['redirect'] = 'admin/global/languages';
}

/**
 * Menu callback for admin/global/languages/import/%
 */
function sony_global_languages_import_translations($langcode = NULL) {
  if (!isset($langcode)) {
    $languages = locale_language_list('name', TRUE);
    $all_batch = array();
    foreach ($languages as $langcode => $name) {
      if ($batch = _sony_global_locale_batch_by_language($langcode)) {
        if (empty($all_batch)) {
          $all_batch = $batch;
        }
        else {
          $all_batch['operations'] = array_merge(array_values($all_batch['operations']), array_values($batch['operations']));
        }
      }
    }
    if (!empty($all_batch)) {
      batch_set($all_batch);
      batch_process('admin/global/languages');
      return;
    }
  }
  if ($batch = _sony_global_locale_batch_by_language($langcode)) {
    batch_set($batch);
    batch_process('admin/global/languages');
    return;
  }

  drupal_set_message(t('No translation files found'));
  drupal_goto('admin/global/languages');
}

/**
 * Replacement for locale_batch_by_language().  Builds a batch to import po
 * files for the given language code and the base language.
 */
function _sony_global_locale_batch_by_language($langcode) {
  include_once('includes/locale.inc');
  $language = sony_global_known_languages($langcode);
  if (!isset($language['base'])) {
    $language['base'] = drupal_substr($langcode, 0, 2);
  }

  // See if we have language files to import for the newly added
  // language, collect and import them.  Translations will be added using the
  // LOCALE_IMPORT_KEEP mode, so make sure the specific translations go in
  // first, followed by the base language translations.
  $batch_spec = locale_batch_by_language($langcode, '_sony_global_locale_batch_language_finished');
  $batch_base = locale_batch_by_language($language['base'], '_sony_global_locale_batch_language_finished');
  if ($batch_spec && $batch_base) {
    $batch = $batch_spec;
    $batch['operations'] = array_merge(array_values($batch_spec['operations']), array_values($batch_base['operations']));
  }
  elseif ($batch_spec) {
    $batch = $batch_spec;
  }
  elseif ($batch_base) {
    $batch = $batch_base;
  }

  if (isset($batch)) {
    foreach ($batch['operations'] as $i => $op) {
      if ($op[0] == '_locale_batch_import') {
        $batch['operations'][$i][0] = '_sony_global_locale_batch_import';
        $batch['operations'][$i][1][] = $langcode;
        $batch['file'] = drupal_get_path('module', 'sony_global') .'/sony_global.languages.inc';
      }
    }
    return $batch;
  }

  return FALSE;
}

/**
 * Replacement for _locale_batch_language_finished().
 */
function _sony_global_locale_batch_language_finished($success, $results) {
  $languages = sony_global_known_languages();
  if ($success) {
    foreach ($results as $langcode => $files) {
      drupal_set_message($languages[$langcode]['name'] .': '. format_plural(count($files), 'One translation file imported for the enabled modules.', '@count translation files imported for the enabled modules.'));
    }
  }
}

/**
 * Replacement for _locale_batch_import().  Adds $langcode so that translation
 * files for one language can be applied to derivative languages.  Example:
 * de.po can be used for languages de-DE and de-AT.
 */
function _sony_global_locale_batch_import($filepath, $langcode, &$context) {
  include_once('includes/locale.inc');
  $file = (object) array('filename' => basename($filepath), 'filepath' => $filepath);
  _locale_import_read_po('db-store', $file, LOCALE_IMPORT_KEEP, $langcode);
  $context['results'][$langcode][] = $filepath;
}

/**
 * Make sure certain language variables get set
 */
function sony_global_language_variables_update() {
  // reset the language_count variables
  $languages = language_list('enabled', TRUE);
  $enabled = $languages[1];
  variable_set('language_count', count($enabled));

  // make sure language_default gets set, otherwise some other stuff doesnt happen
  variable_set('language_default', $enabled['en']);
}

function sony_global_languages_available() {
  $known = sony_global_known_languages();
  $installed = language_list();

  $countries = array();
  foreach ($known as $key => $language) {
    $country_code = drupal_substr($key, -2);
    $countries[$country_code][$key] = $language;
  }

  $rows = array();
  foreach ($countries as $country_code => $languages) {
    $rows[$country_code] = array();
    foreach ($languages as $lang_code => $language) {
      if (!count($rows[$country_code])) {
        $rows[$country_code][] = sony_global_flag_icon($lang_code);
      }
      $rows[$country_code][] = $language['native'] .' ['. $lang_code .']';
    }
    for ($i = count($rows[$country_code]); $i < 4; $i++) {
      $rows[$country_code][] = '';
    }
  }

  $header = array(
    t('Flag'),
    t('Primary'),
    t('Secondary'),
    t('Tertiary'),
  );

  return theme('table', $header, $rows);
}

/**
 * Page callback for i10n population.
 */
function sony_global_menu_populate($item) {
  // Language nuetral menu items can't be populated to other languages.
  if (!isset($item['localized_options']['langcode'])) {
    drupal_access_denied();
    return;
  }

  return drupal_get_form('sony_global_menu_populate_confirm', $item);
}

/**
 * i10n population confirmation form builder.
 */
function sony_global_menu_populate_confirm(&$form_state, $item) {
  $form['#item'] = $item;
  return confirm_form($form,
    t('Are you sure you want to populate the custom menu item %item to all languages?', array('%item' => $item['link_title'])),
    'admin/build/menu-customize/'. $item['menu_name'],
    t('This action will create a copy of this menu item for each language on the system. It can not update previously copied items so you will need to manage any duplication manually using the menu administration page.')
  );
}

/**
 * Submit callback for i10n population form.
 */
function sony_global_menu_populate_confirm_submit($form, &$form_state) {
  $item = $form['#item'];

  // Get a list of enabled languages, minus the language of our menu item.
  $languages = language_list('language', TRUE);
  unset($languages[$item['localized_options']['langcode']]);
  foreach ($languages as $language) {
    // Build a new menu item with each language and then save it.
    $new_item = $item;
    unset($new_item['mlid']);
    $new_item['options']['langcode'] = $language->language;
    menu_link_save($new_item);
  }

  $t_args = array('%title' => $item['link_title']);
  drupal_set_message(t('The menu item %title has been populated to other languages.', $t_args));
  watchdog('menu', 'i10n populated menu item %title.', $t_args, WATCHDOG_NOTICE);
  $form_state['redirect'] = 'admin/build/menu-customize/'. $item['menu_name'];
}
