<?php
// $Id: media-brightcove-videos.tpl.php,v 1.1.2.1 2010/07/13 21:19:39 aaron Exp $

/**
 * @file
 * Theme template for Media: Brightcove files.
 *
 * Available variables:
 *  $div_id         // A unique CSS id.
 *  $classes        // An array of CSS class strings.
 *  $width          // The width of the videos.
 *  $height         // The height of the videos.
 *  $videos         // An array of video outputs.
 *  $output         // The full output to display.
 *  $options        // Various option overrides passed to the videos.
 */
?>
<div id="<?php print $div_id; ?>" class="<?php print implode(' ', $classes); ?>"><?php print $output; ?></div>
