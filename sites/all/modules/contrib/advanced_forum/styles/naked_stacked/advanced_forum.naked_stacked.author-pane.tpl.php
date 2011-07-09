<?php
// $Id: advanced_forum.naked_stacked.author-pane.tpl.php,v 1.1.2.3 2009/07/15 02:54:05 michellec Exp $

/**
 * @file
 * Theme implementation to display information about the post/profile author.
 *
 * See author-pane.tpl.php in Author Pane module for a full list of variables.
 */
?>

<div class="author-pane clear-block">
 <div class="author-pane-inner">
    <?php /* Avatar (has div in variable) */ ?>
    <?php if (!empty($picture)): ?>
      <?php print $picture; ?>
    <?php endif; ?>

    <?php /* General section */ ?>
    <div class="author-pane-section author-pane-section-1">
      <?php /* Account name */ ?>
      <div class="author-pane-line author-name"> 
        <?php print $account_name; ?> 
      </div>

      <?php /* Online status */ ?>
      <?php if (!empty($online_status)): ?>
        <div class="author-pane-line <?php print $online_status_class ?>">
           <?php print $online_status; ?>
        </div>
      <?php endif; ?>

      <?php /* User title */ ?>
      <?php if (!empty($user_title)): ?>
        <div class="author-pane-line author-title"> 
          <?php print $user_title; ?> 
        </div>
      <?php endif; ?>
      
      <?php /* User badges */ ?>
      <?php if (!empty($user_badges)): ?>
        <div class="author-pane-line author-badges"> 
          <?php print $user_badges; ?> 
        </div>
      <?php endif; ?>
    </div>

    <div class="author-pane-section author-pane-section-2">
      <?php /* Location */ ?>
      <?php if (!empty($location)): ?>
        <div class="author-pane-line author-location"> 
          <?php print $location;  ?> 
        </div>
      <?php endif; ?>
      
      <?php /* Joined */ ?>
      <?php if (!empty($joined)): ?>
        <div class="author-pane-line author-joined">
          <span class="author-pane-label"><?php print t('Joined'); ?>:</span> <?php print $joined; ?>
        </div>
      <?php endif; ?>

      <?php /* Posts */ ?>
      <?php if (isset($user_stats_posts)): ?>
        <div class="author-pane-line author-posts">
          <span class="author-pane-label"><?php print t('Posts'); ?>:</span> <?php print $user_stats_posts; ?>
        </div>
      <?php endif; ?>

      <?php /* Points */ ?>
      <?php if (isset($userpoints_points)): ?>
        <div class="author-pane-line author-points">
          <span class="author-pane-label"><?php print t('!Points', userpoints_translation()); ?></span>: <?php print $userpoints_points; ?>
        </div>
      <?php endif; ?>
    </div>

    <?php /* Contact section */ ?>
    <div class="author-pane-section author-pane-contact">
      <?php /* Contact / Email */ ?>
      <?php if (!empty($contact_link)): ?>
        <div class="author-pane-line author-contact">
          <?php print $contact_link; ?>
        </div>
      <?php endif; ?>

      <?php /* Private message */ ?>
      <?php if (!empty($privatemsg)): ?>
        <div class="author-pane-line author-privatemsg">
          <?php print $privatemsg_link; ?>
        </div>
      <?php endif; ?>

      <?php /* User relationships */ ?>
      <?php if (!empty($user_relationships_api_link)): ?>
        <div class="author-pane-line author-user-relationship">
          <?php print $user_relationships_api_link; ?>
        </div>
      <?php endif; ?>
      
      <?php /* Flag friend */ ?>
      <?php if (!empty($flag_friend)): ?>
        <div class="author-pane-line">
          <?php print $flag_friend; ?>
        </div>
      <?php endif; ?>
    </div>

    <?php /* Admin section */ ?>
    <div class="author-pane-section author-pane-admin">
      <?php /* IP */ ?>
      <?php if (!empty($user_stats_ip)): ?>
        <div class="author-pane-line author-ip">
          <span class="author-pane-label"><?php print t('IP'); ?>:</span> <?php print $user_stats_ip; ?>
        </div>
      <?php endif; ?>

     <?php /* Fasttoggle block */ ?>
     <?php if (!empty($fasttoggle_block_author)): ?>
        <div class="author-fasttoggle-block"><?php print $fasttoggle_block_author; ?></div>
      <?php endif; ?>

     <?php /* Troll ban */ ?>
      <?php if (!empty($troll_ban_author)): ?>
        <div class="author-pane-line author-troll-ban"><?php print $troll_ban_author; ?></div>
      <?php endif; ?>        
    </div>    
  </div>
</div>
