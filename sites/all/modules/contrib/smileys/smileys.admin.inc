<?php
// $Id: smileys.admin.inc,v 1.1.2.6 2010/04/07 18:03:05 Gurpartap Exp $

function _smileys_check_filter() {
  $smileys_filter = FALSE;
  // Retrieve all input filters.
  foreach (filter_formats() as $format) {
    // Further retrieve all input formats.
    foreach (filter_list_format($format->format) as $filter) {
      // Check if any of the input formats have smileys filter enabled.
      if ($filter->module == 'smileys') {
        $smileys_filter = TRUE;
        break;
      }
    }
  }

  if (!$smileys_filter) {
    // Warn if smileys filter is not yet enabled for any input format.
    drupal_set_message(t('Smileys filter has not yet been enabled for any input formats. !link!', array('!link' => l(t('Take action'), 'admin/settings/filters'))), 'warning smileys-warning');
  }
}

function smileys_admin_settings() {
  _smileys_check_filter();
  
  $form = array();
  $form['smileys_selectbox'] = array(
    '#type' => 'fieldset',
    '#title' => t('Smileys select-box settings'),
  );
  $form['smileys_selectbox']['smileys_enable_for'] = array(
    '#type' => 'markup',
    '#value' => '<strong>'. t('Enable smileys select box for:') .'</strong>',
  );
  $form['smileys_selectbox']['smileys_enable_for_nodes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Nodes'),
    '#default_value' => variable_get('smileys_enable_for_nodes', 0),
  );
  $form['smileys_selectbox']['smileys_enable_for_comments'] = array(
    '#type' => 'checkbox',
    '#title' => t('Comments'),
    '#default_value' => variable_get('smileys_enable_for_comments', 0),
  );
  $form['smileys_selectbox']['smileys_node_types_content'] = array(
    '#type' => 'checkboxes',
    '#title' => t('On the following node types'),
    '#description' => t('Select the node types you want to enable Smileys select-box for.'),
    '#default_value' => variable_get('smileys_node_types_content', array()),
    '#options' => node_get_types('names'),
  );
  $form['smileys_selectbox']['smileys_select_box_expanded'] = array(
    '#type' => 'checkbox',
    '#title' => t('Expand select-box fieldset by default'),
    '#default_value' => variable_get('smileys_select_box_expanded', TRUE),
  );

  $form['smileys_widgetbox'] = array(
    '#type' => 'fieldset',
    '#title' => t('Smileys dialog window settings'),
  );
  $form['smileys_widgetbox']['smileys_enable_dialog'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Smileys dialog window'),
    '#description' => t('Adds a <em>[more...]</em> link to the end of smileys in select box, which when clicked, opens an inline widget to insert smileys. The widget is an inline popup like approach, allowing ease of usability.'),
    '#default_value' => variable_get('smileys_enable_dialog', TRUE),
  );
  $form['smileys_widgetbox']['smileys_dialog_titles'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Titles in dialog window'),
    '#description' => t('Groups smileys under their package name.'),
    '#default_value' => variable_get('smileys_dialog_titles', TRUE),
  );
  
  $form['smileys_widgetbox']['smileys_dialog_draggable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make the popup dialog draggable'),
    '#default_value' => variable_get('smileys_dialog_draggable', FALSE),
  );
  $form['smileys_widgetbox']['smileys_dialog_resizable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make the popup dialog resizable'),
    '#default_value' => variable_get('smileys_dialog_resizable', FALSE),
  );
  $form['smileys_widgetbox']['smileys_dialog_height']  = array(
    '#type' => 'textfield',
    '#title' => t('Dialog height (in pixels)'),
    '#description' => t('Enter a value between 200 and 650. Enter <em>0</em> for automatic height (recommended).'),
    '#size' => 5,
    '#required' => TRUE,
    '#default_value' => variable_get('smileys_dialog_height', 0),
  );
  $form['smileys_widgetbox']['smileys_dialog_width']  = array(
    '#type' => 'textfield',
    '#title' => t('Dialog width (in pixels)'),
    '#description' => t('Enter a value between 200 and 650.'),
    '#size' => 5,
    '#required' => TRUE,
    '#default_value' => variable_get('smileys_dialog_width', 400),
  );

  return system_settings_form($form);
}

