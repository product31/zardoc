<?php
// $Id$
/**
 * @file
 * Main header management page callbacks.
 */

/**
 * Manage header items.
 */
 
function sony_header_admin_header_manage($form_state, $header_id) {
  $form = array();

  $header = sony_header_load($header_id);
  if (!$header) {
    drupal_goto('admin/build/sony_header');
  }
  $form['#header'] = $header;
  drupal_add_css(drupal_get_path('module', 'sony_header') . '/sony_header.admin.css');
 
  // check to see if the user has permissions to add a new item
  if(user_access('add new item on manage page')){
  $form['new'] = array(
    '#type' =>	 'markup',
    '#value' => l('Add an item to '.$header->title.' ('.$header->language. ')', 'admin/build/sony_header/item/new', array('query' => 'header_id=' . $form['#header']->header_id, 'attributes' => array('id' => 'flash-header-new-link'))),
  );
  } 
  
  $form['items']['#tree'] = true;
  $items = _sony_header_admin_header_tree_flatten($header->items);

  foreach ($items as $id => $item) {

    $form['items'][$id] = array(
      '#item' => $item,
      'title' => array(
        '#value' => theme('indentation', $item->depth)
          . theme('sony_header_item_name', $item),
      ),
      'type' => array(
        '#value' => $item->type,
      ),
      'parent_id' => array(
        '#type' => 'hidden',
        '#default_value' => isset($form_state[$id]['parent_id']) ? $form_state[$id]['parent_id'] : $item->parent_id,
      ),
      'tag_id' => array(
        '#type' => 'hidden',
        '#value' => $id,
      ),
      'weight' => array(
        '#type' => 'weight',
        '#delta' => 50,
        '#default_value' => isset($form_state[$id]['weight']) ? $form_state[$id]['weight'] : $item->weight,
      ),
      '#attributes' => array(),
    );
  }

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function _sony_header_admin_header_tree_flatten($items, &$tree = array(), $depth = 0) {
  foreach ($items as $id => $item) {
    $tree[$id] = $item;
    $tree[$id]->depth = $depth;
    if (!empty($item->items)) {
      _sony_header_admin_header_tree_flatten($item->items, $tree, $depth + 1);
    }
  }
  return $tree;
}

function sony_header_admin_header_manager_validate($form, &$form_state) {
  // TODO validate that we're not moving items to parents that aren't valid.
}

function sony_header_admin_header_manage_submit($form, &$form_state) {

  foreach ($form_state['values']['items'] as $id => $values) {
    $item = $form['items'][$id]['#item'];
    $item->weight = $values['weight'];
    $item->parent_id = $values['parent_id'];
    sony_header_item_save($item);
  }
}

/**
 * FormAPI callback for header edit and creation.
 *
 * @param $form_state
 * FormAPI state variable.
 * @param $header_id
 * The id of the header. To create a new header, 'new' can be passed.
 * @return
 * FormAPI array
 */
function sony_header_admin_header_edit(&$form_state, $header_id) {
  $lang = variable_get('language_default', '');
  $form['#attributes']['enctype'] = 'multipart/form-data';

  if ($header_id == 'new') {
    $header = new stdClass();
    $header->title = '';
    $header->name = '';
    $header->language = $lang->language;
    $header->config_font = '';
    $header->config_css = '';
    $header->check_policy = FALSE;
    $header->embed_fonts = FALSE;
    $header->params = array(
      'width' => 960,
      'height' => 400,
    );
    $header->height = 400;
    $header->items = array();
  }
  else {
    $header = sony_header_load($header_id);
    if (!$header || !$header->header_id) {
      return drupal_access_denied();
    }
  }

  $form['#header'] = $header;
  $form['breadcrumb'] = array (
   '#type' => 'markup',
   '#value' => ($header_id == 'new')? sony_header_build_breadcrumb_for_header() : sony_header_build_breadcrumb_for_header($header),
   '#weight' => -16,
  );
  $form['title'] = array(
    '#title' => t('Title'),
    '#type' => 'textfield',
    '#default_value' => $header->title,
    '#required' => TRUE,
	 '#description' => t('Enter a title for this Flash Header Instance.'),
	 '#weight' => -15,
  );
  $regions = sony_header_return_regions();  
  $form['name'] = array(
        '#type' => 'select',
    '#title' => t('Block Name'),
    '#required' => 1,
    '#options' => $regions,
    '#default_value' => isset($header->name) ? $header->name : 'flash_header',
        '#description' => t('Assign this Flash header to a block region.'),
  );
  $form['language'] = array(
  '#type' => 'select',
  '#title' => t('Language'),
  '#required' => 1,
  '#options' => locale_language_list(),
  '#default_value' => isset($header->language) ? $header->language : $lang->language,
  '#description' => t('Select a language.'),
);

  $form['params'] = array(
    '#type' => 'fieldset',
    '#title' => t('Flash params'),
    '#tree' => TRUE,
  );
  $form['params']['width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#default_value' => isset($header->params['width']) ? $header->params['width'] : 960,
    '#size' => 10,
    '#required' => TRUE,
    '#description' => t('The width of the header in either pixels or percent. For pixels, enter just the number, like <em>600</em> for 600 pixels. For percentages, make sure to include the percent sign (%), like <em>100%</em>.'),
  );
  $form['params']['height'] = array(
    '#title' => t('Height'),
    '#type' => 'textfield',
    '#default_value' => isset($header->params['height']) ? $header->params['height'] : 400,
    '#size' => 10,
    '#required' => TRUE,
    '#description' => t('The height of the header in either pixels or percent. For pixels, enter just the number, like <em>600</em> for 600 pixels. For percentages, make sure to include the percent sign (%), like <em>100%</em>.'),
  );
  $form['params']['bgcolor'] = array(
    '#type' => 'textfield',
    '#title' => t('Background color'),
    '#default_value' => isset($header->params['bgcolor']) ? $header->params['bgcolor'] : '#000000',
    '#size' => 10,
    '#maxlength' => 7,
    '#required' => TRUE,
  );
  $form['params']['transparent'] = array(
    '#type' => 'checkbox',
    '#title' => t('Transparent'),
    '#default_value' => ($header->params['transparent']) ? ($header->params['transparent']) : TRUE ,
  );
  $form['css_path'] = array(
    '#title' => t('CSS path'),
    '#type' => 'sony_header_flexi_file',
    '#default_value' => $header->config_css,
    '#source' => 'css_path',
    '#required' => FALSE,
    '#file_type' => 'css',
    '#file_types' => 'css',
  );
  $form['font_path'] = array(
    '#title' => t('Font path'),
    '#type' => 'sony_header_flexi_file',
    '#default_value' => $header->config_font,
    '#source' => 'font_path',
    '#required' => FALSE,
    '#file_type' => 'swf',
    '#file_types' => 'swf',
  );
  $form['check_policy'] = array(
    '#title' => t('Check Policy'),
    '#type' => 'checkbox',
    '#default_value' => $header->check_policy,
    '#description' => t("When using images who's source is not local to the header swf, it's sometimes necessary to have a <em>local</em> crossdomain.xml file manualy checked by the flash prior to certain events. This attribute triggers this security check."),
  );
  $form['embed_fonts'] = array(
    '#title' => t('Embed Fonts'),
    '#type' => 'checkbox',
    '#default_value' => $header->embed_fonts,
  );
  $form['alternate_content'] = array(
    '#type' => 'textarea',
    '#title' => t('Alternate content'),
    '#default_value' => $header->alternate_content,
    '#description' => t('This is the html content to be replaced by the flash. This is the content that will be spidered by the search engines, similar to alt text for an image.'),
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit callback for header edit form.
 */
function sony_header_admin_header_edit_submit($form, &$form_state) {
  _sony_header_include('file');

  $header = drupal_clone($form['#header']);
  $header->title = $form_state['values']['title'];
  $header->name = $form_state['values']['name'];
  $header->language = $form_state['values']['language'];
  $header->params = $form_state['values']['params'];

  $header->config_css = sony_header_flexi_file_submit(
    $form['css_path'],
    $form_state['values']['css_path'],
    $header->config_css);
  $header->config_font = sony_header_flexi_file_submit(
    $form['font_path'],
    $form_state['values']['font_path'],
    $header->config_font);

  $header->check_policy = (bool) $form_state['values']['check_policy'];
  $header->embed_fonts = (bool) $form_state['values']['embed_fonts'];
  $header->alternate_content = $form_state['values']['alternate_content'];

  sony_header_save($header);

  if (isset($form['#header']->header_id)) {
    // If editing, go back to listing page.
    $form_state['redirect'] = 'admin/build/sony_header';
  }
  else {
    // If its a new item, then redirect to the management page.
    $form_state['redirect'] = 'admin/build/sony_header/' . $header->header_id . '/manage';
  }
}

/**
 * Form callback for header delete page.
 */
function sony_header_admin_header_delete(&$form_state, $header_id) {

  $form = array();
  $form['#redirect'] = 'admin/build/sony_header';

  $header = sony_header_load($header_id);
  $form['#header'] = $header;
  $form['breadcrumb'] = array (
   '#type' => 'markup',
   '#value' => ($header)? sony_header_build_breadcrumb_for_header($header) : sony_header_build_breadcrumb_for_header(),
   '#weight' => -16,
  );
  $msg = '<p>' .
    t('Deleting %name will delete the header and all of its items. This can not be undone. Are you sure you want to do this?', array(
      '%name' => $header->name)) .
    '</p>';

  return confirm_form($form,
    t('Are you sure you want to delete %name', array('%name' => $header->name)),
    'admin/build/sony_header',
    $msg,
    t('Delete'),
    t('Cancel'));
}

/**
 * Submit callback for header delete page.
 */
function sony_header_admin_header_delete_submit($form, &$form_state) {
  sony_header_delete($form['#header']->header_id);
}

/**
 * Function callback to display file dirtectory images.
 */
function sony_header_admin_header_list_files(){
 $path=file_directory_path();// change the path here related to this page
 $base = base_path();
 $handle=opendir($path);
 $output ='';
 while (($file = readdir($handle))!==false) {
 if(strlen($file)>3 && image_get_info($path.'/'.$file)){
 $output .= "<div style=\"display:inline-block; position: relative; margin: 10px;\"><strong>$base$path/$file :</strong><img style=\"display:block; position: relative;max-width:  250px;\"src=$base$path/$file></div>";}
 }
 closedir($handle);
 return $output;
}