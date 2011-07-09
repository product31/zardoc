<?php
// $Id: 

/**
 * @file
 * Administrative page callbacks for sony share module.
 */

/**
 * Theming function for build a draggable sony share table.
 */
function theme_sony_share_drag_table($form) {
  $table = array();

  foreach (element_children($form['sony_share_show']) as $service_id) {
    $service = $form['sony_share_show'][$service_id];
    $col = array();

    $service['name'] = array('#value' => $service['#title']);
    $col[] = drupal_render($service['name']);

    $service['service'] = array('#value' => $service['#service']);
    $col[] = drupal_render($service['service']);

    $service['show'] = array(
      '#type' => 'checkbox',
      '#value' => $service['#default_value'],
      '#id' => $service['#id'],
      '#name' => $service['#name'],
    );
    $col[] = drupal_render($service['show']);

    $service['weight'] = $form['sony_share_weight'][$service_id];
    $service['weight']['#attributes']['class'] = 'service-weight';
    $col[] = drupal_render($service['weight']);

    $table['weights'][] = $service['#weight'];
    $table['rows'][] = array('data' => $col, 'class' => 'draggable');
  }

  if (empty($table['rows'])) {
    $table['rows'][] = array(array('data' => t('No service available.'), 'colspan' => '5'));
  }
  else {
    array_multisort($table['weights'], $table['rows']);
  }

  $table['header'] = array(t('Service Name'), t('Service Group'), t('Show'), t('Weight'));
  drupal_add_tabledrag('sony_share', 'order', 'sibling', 'service-weight');

  return theme('table', $table['header'], $table['rows'], array('id' => 'sony_share'));
}

/**
 * Menu callback administration settings for general options.
 */
function sony_share_admin_settings() {

  $form['where_to_show_the_links'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t("Show for content's type or category"),
    '#description' => t("Set the content's types or categories you want to display links for."),
  );
  $form['where_to_show_the_links']['sony_share_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#default_value' => variable_get('sony_share_node_types', array()),
    '#options' => array_map('check_plain', node_get_types('names')),
    '#attributes' => array('class' => 'container-inline'),
  );
  if (module_exists('taxonomy')) {
    $terms = _sony_share_get_terms();
    $count = count($terms);
    $form['where_to_show_the_links']['sony_share_category_types'] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#title' => t('Categories'),
      '#default_value' => variable_get('sony_share_category_types', array()),
      '#options' => $terms,
      '#size' => ($count > 10 ? 10 : $count),
    );
  }

  $form['places_to_show_the_links'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Places where show sony share'),
  );
  $form['places_to_show_the_links']['sony_share_in_links'] = array(
    '#type' => 'select',
    '#title' => t('sony share in links'),
    '#default_value' => variable_get('sony_share_in_links', SONY_SHARE_IN_BOTH),
    '#options' => array(
      SONY_SHARE_DISABLED => t('Disabled'),
      SONY_SHARE_IN_TEASER => t('Teaser view'),
      SONY_SHARE_IN_FULL => t('Full-page view'),
      SONY_SHARE_IN_BOTH => t('Teasers and full-page view')),
    '#description' => t('When display the services in the links section.'),
  );
  $form['places_to_show_the_links']['sony_share_in_node'] = array(
    '#type' => 'select',
    '#title' => t('sony share in nodes'),
    '#default_value' => variable_get('sony_share_in_node', SONY_SHARE_DISABLED),
    '#options' => array(
      SONY_SHARE_DISABLED => t('Disabled'),
      SONY_SHARE_IN_TEASER => t('Teaser view'),
      SONY_SHARE_IN_FULL => t('Full-page view'),
      SONY_SHARE_IN_BOTH => t('Teasers and full-page view')),
    '#description' => t('When display the services after the content text.'),
  );

  $form['how_to_show_the_links'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('How display sony share'),
  );
 $form['how_to_show_the_links']['sony_share_style'] = array(
    '#type' => 'select',
    '#title' => t('Choose a style'),
    '#default_value' => variable_get('sony_share_style', SONY_SHARE_STYLE_IMAGE),
    '#options' => array(
      SONY_SHARE_STYLE_TEXT => t('Only Text'),
      SONY_SHARE_STYLE_IMAGE => t('Only Image'),
      SONY_SHARE_STYLE_IMAGE_AND_TEXT => t('Image and Text')
    ),
  );
  $form['how_to_show_the_links']['sony_share_hide_if_unpublished'] = array(
    '#type' => 'checkbox',
    '#title' => t("Don't show links if the content is unpublished"),
    '#default_value' => variable_get('sony_share_hide_if_unpublished', 0),
  );
  $form['how_to_show_the_links']['sony_share_path_icons'] = array(
    '#type' => 'textfield',
    '#title' => t("Alternative icon's folder"),
    '#description' => t('If you have alternative icons write here the path from your index.php without trailing slash (b.e. %path1 or %path2)', array('%path1' => 'files/newicons', '%path2' => 'sites/all/files/newicons')),
    '#default_value' => sony_share_expand_path(NULL, 'icons'),
    '#size' => 40,
  );
  $form['how_to_show_the_links']['sony_share_label_in_node'] = array(
    '#type' => 'textfield',
    '#title' => t('Set a label for the section into the node'),
    '#default_value' => variable_get('sony_share_label_in_node', t('Bookmark/Search this post with')),
    '#size' => '40',
  );

  $form['extra_options'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Extra Options'),
  );
  $form['extra_options']['sony_share_new_window'] = array(
    '#type' => 'select',
    '#title' => t('Open link in...'),
    '#default_value' => variable_get('sony_share_new_window', 0),
    '#options' => array(0 => t('Same window'), 1 => t('New window')),
  );
  $form['extra_options']['sony_share_append_to_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Append the following text to your URL'),
    '#description' => t('This text will be inserted at the end of the current URL (b.e. %param => %url)', array('%param' => 'param1=value1&param2=value2', '%url' => 'http://domain.com/current-page&param1=value1&param2=value2')),
    '#default_value' => variable_get('sony_share_append_to_url', ''),
    '#size' => 40,
  );

  $form['short_links'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Short Links'),
  );
  $form['short_links']['sony_share_short_links_use'] = array(
    '#type' => 'select',
    '#title' => t('Use short links'),
    '#default_value' => variable_get('sony_share_short_links_use', 0),
    '#options' => array(
      SONY_SHARE_SHORT_URL_USE_NEVER => t('Never'),
      SONY_SHARE_SHORT_URL_USE_WHEN_REQUESTED => t('Only when requested'),
      SONY_SHARE_SHORT_URL_USE_ALWAYS => t('Always')),
  );
  if (variable_get('sony_share_short_links_use', 0) > 0) {
    $form['short_links']['sony_share_short_links_type'] = array(
      '#type' => 'select',
      '#title' => t('How generate short links'),
      '#default_value' => variable_get('sony_share_short_links_type', SONY_SHARE_SHORT_URL_TYPE_NODE),
      '#description' => t('If you select "Short URL," it will use the service selected with the <a href="@shorten">Shorten URLs module</a>. If you have not enabled the module, sony share will default to TinyURL.', array('@shorten' => 'http://drupal.org/project/shorten')),
      '#options' => array(
        SONY_SHARE_SHORT_URL_TYPE_NODE => t('Use node/xxx alias'),
        SONY_SHARE_SHORT_URL_TYPE_SERVICE => t('Use Short Url service'),
        SONY_SHARE_SHORT_URL_TYPE_REDIRECT_DOMAIN => t('Redirect only the Domain name'),
        SONY_SHARE_SHORT_URL_TYPE_REDIRECT_ALL => t('Combo: domain redirect and node/xxx alias')),
    );
    $form['short_links']['sony_share_domain_redirect'] = array(
      '#type' => 'textfield',
      '#title' => t('Domain to redirect'),
      '#description' => t('Write here the complete address without trailing slash (b.e. %name)', array('%name' => 'http://www.example.com') ),
      '#default_value' => variable_get('sony_share_domain_redirect', ''),
      '#size' => 40,
    );
    $form['#validate'][] = 'sony_share_admin_services_validate';
  }

  return system_settings_form($form);
}

