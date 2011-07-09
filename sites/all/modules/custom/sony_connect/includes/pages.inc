<?php
// $Id$

/**
 * @file
 * Page callbacks.
 */

/**
 * Redirect callback after logging in through a social network. Login the user
 * if an existing connection has been made.  Otherwise, prompt to create a new
 * account or connect to an existing account.
 */
function sony_connect_connect_redirect($network, $js) {
  $nuid = sony_connect_get_network_user($network['name']);

  // If for some odd reason we can't get the nuid, bail out.
  if (!$nuid) {
    drupal_set_message('nuid could not be determined');
    return MENU_ACCESS_DENIED;
  }

  // Store network info in session for later calls.
  $_SESSION['sony_connect'] = array(
    'network' => $network['name'],
    'nuid' => $nuid,
    'status' => SONY_CONNECT_STATUS_AUTHORIZED,
  );

  global $user;
  $uid = $user->uid;

  // if not logged in, try to find an existing connection.
  if (!$uid) {
    $uid = sony_connect_connected_user_load($network['name'], $nuid);
  }

  // If still no uid, prompt to register.
  if (!$uid) {
    return sony_connect_modal_user_connect($js, 'register');
  }

  // Log in the found user if not aleady logged in.
  if (!user_is_logged_in()) {
    $_SESSION['sony_connect']['status'] = SONY_CONNECT_STATUS_CONNECTED;
    $account = user_load(array('uid' => $uid));
    user_external_login($account);
  }
  // Otherwise, we are connecting an existing account.
  else {
    sony_connect_connect_user($uid, $network['name'], $nuid);
  }

  // Ajax render if using ajax.
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    $commands = array();
    $output = '<div id="sony-connect-registration">'. sony_connect_user_register_help('login-success') .'</div>';
    $commands[] = ctools_modal_command_display(t('Connected'), $output);
    $commands[] = sonybmg_ajax_command_reload();
    ctools_ajax_render($commands);
    return;
  }

  // Otherwise, just go to the home page or destination.
  drupal_goto();
}

function sony_connect_connect_post_authorize($network) {
  $data = sony_connect_network_invoke($network, 'post_authorize');

  // Save this data for later when we connect the user.
  if ($data) {
    $_SESSION['sony_connect_token_data'] = $data;
  }

  print theme('sony_connect_post_authorize');
}

function sony_connect_connect_cancel() {
  print theme('sony_connect_cancel');
}

function sony_connect_connect_pre_authorize($network) {
  sony_connect_network_invoke($network, 'pre_authorize');

  return 'debugging';
}

function sony_connect_user_networks($account) {
  $nets = array();
  $result = db_query('SELECT * FROM {sony_connect} WHERE uid = %d', $account->uid);
  while ($row = db_fetch_object($result)) {
    $nets[$row->network] = sony_connect_load_profile($row->network, $row->nuid);
  }

  $rows = array();
  foreach (sony_connect_get_networks() as $network) {
    $profile = isset($nets[$network['name']]) ? $nets[$network['name']] : array();
    if (isset($profile['picture'])) {
      $img = theme('image', $profile['picture'], '', '', NULL, FALSE);
      $img .= '<h3>'. $profile['name'] .'</h3>';
    }
    else {
      $img = theme('image', $network['path'] .'/'. $network['favicon'], $network['title']);
    }
    $row = array(
      $img,
      $network['title'],
    );
    if ($nets[$network['name']]) {
      $row[] = l(t('Disconnect'), 'user/'. $account->uid .'/networks/'. $network['name'] .'/nojs/disconnect', array('attributes' => array('class' => 'ctools-use-modal', 'rel' => $network['name'])));
    }
    else {
      $row[] = l(t('Connect now'), 'user/'. $account->uid .'/networks/'. $network['name'] .'/connect', array('attributes' => array('class' => 'sony-connect-'. $network['name'], 'rel' => $network['name'])));
    }
    $rows[] = $row;
  }

  $output = theme('table', array(array('data' => t('Network'), 'colspan' => 2), t('Operations')), $rows);
  return $output;
}