function smileys_admin_list() {
  _smileys_check_filter();
  
  $path = drupal_get_path('module', 'smileys');
  drupal_add_js($path . '/scripts/admin/smileys-admin.js', 'module', 'header', FALSE, TRUE, FALSE);
  drupal_add_css($path . '/scripts/admin/smileys-admin.css', 'module', 'all', FALSE);

  $header = array(t('Smiley'), t('Visibility'), t('Acronyms'), t('Description'), t('Category'), t('Weight'));
  $rows = array();
  $packages = array();

  $categories = array('Miscellaneous' => 'Miscellaneous');
  $smileyp = db_query("SELECT DISTINCT package FROM {smileys} ORDER BY package");
  while ($pack = db_fetch_object($smileyp)) {
    $categories[$pack->package] = $pack->package;
  }
  ksort($categories);
  $categories = array_unique($categories);

  $output = '<form id="smileys-admin-form">';
  $smileyp = db_query("SELECT DISTINCT package FROM {smileys} ORDER BY package");
  while ($pack = db_fetch_object($smileyp)) {
    $packages[] = $pack->package;

    $select = '';
    foreach ($categories as $category) {
      $select .= '<option value="' . $category . '"' . ($category == $pack->package ? 'selected="selected"' : '') . '>' . $category . '</option>' . "\n";
    }

    $rows[] = array('data' => array(array('data' => '<span>' . $pack->package . '</span>', 'class' => 'category', 'colspan' => 7)), 'class' => 'category');

    $rows[] = array('data' => array(array('data' => '<em>' . t('No smileys in this category') . '</em>', 'colspan' => 7)), 'class' => "category-message category-populated category-" . str_replace(array('_', ' '), '-', drupal_strtolower($pack->package)) . "-message");

    $list = _smileys_list(1, " WHERE package = '$pack->package' ORDER BY weight");
    foreach ($list as $smiley) {
      $each_acronym = explode(' ', $smiley->acronyms);
      if ($smiley->promote_to_box == -1) {
        $promoted = '<span class="smiley-deselected" id="'. $smiley->id .'">&nbsp;</span>';
      }
      elseif ($smiley->promote_to_box == 0) {
        $promoted = '<span class="smiley-middle" id="'. $smiley->id .'">&nbsp;</span>';
      }
      elseif ($smiley->promote_to_box == 1) {
        $promoted = '<span class="smiley-selected" id="'. $smiley->id .'">&nbsp;</span>';
      }
      $acronyms = '';
      foreach ($each_acronym as $key => $eac) {
        $eac = str_replace("&lt;", "<", $eac);
        $eac = str_replace("&gt;", ">", $eac);
        $acronyms .= '<span style="color:'. ($key % 2 == 0 ? "#000000" : "#53616e") .';">'. check_plain($eac) .'</span>&nbsp;';
      }
      $rows[] = array(
        'data' => array(
          array(
            'data' => '<div class="nub">' .
          l(t('Edit'), 'admin/settings/smileys/edit/'. $smiley->id, array('attributes' => array('class' => 'edit', 'title' => t('Edit this smiley')))) .
          l(t('Delete'), 'admin/settings/smileys/delete/'. $smiley->id, array('attributes' => array('class' => 'delete', 'title' => t('Delete this smiley')))) .
          '</div>' .
          theme('image', check_url($smiley->image), check_plain($smiley->description), check_plain($smiley->description)),
          'class' => 'nub-td'),
          $promoted,
          $acronyms,
          check_plain($smiley->description),
          '<center><select id="edit-category" class="form-select smiley-category-select smiley-category-' . str_replace(array('_', ' '), '-', drupal_strtolower($pack->package)) . '" name="category">' . $select . '</select></center>',
          '<center><input style="text-align: center;" size="1" id="' . $smiley->id . '" class="smiley-weight" value="' . $smiley->weight . '"></input></center>',
        ),
        'class' => 'draggable',
      );
      $acronyms = '';
    }
  }

  $form['smileys'] = array(
    '#type' => 'markup',
    '#value' => theme('table', $header, $rows, array('id' => 'smileys_admin_list')),
  );
  $output .= drupal_render($form);

  foreach ($packages as $package) {
    drupal_add_tabledrag('smileys_admin_list', 'match', 'sibling', 'smiley-category-select', 'smiley-category-' . str_replace(array('_', ' '), '-', drupal_strtolower($package)), NULL, FALSE);
    drupal_add_tabledrag('smileys_admin_list', 'order', 'sibling', 'smiley-weight');      
  }

  if (count($rows) == 0) {
    if (module_exists('smileys_import')) {
      $msg = t('No smileys found. You may !add, or !import.', array('!add' => l(t('add a custom smileys'), 'admin/settings/smileys/add'), '!import' => l(t('import smiley packages'), 'admin/settings/smileys/import')));
    }
    else {
      $msg = t('No smileys found. You may !add, or install smileys_import module & import smiley packages.', array('!add' => l(t('add custom smileys'), 'admin/settings/smileys/add')));
    }
    drupal_set_message($msg);
    $output = '';
  }
  else {
    $output .= '<br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<i>'. t('Visibility Legend')
     . '</i><br /><span class="smiley-selected"></span>' . t('Visible on select box + popup')
     . '<br /><span class="smiley-middle"></span>' . t('Visible on only on popup i.e. "More Smileys"')
     . '<br /><span class="smiley-deselected"></span>' . t('Invisible (but not disabled)');
  }

  return $output . '</form>';
}