/**
 * Check if domain address textbox is empty
 */
function sony_share_admin_services_validate($form, &$form_state) {
  if (isset($form_state['values']['sony_share_short_links_type']) && (int) $form_state['values']['sony_share_short_links_type'] > 2) {
    if (!$form_state['values']['sony_share_domain_redirect']) {
      form_set_error('sony_share_domain_redirect', t('Domain redirect address is not set.'));
    }
    if (preg_match("/\/$/", $form_state['values']['sony_share_domain_redirect'])) {
      form_set_error('sony_share_domain_redirect', t('No trailing slash!'));
    }
  }
}

/**
 * Menu callback administration settings for services links list.
 */
function sony_share_admin_services() {
  $settings = array();

  $services = sony_share_get_links(NULL, TRUE);
  $settings['show'] = variable_get('sony_share_show', NULL);
  $settings['weight'] = variable_get('sony_share_weight', NULL);

  $form['sony_share'] = array('#theme' => 'sony_share_drag_table');
  $form['sony_share']['sony_share_show'] = array('#tree' => TRUE);
  $form['sony_share']['sony_share_weight'] = array('#tree' => TRUE);

  foreach ($services as $service_id => $service) {
    $icon = isset($service['icon']) ? sony_share_expand_path($service['icon'], 'preset') : sony_share_expand_path("$service_id.png", 'preset');
    $weight = isset($settings['weight'][$service_id]) ? $settings['weight'][$service_id] : 0;

    $form['sony_share']['sony_share_show'][$service_id] = array(
      '#service' => ucwords(str_replace('_', ' ', $service['module'])),
      '#weight' => $weight,
      '#type' => 'checkbox',
      '#title' => theme('image', $icon) . " " . t('Show %name link', array('%name' => $service['name'])),
      '#return_value' => 1,
      '#default_value' => isset($settings['show'][$service_id]) ? $settings['show'][$service_id] : 0,
    );
    $form['sony_share']['sony_share_weight'][$service_id] = array(
      '#type' => 'weight',
      '#delta' => 100,
      '#default_value' => $weight,
    );
  }

  if (empty($services)) {
    drupal_set_message(t('You need to load at least one of XXX Services module, please enable them in <a href="@url">admin > modules</a> page', array('@url' => url('admin/build/modules'))), 'warning');
  }
  
  return system_settings_form($form);
}
