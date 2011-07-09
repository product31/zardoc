<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">
<div class="back-button">
  <?php print (!empty($bc)) ? $bc : ' ' ; ?>
</div>
    <?php if ($cover_art_big): ?>
    <div class="album-node-cover"><?php print $cover_art_big; ?></div>
    <?php endif; ?>

    <div class="right-details">
      
      <div class="release-date row">
        <span class="release-date"><?php print format_date($release_date, 'custom', 'Y'); ?></span>
        <span class="tracks"><?php print format_plural($track_count, '1 Track', '@count Tracks'); ?></span>
      </div>
      
         <div class="comment-flag">
          <?php print l(t('<span>@count</span> <strong>Comments</strong>', array('@count' => $review_count)), 'node/' . $node->nid, array('html' => TRUE, 'fragment' => 'comments', 'attributes' => array('class' => 'comm'))); ?>
          
          <?php print theme('flags_popup', $node->nid, 'favorites'); ?>
        </div>
      
      
      <?php if ($node->field_album_site_url[0]['view']): ?>
      <div class="playalbum">
        <?php print l(t('Play Album'), $node->field_album_site_url[0]['view'], array('attributes' => array('onclick' => 'popUpAudio(this.href); return false;'))); ?>
      </div>
      <?php endif; ?> 
     
      <?php if($m2_links){ ?>
      
      <div class="buy-links">
        <?php print theme('sonybmg_dropdown_links', $m2_links, t('Buy Now')); ?>
      </div>
      
      <?php } else if ($download_links) { ?>
      
      <div class="buy-links">
        <?php print theme('sonybmg_dropdown_links', $download_links, t('Buy Now')); ?>
      </div>
      
      <?php } ?>

    </div>

    <?php if ($tracks): ?>
    <div id="tracks" class="tracks">
      <?php print $tracks; ?>
    </div>
    <?php endif; ?>
    
    <?php print $links; ?>

</div>
