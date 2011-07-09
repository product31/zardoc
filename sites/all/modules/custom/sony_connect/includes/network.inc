<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Abstract base class to provide interface common to all network plugins.
 */
class sony_connect_network {
  var $plugin;

  function __construct($plugin) {
    $this->plugin = $plugin;
  }

  function admin_settings() {
    return array();
  }

  function user() {
  }

  function post_authorize() {
  }

  function pre_authorize() {
  }

  function get_profile($nuid) {
  }

  function syndicate($message) {
  }
}
