<?php
// $Id$
/**
 * @file
 *
 * Panels Administration callbacks.
 */

/**
 * Panel listing page callback.
 *
 * @param unknown_type $queue_id
 * @return unknown_type
 */
function sony_queuedcarousel_panel_list_page($queue_id) {
  $output = '';

  $queue = sony_queuedcarousel_queue_load($queue_id);

  $output .= drupal_get_form('sony_queuedcarousel_panel_list_form', $queue);

  return $output;
}

/**
 * Panel listing form callback.
 *
 * We have this as a form so we can manage weights.
 *
 * @param array $form_state
 * The FormAPI state array.
 * @param array $panels
 * An array of panels.
 * @return
 * FormAPI definition array.
 */
function sony_queuedcarousel_panel_list_form($form_state, $queue) {
  $form = array();

  $form['panels'] = array('#tree' => TRUE);

  foreach ($queue->panels as $id => $panel) {
    $form['panels'][$panel->pid] = array(
      '#panel' => $panel,
      'title' => array(
        '#type' => 'markup',
        '#value' => l($panel->title, 'admin/build/queuedcarousel/panel/' . $panel->pid . '/edit'),
      ),
      'weight' => array(
        '#type' => 'weight',
        '#delta' => 50,
        '#default_value' => isset($form_state[$id]['weight']) ? $form_state[$id]['weight'] : $panel->weight,
      ),
    );
  }

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Update order'),
  );

  return $form;
}

/**
 * Submit callback for panel listing form.
 *
 * @todo save new weight values.
 * @return
 * No return.
 */
function sony_queuedcarousel_panel_list_form_submit($form, &$form_state) {

  foreach ($form_state['values']['panels'] as $key => $element) {
    $panel = &$form['panels'][$key]['#panel'];
    if ($panel->weight != $element['weight']) {
      $panel->weight = $element['weight'];
      sony_queuedcarousel_panel_save($panel);
    }
  }
}

/**
 * Theme panel listing form.
 *
 * We use this theme function to add table dragging magic.
 * @ingroup themeable
 * @param array $form
 * FormAPI definition array.
 * @return
 * Fully rendered HTML string.
 */
function theme_sony_queuedcarousel_panel_list_form($form) {
  //
  drupal_add_tabledrag('sony-queuedcarousel-panels', 'order', 'sibling', 'item-weight');

  foreach (element_children($form['panels']) as $key) {
    $element = &$form['panels'][$key];
    $panel = $element['#panel'];

    $element['weight']['#attributes']['class'] = 'item-weight';

    $row = array();
    $row[] = drupal_render($element['title']);

    $ops = array();
    $ops[] = l('Edit', 'admin/build/queuedcarousel/panel/' . $panel->pid . '/edit');
    $ops[] = l('Delete', 'admin/build/queuedcarousel/panel/' . $panel->pid . '/delete');

    $row[] = implode(' | ', $ops);

    $row[] = drupal_render($element['weight']);

    $element['#attributes'] = empty($element['#attributes']) ? array() : $element['#attributes'];
    $row = array_merge(array('data' => $row), $element['#attributes']);
    $row['class'] = !empty($row['class']) ? $row['class'] . ' draggable' : 'draggable';

    $rows[] = $row;
  }

  if (empty($rows)) {
    $rows[] = array(array(
      'data' => t('No flash header items found.'),
      'colspan' => 3,
    ));
  }

  $output = '';
  $output .= theme('table', array('Name', 'Operations', ''), $rows, array('id' => 'sony-queuedcarousel-panels'));
  $output .= drupal_render($form);

  return $output;

}

function sony_queuedcarousel_panel_get_cache($queue_id) {

  ctools_include('object-cache');
  $queued_panel = ctools_object_cache_get('sony_queuedcarousel_panel', $queue_id);
  if (!$queued_panel) {
    $queued_panel = new stdClass();
    $queued_panel->display = panels_new_display();
    $queued_panel->display->layout = '';
    $queued_panel->queue_id = $queue_id;
    $queued_panel->pid = 'new';
    $queued_panel->did = 'new';
    $queued_panel->title = '';
    $queued_panel->name = '';
    $queued_panel->category = '';
    $queued_panel->weight = 0;
    $queued_panel->conf = array();
  }
  return $queued_panel;
}

