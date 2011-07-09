<?php
// $Id: winners.pages.inc,v 1.1.2.1 2010/04/01 19:25:35 andrewlevine Exp $

/**
 * Thanks to Nick Lewis whose guide helped me figure out wizard.inc! And of
 * course Earl for writing wizard.inc
 * http://www.nicklewis.org/using-chaos-tools-form-wizard-build-multistep-forms-drupal-6
 */

/*----- PART I CTOOLS WIZARD IMPLMENTATION ----- */
/**
 * menu callback for the multistep form
 */
function winners_pick_wizard() {
  // required includes for wizard
  ctools_include('wizard');
  ctools_include('object-cache');

  $step = arg(4);
  
  // *** SETUP ARRAY multistep setup ****
 // these are defined in some docs at end of article
  $form_info = array(
    'id' => 'winners_pick_info_form',
    'path' => "admin/user/winners/pick/%step",
    'show trail' => TRUE,
    'show back' => TRUE,
    'show cancel' => true,
    'show return' =>false,
    'next text' => t('Proceed to next step'),
    'finish text' => t('Finalize these winners'),
    'next callback' =>  'winners_pick_info_form_next',
    'finish callback' => 'winners_pick_info_form_finish',
    'return callback' => 'winners_pick_info_form_finish',
    'cancel callback' => 'winners_pick_info_form_cancel',
   // this controls order, as well as form labels
    'order' => array(
      'info' => t('Step 1: Basic Info'),
      'verify_choices' => t('Step 2: Verify Choices'),
    ),
   // here we map a step to a form id.
    'forms' => array(
      // e.g. this for the step at wombat/create
      'info' => array(
        'form id' => 'winners_pick_info_form'
      ),
      'verify_choices' => array(
        'form id' => 'winners_pick_verify_form'
      ),
    ),
  );

  // no matter the step, you will load your values from the callback page
  $data = winners_multistep_get_page_cache(NULL);
  
  // *** SETTING THE FORM UP FOR MULTISTEP *** //
  $form_state = array(
    'cache name' => NULL,
  );
 
  if (!$data) {
    $data = new stdClass();
    // ** set the storage object so its ready for whatever comes next
    ctools_object_cache_set('winners_multistep', $form_state['cache name'], $data);
  }
  if (!isset($step) || !in_array($step, array_keys($form_info['order']))) {
    // default step
    $step = current(array_keys($form_info['order']));
  }
  
  //THIS IS WHERE WILL STORE ALL FORM DATA
  $form_state['winners_multistep'] = $data;

  // and this is the witchcraft that makes it work
  $output = ctools_wizard_multistep_form($form_info, $step, $form_state);
  return $output;
}

function winners_pick_info_form(&$form, &$form_state) {
  $data = &$form_state['winners_multistep'];
  $form['contest'] = array(
    '#type' => 'textfield',
    '#title' => t('Contest'),
    '#description' => t('If you do not select a contest from the drop-down, one will be automatically created for you.'),
    '#maxlength' => 60,
    '#autocomplete_path' => 'winners/contests_autocomplete',
    '#default_value' => !empty($data->contest) ? $data->contest : '',
    '#required' => TRUE,
    '#weight' => -1,
  );
  $views = views_get_all_views();
  $options = array();
  foreach ($views as $name => $view) {
    if ($view->tag == "winners chooser") {
      $options[$name] = $view->name;
    }
  }
  $form['winner_view'] = array(
    '#type' => 'select',
    '#title' => t('Winner Choosing View'),
    '#description' => t('The view that will be executed to select the winners of this contest.'),
    '#options' => $options,
    '#default_value' => !empty($data->winner_view) ? $data->winner_view : 'winners_chooser_default',
    '#required' => TRUE,
    '#weight' => 0,
  );
  $form['num_winners'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of Winners'),
    '#description' => t('Number of winners to pick for this contest'),
    '#maxlength' => 10,
    '#size' => 5,
    '#default_value' => !empty($data->num_winners) ? $data->num_winners : '',
    '#required' => TRUE,
    '#weight' => 1,
  );

  $form_state['no buttons'] = TRUE; 
}

