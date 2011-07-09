<?php
// $Id$

/**
 * @file
 * file_description
 */

/**
 * Called by sonybmg_default_panel_pages().
 */
function _sonybmg_default_panel_pages() {
  $page = new stdClass();
    $page->pid = 'new';
    $page->did = 'new';
    $page->name = 'Home';
    $page->title = 'Home';
    $page->access = array();
    $page->path = 'home';
    $page->load_flags = 0;
    $page->css_id = 'homepage';
    $page->css = '';
    $page->arguments = array();
    $page->relationships = array();
    $page->no_blocks = '1';
    $page->switcher_options = array();
    $page->menu = '0';
    $page->menu_tab = '0';
    $page->menu_tab_weight = '0';
    $page->menu_title = '';
    $page->menu_tab_default = '0';
    $page->menu_tab_default_parent_type = 'tab';
    $page->menu_parent_title = '';
    $page->menu_parent_tab_weight = '0';
  $page->contexts = array();
  $display = new panels_display();
  $display->did = 'new';
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'width_type' => 'px',
    'percent_width' => '960',
    'rows' => '2',
    'row_1' =>
    array(
      'columns' => '2',
      'width_1' => '620',
      'width_2' => '320',
      'names' =>
      array(
        0 => 'Top Left',
        1 => 'Top Right',
      ),
    ),
    'row_2' =>
    array(
      'columns' => '2',
      'width_1' => '400',
      'width_2' => '540',
      'names' =>
      array(
        0 => 'Left',
        1 => 'Right',
      ),
    ),
    'sidebars' =>
    array(
      'left' => 0,
      'left_width' => '',
      'right' => 0,
      'right_width' => '',
      'width_type' => 'px',
    ),
  );
  $display->panel_settings = array(
    'style' => 'default',
    'style_settings' =>
    array(
    ),
    'individual' => 0,
    'panel' =>
    array(
      'row_1_1' =>
      array(
        'style' => -1,
      ),
      'row_1_2' =>
      array(
        'style' => -1,
      ),
      'row_2_1' =>
      array(
        'style' => -1,
      ),
      'row_2_2' =>
      array(
        'style' => -1,
      ),
    ),
  );
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
      $pane->pid = 'new-1';
      $pane->panel = 'row_1_1';
      $pane->type = 'block';
      $pane->subtype = 'swfobject-1';
      $pane->access = array();
      $pane->configuration = array(
        'style' => 'default',
        'override_title' => 0,
        'override_title_text' => '',
        'css_id' => '',
        'css_class' => '',
        'module' => 'swfobject',
        'delta' => '1',
        'block_visibility' => 0,
        'block_settings' =>
        array(
          'swfobject_name_1' => 'Front Page Flash',
          'swfobject_swf_1_file' => '',
          'swfobject_swf_1_url' => '',
          'swfobject_id_1' => 'homeflash',
          'swfobject_width_1' => '600',
          'swfobject_height_1' => '250',
          'swfobject_version_1' => '8',
          'swfobject_bgcolor_1' => '#000000',
          'swfobject_provide_container_1' => 1,
          'swfobject_container_id_1' => 'homeflash-container',
          'swfobject_container_text_1' => '<a href="http://www.macromedia.com/go/getflashplayer">Get Flash Player</a>',
          'swfobject_wmode_1' => 'default',
          'swfobject_play_1' => 'default',
          'swfobject_loop_1' => 'default',
          'swfobject_menu_1' => 'default',
          'swfobject_quality_1' => 'default',
          'swfobject_scale_1' => 'default',
          'swfobject_flashvars_1' => '',
        ),
      );
    $display->content['new-1'] = $pane;
    $display->panels['row_1_1'][0] = 'new-1';
    $pane = new stdClass();
      $pane->pid = 'new-2';
      $pane->panel = 'row_1_2';
      $pane->type = 'block';
      $pane->subtype = 'block-4';
      $pane->access = array();
      $pane->configuration = array(
        'style' => 'default',
        'override_title' => 0,
        'override_title_text' => '',
        'css_id' => '',
        'css_class' => '',
        'module' => 'block',
        'delta' => '4',
        'block_visibility' => 0,
        'block_settings' =>
        array(
          'info' => 'Ad sidebar',
          'body' => '<div style="width: 300px; height: 280px; line-height: 280px; border: #999 solid 1px;">Sidebar Advertisement</div>',
          'format' => '4',
        ),
      );
    $display->content['new-2'] = $pane;
    $display->panels['row_1_2'][0] = 'new-2';
    $pane = new stdClass();
      $pane->pid = 'new-3';
      $pane->panel = 'row_2_1';
      $pane->type = 'views';
      $pane->subtype = 'news_blog-block_1';
      $pane->access = array();
      $pane->configuration = array(
        'style' => 'block',
        'override_title' => 0,
        'override_title_text' => '',
        'css_id' => '',
        'css_class' => '',
        'link_to_view' => 0,
        'more_link' => 0,
        'feed_icons' => 0,
        'use_pager' => 0,
        'pager_id' => '',
        'nodes_per_page' => '4',
        'offset' => '0',
        'panel_args' => 0,
        'args' => '',
        'url' => '',
      );
    $display->content['new-3'] = $pane;
    $display->panels['row_2_1'][0] = 'new-3';
    $pane = new stdClass();
      $pane->pid = 'new-4';
      $pane->panel = 'row_2_2';
      $pane->type = 'views';
      $pane->subtype = 'front_photos-block_1';
      $pane->access = array();
      $pane->configuration = array(
        'style' => 'block',
        'override_title' => 0,
        'override_title_text' => '',
        'css_id' => '',
        'css_class' => '',
        'link_to_view' => 0,
        'more_link' => 0,
        'feed_icons' => 0,
        'use_pager' => 0,
        'pager_id' => '',
        'nodes_per_page' => '3',
        'offset' => '0',
        'panel_args' => 0,
        'args' => '',
        'url' => '',
      );
    $display->content['new-4'] = $pane;
    $display->panels['row_2_2'][0] = 'new-4';
    $pane = new stdClass();
      $pane->pid = 'new-5';
      $pane->panel = 'row_2_2';
      $pane->type = 'block';
      $pane->subtype = 'block-1';
      $pane->access = array();
      $pane->configuration = array(
        'style' => 'block',
        'override_title' => 0,
        'override_title_text' => '',
        'css_id' => '',
        'css_class' => '',
        'module' => 'block',
        'delta' => '1',
        'block_visibility' => 0,
        'block_settings' =>
        array(
          'info' => 'Front Videos',
          'body' => '<div class="clear-block"><div style="width: 160px; height: 120px; border: 1px solid black; margin: 10px; float: left;">Video</div><div style="width: 160px; height: 120px; border: 1px solid black; margin: 10px; float: left;">Video</div><div style="width: 160px; height: 120px; border: 1px solid black; margin: 10px; float: left;">Video</div></div><p>Check out our <a href="/videos">new videos</a>!</p>',
          'format' => '4',
        ),
      );
    $display->content['new-5'] = $pane;
    $display->panels['row_2_2'][1] = 'new-5';
    $pane = new stdClass();
      $pane->pid = 'new-6';
      $pane->panel = 'row_2_2';
      $pane->type = 'block';
      $pane->subtype = 'sonybmg-12';
      $pane->access = array();
      $pane->configuration = array(
        'style' => 'block',
        'override_title' => 0,
        'override_title_text' => '',
        'css_id' => '',
        'css_class' => '',
        'module' => 'sonybmg',
        'delta' => '12',
        'block_visibility' => 0,
        'block_settings' =>
        array(
          'number_fans' => '8',
          'image_cache' => 'icon_large',
        ),
      );
    $display->content['new-6'] = $pane;
    $display->panels['row_2_2'][2] = 'new-6';
    $pane = new stdClass();
      $pane->pid = 'new-7';
      $pane->panel = 'row_2_2';
      $pane->type = 'block';
      $pane->subtype = 'poll-0';
      $pane->access = array();
      $pane->configuration = array(
        'style' => 'block',
        'override_title' => 0,
        'override_title_text' => '',
        'css_id' => '',
        'css_class' => '',
        'module' => 'poll',
        'delta' => '0',
        'block_visibility' => 0,
      );
    $display->content['new-7'] = $pane;
    $display->panels['row_2_2'][3] = 'new-7';
  $page->display = $display;
  $page->displays = array();

  return $page;
}
