<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <?php print $head; ?>
  <title>Chat</title>
  
  <?php $path = $GLOBALS['base_url'] .'/'. drupal_get_path('module', 'broserver'); ?>
  <script type="text/javascript" src="<?php print $GLOBALS['base_url'] .'/'. JQUERY_UPDATE_REPLACE_PATH .'/jquery.min.js'; ?>"></script>
  <script type="text/javascript" src="<?php print $path .'/v1/js/jquery.cookie.js'; ?>"></script>
  <script type="text/javascript" src="<?php print $path .'/chat/jquery.scrollTo-min.js'; ?>"></script>
  <script type="text/javascript" src="<?php print $path .'/chat/jsjac.js'; ?>"></script>
  <script type="text/javascript" src="<?php print $path .'/chat/chat.js?' . broserver_cachebuster(); ?>"></script>
  
  <script type="text/javascript">
    var bro_user = "<?php print $bro_user; ?>";
    var bro_nick = "<?php print $bro_nick; ?>";
    var bro_domain = "<?php print $bro_domain; ?>";
    var bro_timestamp = "<?php print $bro_timestamp; ?>";
    var bro_hash = "<?php print $bro_hash; ?>";
    var bro_chatroom = "<?php print $bro_chatroom; ?>";
  </script>
  
  <link href="<?php print $path .'/chat/chat.css?' . broserver_cachebuster(); ?>" type="text/css" rel="stylesheet" />
</head>
<body>

<div id="chat">
  <?php print $messages; ?>
</div>

<?php print $content; ?>

</body>
</html>

