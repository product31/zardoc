<?php
// $Id$

/**
 * @file
 * file_description
 */

class Tumblr {
  public $url;
  private $email;
  private $password;
  protected $type;
  protected $user;
  protected $posts;
  protected $blog;

  public function __construct($url, $email = NULL, $password = NULL, $type = NULL) {
    // normalize the url
    $parts = parse_url($url);
    $this->url = $parts['scheme'] .'://'. $parts['host'];

    $this->email = $email;
    $this->password = $password;
    
    $this->type = $type;
  }

  public function validate() {
    return ($xml = $this->read(array(), TRUE)) ? TRUE : FALSE;
  }

  protected function read($options = array(), $private = FALSE) {
    $private = ($private && $this->email && $this->password);
    if (isset($this->type) && $this->type > '') { $options['type'] = $this->type; }
    if ($private) {
      $headers = array('content-type' => 'application/x-www-form-urlencoded');
      $options['email'] = $this->email;
      $options['password'] = $this->password;
      $data = drupal_query_string_encode($options);
      $response = drupal_http_request($this->url .'/api/read', $headers, 'POST', $data);
    }
    else {
      $url = $this->url . '/api/read?'. drupal_query_string_encode($options) . '&' . rand();
      $response = drupal_http_request($url);
    }

    if ($response->code == '200' || $response->redirect_code == '200') {
      $xml = new SimpleXMLElement($response->data);

      // Some basic validation of the xml.
      if ($xml->getName() == 'tumblr') {
        return $xml;
      }
    }

    return FALSE;
  }

  protected function getPosts() {
    $xml = $this->read(array(), TRUE);
    $posts = array();
    foreach ($xml->xpath('//post') as $data) {
      // Add to array
      //$posts[] = new TumblrPost($data);
      $posts[] = TumblrPost::load($data);
    }
    $this->posts = $posts;

    $this->blog = new stdClass();
    $this->blog->name = (string)$xml->tumblelog['name'];
    $this->blog->title = (string)$xml->tumblelog['title'];
    $this->blog->timezone = (string)$xml->tumblelog['timezone'];
    $this->blog->cname = (string)$xml->tumblelog['cname'];
    $this->blog->description = (string)$xml->tumblelog;

    return $posts;
  }

  protected function authenticate() {
    if (!($this->email && $this->password)) {
      dsm('no email or password');
      return FALSE;
    }

    $headers = array('content-type' => 'application/x-www-form-urlencoded');
    $options['email'] = $this->email;
    $options['password'] = $this->password;
    $data = drupal_query_string_encode($options);
    $response = drupal_http_request('http://www.tumblr.com/api/authenticate', $headers, 'POST', $data);

    if ($response->code == '200' || $response->redirect_code == '200') {
      $xml = new SimpleXMLElement($response->data);

      // Some basic validation of the xml.
      if ($xml->getName() == 'tumblr') {
        return $xml;
      }
    }

    return FALSE;
  }

  protected function getUserInfo() {
    $xml = $this->authenticate();
    if (!$xml) {
      return FALSE;
    }

    $info = new stdClass();
    $info->user = new stdClass();
    $info->user->default_post_format = (string)$xml->user['default-post-format'];
    $info->user->can_upload_audio = (string)$xml->user['can-upload-audio'];
    $info->user->can_upload_aiff = (string)$xml->user['can-upload-aiff'];
    $info->user->can_upload_video = (string)$xml->user['can-upload-video'];
    $info->user->vimeo_login_url = (string)$xml->user['vimeo-login-url'];

    $info->user->blogs = array();
    foreach ($xml->xpath('//tumblelog') as $data) {
      $blog = new stdClass();
      $blog->title = (string)$data['title'];
      $blog->primary = ((string)$data['is-primary'] == 'yes');
      $blog->private = ((string)$data['type'] == 'private');
      if ($blog->private) {
        $blog->private_id = (string)$data['private-id'];
      }
      else {
        $blog->name = (string)$data['name'];
        $blog->url = (string)$data['url'];
        $blog->avatar = (string)$data['avatar-url'];
      }
      $info->user->blogs[] = $blog;
    }

    $this->user = $info->user;

    return $info;
  }

