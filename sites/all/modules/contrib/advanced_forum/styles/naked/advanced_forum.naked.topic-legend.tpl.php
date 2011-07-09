<?php
// $Id: advanced_forum.naked.topic-legend.tpl.php,v 1.1.2.2 2009/07/14 21:33:34 michellec Exp $

/**
 * @file
 * Theme implementation to show forum legend.
 *
 */
?>

<div class="forum-topic-legend clear-block">
  <div class="topic-icon-new"><?php print t('New posts'); ?></div>
  <div class="topic-icon-default"><?php print t('No new posts'); ?></div>
  <div class="topic-icon-hot-new"><?php print t('Hot topic with new posts'); ?></div>
  <div class="topic-icon-hot"><?php print t('Hot topic without new posts'); ?></div>
  <div class="topic-icon-sticky"><?php print t('Sticky topic'); ?></div>
  <div class="topic-icon-closed"><?php print t('Locked topic'); ?></div>
</div>
 
 