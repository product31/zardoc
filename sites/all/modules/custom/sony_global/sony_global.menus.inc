<?php
// $Id$
/**
 * @file
 * Page callbacks for the menus section of the sony_global module.
 */

/**
 * Indicates that the menu item will be translated by the locale module using
 * the t() function.
 */
define('SONY_GLOBAL_MENU_TRANSLATION_LOCALE', 't');

/**
 * Indicates that the menu item will be translated by the i18nmenu module using
 * the tt() function.
 */
define('SONY_GLOBAL_MENU_TRANSLATION_I18NMENU', 'tt');

/**
 * Indicates that the menu item will not be translated since it has been
 * assigned to a specific language, using the i18nmenu module.
 */
define('SONY_GLOBAL_MENU_TRANSLATION_MENU', 'menu');


/**
 * Menu call back for admin/global/menus
 */
function sony_global_menus_overview() {
  $menus = menu_get_menus();
  // remove navigation
  unset($menus['navigation']);
  unset($menus['devel']);

  foreach (language_list() as $key => $language) {
    $row = array(
      sony_global_flag_icon($language) .' '. $language->name,
    );
    foreach ($menus as $menu_name => $title) {
      $row[] = l($title, 'admin/global/menus/'. $key .'/'. $menu_name);
    }

    $rows[] = $row;
  }

  $header = array(t('Language'), array('data' => t('Translate'), 'colspan' => count($menus)));

  return theme('table', $header, $rows);
}

/**
 * Form builder for admin/global/menus/%
 */
function sony_global_menus_edit(&$form_state, $langcode, $menu_name = 'primary-links') {
  if ($langcode == language_default('language')) {
    drupal_set_message(t('Sorry, no translating the default language.'), 'warning');
    drupal_goto('admin/global/menus');
    exit;
  }

  $languages = language_list();
  $language = $languages[$langcode];

  $menus = menu_get_menus();

  drupal_set_title($language->name .':'. $menus[$menu_name]);

  $form['langcode'] = array(
    '#type' => 'value',
    '#value' => $langcode,
  );

  $tree = menu_tree_all_data($menu_name);

  $form['translations'] = array('#tree' => 1);

  sony_global_menus_edit_recurse($form, $tree);

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save translations'), '#weight' => 10);

  return $form;
}

function sony_global_menus_edit_recurse(&$form, $items, $depth = 0) {
  $langcode = $form['langcode']['#value'];

  // borrowed from i18nmenu_localize_tree().
  foreach ($items as $index => $item) {
    $link = $item['link'];

    // Links with language wont be localized. To change the text, update the
    // menu title.
    if (!empty($link['options']['langcode'])) {
      // skip links for other languages than current
      if ($link['options']['langcode'] != $langcode) {
        continue;
      }
      $method = SONY_GLOBAL_MENU_TRANSLATION_MENU;
      $title = $link['title'];
    }
    else {
      $router = i18nmenu_get_router($link['router_path']);
      // If the title is not the same it will be localized by the i18nmenu
      if ($link['link_title'] != $router['title']) {
        $method = SONY_GLOBAL_MENU_TRANSLATION_I18NMENU;
        $title = tt('menu:item:'. $link['mlid'] .':title', $link['link_title'], $langcode, TRUE);
      }
      // If the title is the same it will be localized by the menu system
      else {
        $method = SONY_GLOBAL_MENU_TRANSLATION_LOCALE;
        $title = t($link['title'], array(), $langcode);
      }
    }

    $form['translations'][$link['mlid']]['depth'] = array(
      '#type' => 'value',
      '#value' => $depth,
    );

    $form['translations'][$link['mlid']]['link'] = array(
      '#type' => 'value',
      '#value' => $link,
    );

    $form['translations'][$link['mlid']]['title'] = array(
      '#type' => 'textfield',
      '#default_value' => $title,
      '#required' => TRUE,
      '#size' => 20,
    );

    $form['translations'][$link['mlid']]['method'] = array(
      '#type' => 'value',
      '#default_value' => $method,
      '#required' => TRUE,
    );
    if ($item['below']) {
      sony_global_menus_edit_recurse($form, $item['below'], $depth + 1);
    }
  }  
}