function winners_pick_info_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  if (trim($values['contest']) == '') {
    form_set_error('contest', t('Contest names must be non-empty'));
  }
  else if (winners_parse_contest($values['contest']) === FALSE) {
    form_set_error('contest', t('Invalid contest %c entered.', array('%c' => $values['contest'])));
  }

  if (empty($values['num_winners']) || !ctype_digit($values['num_winners'])) {
    form_set_error('num_winners');
  }
}

function winners_pick_info_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  foreach(array('contest', 'winner_view', 'num_winners') as $property) {
    $form_state['winners_multistep']->$property = trim($values[$property]);
  }

  $contest = winners_parse_contest($form_state['winners_multistep']->contest);
  if ($contest === TRUE) {
    // We need to create the contest
    $new = new StdClass();
    $new->name = $form_state['winners_multistep']->contest;
    $new->last_picked = 0;
    drupal_write_record('winners_contests', $new);
    $contest = winners_parse_contest("{$new->name} [cid:{$new->contest_id}]");
  }
  $form_state['winners_multistep']->contest_name = $contest->name;
  $form_state['winners_multistep']->contest_id = $contest->contest_id;

  // Actually pick winners
  $view = views_get_view($values['winner_view']);
  $view->init_display();
  $view->display_handler->set_option('items_per_page', $values['num_winners']);
  $view->display_handler->set_option('offset', 0);
  $view->preview('default');

  $uids = array();
  if (empty($view->result) || !is_array($view->result)) {
    return $items;
  }
  foreach ($view->result as $i => $row) {
    $uids[] = $row->uid;
  }
  $form_state['winners_multistep']->winners = $uids;

  if(count($form_state['winners_multistep']->winners) != $form_state['winners_multistep']->num_winners) {
    drupal_set_message(t('Please note that although you requested %req winners, only %rec winners could be selected by your winner choosing view.', array('%req' => $form_state['winners_multistep']->num_winners, '%rec' => count($form_state['winners_multistep']->winners))), 'warning');
  }
}

function winners_pick_verify_form(&$form, &$form_state) {
  $form['verify_message'] = array(
    '#value' => '<h3>' .t('Please verify that the following contest action is correct:') . '</h3>',
  );
  
  $winners = array();
  foreach ($form_state['winners_multistep']->winners as $uid) {
    $winners[$uid] = user_load(array('uid' => $uid));
  }
  
  $form['info'] = array(
    '#value' => theme('winners_pick_verify',
      $form_state['winners_multistep']->contest_id,
      $form_state['winners_multistep']->contest_name,
      $form_state['winners_multistep']->winner_view,
      $form_state['winners_multistep']->num_winners,
      $winners
    ),
  );
}

function theme_winners_pick_verify($contest_id, $contest_name, $view_name, $num_winners, $winners) {
  $header = array();
  $rows = array(
    array(
      t('Contest'),
      $contest_name . ' (ID: ' . $contest_id  . ')',
    ),
    array(
      t('Winner Choosing View'),
      module_exists('views_ui') ?
        t("!link (Note: Editing and saving the view at this point won't affect the winners unless you cancel and start again.", array('!link' => l($view_name, 'admin/build/views/edit/' . $view_name)))
        : $view_name,
    ),
    array(
      t('Number of Winners'),
      t("@rec (@req requested)", array('@rec' => count($winners), '@req' => $num_winners)),
    ),
  );
  $winners_list = '<ul>';
  foreach ($winners as $winner) {
    $winners_list .= "<li>" . theme('username', $winner) . "</li>\n";
  }
  $winners_list .= '</ul>';
  $rows[] = array (
    t('Winners'),
    $winners_list
  );
  return theme('table', $header, $rows);
}

function winners_parse_contest($value) {
  preg_match('/^(?:\s*|(.*) )?\[\s*cid\s*:\s*(\d+)\s*\]$/', $value, $matches);
  if (!empty($matches)) {
    // Explicit [cid:n].
    list(, $title, $cid) = $matches;
    $result = db_fetch_object(db_query("SELECT contest_id, name FROM {winners_contests} WHERE contest_id=%d", $cid));
    if (!result) {
      return FALSE;
    }
    return $result;
  }
  else {
    return TRUE;
  }
  return FALSE;
}