function smileys_category_handle($orig_name, $new_name) {
  if (!empty($orig_name) && !empty($new_name)) {
    db_query("UPDATE {smileys} SET package='%s' WHERE package='%s'", $new_name, $orig_name);
    exit;
  }
  else {
    drupal_access_denied();
    return;
  }
}

function smileys_promote_handle($action, $id = NULL) {
  if (!empty($id) && ($action == -1 || $action == 0 || $action == 1)) {
    db_query('UPDATE {smileys} SET promote_to_box=%d WHERE id=%d', $action, $id);
    exit();
  }
  else {
    drupal_access_denied();
    return;
  }
}

function smileys_weight_handle($weights, $ids, $categories) {
  $ids = explode(':', $ids);
  $weights = explode(':', $weights);
  $categories = explode(':', $categories);
  foreach ($ids as $key => $id) {
    db_query("UPDATE {smileys} SET package='%s', weight=%d WHERE id=%d", $categories[$key], $weights[$key], $id);
    $smileys[$id] = array('category' => $categories[$key], 'weight' => $weights[$key]);
  }
}

function smileys_admin_form($form_state, $edit) {
  $form = array();

  if ($edit['id']) {
    $form['id'] = array('#type' => 'hidden', '#value' => $edit['id']);
  }
  $categories = array('Miscellaneous' => 'Miscellaneous');
  $smileyp = db_query("SELECT DISTINCT package FROM {smileys} ORDER BY package");
  while ($pack = db_fetch_object($smileyp)) {
    $categories[$pack->package] = $pack->package;
  }
  ksort($categories);
  array_push($categories, '<New Category>');

  $form['acronyms'] = array('#type' => 'textfield', '#title' => t('Acronyms'), '#default_value' => $edit['acronyms'], '#size' => 16, '#maxlength' => 255, '#description' => t('Enter a list of shorthands for the smiley you wish to add, separated by spaces. e.g. \':) ;) :smile:\''));
  $form['image'] = array('#type' => 'textfield', '#title' => t('Image Path'), '#default_value' =>  $edit['image'], '#size' => 50, '#maxlength' => 255, '#description' => t('Enter the relative of the smiley-image relative to the root of your Drupal site. e.g. \'images/smileys/happy.png\'.'));
  $form['description'] = array('#type' => 'textfield', '#title' => t('Description'), '#default_value' => $edit['description'], '#size' => 50, '#maxlength' => 64, '#description' => t('A short description of the emotion depicted to be used as tooltip for the image. e.g. \'Laughing out loud\'.'));
  $form['category'] = array('#prefix' => '<div class="container-inline">', '#type' => 'select', '#title' => t('Category'), '#default_value' => $edit['package'], '#options' => array_unique($categories));
  $form['category_other'] = array('#suffix' => '</div>', '#type' => 'textfield', '#default_value' => t('Enter new category here'), '#size' => 20);
  $form['weight'] = array('#type' => 'weight', '#title' => t('Weight'), '#default_value' => ($edit['weight'] ? $edit['weight'] : 0),);
  $form['standalone'] = array('#type' => 'checkbox', '#title' => t('Stand-alone'), '#default_value' =>  $edit['standalone'], '#description' => t('When checked, the smiley will only be inserted when an acronym is found as a separate word. This is useful for preventing accidental smileys with short acronyms.'));
  $form['promote_to_box'] = array('#type' => 'radios', '#title' => t('Visibility'), '#default_value' =>  $edit['promote_to_box'], '#options' => array('0' => t('Visible on only on popup i.e. "More Smileys"'), '1' => t('Visible on select box + popup'), '-1' => t('Invisible (but not disabled)')), '#description' => t('When checked, the smiley will be shown on the <em>Smiley Select Box</em> in node and comment forms. Unchecked Smileys will be usable only in "<em>more...</em>" pop-up widget.'));
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
  if ($edit['id']) {
      $form['delete'] = array('#type' => 'submit', '#value' => t('Delete'), '#submit' => array('smileys_admin_form_delete'));
  }
  
  return $form;
}