function sony_connect_disconnect($account, $network, $js = FALSE) {
  if (!$js) {
    return drupal_get_form('sony_connect_disconnect_confirm', $account, $network);
  }

  ctools_include('modal');
  ctools_include('ajax');

  $form_state = array(
    'ajax' => TRUE,
    'account' => $account,
    'network' => $network,
  );
  $commands = ctools_modal_form_wrapper('sony_connect_disconnect_confirm', $form_state);

  // Empty output signals the form was submitted and passed validation.
  if (empty($commands)) {
    drupal_set_message('Disconnecting...');
    $commands[] = sonybmg_modal_command_messages();
    $commands[] = sonybmg_ajax_command_reload();
  }
  // otherwise, add our specific CSS for the form.
  else {
    $command = sonybmg_ajax_command_load_css(drupal_get_path('module', 'sony_connect') .'/sony_connect.css?'. time());
    array_unshift($commands, $command);
  }


  return ctools_ajax_render($commands);
}

function sony_connect_disconnect_confirm($form_state, $account = NULL, $network = NULL) {
  if (!isset($account)) {
    $account = $form_state['account'];
  }
  if (!isset($network)) {
    $network = $form_state['network'];
  }
  $nuid = sony_connect_get_network_user($network['name']);
  $profile = sony_connect_load_profile($network['name'], $nuid);

  $form = array();
  $form['_picture'] = array(
    '#value' => '<div class="picture">'. theme('image', $profile['picture'], '', '', NULL, FALSE) .'</div>',
  );
  $form['_help'] = array(
    '#value' => '<h2>'. t('Disconnect your %network account?', array('%network' => $network['title'])) .'</h2>',
  );

  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );
  $form['network'] = array(
    '#type' => 'value',
    '#value' => $network['name']
  );

  $form['#prefix'] = '<div id="sony-connect-registration">';
  $form['#suffix'] = '</div>';

  return confirm_form($form,
    t('Disconnect your %network account?', array('%network' => $network['title'])),
    isset($_GET['destination']) ? $_GET['destination'] : 'user/'. $account->uid .'/networks',
    '<p>'. t('This action cannot be undone.') .'</p>',
    t('Disconnect'),
    t('Cancel')
  );
}

function sony_connect_disconnect_confirm_submit($form, &$form_state) {
  sony_connect_disconnect_user($form_state['values']['uid'], $form_state['values']['network']);
  $form_state['redirect'] = 'user/'. $form_state['values']['uid'] .'/networks';
}

/**
 * Customized user registration and login callback for social network
 * connections, supports ajax and non-ajax operation.
 */
function sony_connect_modal_user_connect($js, $type) {
  if ($type == 'register') {
    $form = 'sony_connect_user_register_form';
  }
  elseif ($type == 'login') {
    $form = 'sony_connect_user_login_form';
  }
  else {
    return;
  }

  if (!$js) {
    return drupal_get_form($form);
  }

  ctools_include('modal');
  ctools_include('ajax');

  $form_state = array(
    'ajax' => TRUE,
  );
  $commands = ctools_modal_form_wrapper($form, $form_state);

  // Empty output signals the form was submitted and passed validation.
  if (empty($commands)) {
    global $user;
    $output = '<div id="sony-connect-registration">';
    $output .= sony_connect_user_register_help('register-success');
    $output .= '<p>';
    $output .= l(t('Return to page'), NULL, array('attributes' => array('class' => 'button', 'onclick' => 'location.reload(); return false;')));
    $output .= l(t('Continue to profile'), 'user/'. $user->uid .'/edit', array('attributes' => array('class' => 'button')));
    $output .= '</p>';
    $output .= '</div>';

    $commands[] = ctools_modal_command_display('Registration successful', $output);
    if ($form_state['clicked_button']['#id'] == 'edit-submit-profile') {
      global $user;
      $commands[] = sonybmg_ajax_command_redirect('user/'. $user->uid .'/edit');
    }
  }
  // otherwise, add our specific CSS for the form.
  else {
    $command = sonybmg_ajax_command_load_css(drupal_get_path('module', 'sony_connect') .'/sony_connect.css?'. time());
    array_unshift($commands, $command);
  }

  return ctools_ajax_render($commands);
}

