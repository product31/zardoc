<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">
  <div class="forum-post">
    <div class="user-info">
      <?php print $picture ?>
      <div class="user-title">
        <?php print $user_title; ?>
      </div>
      <div class="user-since">
        <?php print t('Joined'); ?>: <strong><?php print $user_since; ?></strong>
      </div>
      <?php if (isset($user_posts)): ?>
        <div class="user-posts">
          <?php print t('Posts'); ?>: <strong><?php print $user_posts; ?></strong>
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

    <?php if ($page == 0): ?>
      <div class="clear-block">
        <div class="content-type">
          <?php print drupal_strtoupper($node->type); ?>
        </div>
      </div>
    <?php endif; ?>

    <?php if ($submitted): ?>
      <div class="submitted"><?php print format_date($node->created, 'large') ?></div> 
    <?php endif; ?>

    <?php if (!$hide_attribution && $submitted): ?>
        <div class="username"><?php print theme('username', $node) ?>:</div>
    <?php endif; ?>
    
    <?php if ($page == 0): ?>
      <h2 class="node-title title">
        <a href="<?php print $node_url ?>"><?php print $title; ?></a>
      </h2>
    <?php else: ?>
      <div class="subject">
        <?php print $title; ?>
      </div>
    <?php endif; ?>

    <div class="content clear-block">
      <?php print $content; ?>
    </div>
    
    <div class="links clear-block">
      <?php if ($links): ?>
        <?php print $links; ?>
       <?php endif; ?>
    </div>
   
  </div>
</div>
