<?php
// $Id$

/**
 * @file
 */

/**
 * admin/settings/pluto/achievement
 * The admin interface for achievements
 * Drag-sortable
 */


function pluto_admin_achievement(&$form_state) {
  $result = db_query('SELECT aid FROM {pluto_achievement} ORDER BY weight');
  while ($row = db_fetch_object($result)) {
    $achievement = pluto_achievement_load($row->aid);
    $content = '<strong>'. $achievement->name .'</strong><br/>'. $achievement->description;
    $items = array();
    foreach ($achievement->tasks as $task) {
      $method = pluto_achievement_filters($task->method);
      $items[] = $method['name'] .' ('. $task->value .')';
    }
    if (!$items) {
      $items[] = '<em>No tasks defined yet.</em>';
    }
    $content .= theme('item_list', $items);

    $data = array(
      theme('image', $achievement->badge),
      $content,
      l('Tasks', 'admin/settings/pluto/achievement/'. $achievement->aid),
      l('Edit', 'admin/settings/pluto/achievement/'. $achievement->aid .'/edit', array(), drupal_get_destination()),
      l('Delete', 'admin/settings/pluto/achievement/'. $achievement->aid .'/delete', array(), drupal_get_destination()),
    );
    
    $form['rows'][$row->aid]['data'] = array('#type' => 'value',
                                             '#value' => $data);
    $form['rows'][$row->aid]['weight-'. $row->aid] = array('#type' => 'textfield',
                                                          '#size' => 5,
                                                          '#default_value' => $achievement->weight,
                                                          '#attributes' => array('class' => 'weight'));
    
  }
  $form['submit'] = array('#type' => 'submit',
                            '#value' => t('Save changes'));
  return $form;
  
}

/* Theme the above form to add the draggable goodness */

function theme_pluto_admin_achievement($form) {
    //loop through each "row" in the table array
    if (!$form['rows']) {
      return t('There are no achievements. ') . l(t('Add the first achievement'), 'admin/settings/pluto/achievement/add');
    }
    foreach($form['rows'] as $id => $row){
      //we are only interested in numeric keys
      if (intval($id)){  
        $this_row = $row['data']['#value'];

        //Add the weight field to the row
        $this_row[] = drupal_render($form['rows'][$id]['weight-'.$id]);
   
        //Add the row to the array of rows
        $table_rows[] = array('data'=>$this_row, 'class'=>'draggable');
      }
    }
    //dsm($table_rows);
    //Make sure the header count matches the column count
    $header=array(
      t("Image"),t("Achievement"), array('data' => t('Operations'), 'colspan' => '3'), "weight"
    );

    $output = theme('table',$header,$table_rows,array('id'=>'example-table'));
    $output .= drupal_render($form);
 
    // Call add_tabledrag to add and setup the JS for us
    // The key thing here is the first param - the table ID
    // and the 4th param, the class of the form item which holds the weight
    drupal_add_tabledrag('example-table', 'order', 'sibling', 'weight');   
    return $output;
}

/* submit handler for the above form to save the weights */

function pluto_admin_achievement_submit($form, &$form_state) {
  foreach($form_state['values'] as $key=>$data){
    //we are only interested in weight elements
    if (substr($key,0,6)=='weight'){
      //cunningly we have the DB id of the row in the element name
      $id = str_replace('weight-','',$key);
      db_query("UPDATE {pluto_achievement} SET weight=%d WHERE aid=%d",$data,$id);
    }
  }
  //optionally set the redirect value in form_submit ...
}


/**
 * Single achievement view
 */
function pluto_admin_achievement_view($achievement) {
  drupal_set_title($achievement->name);
  $output = '<p>'. check_plain($achievement->description) .'</p>';
  $output .= '<p>'. theme('pluto_badge', $achievement) .'</p>';
  $output .= drupal_get_form('pluto_admin_achievement_tasks', $achievement);
  return $output;
}

/**
 * achievement add/edit tasks form
 */