function sony_connect_user_register_help($phase = 'register') {
  $session = $_SESSION['sony_connect'];
  $profile = sony_connect_load_profile($session['network'], $session['nuid']);
  $network = sony_connect_network_load($session['network']);

  $output = '<div class="picture">'. theme('image', $profile['picture'], '', '', NULL, FALSE) .'</div>';
  $output .= '<h2>'. t('Welcome %username', array('%username' => $profile['name'])) .'</h2>';

  switch ($phase) {
    case 'register':
      $output .= '<p>'. t('Registration almost complete... just one more step!') .'</p>';
      $output .= '<p>'. l(t('Already have an account on this site?'), 'connect/nojs/login', array('attributes' => array('class' => 'ctools-use-modal'))) .'</p>';
      break;

    case 'login':
      $output .= '<p>'. t('Registration almost complete... just one more step!') .'</p>';
      $output .= '<p>'. l(t('Don\'t have an account on this site?'), 'connect/nojs/register', array('attributes' => array('class' => 'ctools-use-modal'))) .'</p>';
      break;

    case 'register-success':
      $output .= '<h2>'. t('Registration successful!') .'</h2>';
      $output .= '<p>'. t('Your %network account has been connected. Logging in, please be patient.', array('%network' => $network['title'])) .'</p>';
      break;

    case 'login-success':
      $output .= '<p>'. t('Logging in, please be patient.') .'</p>';
      break;
  }

  return $output;
}

/**
 * Customized user registration form for social network connections.
 */
function sony_connect_user_register_form($form_state) {
  $session = $_SESSION['sony_connect'];
  $profile = sony_connect_load_profile($session['network'], $session['nuid']);

  $form = array();
  $form['_help'] = array('#value' => sony_connect_user_register_help('register'));

  $form['sony_connect'] = array(
    '#type' => 'value',
    '#value' => $session,
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Please pick a username'),
    '#size' => 25,
    '#validation_rules' => array(
      'uniqueUsername' => TRUE,
    ),
    '#required' => TRUE,
  );
  $form['pass'] = array(
    '#type' => 'value',
    '#value' => user_password(),
  );

  if (variable_get('sony_coppa_reac', 0)) {
    $form = sony_coppa_dob_form($form);
  }
  else {
    $form = sony_coppa_u13_form($form);
  }

  if (module_exists('legal')) {
    $legal = module_invoke('legal', 'user', 'register', NULL, NULL);
    $legal['legal']['#type'] = 'markup';
    unset($legal['legal']['#weight']);
    $form += $legal;
  }

  $form['newsletter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Yes, I want to receive the latest news & updates'),
    '#attributes' => array(
      'onchange' => '$("#mail-toggle").toggle($(this).is(":checked"));',
    ),
  );
  $form['mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#prefix' => '<div id="mail-toggle" style="display: none;">',
    '#suffix' => '</div>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Finish'),
    '#weight' => 100,
  );

  $form['#submit'] = array();
  $form['#submit'][] = 'user_register_submit';
  $form['#submit'][] = 'sony_connect_user_login_submit';

  $form['#prefix'] = '<div id="sony-connect-registration">';
  $form['#suffix'] = '</div>';

  return $form;
}

/**
 * Customized user login form for social network connections.
 */
