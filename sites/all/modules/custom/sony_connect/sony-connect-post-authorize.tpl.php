<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head> <title>Cross-Domain Receiver Page</title> </head>
<body>
<script src="http://static.ak.facebook.com/js/api_lib/v0.4/XdCommReceiver.debug.js" type="text/javascript"></script>
<script type="text/javascript">
function closeAndContinue() {
  window.opener.Drupal.sonyConnect.onPopupClose();
  window.close();
}
closeAndContinue();
</script>
<a href="#" onclick="closeAndContinue();return false;"><?php print t('Click here to continue') ?></a>
</body>
</html>