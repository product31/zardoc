<?php
// $Id$

/**
 * @file
 * Page callbacks for sonybmg.module
 */

/**
 * Redirect the user to the login form for access denied pages
 */
function sonybmg_access_denied() {
  global $user;
  if ($user->uid == 0) {
    drupal_set_message(t('You must log in or <a href="@register_url">create an account</a> to access this page.', array('@register_url' => url('user/register'))));
    header('Location: '. url('user/login', array('query' => drupal_get_destination())));
    exit();
  }
  if ($user->uid && ($path == 'user/login' || $path == 'user/register')) {
    drupal_set_message(t('You are already registered as <a href="@profile_url">@username</a>. Not @username? <a href="@logout_url">Log out</a>.', array('@username' => $user->name, '@profile_url' => url('user'), '@logout_url' => url('logout'))));
    return '<!--Already logged in-->';
  }
}

/**
 * Redirects to the first node in a taxonomy term.
 */
function sonybmg_term_goto($tid = 0) {
  $term = taxonomy_get_term($tid);
  if (!$term) {
    return drupal_not_found();
  }

  if ($term) {
    $query = db_rewrite_sql("SELECT n.nid FROM {node} n INNER JOIN {term_node} t ON n.nid = t.nid WHERE n.status = 1 AND n.moderate = 0 AND t.tid = %d ORDER BY n.created DESC");
    $nid = db_result(db_query_range($query, $term->tid, 0, 1));
    if (is_numeric($nid) ) {
      drupal_goto("node/$nid");
      exit();
    }
  }

  // Figure out what node types the term applies to, then redirect to the create form.
  $voc = taxonomy_vocabulary_load($term->vid);
  $type = key($voc->nodes);
  $type_name = node_get_types('name', $type);
  $type_url_str = str_replace('_', '-', $type); // taken from node_menu().

  if (empty($type) || !node_access('create', $type)) {
    global $user;
    if ($user->uid) {
      drupal_set_message(t('No content was found in the category you selected. Post your own content here!'));
      drupal_goto('node/add');
    }
    else {
      drupal_set_message(t('Be the first to post a %type_name! Login or create a free account to post!', array('%type_name' => $type_name)));
      drupal_goto('user', 'destination=node/add/'. $type_url_str);
    }
  }
  else {
    drupal_set_message(t('Be the first to post a %type_name!', array('%type_name' => $type_name)));
    drupal_goto('node/add/'. $type_url_str);
  }
}

/**
 * Fetch all available footers from the sonymusic domain.
 */
function sonybmg_label_fetch_footers() {
  $result = drupal_http_request('http://www.sonymusic.com/footers/');
  $matches = array();
  preg_match_all('!src="http://www.sony(music|bmg).com/footers/(.*)\.js!', $result->data, $matches);

  foreach ($matches[2] as $text) {
    $title = preg_replace('/[-_]/', ' ', $text);
    $footers[$text] = drupal_ucfirst($title);
  }

  return $footers;
}

/**
 * FAPI callback
 */