function sony_queuedcarousel_panel_store_cache($queued_panel) {

  ctools_include('object-cache');
  ctools_object_cache_set('sony_queuedcarousel_panel', $queued_panel->queue_id, $queued_panel);
}

function sony_queuedcarousel_panel_clear_cache($queued_id) {

  ctools_include('object-cache');
  ctools_object_cache_clear('sony_queuedcarousel_panel', $queued_id);
}

/**
 * Provide a basic queuedcarousel addition form.
 *
 * @param unknown_type $form_state
 * @param unknown_type $queued_panel
 * @return unknown_type
 */
function sony_queuedcarousel_panel_add_form(&$form_state, $queue_id) {

  drupal_add_css(panels_get_path('css/panels_admin.css'));

  $form['#queued_panel'] = $queued_panel = sony_queuedcarousel_panel_get_cache($queue_id);

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );
  $form['settings']['title'] = array(
    '#type' => 'textfield',
    '#size' => 24,
    '#default_value' => $queued_panel->title,
    '#title' => t('Panel title'),
    '#description' => t('The title for this panel. If not set, some forms will be confusing and unusable.'),
  );

  $form['settings']['name'] = array(
    '#type' => 'textfield',
    '#size' => 24,
    '#default_value' => $queued_panel->name,
    '#title' => t('Panel name'),
    '#maxlength' => 32,
    '#required' => TRUE,
    '#description' => t('A unique name used to identify this panel page internally. It must be only be alpha characters and underscores. No spaces, numbers or uppercase characters.'),
  );

  // I don't really care about this ATM. I'm not sure I'm going to even expose these panels to other panels yet.
  $form['settings']['category'] = array(
    '#type' => 'value',
//    '#size' => 24,
    '#default_value' => $queued_panel->category,
//    '#title' => t('Panel category'),
//    '#description' => t("The category that this mini-panel will be grouped into on the Add Content form. Only upper and lower-case alphanumeric characters are allowed. If left blank, defaults to 'Mini panels'."),
  );

  ctools_include('dependent');
  $form['advanced'] = array(
    '#type' => 'checkbox',
    '#title' => t('Advanced'),
    '#default_value' => FALSE,
    '#description' => t('By enabling the advanced creation features you will be able to take advantage of the full panels administraion system. When disabled you will get a streamlined simple content addition form.'),
  );

  $form['layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout'),
    '#input' => TRUE, // trigger processing functions.
    '#prefix' => '<div class="form-item" id="edit-layout-wrapper">', '#suffix' => '</div>',
    '#process' => array('ctools_dependent_process'),
    '#dependency' => array('edit-advanced' => array(TRUE)),
  );

  panels_load_include('plugins');
  panels_load_include('common');
  $layouts = panels_common_get_allowed_layouts('sony_queuedcarousel');

  foreach ($layouts as $id => $layout) {
    $options[$id] = panels_print_layout_icon($id, $layout, check_plain($layout['title']));
  }

  drupal_add_js(panels_get_path('js/layout.js'));
  $form['layout']['layout'] = array(
    // Hack panels admin styles onto this.
    '#prefix' => '<div id="panels-choose-layout">',
    '#suffix' => '</div>',
    '#type' => 'radios',
    '#title' => t('Choose layout'),
    '#options' => $options,
    '#default_value' => in_array($queued_panel->display->layout, array_keys($layouts)) ? $queued_panel->display->layout : NULL,
  );

  $form['next'] = array(
    '#type' => 'submit',
    '#value' => t('Next'),
  );

  return $form;
}

/**
 * Validate submission of the queued carousel panel addition form.
 */
