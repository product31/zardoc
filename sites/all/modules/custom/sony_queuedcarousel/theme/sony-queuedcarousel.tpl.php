<?php
/**
 * @file
 * Theme a queued carousel.
 *
 * Variables:
 *   - $carousel_id - The css ID of the carousel.
 *   - $queue - The queue object.
 *   - $panels - an array of rendered panels.
 */

?>
<div id="<?php print $carousel_id; ?>" class="queuedcarousel">
  <div class="queuedcarousel-nav-left ui-carousel-prev"></div>
  <ul class="queuedcarousel-wrapper">
  <?php print implode('', $panels); ?>
  </ul>
  <div class="queuedcarousel-nav-right ui-carousel-next"></div>
</div>