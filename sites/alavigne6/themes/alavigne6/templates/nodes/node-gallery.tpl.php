<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">

<div class="back-button">
  <?php print (!empty($bc)) ? $bc : ' ' ; ?>
</div>

  <?php if ($page == 0): ?>
    <div class="clear-block">
      <h2 class="node-title">
        <a href="<?php print $node_url ?>"><?php print $title; ?></a>
      </h2>
    </div>
  <?php endif; ?>

  <div class="content-title">
    <h1><?php print $title; ?></h1>
    <span class="count"><?php print format_plural($photo_count, '1 Photo', '@count Photos'); ?></span>
  </div>

  <div class="photos">
    <?php print $photo_thumbs; ?>
  </div>


  <?php if ($links): ?>
  <div class="links clear-block">
    <?php print $links; ?>
  </div>
  <?php endif; ?>

</div>
