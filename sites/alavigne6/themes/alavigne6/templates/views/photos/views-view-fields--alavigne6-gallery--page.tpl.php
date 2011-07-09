<?php // dsm($row); ?>
<?php // dsm($fields); ?>


<h3>
  <?php print $fields['title']->content; ?>
</h3>

<span class="count">
  <?php $count = format_plural($photo_count, 'See all','See all @count'); ?>
  <?php print ($photo_count > 0) ? l($count, 'node/' . $fields['nid']->raw) : NULL; ?>
</span>

<div class="thumb">
  <?php print l($photo_thumb, 'node/' . $fields['nid']->raw, array('html' => TRUE)); ?>
</div>

<div class="photo-title">
  <?php print $photo_title; ?>
</div>
