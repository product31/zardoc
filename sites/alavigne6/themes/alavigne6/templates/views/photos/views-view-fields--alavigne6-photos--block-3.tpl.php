<?php // dsm($row); ?>
<?php // dsm($fields); ?>

<div class="thumb">
  <?php print $fields['field_photo_fid']->content; ?>
</div>

<?php  if(!empty($fields['count']->content)) { ?>
<span class="likes">
  <?php print $fields['count']->content . ' +'; ?>
</span>
<?php } ?>

<?php  if(!empty($fields['title']->content)) { ?>
<div class="photo-title">
  <?php print $fields['title']->content; ?>
</div>
<?php } ?>
