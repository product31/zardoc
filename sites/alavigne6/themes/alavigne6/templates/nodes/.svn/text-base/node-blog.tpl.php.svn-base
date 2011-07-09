<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">

  <?php if ($page == 0): ?>
    <div class="clear-block">
      <h2 class="node-title">
        <a href="<?php print $node_url ?>"><?php print $title; ?></a>
      </h2>
    </div>
  <?php endif; ?>

  <?php if ($submitted): ?>
   <?php 
    $thisdate=$node->created; /*use strtotime() if necessary */
    $month=format_date($thisdate, 'custom', 'M' );
    $day=format_date($thisdate, 'custom', 'd' );
    $year=format_date($thisdate, 'custom', 'Y' );
    print "<div class=\"datebox\"><div class=\"month\">" . $month . "</div><div class=\"day\">" . $day . "</div><div class=\"year\">" . $year . "</div></div>";
  ?> 
  <?php endif; ?>
  <div class="blog-wrapper">
    <div class="content clear-block">
      <?php print $content; ?>
    </div>

    <?php if (!$hide_attribution && $submitted): ?>
        <div class="username"><?php print t('Posted by') .' '. theme('username', $node, TRUE) ?></div>
    <?php endif; ?>

    <?php if ($links): ?>
    <div class="links clear-block">
      <?php print $links; ?>
    </div>
    <?php endif; ?>
  </div>
</div>
