<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">

  <?php if ($page == 0): ?>
    <div class="clear-block">
      <div class="content-type">
        <?php print drupal_strtoupper($node->type); ?>
      </div>
      <h2 class="node-title title">
        <a href="<?php print $node_url ?>"><?php print $title; ?></a>
      </h2>
    </div>
  <?php else: ?>
  
  <div class="buyit-track clear-block">
    <?php print views_embed_view('track_album_buyit'); ?>
  </div>

      
<div class="track-information clear-block">

  <div class="title-row">
    <?php if ($track_num): ?>
    <span class="track-num"><?php print t('Track ') . $track_num; ?>: </span>
    <?php endif; ?>
    <span class="track-name"><?php print $title; ?></span>
  </div>

  <div class="play-row clear-block">
    <?php if ($track_url): ?>
      <div class="track-play"><a href="<?php print $track_url; ?>" onclick="popUpAudio(this.href); return false;"><?php print t('Play') . ' ' . $title; ?></a></div>
    <?php endif; ?>
            
    <?php if ($video_url): ?>
      <div class="track-video"><a href="<?php print $video_url; ?>" onclick="popUpVideo(this.href); return false;"><?php print t('Watch Video'); ?></a></div>
    <?php endif; ?>
  </div>

  <div class="clear-block">
    <?php if (isset($review_count)): ?>
      <div class="review-count"><?php print t('Reviews: ') . $review_count; ?> | <a href="<?php print url('node/add/review/' . $node->nid) ?>" class="rate-review"><?php print t('add review'); ?> &gt;</a></div>
    <?php endif; ?>
    <?php if ($vote_display): ?>
      <div class="rating"><?php print t('Average Rating: ') . $vote_display; ?></div>
    <?php endif; ?>
    <div class="rate"><a href="<?php print url('node/add/review/' . $node->nid) ?>" class="rate-review"><?php print t('rate it!'); ?> &gt;</a></div>
  </div>
        
        
      <?php if ($pager): ?>
        <div class="song-pager"><?php print $pager ?></div>
      <?php endif; ?>
        
    </div>
  <?php endif; ?>
    
  <?php if ($content): ?>
  <div class="content clear-block">
    <h3><?php print t('LYRICS'); ?></h3>
    <?php print $content; ?>
  </div>
  <?php endif; ?>

  <div class="links clear-block">
    <?php if ($links): ?>
      <?php print $links; ?>
     <?php endif; ?>
  </div>
 
</div><!-- end node -->