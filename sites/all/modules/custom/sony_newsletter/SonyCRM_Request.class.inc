<?php
// $Id$

/**
 * @file
 * file_description
 */


class SonyCRM_Request {
  private $base_url;
  private $login;
  private $secret;
  private $email;
  private $time;

  public $response;
  public $error = FALSE;
  public $error_message = '';

  /**
   * Construct a request object.
   *
   * @param $base_url
   *   API end point URL.
   * @param $login
   *   API user name.
   * @param $secret
   *   API secret.
   * @param $email
   *   User's email address.
   *
   * @see sony_newsletter_request_instance()
   */
  function SonyCRM_Request($base_url, $login, $secret, $email) {
    $this->base_url = $base_url;
    $this->login = $login;
    $this->secret = $secret;
    $this->email = $email;
    $this->time = time();
  }

  /**
   * Make a request to SonyCRM.
   *
   * @param $action
   * @param $params
   * @param $method
   *
   * @see http://subs.sonymusic.com/app/pages/client/crm-api/
   */
  function request($action, $params = array(), $method = 'POST') {
    $this->error = FALSE;
    $this->error_message = '';

    $headers = array();

    $params += array(
      'time' => $this->time,
      'email' => $this->email,
      'login' => $this->login,
      'signup_url' => url($_GET['q'], array('absolute' => TRUE)),
    );
    $params['token'] = md5($params['login'] . $this->secret . $params['email'] . $params['time']);

    // The Lyris API has some wierd requirements for POST.
    if ($method == 'POST') {
      $headers['content-type'] = "application/x-www-form-urlencoded";

      // The api needs a query string like list=xxx&list=yyy&list=zzz rather than
      // the normal list[]=xxx&list[]=yyy&list[]=zzz
      $extra = '';
      if (isset($params['list'])) {
        foreach ((array) $params['list'] as $list) {
          $extra .= '&list='. drupal_urlencode($list);
        }
        unset($params['list']);
      }
      // API expects some POST params to be on the query string, not in the
      // body. Encode parameters and append to url.
      $data = drupal_query_string_encode($params) . $extra;
      $url = $this->base_url . $action;
    }
    else {
      $data = NULL;
      $url = url($this->base_url . $action, array('query' => $params, 'external' => TRUE));
    }

    $this->response = drupal_http_request($url, $headers, $method, $data);
    if ($this->response->code >= 300) {
      $this->error = TRUE;
      $this->error_message = $this->response->error;
      $this->result = NULL;
    }
    else {
      // If we got an HTTP error try to parse the xml.
      $this->result = simplexml_load_string($this->response->data);
      if (!$this->result) {
        $this->error = TRUE;
        $this->error_message = t('Invalid XML returned.');
      }
      elseif ((string)$this->result->Status == 'ERROR') {
        $this->error = TRUE;
        // If the error message has child elements maintain the HTML structure
        // otherwise treat it as a string.
        $children = $this->result->ErrorMsg->children();
        if (count($children)) {
          $this->error_message = (string) $children->asXML();
        }
        else {
          $this->error_message = (string) $this->result->ErrorMsg;
        }
      }
    }

    if ($this->error && user_access('administer site configuration')) {
      drupal_set_message(t('A problem occured while executing the %action method on Sony CRM: %error<br>%response', array('%action' => $action, '%error' => $this->error_message, '%response' => $this->response->data)), 'error');
    }

    return !$this->error;
  }

  /**
   * Unsubscribe the user from a list.
   */
  function unsubscribe($list) {
    $params = array('list' => $list);
    if (!$this->request('unsubscribe', $params, 'POST')) {
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Subscribe the user to a list.
   */
  function subscribe($lists, $demographics = array()) {
    $params = array('list' => $lists) + $demographics;
    if (!$this->request('subscribe', $params, 'POST')) {
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Get current subscription statuses for the user.
   */
  function subscriptionStatus() {
    $params = array();
    if (!$this->request('subscriptions', $params, 'GET')) {
      return FALSE;
    }

    $status = array();
    foreach($this->result->Member->Lists->List as $list) {
      $status[(string)$list['code']] = (string)$list->ListName;
    }

    return $status;
  }

  /**
   * Find artists by name.
   *
   * @param $search_text
   *   String to search for.
   * @return
   *   Array of artist names keyed by id.
   */
  function findArtists($search_text) {
    $params = array('email' => $this->login, 'name' => $search_text);
    if (!$this->request('artists', $params, 'GET')) {
      return FALSE;
    }

    $artists = array();
    foreach($this->result->Artists->Artist as $artist) {
      $artists[(string)$artist['id']] = (string)$artist->ArtistName;
    }
    return $artists;
  }

  /**
   * Get the lists for an artist.
   *
   * @param $id
   *   Artist id.
   * @return
   *   Array with two child arrays 'mailing' and 'mobile'.
   */
  function getArtistLists($id) {
    $params = array('email' => $this->login, 'id' => $id);
    if (!$this->request('artistlists', $params, 'GET')) {
      return FALSE;
    }

    $lists = array('mailing' => array(), 'mobile' => array());
    foreach ($this->result->MailingLists->List as $list) {
      $lists['mailing'][(string)$list['code']] = array(
        'description' => (string) $list->ListName,
        'client'      => (string) $list['clientName'],
        'label'       => (string) $list['labelName'],
      );
    }
    foreach ($this->result->MobileLists->List as $list) {
      $lists['mobile'][(string)$list['code']] = array(
        'description' => (string) $list->ListName,
        'partner'     => (string) $list['partnerName'],
      );
    }
    return $lists;
  }
}