function pluto_admin_achievement_tasks($form_state, $achievement) {
  $options = array();
  foreach (pluto_achievement_filters() as $key => $filter) {
    $options[$filter['group']][$key] = $filter['name'];
    $descriptions[$filter['group']][] = '<strong>'. $filter['name'] .'</strong>: '. $filter['description'];
  }
  foreach ($descriptions as $group_name => $group) {
    $help .= theme('item_list', $group, $group_name);
  }

  $form['tasks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Achievement Tasks'),
    '#tree' => 1,
  );

  $achievement->tasks[] = (object)array('tid' => 'new', 'aid' => $achievement->aid);
  foreach ($achievement->tasks as $task) {
    $form['tasks'][$task->tid] = array('#tree' => 1);
    $form['tasks'][$task->tid]['tid'] = array(
      '#type' => 'value',
      '#value' => $task->tid == 'new' ? NULL : $task->tid,
    );
    $form['tasks'][$task->tid]['aid'] = array(
      '#type' => 'value',
      '#value' => $task->aid,
    );
    $form['tasks'][$task->tid]['method'] = array(
      '#type' => 'select',
      '#title' => t('Method'),
      '#description' => t('Choose from the list of tasks that users can gain an achievement with. Further details are in the Method Descriptions section below.'),
      '#default_value' => $task->method,
      '#options' => ($task->tid == 'new') ? (array('' => t('-- Select a task --')) + $options) : $options,
    );
    $form['tasks'][$task->tid]['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Value'),
      '#description' => t('A value associated with the above task - e.g. the number of userpoints to be achieved. Further details are in the Method Descriptions section below.'),
      '#default_value' => $task->value,
      '#size' => 20,
    );
    $form['tasks'][$task->tid]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Task Weight'),
      '#default_value' => $task->weight,
    );
    if ($task->tid == 'new') {
      $form['tasks'][$task->tid]['button'] = array(
        '#type' => 'submit',
        '#value' => t('Add task'),
      );
    }
    else {
      $image = theme('image', 'misc/watchdog-error.png', t('Remove this task.'), t('Remove'));
      $path = 'admin/settings/pluto/achievement/'. $task->aid .'/task/'. $task->tid .'/delete';
      $form['tasks'][$task->tid]['button'] = array(
        '#value' => l($image, $path, array('query' => drupal_get_destination(), 'html' => TRUE)),
      );
    }
  }

  $form['tasks']['new']['help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Method Descriptions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#value' => $help,
  );

  $form['achievement'] = array('#type' => 'value', '#value' => $achievement);

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));

  return $form;
}

/**
 * theme the achievement tasks form into a nice table
 */
function theme_pluto_admin_achievement_tasks($form) {
  $rows = $new = array();
  foreach (element_children($form['tasks']) as $key) {
    $row = array(
      drupal_render($form['tasks'][$key]['method']),
      drupal_render($form['tasks'][$key]['value']),
      drupal_render($form['tasks'][$key]['weight']),
      drupal_render($form['tasks'][$key]['button']),
    );
    $rows[] = $row;
  }
  $headers = array(t('Method'), t('Value'), t('Weight'));
  $output = theme('table', $headers, $rows) . drupal_render($form['tasks']['new']['help']);
  $form['tasks']['#value'] = $output;

  return drupal_render($form);
}

/**
 * achievement add/edit tasks form submit
 */
function pluto_admin_achievement_tasks_submit($form, &$form_state) {
  if ($form_state['values']['op'] == t('Add task')) {
    pluto_achievement_task_save($form_state['values']['tasks']['new']);
  }
  else {
    foreach ($form_state['values']['tasks'] as $tid => $task) {
      // only save if tid is already there, or if tid is empty method must be there
      if ($task['tid'] || $task['method']) {
        $task = pluto_achievement_task_save($task);
      }
    }
  }

  return 'admin/settings/pluto/achievement/'. $form_state['values']['achievement']->aid;
}

/**
 * achievement add/edit form
 */
