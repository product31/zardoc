<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">

    <div class="clear-block">
      <?php if (!$is_front) { ?>
      <h2 class="node-title title">
        <?php print t("Why I'm A Fan And You Should Be Too"); ?>:
      </h2>
      <?php } ?>
    </div>
  
  <div class="content clear-block">
  
  <?php if ($picture) print $picture; ?>
  
  <div class="username"><?php print theme('username', $node) ?> <?php print t('Writes'); ?>:</div>
  
    <?php print $content; ?>
    
  </div>
  
  <?php if ($links): ?>
    <div class="links clear-block">
      <?php print $links; ?>
    </div>
  <?php endif; ?>
</div>
