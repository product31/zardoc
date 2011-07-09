<?php // dsm($fields); ?>

<?php print $fields['field_album_cover_fid']->content; ?>
<h3 class="album-title"><?php print $fields['title']->content; ?></h3>
<?php if($fields['teaser']->content){ ?>
  <p class="desc"><?php print $fields['teaser']->content; ?></p>
<?php } ?>

<?php if($fields['m2_buy_album']->content){ ?>
  <div class="buy-links">
    <?php print $fields['m2_buy_album']->content; ?>
  </div>
<?php } else if ($fields['field_album_download_links_url']->content) { ?>
  <div class="buy-links">
    <?php 
    // inserting BUY NOW text in translatable function
    print str_replace("<h3>","<h3>".t('BUY NOW'),$fields['field_album_download_links_url']->content); ?>   
  </div>
<?php } ?>
