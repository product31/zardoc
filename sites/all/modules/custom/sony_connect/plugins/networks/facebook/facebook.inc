<?php
// $Id$

/**
 * @file
 * description
 */

function sony_connect_facebook_sony_connect_networks() {
  return array(
    'title' => t('Facebook'),
    'js' => array(
      'facebook.js',
    ),
    'icon' => 'icons/connect_white_square.gif',
    'favicon' => 'icons/Connect_white_small_short.gif',
    'settings' => array(
      'authorize' => array(
        'width' => '450',
        'height' => '450',
      ),
    ),
    'network' => 'sony_connect_facebook',
  );
}

/**
 * Get the facebook client object for easy access.
 * @return object
 *   Facebook Api object
 */
function facebook_client() {
  static $fb = NULL;
  if (!$fb instanceof Facebook) {
    if ($plugin = sony_connect_get_network('facebook')) {
      global $user;

      // Include facebook.php
      include_once($plugin['path'] .'/lib/facebook.php');
      $fb = new Facebook($plugin['conf']['api_key'], $plugin['conf']['secret_key']);

      // If the $fb->user is not set, try to reconnect the previous session.
      if (!$fb->user) {
        // Grab the previous connection data.
        $connection = sony_connect_connection_load('facebook');

        // If there is previous connection data, attempt to reconnect the session.
        if ($connection->data) {
          $session = $connection->data;
          $fb->set_user($session['uid'], $session['session_key'], $session['expires']);
        }
      }
    }
  }
  return $fb;
}

function _sony_connect_facebook_fix_json($json) {
  $json = preg_replace('/"uid":([0-9]+)/', '"uid":"$1"', $json);
  return $json;
}

function sony_connect_facebook_auto_config() {
  global $base_url;
  $uri = parse_url($base_url);
  
  $properties = array(
    'application_name' => variable_get('site_name', 'Drupal'),
    'description' => '',
    'contact_email' => 'd2c.connect@sonymusic.com',
    'email' => 'd2c.connect@sonymusic.com',
    'help_url' => 'http://sonymusic.com/',
    'privacy_url' => 'http://sonymusic.com/privacypolicy.html',
    'tos_url' => 'http://sonymusic.com/termsandconditions.html',
    'authorize_url' => $base_url . base_path() . 'connect/facebook/post_authorize',
    'installable' => 0,
    'connect_url' => $base_url,
    'base_domain' => parse_url($base_url, PHP_URL_HOST),
    'desktop' => 0,
    'dev_mode' => 0,
  );
  $fb = facebook_client();
  return $fb->api_client->admin_setAppProperties($properties);
}

class sony_connect_facebook extends sony_connect_network {

  function admin_settings($form_state) {
    $help = theme('advanced_help_topic', 'sony_connect', 'facebook-config');
    $help .= '&nbsp;' . t('Click the help icon to view detailed setup information.');
    $form['_help'] = array('#value' => $help);

    $form['api_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Facebook API key'),
      '#default_value' => $this->plugin['conf']['api_key'],
    );