function sony_connect_user_login_form() {
  $session = $_SESSION['sony_connect'];
  $profile = sony_connect_load_profile($session['network'], $session['nuid']);

  $form = array();
  $form['_help'] = array('#value' => sony_connect_user_register_help('login'));

  $form['sony_connect'] = array(
    '#type' => 'value',
    '#value' => $session,
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#required' => TRUE,
    '#size' => 25,
  );
  $form['pass'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#required' => TRUE,
    '#description' => l(t('Forgot password?'), 'user/password'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Sign in'),
    '#weight' => 100,
  );

  $form['submit_profile'] = array(
    '#type' => 'submit',
    '#value' => t('Sign in & Complete your profile'),
    '#weight' => 101,
  );

  $form['#validate'] = user_login_default_validators();

  $form['#submit'] = array();
  $form['#submit'][] = 'user_login_submit';
  $form['#submit'][] = 'sony_connect_user_login_submit';

  $form['#prefix'] = '<div id="sony-connect-registration">';
  $form['#suffix'] = '</div>';

  return $form;
}

/**
 * Form submit callback to handle connecting a user account with a network on
 * login or registration.
 */
function sony_connect_user_login_submit($form, &$form_state) {
  global $user;

  if ($user->uid) {
    $info = $form_state['values']['sony_connect'];

    if (isset($info) && $info['status'] == SONY_CONNECT_STATUS_AUTHORIZED) {
      sony_connect_connect_user($user->uid, $info['network'], $info['nuid']);
    }
  }
}

function sony_connect_user_preferences($form_state, $account) {
  $types = sony_connect_publish_info();
  $networks = sony_connect_get_networks();
  $connected_networks = sony_connect_get_connected_networks($account);

  drupal_add_js(drupal_get_path('module', 'sony_connect') . '/checkbox/jquery.checkbox.min.js');
  drupal_add_js(drupal_get_path('module', 'sony_connect') . '/js/user.js');
  drupal_add_css(drupal_get_path('module', 'sony_connect') . '/sony_connect.css');

  $form = array();
  $form['account'] = array('#type' => 'value', '#value' => $account);
  $form['preferences'] = array('#tree' => 1);

  $duplicates = array(
    'node' => array(
    ),
    'comment' => array(
      'photo' => 'official_photo',
      'track' => 'album',
    ),
  );

  foreach ($types as $type_name => $type) {
    $form['preferences'][$type_name] = array(
      '#tree' => 1,
    );

    foreach ($type['subtypes'] as $subtype_name => $subtype) {
      if ($subtype['enabled']) {
        $form['preferences'][$type_name][$subtype_name] = array(
          '#title' => $subtype['preference'],
        );

        foreach ($networks as $network) {
          $form['preferences'][$type_name][$subtype_name][$network['name']] = array(
            '#type' => 'checkbox',
            '#default_value' => $connected_networks[$network['name']]->preferences[$type_name][$subtype_name],
            '#disabled' => !isset($connected_networks[$network['name']]),
            '#return_value' => SONY_CONNECT_PREFERENCES_ENABLED,
          );
          if (isset($duplicates[$type_name][$subtype_name])) {
            $dupe = $duplicates[$type_name][$subtype_name];
            $form['preferences'][$type_name][$subtype_name][$network['name']]['#type'] = 'hidden';
            $form['preferences'][$type_name][$subtype_name][$network['name']]['#duplicate'] = $dupe;
            unset($form['preferences'][$type_name][$subtype_name]['#title']);
          }
        }
      }
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save my preferences'),
  );
  return $form;
}

function sony_connect_user_preferences_submit($form, &$form_state) {
  // separate by network.
  $preferences = array();
  foreach ($form_state['values']['preferences'] as $type_name => $subtypes) {
    foreach ($subtypes as $subtype_name => $networks) {
      foreach ($networks as $network => $enabled) {
        if ($enabled == SONY_CONNECT_PREFERENCES_ENABLED) {
          $preferences[$network][$type_name][$subtype_name] = SONY_CONNECT_PREFERENCES_ENABLED;
        }
        else {
          $preferences[$network][$type_name][$subtype_name] = SONY_CONNECT_PREFERENCES_DISABLED;
        }
      }
    }
  }

  // duplicate handling
  foreach ($form_state['values']['preferences'] as $type_name => $subtypes) {
    foreach ($subtypes as $subtype_name => $networks) {
      foreach ($networks as $network => $enabled) {
        $form_item = $form['preferences'][$type_name][$subtype_name][$network];
        if ($form_item['#type'] == 'hidden') {
          $dupe = $form_item['#duplicate'];
          $preferences[$network][$type_name][$subtype_name] = $preferences[$network][$type_name][$dupe];
        }
      }
    }
  }

  foreach ($preferences as $network => $network_prefs) {
    $row = array(
      'uid' => $form_state['values']['account']->uid,
      'network' => $network,
      'preferences' => $network_prefs,
    );
    drupal_write_record('sony_connect', $row, array('uid', 'network'));
  }
  drupal_set_message(t('Your sharing preferences have been saved.'));
}

function theme_sony_connect_user_preferences($form) {
  $account = $form['account']['#value'];
  $rows = array();
  $header = array();

  foreach (element_children($form['preferences']) as $type) {
    foreach (element_children($form['preferences'][$type]) as $subtype) {
      if (empty($header)) {
        $header[] = t('Share with my networks');
        $row = array('');
        foreach (element_children($form['preferences'][$type][$subtype]) as $network) {
          $network = sony_connect_get_network($network);
          $header[] = array(
            'data' => theme('image', $network['path'] .'/'. $network['icon'], $network['title']),
            'class' => 'checkbox',
          );
          if (!$form['preferences'][$type][$subtype][$network['name']]['#disabled']) {
            $row[] = array('class' => 'select-all checkbox');
          }
          else {
            $row[] = l(t('Connect'), 'user/'. $account->uid .'/networks/'. $network['name'] .'/connect', array('attributes' => array('class' => 'sony-connect-'. $network['name'], 'rel' => $network['name'])));
          }
        }
        $rows[] = $row;
      }

      if ($form['preferences'][$type][$subtype]['#title']) {
        $row = array(
          $form['preferences'][$type][$subtype]['#title'],
        );
        foreach (element_children($form['preferences'][$type][$subtype]) as $network) {
          $row[] = array(
            'data' => drupal_render($form['preferences'][$type][$subtype][$network]),
            'class' => 'checkbox',
          );
        }
        $rows[] = $row;
      }
    }
  }

  $output = theme('table', $header, $rows);
  $output .= drupal_render($form);
  return $output;
}

function sony_connect_modal_activity_preferences($type, $subtype, $js = FALSE) {
  $form = 'sony_connect_activity_preferences_form';

  if (!$js) {
    return drupal_get_form($form);
  }

  ctools_include('modal');
  ctools_include('ajax');

  $types = sony_connect_publish_info();
  if (!empty($types[$type]['subtypes'][$subtype])) {
    $subtype = $types[$type]['subtypes'][$subtype];
  }

  $title = t('Share this with:');

  $form_state = array(
    'ajax' => TRUE,
    'title' => $title,
    'type' => $type,
    'subtype' => $subtype,
  );
  $commands = ctools_modal_form_wrapper($form, $form_state);

  // Empty output signals the form was submitted and passed validation.
  if (empty($commands)) {
    $commands[] = ctools_modal_command_dismiss();
    $commands[] = sony_connect_command_form_submit('#node-form');
  }
  // otherwise, add our specific CSS for the form.
  else {
    $command = sonybmg_ajax_command_load_css(drupal_get_path('module', 'sony_connect') .'/sony_connect.css?'. time());
    array_unshift($commands, $command);
  }

  return ctools_ajax_render($commands);
}

function sony_connect_activity_preferences_form($form_state) {
  global $user;

  $connections = sony_connect_get_connected_networks($user);
  $networks = sony_connect_get_networks();

  $form['title'] = array(
    '#value' => '<div class="modal-title">'. t('For %plural_title, share with', array('%plural_title' => $form_state['subtype']['title'])) .'</div>',
  );

  $form['networks'] = array(
    '#tree' => TRUE,
    '#prefix' => '<div id="network-preferences">',
    '#suffix' => '</div>',
  );

  $network_options = array();
  foreach ($networks as $network) {
    $enabled = isset($connections[$network['name']]);
    $form['networks'][$network['name']] = array(
      '#type' => 'checkbox',
      //'#title' => $network['title'],
      '#return_value' => $network['name'],
      '#default_value' => $enabled,
      '#disabled' => !$enabled,
    );
  }

  $form['type'] = array(
    '#type' => 'value',
    '#value' => $form_state['type'],
  );

  $form['subtype'] = array(
    '#type' => 'value',
    '#value' => $form_state['subtype']['name'],
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Continue'),
  );

  $form['remember'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remember this choice & don\'t show this message again.'),
  );

  $form['prefs'] = array(
    '#value' => t('Set your <a href="!sharing-url" target="_blank">sharing preferences</a> in your profile.', array('!sharing-url' => url('user/'. $user->uid .'/networks'))),
  );

  $form['#prefix'] = '<div id="sony-connect-activity-preferences-modal">';
  $form['#suffix'] = '</div>';

  return $form;
}

/**
 * Submit handler for activity preferences modal form.
 */
function sony_connect_activity_preferences_form_submit($form, &$form_state) {
  global $user;
  $connections = sony_connect_get_connections($user);

  $values = $form_state['values'];
  $remember = $values['remember'];

  foreach ($values['networks'] as $network => $value) {
    if ($remember) {
      $pref = empty($value) ? SONY_CONNECT_PREFERENCES_DISABLED : SONY_CONNECT_PREFERENCES_ENABLED;
    }
    else {
      $pref = empty($value) ? SONY_CONNECT_PREFERENCES_PROMPT_NO : SONY_CONNECT_PREFERENCES_PROMPT_YES;
    }

    if (isset($connections[$network])) {
      $connections[$network]->set_preference($values['type'], $values['subtype'], $pref);
      //dvm($connections[$network]->preferences);
    }
  }

  if ($remember) {
    drupal_set_message(t('Your sharing preferences have been saved.  You can change them at any time in your <a href="!profile_link">profile</a>.',
      array('!profile_link' => url('user/'. $user->uid .'/networks'))));
  }
}