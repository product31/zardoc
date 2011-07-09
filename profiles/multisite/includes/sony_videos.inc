<?php
/**
 * @file
 * Create our Videos section of the site.
 */
function sony_videos_info() {
  return array(
    'name' => st('Videos Section'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 0,
  );
}

/**
 * Required modules.
 */
function sony_videos_modules() {
  return array('menu', 'token', 'content', 'pathauto', 'sonybmg', 'emfield', 'emvideo', 'media_brightcove', 'feedapi', 'feedapi_eparser', 'feedapi_mapper', 'eparser_brightcove', 'filefield', 'imagefield', 'sony_video');
}

function sony_videos_task_list() {
  return array(
    /* We have a new video system. That integrates with brightcove.
     * We haven't created a default page yet (will probably be a view)
     * 'pages_videos_video_page' => array(
      'message' => st('Created default video page.'),
      'weight' => 0,
    ),*/
    'sony_videos_block' => array(
      'message' => st('Created default video block.'),
      'weight' => 0,
    ),
    'sony_videos_menu' => array(
      'message' => st('Created videos menu item.'),
      'weight' => 0,
    ),
    'sony_videos_content_type_video' => array(
      'message' => st('Created video content type.'),
      'weight' => 8,
    ),
    'sony_videos_configure_emvideo' => array(
      'message' => st('Configured emvideo.'),
      'weight' => 10,
    ),
  );
}

/**
 * Generate video page.
 *
function pages_videos_video_page() {
  $node = array(
    'type' => 'page',
    'title' => st('Videos'),
    'uid' => 3,
    'language' => 'en',
    'format' => 4,
    'path' => 'videos',
    'body' => pages_videos_default_video_content(),
  );
  $node = (object) $node;
  node_save($node);
}  
 */

/**
 * Our default video content.
 *
function pages_videos_default_video_content() {
  $output .= '<p align="left"><embed
  src="http://admin.brightcove.com/labs/badges/rssbadge.swf"
  bgcolor="#E6E6E4"
  flashVars="playerId=44170226&bgcolor=#E6E6E4&columns=4&
    rows=2&lineupId=44160818&openInNewWindow=true" name="flashObj"
  width="520"
  height="220"
  type="application/x-shockwave-flash"
  pluginspage="http://www.macromedia.com/shockwave/
    download/index.cgi?P1_Prod_Version=ShockwaveFlash">
  </embed>
  </p>
  <p>
  Click a video to play it</p>
  <p>
  <strong><a href="http://www.myplay.com/artists/justin-timberlake">Get codes to put our videos on your homepage or blog</a></strong>
  </p>';
  return $output;
}*/

/**
 * Create menu item.
 */
function sony_videos_menu() {
  $path = drupal_get_normal_path('videos');
  install_menu_create_menu_item($path, 'Videos', 'Videos', 'Primary Links');
}

/*
 * Create a default videos block with dummy content
 */
function sony_videos_block() {
  // TODO: Add install_get_format_id() to Install Profile API.
  //$input_format = install_get_format_id('Full HTML (unfiltered)');
  $input_format = 4;

  $video_block_delta = install_create_custom_block(
    '<div class="clear-block">' .
    '<div style="width: 275px; height: 226px; border: 1px solid black; margin: 10px; float: left;">Video</div>' .
    '</div>' .
    '<div class="more"><a class="more" href="/videos">More Videos</a></div>',
    'Front Videos', $input_format);

  variable_set('sonybmg_video_block', $video_block_delta);
  //install_add_block('block', $video_block_delta, $theme, $status, 4, 'content_bottom', 1, '<front>', $custom, $throttle);
}

function sony_videos_content_type_video() {
  $path = drupal_get_path('module', 'sonybmg');
  install_include(array('content_copy'));
  install_content_copy_import_from_file($path .'/node.video.inc');
}

function sony_videos_configure_emvideo() {
  // Enable brightcove
  variable_set('emfield_emvideo_allow_brightcove3', 1);
  variable_set('brightcove3_publisher_id', "59121");
  variable_set('brightcove3_player_id', "36696665001");
  variable_set('emvideo_brightcove3_token', "6eUYhfyQNKfGGwY1oxrb62z4Nd6FaYbq7DK2LmhpwFY.");
  // Enable youtube
  variable_set('emfield_emvideo_allow_youtube', 1);
  variable_set('emvideo_youtube_show_related_videos', 0);
  variable_set('emvideo_youtube_api_key', "");
  variable_set('emvideo_youtube_api_secret', "");
  variable_set('emvideo_youtube_show_colors', 0);
  variable_set('emvideo_youtube_show_border', 0);
  variable_set('emvideo_youtube_colors_color1', "#FFFFFF");
  variable_set('emvideo_youtube_colors_color2', "#CCCCCC");
}
