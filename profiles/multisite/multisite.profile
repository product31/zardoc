<?php

/**
 * Return an array of the modules to be enabled when this profile is installed.
 *
 * @return
 *   An array of modules to enable.
 */
// Drop the pathcache module since we're on PressFlow and it has path_alias_cache
function multisite_profile_modules() {
  return array('system', 'filter', 'block', 'user', 'node', 'comment', 'taxonomy', 'menu', 'upload', 'path', 'install_profile_api');
}

/**
 * Return an array of modules that are required. Note that if this
 * function is called with $all == FALSE BEFORE includes are selected,
 * you may get unexpected results.
 *
 * @param $all
 *   If $all is TRUE, the module reqs from every inc will be included
 *   regardless of whether the inc is enabled. If left as false, only
 *   modules required by enabled incs will be returned.
 * @return
 *   An array of modules.
 */
function multisite_profile_get_required_modules() {
  $enabled_incs = variable_get('multisite_incs', array());

  // Take modules from include files and merge.
  $modules = array();
  foreach ($enabled_incs as $name => $inc) {
    require_once("./profiles/multisite/includes/$name.inc");
    $function = $name . '_modules';
    if (function_exists($function)) {
      $modules = array_merge($modules, $function());
    }
  }

  $modules = array_unique($modules);

  // This sort is screwing up module dependencies.  No sorting will be done on
  // the modules list.  inc files are responsible for properly ordering any
  // dependent modules.
  //uasort($modules, 'multisite_weight_cmp');

  return $modules;
}

/**
 * Return a description of the profile for the initial installation screen.
 *
 * @return
 *   An array with keys 'name' and 'description' describing this profile,
 *   and optional 'language' to override the language selection for
 *   language-specific profiles.
 */
function multisite_profile_details() {
  return array(
    'name' => 'Sony BMG Artist Site',
    'description' => 'Select this profile to install a Sony BMG artist site with standard modules and themes.'
  );
}

function multisite_form_alter(&$form, $form_state, $form_id) {
  if ($form_id == 'install_configure') {
    require_once("./profiles/multisite/includes/default_settings.inc");

    $form['site_information']['site_name']['#default_value'] = 'The Official Artist Site';
    $form['site_information']['#weight'] = -2;

    // Merge in the default site settings form.
    $form['artist_information'] = default_settings_artist_info_form();
    $form['artist_information']['#type'] = 'fieldset';
    $form['artist_information']['#title'] = st('Artist information');
    $form['artist_information']['#weight'] = -1;

    $form['#submit'] = array('default_settings_artist_info_form_submit', 'install_configure_form_submit');
    unset($form['artist_information']['submit']);
    unset($form['artist_information']['#redirect']);

    // Set username to adminn and create dummy textfield to show user.
    $form['admin_account']['account']['name'] = array(
      '#type' => 'value',
      '#value' => 'adminn',
    );
    $form['admin_account']['account']['name_dummy'] = array(
      '#type' => 'textfield',
      '#title' => st('Username'),
      '#value' => 'adminn',
      '#default_value' => 'adminn',
      '#disabled' => TRUE,
      '#maxlength' => USERNAME_MAX_LENGTH,
      '#description' => st('Spaces are allowed; punctuation is not allowed except for periods, hyphens, and underscores.'),
      '#required' => FALSE,
      '#weight' => -10,
    );
    // Real password is set in standard_users.inc
    $form['admin_account']['account']['pass'] = array(
      '#type' => 'value',
      '#value' => 'dummy_password_will_be_changed',
    );
  }
}

/**
 * Return a list of tasks that this profile supports.
 *
 * @return
 *   A keyed array of tasks the profile will perform during
 *   the final stage. The keys of the array will be used internally,
 *   while the values will be displayed to the user in the installer
 *   task list.
 */
function multisite_profile_task_list() {
  return array(
    'multisite-select-incs' => st('Select features'),
    'multisite-install-modules-batch' => st('Install modules'),
    'multisite-custom-tasks-batch' => st('Additional tasks'),
  );
}

