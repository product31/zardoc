<div class="node-navigation">
  <div class="node-nav-arrows">
    <?php if ($nav_array['prev']): ?>
      <a href="<?php print url('node/'. $nav_array['prev']) ?>" class="node-previous arrow"><?php print t('Previous') ?></a>
    <?php else: ?>
      <span class="node-previous-disabled arrow"><?php print t('Previous') ?></span>
    <?php endif; ?>

    <?php if ($nav_array['next']): ?>
      <a href="<?php print url('node/'. $nav_array['next']) ?>" class="node-next arrow"><?php print t('Next') ?></a>
    <?php else: ?>
      <span class="node-next-disabled arrow"><?php print t('Next') ?></span>
    <?php endif; ?>
  </div>

  <span class="node-pager-counter">
    <?php print t('!count of !total', array('!count' => (1 + $nav_array['current_index']), '!total' => count($nav_array['full_list']))) ?>
  </span>
</div>