/**
 * Render the menu editing form as a table
 */
function theme_sony_global_menus_edit($form) {
  $header = array(t('English title'), t('Translated title'), t('Path'), t('Method'), t('Operations'));
  foreach (element_children($form['translations']) as $mlid) {
    $link = $form['translations'][$mlid]['link']['#value'];
    $label = $link['title'];
    if ($link['hidden']) {
      $label .= ' ('. t('disabled') .')';
    }
    $depth = $form['translations'][$mlid]['depth']['#value'];
    if ($depth) {
      $label = str_repeat('<div class="indentation"></div>', $depth) .' '. $label;
    }

    $ops = array();
    if (!empty($link['options']['langcode']) && user_access('administer menu')) {
      $ops[] = l(t('Edit'), 'admin/build/menu/item/'. $mlid .'/edit', array('query' => drupal_get_destination()));
    }

    $rows[] = array(
      $label,
      drupal_render($form['translations'][$mlid]['title']),
      check_plain($link['href']),
      check_plain($form['translations'][$mlid]['method']['#value']),
      join(' ', $ops),
    );
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => t('There are no menu items yet.'), 'colspan' => count($header)));
  }

  $output = theme('table', $header, $rows);

  return $output . drupal_render($form);
}

/**
 * Submit callback for sony_global_menus_edit().
 */
function sony_global_menus_edit_submit($form, &$form_state) {
  $langcode = $form_state['values']['langcode'];

  foreach ($form_state['values']['translations'] as $mlid => $data) {
    // don't bother updating if nothing changed.
    if ($data['title'] == $form['translations'][$mlid]['title']['#default_value']) {
      continue;
    }

    switch ($data['method']) {
      // update for t()
      case SONY_GLOBAL_MENU_TRANSLATION_LOCALE:
        $query = "SELECT s.lid FROM {locales_source} s WHERE s.source = '%s' AND s.textgroup = 'default'";
        $lid = db_result(db_query_range($query, $data['link']['title'], 0, 1));
        _sony_global_update_locale_target($lid, $data['title'], $langcode);
        break;

      // update for tt()
      case SONY_GLOBAL_MENU_TRANSLATION_I18NMENU:
        $context = 'menu:item:'. $mlid .':title';
        $source = i18nstrings_get_source($context);
        _sony_global_update_locale_target($source->lid, $data['title'], $langcode);
        break;

      // update the menu title directly
      case SONY_GLOBAL_MENU_TRANSLATION_MENU:
        $menu_link = menu_link_load($mlid);
        $menu_link['link_title'] = $data['title'];
        menu_link_save($menu_link);
        break;
    }
  }

  // clear the locale cache for this language.
  cache_clear_all('locale:'. $langcode, 'cache');

  // Force JavaScript translation file recreation for this language.
  locale_inc_callback('_locale_invalidate_js', $langcode);

}

/**
 * Update the translation string for a given locale source id, in the given
 * language.  It is the responsibility of the calling function to figure out the
 * required $lid.
 *
 * @param $lid
 *   The locale ID.
 * @param $string
 *   The translated string.
 * @param $langcode
 *   The language code for the updated string.
 */
function _sony_global_update_locale_target($lid, $string, $langcode) {
  $translation = db_result(db_query("SELECT translation FROM {locales_target} WHERE lid = %d AND language = '%s'", $lid, $langcode));
  if (!empty($string)) {
    if (!empty($translation)) {
      db_query("UPDATE {locales_target} SET translation = '%s' WHERE lid = %d AND language = '%s'", $string, $lid, $langcode);
    }
    else {
      db_query("INSERT INTO {locales_target} (lid, translation, language) VALUES (%d, '%s', '%s')", $lid, $string, $langcode);
    }
  }
}