function pluto_admin_achievement_edit($form_state, $achievement=NULL) {

  $form['aid'] = array(
    '#type' => 'hidden',
    '#value' => $achievement->aid,
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $achievement->name,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $achievement->description,
  );

  $form['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#description' => t('Achievements with the lowest weight are considered to be the best'),
    '#default_value' => $achievement->weight ? $achievement->weight : 10,
    '#delta' => 100,
  );

  $form['badges'] = array(
    '#type' => 'fieldset',
    '#title' => t('Badge settings'),
    '#tree' => 0,
  );

  $form['badges']['badge'] = array('#type' => 'value', '#value' => $achievement->badge);
  if ($achievement->badge) {
    $form['badges']['_badge'] = array('#value' => theme('image', $achievement->badge));
  }

  $form['badges']['badge_upload'] = array(
    '#type' => 'file',
    '#title' => t('Small Image'),
    '#description' => t('Uploading an image will overwrite any previously uploaded badge.'),
  );

  $form['badges']['placeholder'] = array('#type' => 'value', '#value' => $achievement->placeholder);
  if ($achievement->placeholder) {
    $form['badges']['_placeholder'] = array('#value' => theme('image', $achievement->placeholder));
  }

  $form['badges']['placeholder_upload'] = array(
    '#type' => 'file',
    '#title' => t('Placeholder Image'),
    '#description' => t('This is not usually used. It shows in a users profile when they have not achieved this badge. Uploading an image will overwrite any previously uploaded placeholder.'),
  );

  $form['badges']['fullsize'] = array('#type' => 'value', '#value' => $achievement->fullsize);
  if ($achievement->fullsize) {
    $form['badges']['_fullsize'] = array('#value' => theme('image', $achievement->fullsize));
  }

  $form['badges']['fullsize_upload'] = array(
    '#type' => 'file',
    '#title' => t('Large Image'),
    '#description' => t('This image shows in the popup when the small badge is clicked. Uploading an image will overwrite any previously uploaded placeholder.'),
  );  
  
  $all_rewards = pluto_reward_load_all();
  $form['rewards'] = array(
    '#type' => 'fieldset',
    '#title' => t('Rewards'),
    '#description' => t('Select the rewards to associate with this achievement.'),
    '#tree' => 1,
  );

  if (count($all_rewards)) {
    foreach ($all_rewards as $reward) {
      $form['rewards'][$reward->rid] = array(
        '#type' => 'checkbox',
        '#title' => $reward->name,
        '#description' => $reward->description,
        '#default_value' => isset($achievement->rewards[$reward->rid]),
      );
    }
  }
  else {
    $form['rewards']['#value'] = t('No rewards available.');
  }

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
  $form['#attributes']['enctype'] = 'multipart/form-data';

  return $form;
}

/**
 * achievement add/edit form validate
 */