function winners_contests_autocomplete($name) {
  $num_choices = variable_get('winners_contests_num_autocomplete', 5);
  $result = db_query_range("SELECT contest_id, name FROM {winners_contests} WHERE name LIKE '%s%%'", $name, 0, $num_choices);
  $choices = array();
  while ($row = db_fetch_object($result)) {
    $choices["$row->name [cid:{$row->contest_id}]"] = $row->name;
  }
  print drupal_to_js($choices);
  exit;
}

/*----PART 3  FORM BUTTON CALLBACKS   ---------------------- */

/**
 * Callback generated when the multistep form is complete
 * this is where you'd normally save. in this case, drupal_set_message just squaks something
 */
function winners_pick_info_form_finish(&$form_state) {
  drupal_set_message(t('@cnt winners picked for %name!', array('@cnt' => count($form_state['winners_multistep']->winners), '%name' => $form_state['winners_multistep']->contest_name)));
  $time_picked = time();
  foreach ($form_state['winners_multistep']->winners as $uid) {
    $winner = new StdClass();
    $winner->contest_id = $form_state['winners_multistep']->contest_id;
    $winner->uid = $uid;
    $winner->picked = $time_picked;
    drupal_write_record('winners', $winner);
  }

  // Update last picked time
  $contest = new StdClass();
  $contest->last_picked = $time_picked;
  $contest->contest_id = $winner->contest_id;
  drupal_write_record('winners_contests', $contest, 'contest_id');

  // Clear the cache
  winners_multistep_clear_page_cache($form_state['cache name']);
  $form_state['redirect'] = 'admin/user/winners';
}

/**
 * Callback for the proceed step
 *
 */
function winners_pick_info_form_next(&$form_state) {
  // get wombat
  $data = &$form_state['winners_multistep'];
  // set wombat in cache... pretty simple
  $cache = ctools_object_cache_set('winners_multistep', $form_state['cache name'], $data);
}

/**
 * Callback generated when the 'cancel' button is clicked.
 *
 * All we do here is clear the cache.
* redirect them to where they started
* and call them a coward
 */
function winners_pick_info_form_cancel(&$form_state) {
  winners_multistep_clear_page_cache($form_state['cache name']);
  $form_state['redirect'] = 'admin/user/winners';
}

/*----PART 4 CTOOLS FORM STORAGE HANDLERS -- these usually don't have to be very unique  i think some of them are unused.. [ :- ) ]---------------------- */

/**
 * Remove an item from the object cache.
 */
function  winners_multistep_clear_page_cache($name) {
  ctools_object_cache_clear('winners_multistep', $name);
}

/**
 * Get the cached changes to a given task handler.
* (Earl wrote that, not me...)
 */
function winners_multistep_get_page_cache($name) {
  $cache = ctools_object_cache_get('winners_multistep', $name);
  return $cache;
}

function winners_contests_page() {
  $result = db_query("SELECT * FROM {winners_contests} ORDER BY name ASC");
  $contests = array();
  while ($row = db_fetch_object($result)) {
    $contests[$row->contest_id] = $row;
    $contests[$row->contest_id]->num_picked = db_result(db_query('SELECT COUNT(*) FROM {winners} WHERE contest_id=%d', $row->contest_id));
  }
  return theme('winners_contests_page', $contests);
}

function theme_winners_contests_page($contests) {
  $output = '';
  $output .= '<h3>' . t('Contests') . "</h3>\n";
  $header = array(t('Contest Name'), t('Winners'), t('Last Picked'));
  $rows = array();
  foreach ($contests as $contest) {
    $rows[] = array(
      l($contest->name, 'admin/user/winners/contests/' . $contest->contest_id),
      $contest->num_picked,
      format_date($contest->last_picked),
    );
  }
  $output .= theme('table', $header, $rows);
  return $output;
}