/**
 * Perform any final installation tasks for this profile.
 *
 * The installer goes through the profile-select -> locale-select
 * -> requirements -> database -> profile-install-batch
 * -> locale-initial-batch -> configure -> locale-remaining-batch
 * -> finished -> done tasks, in this order, if you don't implement
 * this function in your profile.
 *
 * If this function is implemented, you can have any number of
 * custom tasks to perform after 'configure', implementing a state
 * machine here to walk the user through those tasks. First time,
 * this function gets called with $task set to 'profile', and you
 * can advance to further tasks by setting $task to your tasks'
 * identifiers, used as array keys in the hook_profile_task_list()
 * above. You must avoid the reserved tasks listed in
 * install_reserved_tasks(). If you implement your custom tasks,
 * this function will get called in every HTTP request (for form
 * processing, printing your information screens and so on) until
 * you advance to the 'profile-finished' task, with which you
 * hand control back to the installer. Each custom page you
 * return needs to provide a way to continue, such as a form
 * submission or a link. You should also set custom page titles.
 *
 * You should define the list of custom tasks you implement by
 * returning an array of them in hook_profile_task_list(), as these
 * show up in the list of tasks on the installer user interface.
 *
 * Remember that the user will be able to reload the pages multiple
 * times, so you might want to use variable_set() and variable_get()
 * to remember your data and control further processing, if $task
 * is insufficient. Should a profile want to display a form here,
 * it can; the form should set '#redirect' to FALSE, and rely on
 * an action in the submit handler, such as variable_set(), to
 * detect submission and proceed to further tasks. See the configuration
 * form handling code in install_tasks() for an example.
 *
 * Important: Any temporary variables should be removed using
 * variable_del() before advancing to the 'profile-finished' phase.
 *
 * @param $task
 *   The current $task of the install system. When hook_profile_tasks()
 *   is first called, this is 'profile'.
 * @param $url
 *   Complete URL to be used for a link or form action on a custom page,
 *   if providing any, to allow the user to proceed with the installation.
 *
 * @return
 *   An optional HTML string to display to the user. Only used if you
 *   modify the $task, otherwise discarded.
 */
function multisite_profile_tasks(&$task, $url) {
  $output = NULL;

  // Initial task given by install.php.
  if ($task == 'profile') {
    $task = 'multisite-select-incs';
  }

  // First step: select which features are desired.
  if ($task == 'multisite-select-incs') {
    $incs = multisite_get_includes();
    $form = drupal_get_form('multisite_select_incs_form', $incs);
    $enabled_includes = variable_get('multisite_incs', array());
    if (empty($enabled_includes)) {
      drupal_set_title(st('Select site features'));
      $output = $form;
    }
    else {
      $task = 'multisite-install-modules';
    }
  }

  // Install profile modules.
  if ($task == 'multisite-install-modules') {
    drupal_set_title(st('Installing modules for selected features'));
    $modules = multisite_profile_get_required_modules();

    $files = module_rebuild_cache();
    $operations = array();
    $modules = _multisite_module_dependencies($modules);
    file_put_contents('/tmp/modules.recursive.txt', print_r($modules, 1));

    foreach ($modules as $module) {
      $operations[] = array('_install_module_batch', array($module, $files[$module]->info['name']));
    }
    $batch = array(
      'operations' => $operations,
      'finished' => 'multisite_install_modules_batch_finished',
      'title' => st('Installing selected modules'),
      'error_message' => st('The installation has encountered an error.'),
    );
    // Start a batch, switch to 'multisite-install-modules-batch' task. We need to
    // set the variable here, because batch_process() redirects.
    variable_set('install_task', 'multisite-install-modules-batch');
    batch_set($batch);
    batch_process($url, $url);
  }

  // Batch operation for enabling each additionally needed module.
  if ($task == 'multisite-install-modules-batch') {
    include_once 'includes/batch.inc';
    $output = _batch_page();
  }

  // Execute the tasks specified in the .inc files.
  if ($task == 'multisite-custom-tasks') {

    drupal_set_title(st('Performing additional tasks'));
    $enabled_includes = variable_get('multisite_incs', array());
    $custom_tasks = multisite_get_tasks(FALSE, $enabled_includes);

    $operations = array();
    foreach ($custom_tasks as $task_function => $task_details) {
      $operations[] = array('multisite_custom_tasks_batch', array($task_function, $task_details));
    }
    $batch = array(
      'operations' => $operations,
      'finished' => 'multisite_custom_tasks_batch_finished',
      'title' => st('Performing custom setup tasks'),
      'error_message' => st('The installation has encountered an error.'),
    );
    // Start a batch, switch to 'multisite-custom-tasks-batch' task. We need to
    // set the variable here, because batch_process() redirects.
    variable_set('install_task', 'multisite-custom-tasks-batch');
    batch_set($batch);
    batch_process($url, $url);
  }

  // Batch execution of each of the tasks in .inc files.
  if ($task == 'multisite-custom-tasks-batch') {
    include_once 'includes/batch.inc';
    $output = _batch_page();
  }

  // Final cleanup.
  if ($task == 'profile-finished') {
    // Disable the Install Profile API module.
    module_disable(array('install_profile_api'));
    // If a sonybmg module is enabled after the install, we need
    // install_profile_api again later, so leave it installed (but disabled).
    //drupal_set_installed_schema_version('install_profile_api', SCHEMA_UNINSTALLED);
  }

  return $output;
}