/**
 * Implementation of hook_submit().
 */
function smileys_admin_form_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  $form_values['category'] = empty($form_values['category']) ? $form_values['category_other'] : $form_values['category'];

  if (isset($form_values['id'])) {
    db_query("UPDATE {smileys} SET acronyms='%s', image='%s', description='%s', standalone=%d, promote_to_box=%d, package='%s' WHERE id = %d", trim($form_values["acronyms"]), trim($form_values['image']), trim($form_values['description']), $form_values['standalone'], $form_values['promote_to_box'], $form_values['category'], $form_values['id']);
    $message = t('Updated smiley: %smiley', array('%smiley' => $form_values['acronyms']));
  }
  else {
    db_query("INSERT INTO {smileys} (acronyms, image, description, standalone, promote_to_box, package) VALUES ('%s', '%s', '%s', %d, %d, '%s')", trim($form_values["acronyms"]), trim($form_values["image"]), trim($form_values["description"]), $form_values["standalone"], $form_values['promote_to_box'], $form_values['category']);
    $message = t('Added smiley: %smiley', array('%smiley' => $form_values['acronyms']));
  }

  drupal_set_message($message);
  $form_state['redirect'] = 'admin/settings/smileys';
}

/**
 * Implementation of hook_validate().
 */
function smileys_admin_form_validate($form, &$form_state) {
  if (trim($form_state['values']['acronyms']) == '') {
    form_set_error('acronyms', t('Please enter an acronym for your smiley.'));
  }

  if ($form_state['values']['image'] == '') {
    form_set_error('image', t('Please enter the URL of the smiley image.'));
  }
}

function smileys_admin_form_delete($form, &$form_state) {
  smileys_admin_delete($form_state['values']['id'], FALSE);
  $form_state['redirect'] = 'admin/settings/smileys';
  return;
}

function smileys_admin_delete_confirm(&$form_state, $smiley_id) {
  $smiley_id = $smiley_id ? $smiley_id : arg(4);
  $smiley = db_fetch_array(db_query('SELECT * FROM {smileys} WHERE id = %d', $smiley_id));
  $form = array();
  
  return confirm_form(
    $form,
    t('Are you sure you want to delete the smiley %acronyms?', array('%acronyms' => $smiley['acronyms'])),
    'admin/settings/smileys',
    t(''),
    t('Delete'),
    t('Cancel'),
    'smileys_admin_delete');
}

function smileys_admin_delete_confirm_submit($form, &$form_state) {
  smileys_admin_delete($form_state['values']['id'], FALSE);
  $form_state['redirect'] = 'admin/settings/smileys';
}

function smileys_admin_delete($smiley_id, $redirect = TRUE) {
  $smiley_id = $smiley_id ? $smiley_id : arg(4);
  $smiley = db_fetch_array(db_query('SELECT * FROM {smileys} WHERE id = %d', $smiley_id));
  if ($smiley_id) {
    db_query("DELETE FROM {smileys} WHERE id = %d", $smiley_id);
    $message = t('Deleted smiley: %smiley', array('%smiley' => $smiley['acronyms']));
    drupal_set_message($message);
  }
  if ($redirect) {
    drupal_goto('admin/settings/smileys');
  }
}

function smileys_admin_add($smiley_id = NULL) {
  $path = drupal_get_path('module', 'smileys');
  drupal_add_js($path . '/scripts/admin/smileys-admin.js', 'module', 'header', FALSE, TRUE, FALSE);
  if ($smiley_id) {
    $smiley = db_fetch_array(db_query('SELECT * FROM {smileys} WHERE id = %d', $smiley_id));
  }
  return drupal_get_form('smileys_admin_form', $smiley);
}
