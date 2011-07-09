<?php
/**
 * For comments as nodes to work, we need to know in advance what node types
 * will be used as comments and theme them differently. In particular, pay
 * attention to the way the title is output. This tpl.php assumes a content
 * type called "comment".
 *
 * Important: This .tpl.php is also used for nodes of type "review".
 *
 */
 ?>

<div id="comment-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?>">
  <?php if ($subject): ?>
    <div class="clear-block">
      <h2 class="node-title title"><?php print $subject; ?></h2>
    </div>
  <?php endif; ?>

  <?php if ($parent_link): ?>
    <div class="comment-parent"><?php print $parent_link; ?></div>
  <?php endif; ?>

  <?php if ($submitted): ?>
    <span class="submitted"><?php print t('!date — !username', array('!username' => theme('username', $node), '!date' => format_date($node->created))); ?></span>
  <?php endif; ?>
  
  <div class="clear-block">
    <?php if (!$parent_link): ?> 
      <?php print $picture ?>
    <?php endif; ?>
  
    <div class="content">
      <?php print $content ?>
    </div>
    <?php if ($signature): ?>
    <div class="user-signature clear-block">
      <?php print $signature ?>
    </div>
    <?php endif; ?>
  </div>

  <div class="clear-block">
    <div class="meta">
    <?php if ($taxonomy): ?>
      <div class="terms"><?php print $terms ?></div>
    <?php endif;?>
    </div>

    <?php if ($links): ?>
      <div class="links clear-block"><?php print $links; ?></div>
    <?php endif; ?>
  </div>
</div>