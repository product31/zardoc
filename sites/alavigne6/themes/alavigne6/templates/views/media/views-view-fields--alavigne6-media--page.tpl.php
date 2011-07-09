<?php // dsm($fields); ?>

<?php // print $fields['field_album_cover_fid']->content; 
$moreurl = 'node/' . $fields['nid']->raw;
?>

<?php print $fields['field_mediaimage_fid']->content; ?>
<?php /* 
<div class="readmore"><?php print l(t('Read More') . ' &raquo;', $moreurl, array('html' => TRUE)) ?></div>
*/ ?>
<h3 class="magtitle"><?php print $fields['field_magtitle_value']->content; ?></h3>
<div class="date"><?php print $fields['field_published_value']->content; ?></div>
