<a href="#" class="jqmClose"><em>Close</em></a>
<?php print theme('pluto_badge',$achievement,'large', FALSE); ?>
<div id="badge-left">
  <h2><?php print $achievement->name; ?></h2>
  <p><?php print $achievement->description; ?></p>
</div>

<div id="badge-right">
  <h2><?php print t('Get Your Own Rank!'); ?></h2>

  <?php
  global $user;
  if (!($user->uid)) { ?>
    <p><?php print t('Join now or Log in and start meeting new friends and earning points you can use for special prizes.'); ?></p>
    <?php  $block = module_invoke('user', 'block', 'view', 0);
    print $block['content'];
  } else { ?>
    <p><?php print t('<a href="!url">Learn more</a> about earning points you can use for special prizes.', array('!url' => url('membership'))); ?></p>
  <?php } ?>

</div>