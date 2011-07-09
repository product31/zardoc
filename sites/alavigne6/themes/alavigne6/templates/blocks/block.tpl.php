<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="block block-<?php print $block->module ?>">  
  <div class="blockinner clear-block">
    <?php if ($block->subject): ?>
    <h2 class="block-title title"><?php print $block->subject; ?></h2>
    <?php endif; ?>
    <div class="content">
      <?php print $block->content; ?>
    </div>
    <?php if (user_access('administer blocks') && $block->module == 'block'): ?>
      <?php
        $links = array(
          'sonybmg_edit' => array(
            'title' => t('Edit'), 
            'href' => 'admin/build/block/configure/' . $block->module . '/' . $block->delta, 
            'query' => drupal_get_destination(),
          ),
        );
        print theme('links', $links);
      ?>
    <?php endif; ?>
  </div>
</div>
