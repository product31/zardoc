<?php

// $Id:


/**
 * @file
 * tweet.views.inc
 */

/**
 * Implementation of hook_views_data()
 */
function tweet_views_data(){
  $data = array();

  $data['tweet']['table']['group'] = t('Sony Connect');

  $data['tweet']['table']['join'] = array(
      '#global' => array()
  );

  $data['tweet']['tweet'] = array(
      'group' => t('Sony Connect'),
      'field' => array(
          'title' => t('Twitter Tweet button'),
          'help' => t('Provides the Tweet button as a view field'),
          'handler' => 'tweet_handler_field_tweet'
      )
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers() to register all of the basic handlers
 * views uses.
 */
function tweet_views_handlers(){
  return array(
      'info' => array(
          'path' => drupal_get_path('module', 'tweet') . '/views',
      ),
      'handlers' => array(
          'tweet_handler_field_tweet' => array(
              'parent' => 'views_handler_field_node'
          )
      )
  );
}