function _multisite_module_dependencies($modules) {
  static $all_modules;
  if (!isset($all_modules)) {
    $all_modules = module_rebuild_cache();
  }
  $return = array();

  foreach ($modules as $m) {
    $dependencies = $all_modules[$m]->info['dependencies'];
    if (is_array($dependencies) && count($dependencies)) {
      $dependencies = _multisite_module_dependencies($dependencies);
      foreach ($dependencies as $d) {
        if (!isset($return[$d])) {
          $return[$d] = $d;
        }
      }
    }
    $return[$m] = $m;
  }

  return array_values($return);
}

/**
 * Batch callback for batch installation of modules.
 */
function multisite_install_module_batch($module, $module_name, &$context) {
  // This bit is really weird. drupal_execute() cannot be used in batch
  // operations (it should apparently, but doesn't). So we unset the current
  // batch and then restore it after the task is done.
  // CAKE IS A LIE! this doesn't run EVER!
  $previous_batch = batch_get();
  $batch = &batch_get();
  $batch = array();
  $result = watchdog("Installing...", $module_name);
  _drupal_install_module($module);
  // We enable the installed module right away, so that the module will be
  // loaded by drupal_bootstrap in subsequent batch requests, and other
  // modules possibly depending on it can safely perform their installation
  // steps.

  module_enable(array($module));

  // Restore the batch state;
  $batch = $previous_batch;


  $context['results'][] = $module;
  $context['message'] = st('Installed %module module.', array('%module' => $module_name));
}

/**
 * Finished callback for the multisite modules install batch.
 *
 * Advance installer task to all custom tasks from .inc files.
 */
function multisite_install_modules_batch_finished($success, $results) {
  variable_set('install_task', 'multisite-custom-tasks');
}

/**
 * Function called for each iteration of batch install processes.
 */
function multisite_custom_tasks_batch($task_function, $task_details, &$context) {
  // Load all the needed includes from Install Profile API.
  $modules = array_merge(multisite_profile_modules(), multisite_profile_get_required_modules());
  install_include($modules);

  // See explaination for this in multisite_install_module_batch().
  $previous_batch = batch_get();
  $batch = &batch_get();
  $batch = array();

  // Execute the task.
  $task_function();

  // Restore the batch state;
  $batch = $previous_batch;

  $include_info_function = $task_details['include'] .'_info';
  $include_info = $include_info_function();

  $context['results'][] = $task_function;
  $context['message'] = $include_info['name'] .': '. $task_details['message'];
}

/**
 * Finished callback for the multisite modules install batch.
 */
function multisite_custom_tasks_batch_finished($success, $results) {
  variable_set('install_task', 'profile-finished');
}

