<?php
// $Id: user_titles.admin.inc,v 1.1.2.1 2010/02/02 11:20:15 agileware Exp $

/**
 * @file
 * Admin page callback file for the user_titles module.
 */

/**
 * Form to determine titles and levels.
 *
 * @return
 *   A form array.
 */
function user_titles_settings_form() {
  $form = array();

  $types = user_titles_get_allowed_types();

  foreach (node_get_types() as $type => $info) {
    $nodes[$type] = $info->name;
  }

  $hook_module = user_titles_get_hook_module();
  $hook_modules = module_invoke_all('user_titles', 'register');


  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => 'Settings',
  );
  $form['settings']['hook_module'] = array(
    '#type' => 'radios',
    '#title' => 'Point scheme',
    '#default_value' => $hook_module,
    '#options' => array(),
    '#attributes' => array('class' => 'user-titles-hook-module'),
  );
  foreach ($hook_modules as $module) {
    $name = module_invoke($module, 'user_titles', 'name');
    $form['settings']['hook_module']['#options'][$module] = array(
      'name' => $name,
      'description' => module_invoke($module, 'user_titles', 'description'),
      'url' => module_invoke($module, 'user_titles', 'url'),
    );
    $name_index[$module] = $name;
  }

  array_multisort($name_index, SORT_ASC, SORT_STRING, $form['settings']['hook_module']['#options']);

  // Implementation of user_titles' default behavior
  $form['settings']['types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Counted node types'),
    '#description' => t('Only the checked node types will be counted'),
    '#options' => $nodes,
    '#default_value' => $types,
    '#disabled' => $hook_module !== 'user_titles',
    '#attributes' => array('class' => 'user-titles-types'),
  );
  $form['settings']['types_disabled'] = array(
    '#type' => 'hidden',
    '#default_value' => $hook_module !== 'user_titles',
  );
  // Directory to save images
  $form['settings']['image_dir'] = array(
    '#type' => 'textfield',
    '#title' => t('Image directory'),
    '#description' => t('Subdirectory in the directory %dir where images will be stored.', array('%dir' => file_directory_path() .'/')),
    '#default_value' => variable_get('user_titles_image_dir', DEFAULT_IMAGE_DIR),
    '#size' => 35,
    '#attributes' => array('class' => 'user-titles-image-dir'),
  );

  $form['roles-description'] = array(
    '#type' => 'item',
    '#value' => t('Set the priority of your roles here.  If a user has multiple roles they will get the titles of highest role in this list that they are a member of.  If the users highest role has no titles that user will not get titles.'),
  );
  $form['roles'] = array(
    '#tree' => TRUE,
  );

  $result = db_query("SELECT r.name, ro.*
                      FROM {role} r, {user_titles_roles} ro
                      WHERE r.rid = ro.rid
                      AND r.rid != 1
                      ORDER BY ro.weight");
  while ($role = db_fetch_array($result)) {
    $form['roles'][$role['rid']]['name'] = array(
      '#value' => check_plain($role['name']),
    );
    $form['roles'][$role['rid']]['weight'] = array(
      '#type' => 'weight',
      '#delta' => 30,
      '#default_value' => $role['weight'],
    );
  }

  $form['display'] = array(
    '#type' => 'fieldset',
    '#title' => t('Display'),
  );
  $form['display']['display_on_profile'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display title on user profile'),
    '#default_value' => variable_get('user_titles_display_on_profile', TRUE),
    '#description' => t("If checked, the user's title will be displayed on their profile page."),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit function for the user titles setting form.
 */
function user_titles_settings_form_submit($form, &$form_state) {
  // If they change the allowed types, wipe the existing counts so each one will be fresh.
  $types = user_titles_get_allowed_types();
  if ($types != $form_values['types']) {
    db_query("TRUNCATE TABLE {user_titles_posts}");
  }

  if (!$form_state['values']['types_disabled']) {
    user_titles_set_allowed_types(array_keys(array_filter($form_state['values']['types'])));
  }

  user_titles_set_hook_module($form_state['values']['hook_module']);
  variable_set('user_titles_image_dir', $form_state['values']['image_dir']);
  variable_set('user_titles_display_on_profile', $form_state['values']['display_on_profile']);

  $image_path = file_create_path(variable_get('user_titles_image_dir', DEFAULT_IMAGE_DIR));
  file_check_directory($image_path, 1, 'image_dir');

  // Role orders
  foreach ($form_state['values']['roles'] as $rid => $role) {
    db_query("UPDATE {user_titles_roles} SET weight = %d WHERE rid = %d", $role['weight'], $rid);
    if (!db_affected_rows()) {
      db_query("INSERT INTO {user_titles_roles} (rid, weight) VALUES (%d, %d)", $rid, $role['weight']);
    }
  }

  drupal_set_message(t('The configuration has been updated.'));
}

/**
 * Form that lists the user titles.
 *
 * @return
 *   A form array.
 */
function user_titles_titles_form() {
  $form = array();

  $form['roles']['#tree'] = TRUE;

  $result = db_query("SELECT r.name, ro.*
                      FROM {role} r, {user_titles_roles} ro
                      WHERE r.rid = ro.rid
                      AND r.rid != 1
                      ORDER BY ro.weight");
  while ($role = db_fetch_array($result)) {
    $titles = user_titles_get_titles_by_role($role['rid']);
    
    $form['roles'][$role['rid']]['name'] = array(
      '#type' => 'markup',
      '#value' => t($role['name']),
    );
    $form['roles'][$role['rid']]['add_title'] = array(
      '#type' => 'item',
      '#value' => l(t('Add another title'), 'admin/user/user-titles/add/title', array('query' => array('rid' => $role['rid']))),
    );

    if (!empty($titles)) {
      foreach ($titles as $i => $title) {
        $form['roles'][$role['rid']]['titles'][$i]['value'] = array(
          '#type' => 'markup',
          '#value' => $title->value,
        );
        $form['roles'][$role['rid']]['titles'][$i]['title'] = array(
          '#type' => 'markup',
          '#value' => $title->title,
        );
        $form['roles'][$role['rid']]['titles'][$i]['image'] = array(
          '#type' => 'markup',
          '#value' => theme('user_titles_image', $title->image, $title->image_title),
        );
        $form['roles'][$role['rid']]['titles'][$i]['tid'] = array(
          '#type' => 'hidden',
          '#value' => $title->tid,
        );
      }
    }
  }

  return $form;
}

/**
 * Form for adding/editing user titles.
 *
 * @param $title
 *   A title object if editing.  NULL if adding a new title.
 *
 * @return
 *   A form array.
 */
function user_titles_add_title_form(&$form_state, $title = NULL) {
  $path = drupal_get_path('module', 'user_titles');
  drupal_add_css("$path/admin.css");

  // For file field to work.
  $form['#attributes'] = array('enctype' => 'multipart/form-data');

  $roles = user_titles_get_roles();
  $rid = is_numeric($_GET['rid']) ? $_GET['rid'] : 0;
  $default_role = $title->rid ? $title->rid : $rid;
  $form['role'] = array(
    '#type' => 'select',
    '#title' => t('Role'),
    '#required' => TRUE,
    '#default_value' => $default_role,
    '#options' => $roles,
  );

  $units = module_invoke(user_titles_get_hook_module(), 'user_titles', 'units');
  $form['value'] = array(
    '#type' => 'textfield',
    '#title' => t($units),
    '#size' => 5,
    '#maxlength' => 10,
    '#required' => TRUE,
    '#default_value' => $title->value,
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#size' => 40,
    '#maxlength' => 128,
    '#required' => TRUE,
    '#default_value' => $title->title,
  );

  $form['image'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image'),
  );

  $form['image']['image_display'] = array(
    '#type' => 'item',
    '#value' => theme('user_titles_image', $title->image, $title->image_title),
  );

  if ($title->image) {
    $form['image']['remove_image'] = array(
      '#type' => 'checkbox',
      '#title' => t('Remove image'),
      '#description' => t('If checked this image will be removed from this title on submit.'),
    );
  }

  $form['image']['image_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Image title/alt text'),
    '#size' => 40,
    '#maxlength' => 255,
    '#default_value' => $title->image_title,
    '#description' => t('This text will be used as the title and alt text for the image when it is displayed.'),
  );

  $form['image']['image_upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload new image'),
    '#size' => 40,
    '#description' => t('Upload an image that can be displayed with this user title.  This image will replace any existing image attached to this title.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  if ($title->tid) {
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
    $form['tid'] = array(
      '#type' => 'value',
      '#value' => $title->tid,
    );
  }

  return $form;
}

/**
 * Validate function for the add title form.
 */
function user_titles_add_title_form_validate($form, &$form_state) {
  $existing_titles = user_titles_get_titles_by_role($form_state['values']['role']);

  if (!is_numeric($form_state['values']['value'])) {
    form_set_error('title', t('Number of posts must be a number!'));
  }

  foreach ($existing_titles as $title) {
    if ($title->tid != $form_state['values']['tid']) {
      if ($title->title == $form_state['values']['title']) {
       form_set_error('title', t('This title already exists for the selected role.  Titles must be unique.'));
      }
      if ($title->value == $form_state['values']['value']) {
        form_set_error('value', t('There is already a title for this number of posts for the selected role.  Posts must be unique.'));
      }
    }
  }
}

/**
 * Submit function for the add title form.
 */
function user_titles_add_title_form_submit($form, &$form_state) {
  // Do file processing if a file has been added.
  $image = '';

  // Get directory
  $dir = file_create_path(variable_get('user_titles_image_dir', DEFAULT_IMAGE_DIR));
  file_check_directory($dir, 1, 'image_upload');

  // Save file
  $validators = array(
    'file_validate_is_image' => array(),
  );
  if ($file = file_save_upload('image_upload', $validators, $dir, TRUE)) {
    file_set_status($file, FILE_STATUS_PERMANENT);
    $image = $file->filepath;
    drupal_set_message(t('The file: <strong>"' . $file->filename . '"</strong> is successfully uploaded'));
  }
 // else if ($file === 0) {
  //  drupal_set_message(t('ERROR uploading the file to ' . $dir . '.  The user title has been created without an image.'), 'error');
 // }

  // Save title information
  if ($form_state['values']['tid']) {
    // Only update image information if an image was uploaded so images don't get lost.
    if ($image != '') {
      db_query("UPDATE {user_titles} SET title = '%s', value = %d, image = '%s', image_title = '%s', rid = %d WHERE tid = %d", $form_state['values']['title'], $form_state['values']['value'], $image, $form_state['values']['image_title'], $form_state['values']['role'], $form_state['values']['tid']);
    }
    elseif ($form_state['values']['remove_image']) {
      db_query("UPDATE {user_titles} SET title = '%s', value = %d, image = '%s', image_title = '%s', rid = %d WHERE tid = %d", $form_state['values']['title'], $form_state['values']['value'], '', '', $form_state['values']['role'], $form_state['values']['tid']);
    }
    else {
      db_query("UPDATE {user_titles} SET title = '%s', value = %d, image_title = '%s', rid = %d WHERE tid = %d", $form_state['values']['title'], $form_state['values']['value'], $form_state['values']['image_title'], $form_state['values']['role'], $form_state['values']['tid']);
    }
    // Reload the titles object from the database and bypass the cache.
    user_titles_get_titles(NULL, TRUE);
    drupal_set_message(t('Updated user title %title.', array('%title' => $form_state['values']['title'])));
    $form_state['redirect'] = 'admin/user/user-titles/titles';
  }
  else {
    db_query("INSERT INTO {user_titles} (title, value, image, image_title, rid) VALUES ('%s', %d, '%s', '%s', %d)", $form_state['values']['title'], $form_state['values']['value'], $image, $form_state['values']['image_title'], $form_state['values']['role']);
    // Reload the titles object from the database and bypass the cache.
    user_titles_get_titles(NULL, TRUE);
    drupal_set_message(t('Created new user title %title.', array('%title' => $form_state['values']['title'])));
    $form_state['redirect'] = 'admin/user/user-titles/add/title';
  }

  return;
}

/**
 * Page to edit a user title.
 * Redirects to either the add title form or the delete title form.
 *
 * @param $title
 *   A title object to edit or delete.
 */
function user_titles_edit_title_form($title) {
  if ($_POST['op'] == t('Delete') || $_POST['confirm']) {
    return drupal_get_form('user_titles_delete_title_form', $title);
  }
  if ($title) {
    return drupal_get_form('user_titles_add_title_form', $title);
  }
  return drupal_not_found();
}

/**
 * Confirm deletion of user title form.
 *
 * @param $title
 *   A title object to delete.
 */
function user_titles_delete_title_form(&$form_values, $title) {
  $form = array();
  $form['tid'] = array(
    '#type' => 'hidden',
    '#value' => $title->tid,
  );

  $form['title'] = array(
    '#type' => 'hidden',
    '#value' => $title->title,
  );

  $confirm_form = confirm_form($form,
    t('Are you sure you want to delete the user title: %title?', array('%title' => $title->title)),
    'admin/user/user-titles/titles',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel'));

  return $confirm_form;
}

/**
 * Submit function for the delete user titles form.
 */
function user_titles_delete_title_form_submit($form, &$form_state) {
  if ($form_state['values']['tid'] && is_numeric($form_state['values']['tid'])) {
    $success = db_query("DELETE FROM {user_titles} WHERE tid = %d", $form_state['values']['tid']);
  }

  if ($success) {
    drupal_set_message("User title '" . $form_state['values']['title'] . "' has been deleted successfully.", 'status');
    // Reload the titles object from the database and bypass the cache.
    user_titles_get_titles(NULL, TRUE);
  }
  else {
    drupal_set_message("Deletion of user title '" . $form_state['values']['title'] . "' has failed.", 'error');
  }

  $form_state['redirect'] = 'admin/user/user-titles/titles';
  return;
}

/**
 * Theme function for the user title settings form.
 *
 * @param $form
 *   The form array of the user titles settings form.
 * 
 * @return
 *   A string containing the html output for the user titles settings form.
 *
 * @ingroup themeable
 */
function theme_user_titles_settings_form($form) {
  // Properly format hook_module
  foreach ($form['settings']['hook_module']['#options'] as $module => $info) {
    if ($info['url']) {
      $name = l($info['name'], $info['url']);
    }
    else {
      $name = check_plain($info['name']);
    }
    // drupal_render uses this area, not the original
    $form['settings']['hook_module'][$module]['#title'] = '<strong>' . $name . '</strong><div class="description">' . $info['description'] . '</div>';
  }

  $output .= '<div class="settings">';
  $output .= drupal_render($form['settings']);
  $output .= '</div>';

  $rows = array();
  foreach (element_children($form['roles']) as $key) {
    if (isset($form['roles'][$key]['name'])) {
      $role = &$form['roles'][$key];

      $row = array();
      $row[] = drupal_render($role['name']);
      if (isset($role['weight'])) {
        $role['weight']['#attributes']['class'] = 'role-weight';
        $row[] = drupal_render($role['weight']);
      }
      $rows[] = array('data' => $row, 'class' => 'draggable');
    }
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('No roles available.')));
  }

  $header = array(t('Role'), t('Weight'));
  drupal_add_tabledrag('roles', 'order', 'sibling', 'role-weight');

  $output .= '<fieldset class="roles-table">';
  $output .= '<legend>' . t('Role priority') . '</legend>';
  $output .= drupal_render($form['roles-description']);
  $output .= theme('table', $header, $rows, array('id' => 'roles'));
  $output .= '</fieldset>';

  $output .= '<div class="clearer">&nbsp;</div>';
  $output .= drupal_render($form);
  return $output;
}

/**
 * Theme function for the user title settings form.
 *
 * @param $form
 *   The form array of the user titles titles form.
 * 
 * @return
 *   A string containing the html output for the user titles titles form.
 *
 * @ingroup themeable
 */
function theme_user_titles_titles_form($form) {
  drupal_add_js('misc/collapse.js');
  $output = '';
  $units = module_invoke(user_titles_get_hook_module(), 'user_titles', 'units');
  $header = array(
    array('data' => $units, 'class' => 'num-posts'),
    array('data' => t('Title'), 'class' => 'user-title'),
    array('data' => t('Image'), 'class' => 'user-title-image'),
    array('data' => t('Operations'), 'colspan' => 2),
  );

  foreach (element_children($form['roles']) as $rid) {
    $role = &$form['roles'][$rid];
    $rows = array();
    if (isset($role['titles'])) {
      foreach (element_children($form['roles'][$rid]['titles']) as $key) {
        // set a reference so that the drupal_render gets remembered.
        unset($elem);
        $elem = &$form['roles'][$rid]['titles'][$key];

        $rows[] = array(
          array('data' => drupal_render($elem['value']), 'class' => 'num-posts'),
          array('data' => drupal_render($elem['title']), 'class' => 'user-title'),
          array('data' => drupal_render($elem['image']), 'class' => 'user-title-image'),
          'edit' => l(t('edit'), "admin/user/user-titles/edit/title/" . $elem['tid']['#value']),
          'delete' => l(t('delete'), "admin/user/user-titles/delete/title/" . $elem['tid']['#value']),
        );
      }
    }
    if (empty($rows)) {
      $rows[] = array(array('data' => t('No titles set.'), 'colspan' => '5'));
    }

    $output .= '<fieldset class="collapsible collapsed title-table ' . $role['name']['#value'] . '">';
    $output .= '<legend>' . drupal_render($role['name']) . '</legend>';
    $output .= theme('table', $header, $rows);
    $output .= drupal_render($role['add_title']);
    $output .= '</fieldset>';
  }

  $output .= '<div class="clearer">&nbsp;</div>';
  $output .= drupal_render($form);
  return $output;
}

