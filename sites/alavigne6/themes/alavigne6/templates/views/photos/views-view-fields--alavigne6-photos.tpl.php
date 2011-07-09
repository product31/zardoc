<?php // dsm($row); ?>
<?php // dsm($fields); ?>


<a href="<?php print url($fields['field_photo_fid_2']->content); ?>" class="highslide_formatter_popup_thumbnail highslide">
<?php print $fields['field_photo_fid']->content; ?>
</a>

<div class='highslide-caption'>
  <h3><?php print $fields['title']->content; ?></h3>
  <div class="comments"><?php print l(t('Comment on this photo'), 'node/' . $row->nid ,array('fragment' => 'comments', 'html' => TRUE, 'attributes' => array('class' => 'button-dim-lg'))); ?></div>
</div>

<?php /*
<div class="photo-title">
  <?php print $fields['title']->content; ?>
</div>

*/ ?>