function sony_queuedcarousel_panel_add_form_validate($form, &$form_state) {

  // Test uniqueness of name:
  if (preg_match("/[^A-Za-z0-9_]/", $form_state['values']['name'])) {
    form_error($form['settings']['name'], t('Name must be alphanumeric or underscores only.'));
  }
  else {
    $query = "SELECT pid FROM {panels_queuedcarousel} WHERE name = '%s'";
    if (!empty($form_state['values']['pid']) && is_numeric($form_state['values']['pid'])) {
      $query .= ' AND pid != ' . $form_state['values']['pid'];
    }
    if (db_result(db_query($query, $form_state['values']['name']))) {
      form_error($form['settings']['name'], t('Panel name must be unique.'));
    }
  }

  if (preg_match("/[^A-Za-z0-9 ]/", $form_state['values']['category'])) {
    form_error($form['settings']['category'], t('Categories may contain only alphanumerics or spaces.'));
  }
}

/**
 * Process submission of the queued carousel panel addition form.
 */
function sony_queuedcarousel_panel_add_form_submit($form, &$form_state) {
  $queued_panel = $form['#queued_panel'];

  $queued_panel->title = $form_state['values']['title'];
  $queued_panel->name = $form_state['values']['name'];
  $queued_panel->category = empty($form_state['values']['category']) ? '' : $form_state['values']['category'];

  if ($form_state['values']['advanced']) {
    $queued_panel->display->layout = $form_state['values']['layout'];

    sony_queuedcarousel_panel_save($queued_panel);

    // Just go to the content addition form. They can handle things from there.
    $form_state['redirect'] = 'admin/build/queuedcarousel/panel/' . $queued_panel->pid . '/content';
  }
  else {
    // Simple will be just putting a single custom pane in a onecolumn display.
    $queued_panel->display->layout = 'onecol';

    // Stash the values so we can get them back on the simple form.
    sony_queuedcarousel_panel_store_cache($queued_panel);

    // Redirect to our simple form.
    $form_state['redirect'] = 'admin/build/queuedcarousel/manage/' . $queued_panel->queue_id . '/add/simple';
  }

}

function sony_queuedcarousel_panel_add_simple_form(&$form_state, $queue_id) {

  $queued_panel = sony_queuedcarousel_panel_get_cache($queue_id);
  if (!$queued_panel) {
    return drupal_not_found();
  }

  $form['#queued_panel'] = $queued_panel;
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
  );

  $form['css'] = array(
    '#type' => 'textarea',
    '#title' => t('CSS'),
  );

  $form['body']['content'] = array(
    '#type' => 'textarea',
    '#title' => t('Content'),
  );
  $form['body']['format'] = filter_form($conf['format'], 1, array('format'));

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function sony_queuedcarousel_panel_add_simple_form_submit(&$form, &$form_state) {

  $panel = $form['#queued_panel'];
  $display = &$panel->display;

  $title = $form_values['values']['title'];
  if (!$title) {
    $title = $panel->title;
  }

  panels_load_include('plugins');
  ctools_include('content');
  $content_type = ctools_get_content_type('custom');
  $subtype = ctools_content_get_subtype($content_type, 'custom');

  $pane = panels_new_pane('custom', 'custom');
  $pane->configuration = ctools_content_get_defaults($content_type, $subtype);
  $pane->panel = 'middle';
  $pane->pid = 'new-' . $panel->display->next_new_pid();
  $pane->configuration = array(
    'admin_title' => $title,
    'title' => $title,
    'body' => $form_state['values']['content'],
    'format' => $form_state['values']['filter'],
  );
  $panel->conf['css'] = $form_state['values']['css'];

  $display->panels[$pane->panel][] = $pane->pid;
  $display->content[$pane->pid] = $pane;

  sony_queuedcarousel_panel_save($panel);
  sony_queuedcarousel_panel_clear_cache($panel->queue_id);
  $form_state['redirect'] = 'admin/build/queuedcarousel/manage/' . $panel->queue_id;
}

