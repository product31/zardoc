<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">

  <?php if ($page == 0): ?>
      <h2 class="node-title">
        <a href="<?php print $node_url ?>"><?php print $title; ?></a>
      </h2>
  <?php endif; ?>
  
    <div class="content clear-block">
    
    <div class="artilceimage">
      <?php print theme('imagecache', '182x222', $node->field_mediaimage[0]['filepath']); ?>
      <h3 class="magtitle"><?php print $node->field_magtitle[0]['value']; ?></h3>
    </div>
      <h2><?php print $title; ?></h2>
      <?php print $body; ?>
    </div>



    <?php if ($links): ?>
    <div class="links clear-block">
      <?php print $links; ?>
    </div>
    <?php endif; ?>
  
</div>
