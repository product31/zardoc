<?php
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

class sony_connect_connection {

  // Private storage for our db field values.
  private $fields = array();

  // A simple list of the available field names.
  static $field_names = array('uid', 'nuid', 'network', 'updated', 'data', 'preferences');

  // Is this a new record?
  private $new = TRUE;

  // Has any of the data been changed since loaded?
  private $dirty = FALSE;

  //
  private $network;

  /**
   * Default constructor.
   */
  function __construct($uid, $network) {
    // Load the connection.
    $this->load($uid, $network);

    // Load the network plugin.
    $this->network = sony_connect_get_network($network);
  }

  /**
   * Load a connection object from the database.
   *
   * @param $uid
   *   The user id associated with the connection to be loaded.
   * @param $network Load
   *   The network of the connection to be loaded.
   */
  public function load($uid, $network) {
    $row = db_fetch_array(db_query('SELECT * FROM {sony_connect} WHERE uid = %d AND network = "%s"', $uid, $network));
    if (!empty($row)) {
      // Unserialize the serialized fields.
      $row['data'] = unserialize($row['data']);
      $row['preferences'] = unserialize($row['preferences']);

      // Save the fields in the object.
      $this->fields = $row;

      // Mark this as not new.
      $this->new = FALSE;
      $this->dirty = FALSE;
    }
  }

  /**
   * Save the current connection to the database.
   */
  public function save() {
    if (!empty($this->fields)) {

      //dvm($fields, 'fields');
      drupal_write_record('sony_connect', $this->fields, $this->new ? array() : array('uid', 'nuid', 'network'));
      $this->dirty = FALSE;
    }
  }

  /**
   * Delete the current connection from the database.
   */
  public function delete() {
    if (!empty($this->fields)) {
      db_query('DELETE FROM {sony_connect} WHERE uid = %d AND nuid = "%s" AND network = "%s"',
        $this->fields['uid'], $this->fields['nuid'], $this->fields['network']);
    }
  }

  /**
   * __set magic method. Set fields in $this->fields.
   */
  public function __set($name, $value) {
    if (in_array($name, self::$field_names) && ($value != $this->fields[$name])) {
      $this->fields[$name] = $value;
      $this->dirty = TRUE;
    }
  }

  /**
   * __get magic method. Get fields from $this->fields.
   */
  public function __get($name) {
    if (array_key_exists($name, $this->fields)) {
      //dvm($this->fields[$name], $name);
      return $this->fields[$name];
    }
    // dsm('undefined property', $name);
    return null;
  }

  /**
   * __isset magic method. Test if fields in $this->fields are set.
   */
  public function __isset($name) {
    return isset($this->fields[$name]);
  }

  /**
   * __unset magic method. Unset fields in $this->fields.
   */
  public function __unset($name) {
    unset($this->fields[$name]);
  }

  /**
   * Set a preference.
   */
  public function set_preference($type, $subtype, $value) {
    $preferences = $this->preferences;
    if (!isset($preferences) || !is_array($preferences)) {
      $preferences = array();
    }
    if (!isset($preferences[$type])) {
      $preferences[$type] = array();
    }
    $preferences[$type][$subtype] = $value;
    $this->preferences = $preferences;
    $this->save();
  }

  /**
   * Get a preference.
   */
  public function get_preference($type, $subtype) {
    if (isset($this->preferences[$type][$subtype])) {
      return $this->preferences[$type][$subtype];
    }

    // This becomes the default for all users.
    return SONY_CONNECT_PREFERENCES_PROMPT_YES;
  }

  /**
   * Is this network publishable for the
   * @param <type> $type
   * @param <type> $subtype
   * @return boolean
   */
  public function publishable($type, $subtype) {
    $value = $this->get_preference($type, $subtype);
    //dvm($value, $type .':'. $subtype);
    if (($value == SONY_CONNECT_PREFERENCES_ENABLED)
      || ($value == SONY_CONNECT_PREFERENCES_PROMPT_YES)) {
      return TRUE;
    }
    return FALSE;
  }

  /**
   *
   */
  public function publish($type, $subtype, $message) {
    if ($this->publishable($type, $subtype)) {
      $account = user_load(array('uid' => $this->uid));
      $this->network->publish($account, $message, $type, $subtype, $object);
    }
    else {
      return FALSE;
    }
  }

}