/**
 * Page callback for editing panels.
 *
 * @param $pid
 * The panel id to be edited.
 * @return unknown_type
 */
function sony_queuedcarousel_panel_edit_page($pid) {
  $queued_panel = sony_queuedcarousel_panel_load($pid);

  return drupal_get_form('sony_queuedcarousel_panel_edit_form', $queued_panel);
}

function sony_queuedcarousel_panel_edit_form(&$form_state, $queued_panel) {
  //
  panels_load_include('common');
  panels_load_include('plugins');
  drupal_add_css(panels_get_path('css/panels_admin.css'));

  $form['pid'] = array(
    '#type' => 'value',
    '#value' => isset($queued_panel->pid) ? $queued_panel->pid : '',
  );

  $form['#queued_panel'] = $queued_panel;

  $form['right'] = array(
    '#prefix' => '<div class="layout-container">',
    '#suffix' => '</div>',
  );
  $form['left'] = array(
    '#prefix' => '<div class="info-container">',
    '#suffix' => '</div>',
  );

  $form['left']['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
  );
  $form['left']['settings']['title'] = array(
    '#type' => 'textfield',
    '#size' => 24,
    '#default_value' => $queued_panel->title,
    '#title' => t('Panel title'),
    '#description' => t('The title for this panel. If not set, some forms will be confusing and unusable.'),
  );

  $form['left']['settings']['name'] = array(
    '#type' => 'textfield',
    '#size' => 24,
    '#default_value' => $queued_panel->name,
    '#title' => t('Panel name'),
    '#maxlength' => 32,
    '#required' => TRUE,
    '#description' => t('A unique name used to identify this panel page internally. It must be only be alpha characters and underscores. No spaces, numbers or uppercase characters.'),
  );

  $form['left']['settings']['css'] = array(
    '#type' => 'textarea',
    '#default_value' => $queued_panel->conf['css'],
    '#title' => t('CSS'),
  );

  // I don't really care about this ATM. I'm not sure I'm going to even expose these panels to other panels yet.
  $form['left']['settings']['category'] = array(
    '#type' => 'value',
//    '#size' => 24,
    '#default_value' => $queued_panel->category,
//    '#title' => t('Panel category'),
//    '#description' => t("The category that this mini-panel will be grouped into on the Add Content form. Only upper and lower-case alphanumeric characters are allowed. If left blank, defaults to 'Mini panels'."),
  );

  ctools_include('context');
  $queued_panel->context = $queued_panel->display->context = ctools_context_load_contexts($queued_panel);

  $form['right']['layout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout'),
  );

  $layout = panels_get_layout($queued_panel->display->layout);

  $form['right']['layout']['layout-icon'] = array(
    '#value' => panels_print_layout_icon($queued_panel->display->layout, $layout),
  );

  $form['right']['layout']['layout-display'] = array(
    '#value' => check_plain($layout['title']),
  );
  $form['right']['layout']['layout-content'] = array(
    '#value' => theme('panels_common_content_list', $queued_panel->display),
  );

  $contexts = theme('panels_common_context_list', $queued_panel);
  if ($contexts) {
    $form['right']['context'] = array(
      '#type' => 'fieldset',
      '#title' => t('Contexts'),
    );

    $form['right']['context']['context'] = array(
      '#value' => $contexts,
    );
  }

  $label = (!empty($queued_panel->pid) && $queued_panel->pid == 'new') ? t('Save and proceed') : t('Save');
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $label,
  );

  return $form;
}

/**
 * Validate submission of the queued carousel panel edit form.
 */