    $form['secret_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Application secret'),
      '#default_value' => $this->plugin['conf']['secret_key'],
    );

    $form['application_id'] = array(
      '#type' => 'textfield',
      '#title' => t('Application id'),
      '#default_value' => $this->plugin['conf']['application_id'],
    );

    if (!empty($this->plugin['conf']['api_key']) && !empty($this->plugin['conf']['secret_key'])) {
      $form['info'] = array(
        '#type' => 'fieldset',
        '#title' => t('App Info'),
      );
      $fb = facebook_client();
      $period = 2592000; // 30 days
      $today = mktime(0, 0, 0);
      $yesterday = $today - (60 * 60 * 24);
      try {
        $result = $fb->api_client->admin_getMetrics($yesterday, $today, $period, array('active_users'));
        $form['info']['users'] = array(
          '#type' => 'item',
          '#title' => t('Active Users'),
          '#value' => t('%num active users in the 30 day period ending %date', array('%num' => $result[0]['active_users'], '%date' => date('F j, Y', $result[0]['end_time']))),
        );
      }
      catch (FacebookRestClientException $e) {
        $form['info']['#value'] = t('No information available.');
        drupal_set_message('Facebook API Exception: '. $e->getMessage(), 'error');
      }
    }
    
    if (!empty($form_state['post'])) {
      $values = $form_state['post']['sony_connect_network_facebook'];
      if (!empty($values['api_key']) && !empty($values['secret_key'])) {
        if (($values['api_key'] != $this->plugin['conf']['api_key']) || $values['secret_key'] != $this->plugin['conf']['secret_key']) {
          // At this point the plugin is not ready to do the auto config because
          // the keys haven't been saved yet.  Set a flag here to do the auto
          // config when the form reloads.
          $_SESSION['sony_connect_facebook_auto_configure'] = TRUE;
        }
      }
    }
    // Now do the auto-config.
    elseif (!empty($_SESSION['sony_connect_facebook_auto_configure'])) {
      $result = sony_connect_facebook_auto_config();
      if ($result) {
        drupal_set_message('Your Facebook application has been auto-configured.  It may take a couple of minutes for the changes to propagate to all of Facebook\'s servers.');
      }
      else {
        drupal_set_message('Your Facebook application could not be auto-configured.', 'error');
      }
      unset($_SESSION['sony_connect_facebook_auto_configure']);
    }

    return $form;
  }
  
  function user() {
    if (isset($_SESSION['facebook_session']['uid'])) {
      return $_SESSION['facebook_session']['uid'];
    }
    return NULL;
  }

  function post_authorize() {
    $session = _sony_connect_facebook_fix_json($_GET['session']);
    $session = (array)json_decode($session);

    $fb = facebook_client();
    $fb->set_user($session['uid'], $session['session_key'], $session['expires']);

    $_SESSION['facebook_session'] = $session;
    $_SESSION['sony_connect_token_data'] = $session;
    return $session;
  }

  function pre_authorize() {
    unset($_SESSION['facebook_session']);
    $fb = facebook_client();

    $plugin = sony_connect_get_network('facebook');
    $params = array(
      'api_key' => $plugin['conf']['api_key'],
      'fbconnect' => 'true',
      'v' => '1.0',
      'connect_display' => 'popup',
      'return_session' => 'true',
      'next' => url('connect/facebook/post_authorize', array('absolute' => TRUE)),
      'cancel_url' => url('connect/cancel', array('absolute' => TRUE)),
      'req_perms' => join(',', array('publish_stream', 'offline_access')),
    );


    $url = 'http://www.facebook.com/login.php?'. http_build_query($params, NULL, '&');
    drupal_goto($url);
  }

  function get_profile($nuid) {
    $fb = facebook_client();
    $result = $fb->api_client->users_getInfo($nuid, array('first_name', 'last_name', 'name', 'pic', 'pic_big', 'pic_square', 'profile_url', 'status'));

    $profile = array(
      'name'      => $result[0]['name'],
      'firstname' => $result[0]['first_name'],
      'lastname'  => $result[0]['last_name'],
      'picture'   => $result[0]['pic_square'],
      'picture_big' => $result[0]['pic_big'],
    );

    return $profile;
  }

  function publish($account, $message, $type = 'node', $subtype = '', $object = NULL) {
    $token_type = isset($object->token_type) ? $object->token_type : $type;
    $replacements = array(
      $token_type => $object,
      'user' => $account,
    );
    $message = token_replace_multiple($message, $replacements);

    $fb = facebook_client();
    try {
      $fb->api_client->stream_publish($message);
      drupal_set_message('Published to Facebook');
    }
    catch (FacebookRestClientException $e) {
      watchdog('sony_connect', '%code: Error publishing to Facebook.', array('%code' => $e->getCode()));
      drupal_set_message('Error publishing to Facebook');
    }
  }
}
