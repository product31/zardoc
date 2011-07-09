<?php
// $Id$

/**
 * @file
 * description
 */

/**
 * Implementation of hook_PLUGIN_sony_connect_networks().
 */
function sony_connect_twitter_sony_connect_networks() {
  return array(
    'title' => t('Twitter'),
    'js' => array(
      'twitter.js',
    ),
    'icon' => 'icons/sign-in-white-square.gif',
    'favicon' => 'icons/favicon_light.png',
    'settings' => array(
      'authorize' => array(
        'width' => '800',
        'height' => '410',
      ),
    ),
    'network' => 'sony_connect_twitter',
  );
}

class sony_connect_twitter extends sony_connect_network {

  function admin_settings() {
    $form['consumer_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Consumer key'),
      '#default_value' => $this->plugin['conf']['consumer_key'],
    );

    $form['consumer_secret'] = array(
      '#type' => 'textfield',
      '#title' => t('Consumer secret'),
      '#default_value' => $this->plugin['conf']['consumer_secret'],
    );

    return $form;
  }

  function user() {
    if (isset($_SESSION['twitter_auth_token'])) {
      return $_SESSION['twitter_auth_token']['user_id'];
    }
    return NULL;
  }

  function post_authorize() {
    $twitter = twitter_client();
    $token = $twitter->getAccessToken();
    $_SESSION['twitter_auth_token'] = $token;
    $_SESSION['sony_connect_token_data'] = $token;
    return $token;
  }

  function pre_authorize() {
    unset($_SESSION['twitter_auth_token']);
    unset($_SESSION['twitter_request_token']);

    $twitter = twitter_client();
    $token = $twitter->getRequestToken();
    $_SESSION['twitter_request_token'] = $token;
    $url = $twitter->getAuthorizeURL($token);
    drupal_goto($url);
  }

  function get_profile($nuid) {
    $twitter = twitter_client();
    $result = $twitter->oAuthRequest('http://twitter.com/users/show.json', array('user_id' => $nuid), 'GET');
    $result = json_decode($result);

    $profile = array(
      'picture' => $result->profile_image_url,
      'name' => $result->name ? $result->name : $result->screen_name,
    );

    return $profile;
  }

  function publish($account, $message, $type = 'node', $subtype = '', $object = NULL) {
    $twitter = twitter_client();

    $token_type = isset($object->token_type) ? $object->token_type : $type;
    $replacements = array(
      $token_type => $object,
      'user' => $account,
    );
    $message = token_replace_multiple($message, $replacements);

    $result = $twitter->oAuthRequest('http://twitter.com/statuses/update.xml', array('status' => $message), 'POST');
    $parsed = simplexml_load_string($result);

    // dsm($message);
    // TODO: figure out error handling.
    drupal_set_message('Published to Twitter');
  }
}

/**
 * Get the twitter client object for easy access.
 * @return object
 *   twitter Api object
 */
function twitter_client() {
  static $twitter;
  if (!$twitter instanceof TwitterOAuth) {
    if ($plugin = sony_connect_get_network('twitter')) {
      // Include twitter.php
      include_once($plugin['path'] .'/lib/twitterOAuth.php');

      // The appropriate token to use can come from several places.
      // 1. If an auth token is present in the session, use it first.
      if ($token = $_SESSION['twitter_auth_token']) {
        $twitter = new TwitterOAuth($plugin['conf']['consumer_key'], $plugin['conf']['consumer_secret'], $token['oauth_token'], $token['oauth_token_secret']);
      }
      // 2. If a request token is present in the session, use it.  This signifies
      //    that we are in the middle of a request for a full session token.
      elseif ($token = $_SESSION['twitter_request_token']) {
        $twitter = new TwitterOAuth($plugin['conf']['consumer_key'], $plugin['conf']['consumer_secret'], $token['oauth_token'], $token['oauth_token_secret']);
      }
      // Otherwise...
      else {
        // Grab the previous connection data.
        $connection = sony_connect_connection_load('twitter');

        // 3. If a previous connection was found, try to reconnect that persistent connection.
        if ($connection->data) {
          $token = $connection->data;
          $_SESSION['twitter_auth_token'] = $token;
          $twitter = new TwitterOAuth($plugin['conf']['consumer_key'], $plugin['conf']['consumer_secret'], $token['oauth_token'], $token['oauth_token_secret']);
        }
        // 4. And if all else fails, generate a non-session connection.
        else {
          $twitter = new TwitterOAuth($plugin['conf']['consumer_key'], $plugin['conf']['consumer_secret']);
        }
      }
    }
  }
  return $twitter;
}
