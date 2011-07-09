<?php
// $Id$
/**
 * @file
 * Default theme function implementations for Sony Header module.
 */

/**
 * Theme a list of operations.
 *
 * This is generally just a list of links but could be ajax links or
 * some other listed operations.
 *
 * @param $items
 * A list of items.
 *
 * @ingroup themeable
 */
function theme_sony_header_operations($items) {

  $list = theme('item_list', $items);

  return '<div class="sony-header-operations">' .  $list . '</div>';
}

/**
 * Theme up our manage form so its a nice table.
 */
 
 
function theme_sony_header_admin_header_manage(&$form) {

  $i = 0;
  $rows = array();
  ctools_include('plugins');
  $plugins = ctools_get_plugins('sony_header', 'type');

  drupal_add_js(drupal_get_path('module', 'sony_header') . '/js/sony_header.admin.js');
  drupal_add_tabledrag('sony-header-items', 'order', 'sibling', 'item-weight');
  drupal_add_tabledrag('sony-header-items', 'match', 'parent', 'item-pid', 'item-pid', 'item-id', TRUE);
   
   $breadcrumb = sony_header_build_breadcrumb_for_header ($form['#header']);
   
  foreach (element_children($form['items']) as $key) {
	  
    $element = &$form['items'][$key];
    $item = $element['#item'];
    
    $element['tag_id']['#attributes']['class'] = 'item-id';
    $element['parent_id']['#attributes']['class'] = 'item-pid';
    $element['weight']['#attributes']['class'] = 'item-weight';
    $row = array();
    $row[] = '<span class="header-item-'.$element['type']['#value'].'">'.drupal_render($element['title']). '  ( '.$element['type']['#value'].' )</span>';
    //$row[] = drupal_render($element['type']);
	$row[] =  sony_header_return_link_text_values ($element['#item']);

    $ops = array();
	
	$ops[] = l('Edit', 'admin/build/sony_header/item/' . $item->tag_id . '/edit');
    $ops[] = l('Delete', 'admin/build/sony_header/item/' . $item->tag_id . '/delete');
	
    if ($plugins[$item->type]['container']) {
      $ops[] = l('Add Item', 'admin/build/sony_header/item/new', array(
        'query' => 'header_id=' . $item->header_id . '&parent_id=' . $item->tag_id));
    }
    $row[] = theme('sony_header_operations', $ops);

    $row[] = drupal_render($element['parent_id'])
      . drupal_render($element['tag_id'])
      . drupal_render($element['weight']);
    // moved down from line 52
    $row[] = drupal_render($element['type']);

    $row = array_merge(array('data' => $row), $element['#attributes']);
    $row['class'] = !empty($row['class']) ? $row['class'] . ' draggable' : 'draggable';
    $row['class'] .= $plugins[$item->type]['container'] ? '' : ' tabledrag-leaf';

    $rows[] = $row;
  }

  if (empty($rows)) {
    $rows[] = array(array(
      'data' => t('No flash header items found.'),
      'colspan' => 3,
    ));
  }

  $output = '';
  $output = $breadcrumb;
  $output .= drupal_render($form['new']);
  $output .= theme('table', array('Name', 'Content', 'Operations','','Type'), $rows, array('id' => 'sony-header-items'));
  $output .= drupal_render($form);
	
  return $output;
}

function theme_sony_header_item_name($item) {
 //$published = (!$item->attributes['publish_item'] && $item->type != 'item') ? 'unpublished' : 'published';
  $published = ($item->publish_item == 0 ) ? 'unpublished' : 'published';
  //l(t($user->name), 'user/'.$user->uid, array('attributes' => array('class' => 'link', 'id' => 'xxx', 'title' => 'Title'))); 
 
   if (!empty($item->id)) {
    $name = l($item->id, 'admin/build/sony_header/item/' . $item->tag_id . '/edit',  array('attributes' => array('class' => $published)));
  }
  else {
    $name = l($item->type . '-' . $item->tag_id, 'admin/build/sony_header/item/' . $item->tag_id . '/edit',  array('attributes' => array('class' => $published)));
  }

  return $name;
}

function theme_sony_header_flexi_file($element) {
  // We don't actually want this because its an array used to populate the sub elements and fieldset will
  // will try to just display it which will just look weird.
  unset($element['#value']);
  return theme_fieldset($element);
}

function sony_header_return_link_text_values ($item) {

  drupal_add_css(drupal_get_path('module', 'sony_header') . '/sony_header.admin.css');
   $published = ($item->publish_item) ? sony_header_build_markup ('Published', 'YES') : sony_header_build_markup ('Published','NO');
   //$dropshadow = ($item->attributes['dropshadow']== 'false'  || $item->attributes['dropshadow']== 0) ? sony_header_build_markup ('Dropshadow', t('No')): sony_header_build_markup ('Dropshadow',t('Yes'));
   $dropshadow = ($item->attributes['dropshadow'] == null || $item->attributes['dropshadow'] == 'false') ? sony_header_build_markup ('Dropshadow', t('No')): sony_header_build_markup ('Dropshadow', t('Yes'));
   $href = ($item->attributes['href']) ? sony_header_build_markup ('Link', $item->attributes['href']): sony_header_build_markup ('Link','None');
   $track = ($item->attributes['src']) ? sony_header_build_markup ('Track', $item->attributes['src']) : sony_header_build_markup ('Track','None');
   $tracking = ($item->attributes['tracking']) ? sony_header_build_markup ('Tracking', $item->attributes['tracking']): sony_header_build_markup ('Tracking',t('None'));  

  switch ($item->type) {
	  case 'textarea'  :
	    $content =  ($item->content) ? sony_header_build_markup ('Content', '<br/><div class="item-content">'. $item->content .'</div>') : sony_header_build_markup ('Content', t('No Content Entered'));
	    $output = $content . $dropshadow ;	
	    break;	  
	  case 'image'  :
	    $imageArray = sony_header_return_image_array($item);
	    $output = $href.$imageArray[0].$imageArray[1].$dropshadow.$tracking;	
	    break;	  
	  case 'track'  :
	    $output = $track;	
	    break;	  
	  case 'videoplayer'  :
	    $output = $track;
	    break;	  
	  case 'audioplayer'  :
	     $output = "";
	     break;
          case 'swf'  :
            $swf = ($item->attributes['src']) ? sony_header_build_markup ('SWF', $item->attributes['src']) : sony_header_build_markup ('SWF', 'None');
	    $output = $swf;
	    break;
	  case 'item'  :
	    $output = $tracking;
	    break;
   }
   $output = '<div class="flash-header-preview">'.$output.'</div>';
   return $output;
}