function sonybmg_label_admin_settings() {
  $form['sonybmg_label'] = array(
    '#type' => 'select',
    '#title' => t('Record Label'),
    '#options' => array(
      'columbia'     => 'Columbia',
      'epic'         => 'Epic',
      'j'            => 'J/Arista',
      'legacy'       => 'Legacy',
      'masterworks'  => 'Masterworks',
      'myplay'       => 'MyPlay',
      'nashville'    => 'Nashville',
      'rca'          => 'RCA',
      'sonybmglatin' => 'Sony BMG Latin',
      'sonywonder'   => 'Sony Wonder',
      'stratmar'     => 'Strategic Marketing',
      'victor'       => 'Victor',
      'zomba'        => 'Zomba',
    ),
    '#default_value' => variable_get('sonybmg_label', NULL),
    '#description' => t('Select the record label for this artist. This will be used to determine which toolbar is called on each page.'),
  );

  $form['sonybmg_footer'] = array(
    '#type' => 'select',
    '#title' => t('Footer'),
    '#options' => array('custom' => t('Custom footer')) + sonybmg_label_fetch_footers(),
    '#default_value' => variable_get('sonybmg_footer', NULL),
    '#description' => t('Select which label information should be displayed in the footer of each page.'),
  );

  $attributes = array(
    'src' => url('admin/settings/sonybmg_label/preview/'. variable_get('sonybmg_footer', NULL)),
    'id' => 'sonybmg-footer-preview',
    'style' => 'width:100%;height:200px;border:0px;',
  );
  $form['_sonybmg_footer'] = array(
    '#type' => 'item',
    '#title' => t('Footer Preview'),
    '#value' => '<iframe '. drupal_attributes($attributes) .'></iframe>',
  );

  $form['sonybmg_footer_custom'] = array(
    '#type' => 'textarea',
    '#title' => t('Custom footer'),
    '#description' => t('This will only be used if the footer is set to Custom'),
    '#default_value' => variable_get('sonybmg_footer_custom', ''),
  );

  drupal_add_js(drupal_get_path('module', 'sonybmg') .'/sonybmg.admin.js');

  return system_settings_form($form);
}

/**
 * Render the specified footer in plain html, suitable for embedding in an iframe
 */
function sonybmg_label_admin_preview_footer($footer = NULL) {
  print '<html><head>';
  print drupal_get_css();
  print '</head><body>'. theme('sonybmg_footer', $footer) .'</body></html>';
  exit();
}

/**
 * Add one day to all dates (to fix bug introduced by date module
 * D5 -> D6 conversion
 */
function sonybmg_add_day_to_dates_form() {
  $already_ran = variable_get('d5-d6_datefixran', 0);
  if ($already_ran) {
    return array('text' => array(
      '#type' => 'markup',
      '#value' => t("Date fix already ran! Tell a developer to delete the d5-d6_datefixran variable if you really want to run again."),
    ));
  }

  return confirm_form(array(), t("Are you sure you want to add one day to EVERY calendar date node on the site (both from and to dates)?", ''));
}

function sonybmg_add_day_to_dates_form_submit() {
  //mark as ran
  variable_set('d5-d6_datefixran', 1);

  $dates_fixed = 0;
  $result = db_query("SELECT vid, field_date_value, field_date_value2 FROM {content_type_date}");
  while ($row = db_fetch_object($result)) {
    $field_updates = array();
    foreach (array('field_date_value', 'field_date_value2') as $col_name) {
      if ($row->$col_name) {
        $t = strtotime($row->$col_name);
        if ($t !== FALSE) {
          $fixed_t = $t + 86400; //add one day to fix
          $fixed_t = date(DATE_ATOM, $fixed_t);
          //example of DATE_ATOM - 2000-07-01T00:00:00+00:00
          $tz_sep = strpos($fixed_t, '+') ? strpos($fixed_t, '+') : strpos($fixed_t, '-', 10);
          if ($tz_sep) {
            $fixed_t = substr($fixed_t, 0, $tz_sep);
          }
          $field_updates[] = "$col_name = '$fixed_t'";
        }
      }
    }
    if (count($field_updates)) {
      $sql = "UPDATE {content_type_date} SET " . implode(', ', $field_updates) . " WHERE vid=%d";
      db_query($sql, $row->vid);
      $dates_fixed++;
    }
  }
  drupal_set_message(t("@fixed dates fixed.", array('@fixed' => $dates_fixed)));
  return '';
}

/**
 *
 * Set a mobileadmin cookie (which prevents redirect to mobile site)
 * and redirect to the home page
 */
function sonybmg_mobile_admin_cookie() {
  setcookie('MOBILE_ADMIN', '1', time()+60*60*24*30, '/');
  $output = '<html>
  <head>
  <title>Admin Redirect</title>
  <META http-equiv="refresh" content="2;URL=' .
  url('<front>', array('absolute' => TRUE)) . '">
  </head>
  <body>
  You will be redirected to the non-mobile site shortly.
  </body>
  </html>';
  print $output;
  module_invoke_all('exit');
  exit;
}

