<div class="<?php print $comment_classes ?>">
  <?php if (!empty($new)): ?>
    <span class="new"><?php print $new; ?></span>
  <?php endif; ?>

  <h3 class="title"><?php print $title; ?></h3>
  <?php if ($picture) print $picture; ?>

  <div class="submitted"><?php print t('On !date !username says:', array('!date' => format_date($comment->timestamp, 'custom', 'F jS, Y'), '!username' => theme('username', $comment))) ?></div>
  <div class="content"><?php print $content; ?></div>
  <div class="links"><?php print $links; ?></div>

</div>
