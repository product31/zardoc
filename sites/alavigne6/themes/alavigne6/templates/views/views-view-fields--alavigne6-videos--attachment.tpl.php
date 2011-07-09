<?php # dsm($row); ?>
<?php # dsm($fields); ?>

<div class="video-thumb-wrapper">
  <div class="video-thumb">
    <?php print $fields['field_video_embed']->content; ?>
    <div class='playvideo'><?php print l(t('Play Video') , 'node/' . $row->nid, $options=array('attributes'=>array('class'=>'playvideolink'))) ?> </div>
  </div>
  <div class="video-title">
    <?php print $fields['title']->content; ?>
  </div>
  <div class="video-comments-link">
    <?php print l(t('Comments (@count)', array('@count' => $fields['comment_count']->content)), 'node/' . $row->nid, array('fragment' => 'comment-37717', 'attributes' => array('class' => 'video-comments'))); ?>
  </div>
</div>

