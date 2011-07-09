<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><?php print check_plain(variable_get('site_name', 'Drupal')); ?></title>

<?php print drupal_get_html_head() ?>

<!-- Scripts -->
<script src="<?php print base_path() . drupal_get_path('module', 'platform_player'); ?>/swfobject.js" type="text/javascript"></script>

<!-- Styles -->
<style type="text/css">
* { margin: 0; padding: 0; border: 0; }
</style>
</head>

<body>

<div id="flashcontent">
  Please download the latest version of Flash Player <a href="http://www.adobe.com/shockwave/download/download.cgi?P1_Prod_Version=ShockwaveFlash" onclick="window.open(this.href,'_blank');return false;">here</a>.
</div>

<script type="text/javascript">
//<![CDATA[
var player = <?php print drupal_to_js($field['audio_player']); ?>;
var so = new SWFObject(player.swf, "jukebox", player.width, player.height, "8", "#ffffff");
so.addVariable('platformURL', '<?php print $platform_url; ?>');
so.write('flashcontent');
// ]]>
</script>

</body>
</html>
