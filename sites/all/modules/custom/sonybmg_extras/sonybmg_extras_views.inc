<?php
/**
 * Expose default views for Extras page.
 */
function sonybmg_extras_views_default_views() {
  return array(
    'buddy_icons' => _sonybmg_extras_views_default_views_buddy_icons(),
    'wallpaper' => _sonybmg_extras_views_default_views_wallpaper(),
  );
}

/**
 * buddy_icons: List our buddy icons.
 */
function _sonybmg_extras_views_default_views_buddy_icons() {
  $view = new view;
  $view->name = 'buddy_icons';
  $view->description = 'Buddy icons';
  $view->tag = 'sonybmg_extras';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Buddy Icons', 'default');
  $handler->override_option('fields', array(
    'field_buddy_icon_fid' => array(
      'label' => '',
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'thumbnail_default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_buddy_icon_fid',
      'table' => 'node_data_field_buddy_icon',
      'field' => 'field_buddy_icon_fid',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'created' => array(
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'buddy_icon' => 'buddy_icon',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'status' => array(
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'value' => '1',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
    'role' => array(),
    'perm' => '',
  ));
  $handler->override_option('title', 'Buddy Icons');
  $handler->override_option('header_format', '1');
  $handler->override_option('footer', 'Click on an icon to automatically set as your Buddy Icon. If you can\'t set your Buddy Icon automatically, please follow these steps:

        <ol>
        <li>Save an icon to your desktop.</li>
        <li>From the "My AIM" menu, click "Edit Options" and then "Edit Preferences."</li>
        <li>In the Category group click "Expressions."</li>
        <li>Choose "Browse PC" and select the saved image.</li>
        <li>Click OK.</li>
        </ol>');
  $handler->override_option('footer_format', '1');
  $handler->override_option('empty', 'No buddy icons found.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('use_pager', TRUE);
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'type' => 'ul',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'extras/buddy_icons');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('items_per_page', 0);
  $handler->override_option('use_pager', '0');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);

  $views[$view->name] = $view;

  return $view;
}

/**
 * wallpaper: Display listing of wallpaper.
 */
function _sonybmg_extras_views_default_views_wallpaper() {
  $view = new view;
  $view->name = 'wallpaper';
  $view->description = 'Display listing of wallpaper';
  $view->tag = 'sonybmg_extras';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'field_wallpaper_fid' => array(
      'label' => '',
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'thumbnail_default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_wallpaper_fid',
      'table' => 'node_data_field_wallpaper',
      'field' => 'field_wallpaper_fid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'created' => array(
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'wallpaper' => 'wallpaper',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'status' => array(
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'value' => '1',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
    'role' => array(),
    'perm' => '',
  ));
  $handler->override_option('title', 'Desktop Wallpaper');
  $handler->override_option('header', 'Click on the desired screen size to open the image. For PCs, right-click on the image to download. For Macs, control-click to download.');
  $handler->override_option('header_format', '1');
  $handler->override_option('footer_format', '1');
  $handler->override_option('empty', 'No wallpaper found.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', '9');
  $handler->override_option('use_pager', TRUE);
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'type' => 'ul',
  ));
  $handler->override_option('row_plugin', 'node');
  $handler->override_option('row_options', array(
    'teaser' => 1,
    'links' => 1,
    'comments' => 0,
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'extras/wallpaper');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('items_per_page', '6');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);

  $views[$view->name] = $view;
  return $view;
}
