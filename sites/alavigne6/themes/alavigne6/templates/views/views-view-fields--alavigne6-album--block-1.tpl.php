<?php # dsm($row); ?>
<?php # dsm($fields); ?>

<div class="albumblock">
  <div class="albumtitle"><?php print $fields['title']->content; ?></div>
  <div class="albumcover"><?php print $fields['field_album_cover_fid']->content; ?></div>
  <div class="albumblock-buttons">
    <?php if (!empty($fields['field_album_site_url_value']->content)){ ?>
      <div class="playalbum"><?php print l(t('Play Album'), $fields['field_album_site_url_value']->content, array('attributes' => array('onclick' => 'popUpAudio(this.href); return false;', 'target' => '_blank'))); ?></div>
    <?php } ?>
    <?php /*if(!empty($fields['field_album_video_url_value']->content)){ ?>
    <div class="watchvideos"><?php print l(t('Watch Videos'), $fields['field_album_video_url_value']->content); ?></div>
<?php }*/ ?>

<?php 

if($fields['m2_buy_album']->content){ ?>
  <div class="buy-links">
    <?php print $fields['m2_buy_album']->content; ?>
  </div>
<?php
 } else if ($fields['field_album_download_links_url']->content) { 
 
 ?>
  <div class="buy-links">
    <?php 
    // inserting BUY NOW text in translatable function
    print str_replace("<h3>","<h3>".t('BUY NOW'),$fields['field_album_download_links_url']->content); ?>   
  </div>
<?php } ?>

  </div>
</div>
