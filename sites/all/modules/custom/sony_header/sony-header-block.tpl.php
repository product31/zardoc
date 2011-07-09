<div id="<?php print $content_id; ?>">
  <?php print $alternate_content; ?>
</div>

<script type="text/javascript">
  swfobject.embedSWF("<?php print $swf; ?>", 
    "<?php print $content_id; ?>", 
    "<?php print $width; ?>", 
    "<?php print $height; ?>", 
    "9.0.45", 
    "<?php print $expressinstall; ?>", 
    <?php print $flashvars; ?>, 
    <?php print $params; ?>, 
    <?php print $attributes; ?>);
</script>
