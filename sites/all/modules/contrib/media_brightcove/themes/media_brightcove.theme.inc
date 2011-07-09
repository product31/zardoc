<?php
// $Id: media_brightcove.theme.inc,v 1.1.2.6 2010/07/13 21:19:39 aaron Exp $

/**
 * @file
 * Theme functions for Media: Brightcove.
 */

function theme_media_brightcove_unavailable_message($message) {
  $message = filter_xss($message);
  return "<div class='media-youtube-status-unavailable'>$message</div>";
}

function template_preprocess_media_brightcove_videos(&$variables) {
  static $count = 0;

  $variables['videos'] = array();
  foreach($variables['video_ids'] as $id) {
    $variables['videos'][] = theme('media_brightcove_video', $id, $variables['width'], $variables['height'], $variables['options']);
  }
  $variables['classes'] = array('media-brightcove-playlist');
  $variables['output'] = theme('item_list', $variables['videos']);
  $variables['div_id'] = 'media-brightcove-'. ($count++);
}

/**
 * The embedded flash displaying the brightcove video.
 * Goes with theme_media_brightcove_video($video_id, $width = NULL, $height = NULL, $options = array());
 */
function template_preprocess_media_brightcove_video(&$variables) {
  static $count = 0;

  if ($variables['video_id']) {
    $variables['width'] = isset($variables['width']) ? $variables['width'] : (isset($variables['options']['width']) ? $variables['options']['width'] : media_brightcove_variable_get('default_width'));
    $variables['height'] = isset($variables['height']) ? $variables['height'] : (isset($variables['options']['height']) ? $variables['options']['height'] : media_brightcove_variable_get('default_height'));

    $variables['full_size'] = isset($variables['options']['full_size']) ? $variables['options']['full_size'] : media_brightcove_variable_get('full_size_default');

    $publisher_id = $variables['publisher_id'] ? $variables['publisher_id'] : (isset($variables['options']['field']['widget'][media_brightcove_variable_name('publisher_id')]) ? $variables['options']['field']['widget'][media_brightcove_variable_name('publisher_id')] : media_brightcove_variable_get('publisher_id'));
    $variables['publisher_id'] = check_plain($publisher_id);

    // Work out which player ID to use:
    $player_id = $variables['player_id'] ? $variables['player_id'] : NULL;
    if ($variables['full_size']) {
      $player_id = isset($player_id) ? $player_id : (isset($variables['options']['field']['widget'][media_brightcove_variable_name('full_player_id')]) ? $variables['options']['field']['widget'][media_brightcove_variable_name('full_player_id')] : media_brightcove_variable_get('full_player_id'));
    }
    else {
      $player_id = isset($player_id) ? $player_id : (isset($variables['options']['field']['widget'][media_brightcove_variable_name('preview_player_id')]) ? $variables['options']['field']['widget'][media_brightcove_variable_name('preview_player_id')] : media_brightcove_variable_get('preview_player_id'));
    }

    $variables['player_id'] = check_plain($player_id);
    $variables['video_id'] = check_plain($variables['video_id']);
    $variables['object_id'] = 'media-brightcove-video-'. ($count++);
    $variables['div_id'] = 'media-brightcove-'. ($count++);
    $variables['classes'] = array('media-brightcove');
    $variables['availability'] = TRUE;

    // Display a message if a video is currently unavailable.
    if (media_brightcove_variable_get('check_for_unavailable') && media_brightcove_echove_path() && !media_brightcove_video_available($variables['video_id']) && ($unavailable_message = media_brightcove_variable_get('status_display_unavailable'))) {
      $variables['availability'] = FALSE;
      $variables['output'] = theme('media_brightcove_unavailable_message', $unavailable_message);
    }
    else if (!empty($variables['publisher_id']) && !empty($variables['player_id'])) {
      // If SWFObject API is available, use it.
      if (function_exists('theme_swfobject_api')) {
        $url = 'http://c.brightcove.com/services/viewer/federated_f9/' . $variables['player_id'] . '?isVid=1&publisherID=' . $variables['publisher_id'];
        $params = array(
          'base' => 'http://admin.brightcove.com',
          'name' => 'flashObj',
          'width' => $variables['width'],
          'height' => $variables['height'],
          'seamlesstabbing' => 'false',
          'type' => 'application/x-shockwave-flash',
          'allowFullScreen' => 'true',
          'swLiveConnect' => 'true',
        );
        $vars = array(
          'videoId' => $variables['video_id'],
          'playerId' => $variables['player_id'],
        );
        $variables['output'] = theme('swfobject_api', $url, $params, $vars);
      }
      else {
        // @TODO: Tie this in.
        $autostart = $variables['options']['autoplay'] ? 'autoStart=true' : 'autoStart=false';
        $variables['output'] = <<<OUTPUT
<object id="{$variables['object_id']}" width="{$variables['width']}" height="{$variables['height']}" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=9,0,47,0"><param name="movie" value="http://c.brightcove.com/services/viewer/federated_f9/{$variables['player_id']}?isVid=1&isUI=1&publisherID={$variables['publisher_id']}" /><param name="bgcolor" value="#FFFFFF" /><param name="flashVars" value="videoId={$variables['video_id']}&playerID={$variables['player_id']}&domain=embed&" /><param name="base" value="http://admin.brightcove.com" /><param name="seamlesstabbing" value="false" /><param name="allowFullScreen" value="true" /><param name="swLiveConnect" value="true" /><param name="allowScriptAccess" value="always" /><embed src="http://c.brightcove.com/services/viewer/federated_f9/{$variables['player_id']}?isVid=1&isUI=1&publisherID={$variables['publisher_id']}" bgcolor="#FFFFFF" flashVars="videoId={$variables['video_id']}&playerID={$variables['player_id']}&domain=embed&" base="http://admin.brightcove.com" name="flashObj" width="{$variables['width']}" height="{$variables['height']}" seamlesstabbing="false" type="application/x-shockwave-flash" allowFullScreen="true" swLiveConnect="true" pluginspage="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash"></embed></object>
OUTPUT;
      }
    }
  }
  else {
    $variables['availability'] = FALSE;
    if ($unavailable_message = media_brightcove_variable_get('status_display_unavailable')) {
      $variables['output'] = theme('media_brightcove_unavailable_message', $unavailable_message);
    }
    else {
      $variables['output'] = '';
    }
  }
}
