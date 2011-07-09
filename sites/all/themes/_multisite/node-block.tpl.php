<?php
/**
 * Node template for the block content type.  This is to be used with nodeblock
 * module. Eventhough this is a node template, the contents will be displayed as
 * the $block->content variable inside of block.tpl.php.  The node title is used
 * as $block->subject, so there is no need to output it here.
 */
?>
 
<?php print $content; ?>

<?php if ($links): ?>
  <div class="links clear-block">
    <?php print $links; ?>
  </div>
<?php endif; ?>
