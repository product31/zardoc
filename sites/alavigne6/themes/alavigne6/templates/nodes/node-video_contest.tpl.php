<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">

  <?php if ($page == 0): ?>
    <div class="clear-block">
      <h2 class="node-title">
        <a href="<?php print $node_url ?>"><?php print $title; ?></a>
      </h2>
    </div>
  <?php endif; ?>

	<div class="back-button">
		<a href="/what-the-hell">WTH TV Videos</a> / <?php print $title; ?>
	</div>

  <div class="content clear-block">
    <?php print $content; ?>
  </div>

  <?php if ($links): ?>
  <div class="links clear-block">
    <?php print $links; ?>
  </div>
  <?php endif; ?>

</div>
