<?php # dsm($row); ?>
<?php # dsm($fields); ?>


<?php 
// this *should* always be true because the view is limiting on users with pictures.
if($row->users_picture) {
  $img = theme('imagecache', '177x118', $row->users_picture, $row->users_name, $row->users_name); 
} else {
  // else print default image, css will resize  
  $img = $fields['picture']->content; 
} 
?>

<div class="userpicture">
  <?php print $img; ?>
</div>


<div class="username">
  <?php print $fields['name']->content; ?>
</div>


<div class="datecreated">
  <?php
    print t('Member Since '); 
    print format_date($row->users_created, 'custom', 'm.d.y') ;
    print '<span class="memberlength">' . $fields['created']->content . '</span>';   
  ?>
</div>


<div class="whyimafan">
  <?php print strip_tags(truncate_utf8($fields['body']->content,190,TRUE,TRUE)); ?>
</div>

<div class="readmore">
  <?php print l(t('Read More'), 'users/' . $row->users_name); ?>
</div>
