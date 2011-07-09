<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>">

<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <style type="text/css" media="all">@import "/modules/system/system.css";</style>
  <style type="text/css" media="all"><?php print $node->field_css[0]['value']; ?></style>
  <?php print $scripts; ?>
</head>
<body>
<?php if ($tabs): ?><div class="tabs"><?php print $tabs; ?></div><?php endif; ?>
<?php print $content;?>
</body>
</html>
