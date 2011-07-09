<?php
// $Id: media-brightcove-video.tpl.php,v 1.1.2.1 2010/05/20 21:48:00 aaron Exp $

/**
 * @file
 * Theme template for Media: Brightcove files.
 *
 * Available variables:
 *  $div_id         // A unique CSS id.
 *  $classes        // An array of CSS class strings.
 *  $width          // The width of the video.
 *  $height         // The height of the video.
 *  $player_id      // The Brightcove player ID.
 *  $publisher_id   // The publisher ID.
 *  $video_id       // The Brightcove video ID.
 *  $full_size      // Whether to display the video as full size or preview.
 *  $output         // The full output to display.
 *  $availability   // Whether the video is available or not.
 *  $item           // The original field item.
 *  $autoplay       // Whether to autoplay or not.
 *  $options        // Various option overrides passed to the theme.
 */
?>
<div id="<?php print $div_id; ?>" class="<?php print implode(' ', $classes); ?>"><?php print $output; ?></div>