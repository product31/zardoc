<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">
  <?php if ($page == 0): ?>
    <?php if (!$hide_attribution): ?>
      <div class="username"><?php print theme('username', $node) ?> Writes:</div>
    <?php endif; ?>
    <div class="clear-block">
      <div class="content-type">
        <?php print drupal_strtoupper($node->type); ?>
      </div>
      <h2 class="node-title title">
        <a href="<?php print $node_url ?>"><?php print $title; ?></a>
      </h2>
      <?php if ($node->field_photo[0]['filepath']): ?>
        <div class="photo">
          <?php //print theme('imagecache', 'icon_large', $node->field_photo[0]['filepath']); ?>
         <?php print theme('imagecache', 'icon_large', $node->field_photo[0]['filepath'], $node->field_photo[0]['data']['alt'], $node->field_photo[0]['data']['alt']); ?>
        </div>
      <?php endif; ?>
    </div>
  <?php else: ?>

<div class="back-button">
  <?php print (!empty($bc)) ? $bc : ' ' ; ?>
</div>

    <?php if ($node->field_photo[0]['filepath']): ?>
      <div class="photo">
         <?php print theme('imagecache', 'preview', $node->field_photo[0]['filepath'], $node->field_photo[0]['data']['alt'], $node->field_photo[0]['data']['alt']); ?>
      </div>
    <?php endif; ?>
		<div id="photo-data" class="clear-block">
    
	    <div class="photo-information">
                <div class="photo-title"><?php print check_plain($node->title); ?></div>
	      <div class="photo-description"><?php print $node->content['body']['#value']; ?></div>
	    <!--  <div class="photo-code">Photo code: < ?php print $node->nid; ?></div> -->
	    </div>
  
		</div>

    <div class="photo-upload clear-block">
      <?php // print theme('sonybmg_upload', 'photo'); ?>
    
      <div class="photo-attribution">
        <?php if ($photographer): ?>
        <div class="photographer">
          <?php print t('Photo by @photographer', array('@photographer' => $photographer)); ?>
        </div>
        <?php endif; ?>
    
        <?php if (!$hide_attribution && $submitted): ?>
            <div class="username"><?php print t('Posted by !username', array('!username' => theme('username', $node))); ?></div>
            <div class="submitted"><?php print format_date($node->created, 'large') ?></div> 
        <?php endif; ?>
       </div>
    </div>
  <?php endif; ?>
  
  <?php if ($links): ?>
    <div class="links clear-block">
      <?php print $links; ?>
    </div>
  <?php endif; ?>
</div>
