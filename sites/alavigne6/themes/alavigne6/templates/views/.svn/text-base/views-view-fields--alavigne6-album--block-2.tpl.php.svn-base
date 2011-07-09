<?php # dsm($row); ?>
<?php # dsm($fields); ?>

<div class="albumblock">
  <div class="albumcover"><?php print $fields['field_album_cover_fid']->content; ?></div>
  <div class="albumtitle"><?php print $fields['title']->content; ?></div>
  <div class="albumprice"><span class='m2-price-placeholder' product_id='<?php print $product_id; ?>'></span></div>
 
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
 

</div>
