<?php
// $Id: 

/**
 * @file
 * Views handler tweet widget.
 *
 * This is a fake field that does not query anything. 
 */

/**
 * Field handler to provie the twitter widget
 * Inherit from views_handler_field_node so we get the nid for free
 * @ingroup views_field_handlers
 */
class tweet_handler_field_tweet extends views_handler_field_node {

  /**
   * query() override to not query this fake field.
   */
  function query(){
    $this->ensure_my_table();
  }

  /**
   * options definitions and their default values
   */
  function option_definition(){
    $options = parent::option_definition();
    
    $options['tweet_button'] = array('default' => 'vertical' );
    $options['tweet_tweet_text'] = array('default' => '' );
    $options['tweet_tweet_url'] = array('default' => '' );
    $options['tweet_language'] = array('default' => '' );
    $options['tweet_account'] = array('default' => '');
    $options['tweet_rel_account_name'] = array('default' => '');
    $options['tweet_rel_account_description'] = array('default' => '');
    return $options;
  }

  /**
   * the tweet button options form
   */
  function options_form(&$form, &$form_state){
    parent::options_form($form, $form_state);
    
    module_load_include('inc', 'tweet', 'tweet.admin');
    $button_elements = tweet_button_settings_form();
    foreach ($button_elements as $key => $value) {
      $form[$key] = $value;
      $form[$key]['#default_value'] = $this->options[$key];
    }
    $follow_elements = tweet_follow_settings_form();
    foreach ($follow_elements as $key => $value) {
      $form[$key] = $value;
      $form[$key]['#default_value'] = $this->options[$key];
    }
    
    // Remove irrelevant controls / settings.
    unset($form['exclude']);
    unset($form['empty']);
    unset($form['empty_zero']);
    unset($form['hide_empty']);
    unset($form['link_to_node']);
    unset($form['alter']);
  }

  /**
   * Render the tweet field
   */
  function render($values){
    
    $tokens = tweet_token_replacement($values->nid);
    $node_url    = isset($tokens['!node_url'])? $tokens['!node_url']: '';
    $attrs = array(
        'data-count' => $this->options['tweet_button'],
        'data-via' => $this->options['tweet_account'],
        'data-related' => $this->options['tweet_rel_account_name'].':'.$this->options['tweet_rel_account_description'],
        'data-text' => strtr($this->options['tweet_tweet_text'], $tokens),
        'data-url' => $this->options['tweet_tweet_url'] ? $this->options['tweet_tweet_url'] : $node_url,
        'data-lang' => $this->options['tweet_language'],
    );
    
    $attrs = drupal_attributes($attrs);
    
    return '<div class="tweet"><a href="http://twitter.com/share" class="twitter-share-button" ' . $attrs . '>Tweet</a></div>';
  
  }
}