function sony_queuedcarousel_panel_edit_form_validate($form, &$form_state) {
  // Test uniqueness of name:
  if (preg_match("/[^A-Za-z0-9_]/", $form_state['values']['name'])) {
    form_error($form['left']['settings']['name'], t('Name must be alphanumeric or underscores only.'));
  }
  else {
    $query = "SELECT pid FROM {panels_queuedcarousel} WHERE name = '%s'";
    if (!empty($form_state['values']['pid']) && is_numeric($form_state['values']['pid'])) {
      $query .= ' AND pid != ' . $form_state['values']['pid'];
    }
    if (db_result(db_query($query, $form_state['values']['name']))) {
      form_error($form['left']['settings']['name'], t('Panel name must be unique.'));
    }
  }

  if (preg_match("/[^A-Za-z0-9 ]/", $form_state['values']['category'])) {
    form_error($form['left']['settings']['category'], t('Categories may contain only alphanumerics or spaces.'));
  }
}

/**
 * Process submission of the queued carousel panel edit form.
 */
function sony_queuedcarousel_panel_edit_form_submit($form, &$form_state) {
  $queued_panel = $form['#queued_panel'];

  $queued_panel->title = $form_state['values']['title'];
  $queued_panel->name = $form_state['values']['name'];
  $queued_panel->category = empty($form_state['values']['category']) ? '' : $form_state['values']['category'];
  if (!is_array($queued_panel->conf)) {
    $queued_panel->conf = array();
  }
  $queued_panel->conf['css'] = $form_state['values']['css'];

  drupal_set_message(t('Your changes have been saved.'));
  sony_queuedcarousel_panel_save($queued_panel);
}

/**
 * Pass through for panels layout editor.
 *
 * @param $panel
 * Panel object or id.
 * @return
 * Return from panels_edit_layout().
 */
function sony_queuedcarousel_panel_edit_layout_page($panel) {
  if (!is_object($panel)) {
    $panel = sony_queuedcarousel_panel_load($panel);
  }

  $output = panels_edit_layout($panel->display, t('Save'), NULL, 'sony_queuedcarousel');
  if (is_object($output)) {
    $panel->display = $output;
    $panel->did = $output->did;
    sony_queuedcarousel_panel_save($panel);
    drupal_goto('admin/build/queuedcarousel/panel/' . $panel->pid . '/layout');
  }

  drupal_set_title(check_plain($panel->title));
  return $output;
}

function sony_queuedcarousel_panel_edit_content_page($panel) {
  if (!is_object($panel)) {
    $panel = sony_queuedcarousel_panel_load($panel);
  }
  ctools_include('context');
  // Collect a list of contexts required by the arguments on this page.
  $panel->display->context = $contexts = ctools_context_load_contexts($panel);

  panels_load_include('common');
  $content_types = panels_common_get_allowed_types('sony_queuedcarousel', $contexts);

  $output = panels_edit($panel->display, NULL, $content_types);
  if (is_object($output)) {
    $panel->display = $output;
    $panel->did = $output->did;
    sony_queuedcarousel_panel_save($panel);
    drupal_goto('admin/build/queuedcarousel/panel/' . $panel->pid . '/content');
  }
  // Print this with theme('page') so that blocks are disabled while editing a display.
  // This is important because negative margins in common block layouts (i.e, Garland)
  // messes up the drag & drop.
  drupal_set_title(check_plain($panel->title));
  print theme('page', $output, FALSE);
}

function sony_queuedcarousel_panel_edit_context_page($pid) {
  return "Contexts are black magic used to do awesome things we probably won't need right away so not implementing this yet.";
}

function sony_queuedcarousel_panel_delete_confirm(&$form_state, $panel) {
  if (!is_object($panel)) {
    $panel = sony_queuedcarousel_panel_load($panel);
  }
  $form['#panel'] = $panel;
  $form['#redirect'] = 'admin/build/queuedcarousel/manage/' . $panel->queue_id;
  return confirm_form($form,
    t('Are you sure you want to delete the panel "@title"?', array('@title' => $panel->title)),
    !empty($_GET['destination']) ? $_GET['destination'] : 'admin/build/queuedcarousel/manage/' . $panel->queue_id,
    t('This action cannot be undone.'),
    t('Delete'), t('Cancel')
  );
}

function sony_queuedcarousel_panel_delete_confirm_submit(&$form, &$form_state) {
  sony_queuedcarousel_panel_delete($form['#panel']);
}