function multisite_select_incs_form($form_state, $incs) {
  $form = array(
    '#redirect' => FALSE,
  );

  $form['includes'] = array(
    '#type' => 'fieldset',
    '#title' => st('Features'),
    '#description' => st('Select the features that you would like to be set up on your new site.'),
    '#tree' => TRUE,
  );

  foreach ($incs as $key => $inc) {
    $form['includes'][$key] = array(
      '#type' => 'checkbox',
      '#title' => $inc['name'],
      '#default_value' => $inc['default_value'] ? $key : NULL,
      '#weight' => $inc['weight'],
      '#return_value' => $key,
    );
    if ($inc['disabled']) {
      $form['includes'][$key]['#attributes']['disabled'] = 'disabled';
      $form['includes'][$key]['#value'] = $key;
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Go'),
  );
  return $form;
}

function multisite_select_incs_form_submit($form, &$form_state) {
  // Set the list of needed includes.
  multisite_get_includes();
  $enabled_includes = array();
  foreach ($form_state['values']['includes'] as $choice) {
    $info_function = $choice .'_info';
    if ($choice) {
      $enabled_includes[$choice] = $choice;
    }
  }

  variable_set('multisite_incs', $enabled_includes);
}

/* MISC */

function multisite_get_includes() {
  $files = file_scan_directory('profiles/multisite/includes', '.*', array('.', '..', 'CVS'), 0, FALSE, 'name');
  $incs = array();
  foreach ($files as $name => $info) {
    require_once("./profiles/multisite/includes/$name.inc");
    $function = $name . '_info';
    if (!function_exists($function)) {
      continue;
    }
    else {
      $info = $function();
      if (!empty($info)) {
        $incs[$name] = $function();
      }
    }
  }
  uasort($incs, 'multisite_weight_cmp');
  return $incs;
}

function multisite_get_tasks($obey_show = TRUE, $enabled_incs = array()) {
  $tasks = array();
  $incs = multisite_get_includes();
  foreach ($incs as $name => $inc) {
    // Skip if we have a list of enabled incs and this module wasn't in it.
    if (!isset($enabled_incs[$name])) {
      continue;
    }

    $function = $name . '_task_list';
    if (function_exists($function)) {
      $inc_tasks = $function();
      foreach ($inc_tasks as $task_name => &$task) {
        // Add include to task so we can use it later.
        $task['include'] = $name;
        // Unset this element if it is not supposed to be shown.
        if ($obey_show && !$task['show']) {
          unset($inc_tasks[$task_name]);
        }
      }
      $tasks = array_merge($tasks, $inc_tasks);
    }
  }
  // Make sure tasks are in the right order.
  multisite_special_sort_tasks($tasks, $incs);
  return $tasks;
}

function multisite_weight_cmp($a, $b) {
  $wa = (int)$a['weight'];
  $wb = (int)$b['weight'];

  if ($wa == $wb) {
    if (isset($a['name']) && isset($b['name']) && $a['name'] != $b['name']) {
      return ($a['name'] < $b['name']) ? -1 : 1;
    }
    return 0;
  }
  return ($wa < $wb) ? -1 : 1;
}

/**
 * Function that will filter down subarrays in an array
 * so you can have only the information you want
 *
 * @param $arr
 *   The array you want to filter
 * @param $val
 *   What you want the value of each element of the main array to be. If
 *   you set this to parameter to 'key', each item will be the original
 *   subarray's key. If you set it to a string that represents a key in
 *   the subarray, each item will be the item in that subarray represented
 *   by the key. If you give an array of strings, each item will be the original
 *   subarray except with only the keys you passed in.
 * @param $key
 *   What you want the key of each element of the main array to be. If you
 *   set this parameter to 'key', the keys will be preserved. If you set it
 *   to NULL, keys will be numerically indexed. If you set to to a string,
 *   the key will be the element of the subarray indexed by that string.
 */
function multisite_filter_array(&$arr, $val, $key=NULL) {
  $new = array();
  foreach ($arr as $k => $v) {
    if ($key !== NULL) {
      $newk = $key == 'key' ? $k : $v[$key];
    }

    if ($val === 'key') {
      $newv = $k;
    }
    else if (!is_array($val)) {
      $newv = $v[$val];
    }
    else {
      $newv = array();
      foreach ($val as $inc) {
        $newv[$inc] = $v[$inc];
      }
    }

    if ($key === NULL) {
      $new[] = $newv;
    }
    else {
      $new[$newk] = $newv;
    }
  }
  $arr = $new;
}

/**
 * Sort tasks with negative weights first ascending by task weight,
 * Then weight 0 tasks grouped by includes and then sorted by include weight,
 * Then tasks with positive weights ascending by task weight
 */
function multisite_special_sort_tasks(&$tasks, $incs) {
  //enforce that tasks of weight 0 are grouped with
  //their own inc in module order
  $weightnegative = array();
  $weight0 = array();
  $weightpositive = array();
  foreach($tasks as $name => $info) {
    if($info['weight'] == 0) {
      if (!isset($weight0[$info['include']])) {
        $weight0[$info['include']] = array('weight' => $incs[$info['include']]['weight'], 'tasks' => array());
      }
      $weight0[$info['include']]['tasks'][$name] = $info;
    }
    else if ($info['weight'] < 0) {
      $weightnegative[$name] = $info;
    }
    else {
      $weightpositive[$name] = $info;
    }
  }

  //sort negative and positive weights by weight
  uasort($weightnegative, 'multisite_weight_cmp');
  uasort($weightpositive, 'multisite_weight_cmp');

  //negative weights (already sorted) go onto new task list first
  $tasks = $weightnegative;

  //sort weight0 by include order
  uasort($weight0, 'multisite_weight_cmp');
  //3d array $weight0[$include]['tasks'][$name -> 2d array $weight0[$include][$name]
  multisite_filter_array($weight0, 'tasks', 'key');
  //2d array $weight0[$include][$name] -> 1d array $tasks[$name]
  foreach ($weight0 as $include => $inc_tasks) {
    $tasks += $inc_tasks;
  }

  //positive weights (already sorted) go on last
  $tasks += $weightpositive;
  //done sorting tasks
}

/**
 * Replaces string instances in a file.
 *
 * @param $file_loc
 *   A sting containing the location of file.
 * @param $search Mixed.
 *   Array or String of search strings.
 * @param $replace Mixed
 *   Array or String of replacement strings.
 *
 * @return
 *   Number of bytes written or FALSE if the get or put failed.
 */
function multisite_file_replace($file_loc, $search = array(), $replace = array()) {
  // Try to pull the file that needs replacements.
  if ($contents = file_get_contents($file_loc)) {
    $contents = str_replace($search, $replace, $contents);
    return file_put_contents($file_loc, $contents);
  }
  // Could not pull the file.
  else {
    return FALSE;
  }
}

/**
 * Recursively remove a directory or list of subdirectories.
 *
 * @param $dir
 *  The directory to recurse from.
 * @param $directory_list
 *   - TRUE deletes the folder without exception.
 *   - An array of folder names to remove.
 *
 * See _imagecache_recursive_delete($path) for a similar implementation if this goes awry.
 */
 function multisite_rrmdir($dir, $directory_list = TRUE) {
   if (is_dir($dir)) {
     $objects = scandir($dir);
     foreach ($objects as $object) {
       // Ignore upper directories that are listed.
       if ($object != "." && $object != "..") {
         if (filetype($dir."/".$object) == "dir") {
           // If this is set for deletion, delete the whole directory tree.
           if ($directory_list === TRUE || in_array($object, $directory_list)) {
             multisite_rrmdir($dir."/".$object, TRUE);
           }
           // If not set for deletion, recurse into the folder.
           else {
             multisite_rrmdir($dir."/".$object, $directory_list);
           }
         }
         // Delete a file.
         else {
           unlink($dir."/".$object);
         }
       }
     }
     reset($objects);
     // Delete the directory.
     rmdir($dir);
   }
 }
 /**
  * Move files recursively to a new destination.
  *
  * @param $source
  *   Source file or directory location.
  * @param $destination
  *   Destination file or directory location.
  * @param $exclude_files
  *   Array of files or directory names to recursively exclude.
  */
 function multisite_copy_files($source, $destination, $exclude_files = array()) {
  if (is_dir($source)) {
    // Create destination directory if it doesn't exist.
    if(!is_dir($destination)) {
      // Not using $mode on mkdir and explicitly using chmod instead. See http://www.php.net/manual/en/function.mkdir.php#99810
      mkdir($destination);
      chmod($destination, 0755);
    }
    $files = scandir($source);
    foreach ($files as $file) {
      if (!in_array($file, array('.', '..')) && !in_array($file, $exclude_files)) {
        multisite_copy_files($source .'/'. $file, $destination .'/'. $file, $exclude_files);
      }
    }
  }
  else {
    $status = copy($source, $destination);
  }
}