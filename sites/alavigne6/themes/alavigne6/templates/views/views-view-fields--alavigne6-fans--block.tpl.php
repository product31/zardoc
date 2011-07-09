<?php # dsm($row); ?>
<?php # dsm($fields); ?>

<?php if($row->users_picture) {
  $img = theme('imagecache', '57x48', $row->users_picture, $row->users_name, $row->users_name); 
} else {
  // else print default image, css will resize
  $img = $fields['picture']->content; 
} 
?>

<div class="thumb">
  <?php print $img; ?>
</div>

<div class="username">
  <?php print $fields['name']->content; ?>
</div>


<div class="datecreated">
  <?php print $fields['created']->content . t(' Ago'); ?>
</div>