  function __get($name) {
    switch ($name) {
      case 'user':
        if (!isset($this->user)) {
          $this->getUserInfo();
        }
        return $this->user;

      case 'posts':
      case 'blog':
        if (!isset($this->$name)) {
          $this->getPosts();
        }
        return $this->$name;

      default:
        return NULL;
    }
  }
}

class TumblrPost {
  public $id;
  public $url;
  public $type;
  public $format;
  public $timestamp;
  public $private;

  public static function load($xml) {
    $type = (string)$xml['type'];
    $class = 'TumblrPost'. ucfirst($type);
    if (class_exists($class)) {
      return new $class($xml);
    }
    return FALSE;
  }

  public function __construct($xml = NULL) {
    if (is_a($xml, 'SimpleXMLElement')) {
      $this->fromXML($xml);
    }
  }

  protected function fromXML($xml) {
    // basic attributes
    $this->id = (int)$xml['id'];
    $this->url = (string)$xml['url'];
    $this->type = (string)$xml['type'];
    $this->format = (string)$xml['format'];
    $this->timestamp = (int)$xml['unix-timestamp'];
    $this->private = ((string)$xml['private'] == 'true');

    $this->tags = array();
    if (isset($xml->tag)) {
      foreach ($xml->tag as $tag) {
        $this->tags[] = (string)$tag;
      }
    }
  }
}

class TumblrPostRegular extends TumblrPost {
  protected function fromXML($xml) {
    // Let the base class handle the common elements.
    parent::fromXML($xml);
    $this->title = (string)$xml->{'regular-title'};
    $this->body = (string)$xml->{'regular-body'};
  }
}

class TumblrPostConversation extends TumblrPost {
  protected function fromXML($xml) {
    // Let the base class handle the common elements.
    parent::fromXML($xml);
    $this->title = (string)$xml->{'conversation-title'};
    $this->conversation = new stdClass();
    $this->conversation->text = (string)$xml->{'conversation-text'};
    $this->conversation->lines = array();
    $this->conversation->names = array();
    foreach ($xml->conversation->line as $line_xml) {
      $line = new stdClass();
      $line->label = (string)$line_xml['label'];
      $line->name = (string)$line_xml['name'];
      $line->text = (string)$line_xml;

      // Add name to array if not there already
      if (!in_array($line->name, $this->conversation->names)) {
        $this->conversation->names[] = $line->name;
      }

      // Add it to the array.
      $this->conversation->lines[] = $line;
    }
  }
}

class TumblrPostLink extends TumblrPost {
  protected function fromXML($xml) {
    // Let the base class handle the common elements.
    parent::fromXML($xml);
    $this->link = new stdClass();
    $this->link->text = (string)$xml->{'link-text'};
    $this->link->url = (string)$xml->{'link-url'};
    $this->link->description = (string)$xml->{'link-description'};
  }
}

class TumblrPostQuote extends TumblrPost {
  protected function fromXML($xml) {
    // Let the base class handle the common elements.
    parent::fromXML($xml);
    $this->quote = new stdClass();
    $this->quote->text = (string)$xml->{'quote-text'};
    $this->quote->source = (string)$xml->{'quote-source'};
  }
}

class TumblrPostPhoto extends TumblrPost {
  protected function fromXML($xml) {
    // Let the base class handle the common elements.
    parent::fromXML($xml);
    $this->photo = new stdClass();
    $this->photo->caption = (string)$xml->{'photo-caption'};
    $this->photo->link = (string)$xml->{'photo-link-url'};
    $this->photo->url = array();
    foreach ($xml->{'photo-url'} as $photo) {
      $this->photo->url[(string)$photo['max-width']] = (string)$photo;
    }
  }
}

class TumblrPostAudio extends TumblrPost {
  protected function fromXML($xml) {
    // Let the base class handle the common elements.
    parent::fromXML($xml);
    $this->audio = new stdClass();
    $this->audio->caption = (string)$xml->{'audio-caption'};
    $this->audio->player = (string)$xml->{'audio-player'};
  }
}

class TumblrPostVideo extends TumblrPost {
  protected function fromXML($xml) {
    // Let the base class handle the common elements.
    parent::fromXML($xml);
    $this->video = new stdClass();
    $this->video->caption = (string)$xml->{'video-caption'};
    $this->video->player = (string)$xml->{'video-player'};
    $this->video->source = (string)$xml->{'video-source'};
  }
}