function pluto_admin_achievement_edit_validate($form, &$form_state) {
  $images = array(
    'badge' => 'badge_upload',
    'placeholder' => 'placeholder_upload',
  );
  
  foreach ($images as $image => $upload) {

    // NEW CODE
    $validators = array(
      'file_validate_is_image' => array(),
      'file_validate_image_resolution' => array(variable_get('pluto_badge_dimensions', '200x200')), // TODO: Create some admin settings for badge size
      'file_validate_size' => array(variable_get('pluto_badge_file_size', '100') * 1024), // TODO: Create some admin settings for file size
    );
    file_check_directory(variable_get('pluto_badge_path', file_directory_path() . '/badges'), FILE_CREATE_DIRECTORY); // check directory exists
    if ($file = file_save_upload($upload, $validators)) {
      // Remove the old picture. @TODO this
      /*
      if (isset($form_state['values']['_account']->picture) && file_exists($form_state['values']['_account']->picture)) {
        file_delete($form_state['values']['_account']->picture);
      }
      */

      // The image was saved using file_save_upload() and was added to the
      // files table as a temporary file. We'll make a copy and let the garbage
      // collector delete the original upload.
      $info = image_get_info($file->filepath);

      $destination = variable_get('pluto_badge_path', file_directory_path() . '/badges') .'/'. $file->filename;
      if (file_copy($file, $destination, FILE_EXISTS_REPLACE)) {
        $form_state['values'][$image] = $file->filepath;
      }
      else {
        form_set_error($upload, t("Failed to upload the picture image; the %directory directory doesn't exist or is not writable.", array('%directory' => variable_get('pluto_badge_path', 'badges'))));
      }
    } else {
        // form_set_error($upload, t("Image is not valid"));
    }
  }
  // deal with the large image separately
  $images = array(
    'fullsize' => 'fullsize_upload'
  );
  
  foreach ($images as $image => $upload) {

    // NEW CODE
    $validators = array(
      'file_validate_is_image' => array(),
      'file_validate_image_resolution' => array(variable_get('pluto_large_badge_dimensions', '600x600')), // TODO: Create some admin settings for badge size
      'file_validate_size' => array(variable_get('pluto_badge_file_size', '1000') * 1024), // TODO: Create some admin settings for file size
    );
    file_check_directory(variable_get('pluto_badge_path', file_directory_path() . '/badges'), FILE_CREATE_DIRECTORY); // check directory exists
    if ($file = file_save_upload($upload, $validators)) {
      // Remove the old picture. @TODO this
      /*
      if (isset($form_state['values']['_account']->picture) && file_exists($form_state['values']['_account']->picture)) {
        file_delete($form_state['values']['_account']->picture);
      }
      */

      // The image was saved using file_save_upload() and was added to the
      // files table as a temporary file. We'll make a copy and let the garbage
      // collector delete the original upload.
      $info = image_get_info($file->filepath);

      $destination = variable_get('pluto_badge_path', file_directory_path() . '/badges') .'/'. $file->filename;
      if (file_copy($file, $destination, FILE_EXISTS_REPLACE)) {
        $form_state['values'][$image] = $file->filepath;
      }
      else {
        form_set_error($upload, t("Failed to upload the large image; the %directory directory doesn't exist or is not writable.", array('%directory' => variable_get('pluto_badge_path', 'badges'))));
      }
    } else {
        // form_set_error($upload, t("Image is not valid"));
    }
  }
}

/**
 * achievement add/edit form submit
 */
function pluto_admin_achievement_edit_submit($form, &$form_state) {
  $achievement = pluto_achievement_save($form_state['values']);
  $form_state['redirect'] = 'admin/settings/pluto/achievement/'. $achievement->aid;
}

/**
 * achievement delete form
 */
function pluto_admin_achievement_delete($form_state, $achievement) {
  $form['aid'] = array('#type' => 'value', '#value' => $achievement->aid);

  return confirm_form($form,
    t('Are you sure you want to delete %name', array('%name' => $achievement->name)),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/settings/pluto/achievement/'. $achievement->aid,
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel'));
}

/**
 * achievement delete form submit
 */
function pluto_admin_achievement_delete_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    pluto_achievement_delete($form_state['values']['aid']);
  }

  $form_state['redirect'] = 'admin/settings/pluto/achievement';
}

/**
 * achievement delete form
 */
function pluto_admin_achievement_task_delete($form_state, $task) {
  $methods = pluto_achievement_filters();
  $achievement = pluto_achievement_load($task->aid);
  $form['tid'] = array('#type' => 'value', '#value' => $task->tid);
  $form['aid'] = array('#type' => 'value', '#value' => $achievement->aid);

  return confirm_form($form,
    t('Are you sure you want to delete the task %method from %name', array('%method' => $methods[$task->method]['name'], '%name' => $achievement->name)),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/settings/pluto/achievement/'. $achievement->aid,
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel'));
}

/**
 * achievement delete form submit
 */
function pluto_admin_achievement_task_delete_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    pluto_achievement_task_delete($form_state['values']['tid']);
  }

  $form_state['redirect'] = 'admin/settings/pluto/achievement/'. $form_state['values']['aid'];
}
