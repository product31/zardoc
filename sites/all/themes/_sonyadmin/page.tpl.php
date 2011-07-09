<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>">

<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>

<body class="<?php print $body_class ?>">
  <div id="header">
    <div class="container">
      <?php if($logo): ?>
        <a href="<?php print $front_page ?>" title="<?php print t('Home'); ?>"><?php print '<img src="'. check_url($logo) .'" alt="'. $site_name .'" id="logo" />'; ?></a>
      <?php endif;  ?>
      <h1><a href="<?php print $front_page ?>" title="<?php print t('Home'); ?>"><?php print $site_name ?></a></h1>
      <div class="site-name"><?php print t('Drupal Control Panel') ?></div>

      <?php if($flag_region): ?>
        <div class="flag-region">
          <?php print $flag_region ?>
        </div>
      <?php endif; ?>

      <div class="top-links">
        <?php print t('Logged in as !username', array('!username' => l($user->name, 'user'))) ?> |
        <?php print l('Back to site', '<front>') ?> |
        <?php print l('Logout', 'logout') ?>
      </div>
    </div>
  </div>

  <div id="primary" class="clear-block">
    <div class="container">
      <?php print theme('links', menu_navigation_links('navigation')); ?>
    </div>
  </div>

  <div id="content">
    <div class="container">
       <?php print $breadcrumb ?>

      <?php print $messages; ?>

      <?php if ($title): ?><h2 class="title"><?php print $title; ?></h2><?php endif; ?>
      <?php if ($tabs): ?><div class="tabs"><?php print $tabs; ?></div><?php endif; ?>

      <?php print $help; ?>
      <?php print $content; ?>
    </div>

  </div>

  <div id="footer">
    <div class="container">
      COPYRIGHT &copy; <?php print date('Y') ?> SONY MUSIC ENTERTAINMENT. All Rights Reserved.
    </div>
  </div>

  <?php print $closure; ?>
</body>
</html>
