<?php
// $Id: mm.drush.inc,v 1.6 2009/05/24 19:47:00 clemenstolboom Exp $

/**
 * @file
 *   The drush Module Manager
 */

/**
 * Implementation of hook_help().
 */
function mm_drush_help($section) {
  switch ($section) {
    case 'drush:mm list':
      return dt("Usage: drush [options] mm list ... lists a computer readable name of the installed modules.");
    case 'drush:mm enable':
      return dt("Usage: drush [options] mm enable <module_1> <module_2> ... <module_n> is the computer readable name of one of the installed modules.\nAfter enabling, you still have to configure the modules through the modules administration page");
    case 'drush:mm disable':
      return dt("Warning: do not disable required core modules!!!\n\nUsage: drush [options] mm disable <module_1> <module_2> ... <module_n> is the computer readable name of one of the modules to install.");
    case 'drush:mm uninstall':
      return dt("Warning: do not uninstall required core modules!!!\n\nUsage: drush [options] mm uninstall <module_1> <module_2> ... <module_n> is the computer readable name of one of the modules to uninstall.");
    case 'drush:mm dot':
      return dt("Usage: drush [options] mm dot ... generated a graphviz dot file for further processing.\n\n");
  }
}

/**
 * Implementation of hook_drush_command().
 */
function mm_drush_command() {
  $items['mm list'] = array(
    'callback' => 'drush_mm_list_modules',
    'description' => 'Lists the available modules.'
  );

  $items['mm enable'] = array(
    'callback' => 'drush_mm_enable_module',
    'description' => 'Enables (and if necessary installs) the given modules and depend.'
  );

  $items['mm disable'] = array(
    'callback' => 'drush_mm_disable_module',
    'description' => 'Disable the given modules and reverse dependants.'
  );

  $items['mm uninstall'] = array(
    'callback' => 'drush_mm_uninstall_module',
    'description' => 'Uninstalls the given modules and reverse dependants.'
  );

  $items['mm dot'] = array(
    'callback' => 'drush_mm_dot',
    'description' => 'Generates a dot file of all modules.'
  );
  
  return $items;
}

function drush_mm_list_modules($return_list=FALSE) {
  require_once "drush_mm.inc";
  global $_drush_mm_module_info;
  _drush_mm_get_modules_info();
  $result = _drush_mm_list_modules($_drush_mm_module_info, $return_list);
  if ($return_list) return $result;
}

function drush_mm_dot() {
  require_once "drush_mm.inc";
  global $_drush_mm_module_info;
  _drush_mm_get_modules_info();

  _drush_mm_generate_dot($_drush_mm_module_info);
}

/**
 * enables the given modules
 *
 * If all modules are present the are enabled
 */
function drush_mm_enable_module() {
  $modules = func_get_args();
  _drush_mm_endis_module( TRUE, $modules);
}

function drush_mm_uninstall_module() {
  $modules = func_get_args();

  if (empty($modules)) {
    drush_die(dt("No modules specified.\n\nRun drush help mm uninstall for more information."));
  }

  drush_log( dt("First disabling modules ..."));
  call_user_func_array( 'drush_mm_disable_module', $modules);

  drush_log( dt("Now uninstalling modules ..."));

  $enable= FALSE;
  require_once "drush_mm.inc";
  $result= _drush_mm_get_module_list( $modules, $enable);

  foreach ($result as $module) {
    if (!drush_get_context('DRUSH_SIMULATE')) {
      include_once './includes/install.inc';
      drush_log( dt("Uninstalling module $module"));
      drupal_uninstall_module( $module);
    }
  }
  _drush_mm_shake_drupal();
}

function _drush_mm_shake_drupal() {
  if (!drush_get_context('DRUSH_SIMULATE')) {
    drupal_flush_all_caches();
  }
  drush_log('Cleared all caches');
  if (!drush_get_context('DRUSH_SIMULATE')) {
    actions_synchronize();
  }
  drush_log('Actions synchronized');
}

function _drush_mm_endis_module( $enable, $modules) {
  require_once "drush_mm.inc";
  
  if (empty($modules)) {
    if ($enable) {
      drush_die(dt("No modules specified.\n\nRun drush help mm enable for more information."));
    } 
    else {
      drush_die(dt("No modules specified.\n\nRun drush help mm disable for more information."));
    }
  }
  $result=_drush_mm_get_module_list( $modules, $enable);
  $real_status=_drush_mm_get_list_by_status($enable);
  if ($enable) {
    drush_log(dt("Enabling modules: '!modules'" , array( "!modules" => implode( ", ", $result))));
    //module_enable( $result);
    include_once './includes/install.inc';
    foreach ($result as $module) {
      if (isset($real_status[$module])) {
        drush_print( "Skipping $module ... already enabled");
      }
      else {
        drush_log( dt("Enabling (and maybe installing) module: $module"), 2);
        if (!drush_get_context('DRUSH_SIMULATE')) {
          // only FRESH installed modules gets enabled
          drupal_install_modules( array($module));
          // enable for sure
          // TODO: this will not solve the 'failed install' scenario
          module_enable( array($module));
          if (module_exists('adminrole')) { 
            drush_log( dt('Found module adminrole'));
            // We eval this to prevent error output like t() function does not exists
            eval(adminrole_update_perms());
            drush_log( dt('Admin Permissions Set'));
          }
        }
      }
    }
  } 
  else {
    drush_log(dt("Disabling modules: '!modules'" , array( "!modules" => implode( ", ", $result))));
    foreach ($result as $module) {
      if (isset($real_status[$module])) {
        drush_print( "Skipping $module ... already disabled");
      }
      else {
        drush_log( dt("Disabling module: $module"), 2);
        if (!drush_get_context('DRUSH_SIMULATE')) {
          module_disable( array($module));
        }
      }
    }
  }
  if (!drush_get_context('DRUSH_SIMULATE')) {
    _drush_mm_shake_drupal();
    //check for the status versus the requested status
    $real_status=_drush_mm_get_list_by_status($enable);
    $diff=array_diff($result, array_keys($real_status));
    if (!count($diff)==0) {
      drush_die(dt("Not all modules are @s", array('@s' => $enabled?dt("enabled"):dt("disabled"))));
    }
    $display_list= array_intersect_key($real_status, array_flip($result));
    drush_log(
      dt("All modules '@modules' are @s", 
        array(
          "@modules" => implode( ", ", $display_list), 
          '@s' => $enable?dt("enabled"):dt("disabled"),
        )
      )
    );
    if (!drush_get_context('DRUSH_VERBOSE')) {
      drush_print(
        dt("All modules '@modules' are @s",
          array(
            "@modules" => implode( ", ", $result),
            '@s' => $enable?dt("enabled"):dt("disabled"),
          )
        )
      );
    }
  }
  else {
    drush_print(dt("Nothing done."));
  }
}

function _drush_mm_get_list_by_status($enable) {
  $result=array();
  $list=drush_mm_list_modules(TRUE);
  if ($enable) {
    $list=$list[1];
  }
  else {
    $list=$list[0];
  }
  foreach ($list as $index => $value) {
    // prevent the verbosed name from not matching aka "drush_mm (1.x)"
    list($clean_value)=explode(" ", $value);
    $result[$clean_value]=$value;
  }
  return $result;
}

function drush_mm_disable_module() {
  $modules = func_get_args();
  _drush_mm_endis_module( FALSE, $modules);
}
