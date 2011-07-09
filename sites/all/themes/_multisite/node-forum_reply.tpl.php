<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">
  <div class="forum-post clear-block">
    <div class="user-info">
      <?php print $picture ?>
      <div class="user-title">
        <?php print $user_title; ?>
      </div>
      <div class="user-since">
        <strong><?php print t('Joined') . ': ' . $user_since; ?></strong>
      </div>
      <?php if (isset($user_posts)): ?>
        <div class="user-posts">
          <strong><?php print t('Posts') . ': ' . $user_posts; ?></strong>
        </div>
      <?php endif; ?>
      <?php if ($user_city): ?>
      <div class="user-city">
        <?php print $user_city; ?>
      </div>
      <?php endif; ?>
      <?php if ($user_country): ?>
      <div class="user-country">
        <?php print $user_country; ?>
      </div>
      <?php endif; ?>
    </div>

    <a name="comment-<?php print $node->nid; ?>"></a>
      
    <?php if ($submitted): ?>
      <div class="submitted"><?php print format_date($node->created, 'large') ?></div> 
    <?php endif; ?>

    <?php if (!$hide_attribution && $submitted): ?>
        <div class="username"><?php print theme('username', $node) ?>:</div>
    <?php endif; ?>
    
    <div class="subject">
      <?php print l( $node->title, $_GET['q'], array('fragment' => "comment-$node->nid")) . ' ' . theme('mark', $node->new); ?>
    </div>

    <div class="content clear-block">
      <?php print $content; ?>
    </div>
    <?php if ($signature): ?>
    <div class="user-signature clear-block">
      <?php print $signature ?>
    </div>
    <?php endif; ?>
    <div class="links clear-block">
      <?php if ($links): ?>
        <?php print $links; ?>
       <?php endif; ?>
    </div>
   
  </div>
</div>