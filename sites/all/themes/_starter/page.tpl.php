<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>" <?php print $namespaces; ?> >

<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <meta http-equiv="X-UA-Compatible" content="IE=8" />
  <!--[if lte IE 6]>
  <style type="text/css" media="all">@import "<?php print $path; ?>css/ie6.css";</style>
  <![endif]-->
  <!--[if IE 7]>
  <style type="text/css" media="all">@import "<?php print $path; ?>css/ie7.css";</style>
  <![endif]-->
  <?php print $scripts; ?>
</head>

<body class="<?php print $body_classes; ?>">
  <?php if ($page_top): ?>
   <div id="page-top">
     <?php print $page_top; ?>
   </div>
  <?php endif; ?>
  <div id="page">
    <div id="header">
      <?php if ($ad_top): ?>
      <div id="ad-top" class="clear-block">
        <?php print $ad_top; ?>
      </div>
      <?php endif; ?>

      <div id="logo-title">
        <div id="name-and-slogan">
          <h1 id="site-name">
            <a href="<?php print $front_page ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
          </h1>
        </div> <!-- /name-and-slogan -->
      </div> <!-- /logo-title -->

      <div id="navigation" class="menu <?php if ($primary_links) { print "withprimary"; } if ($secondary_links) { print " withsecondary"; } ?> ">
        <?php if ($primary_links): ?>
          <div id="primary" class="clear-block">
            <?php print theme('links', $primary_links); ?>
          </div>
        <?php endif; ?>
      </div> <!-- /navigation -->

    </div> <!-- /header -->

    <div id="container" class="clear-block">

      <div id="login-bar" class="clear-block">
        <div class="login">
          <?php if ($user->uid): ?>
            <?php print t('Welcome !username', array('!username' => l($user->name, 'user'))) ?> | <span class="logout"><?php print t('Not %username? <a href="!logout">Logout</a>', array('%username' => $user->name, '!logout' => url('logout'))) ?> &nbsp;<span><?php if ($user->uid) { print l(t('My Account'), 'user'); } ?></span>
          <?php else: ?>
            <?php print t('Welcome guest! Please <a href="!login">login</a> or <a href="!register">create an account</a>.', array('!login' => url('user/login', array('query' => drupal_get_destination())), '!register' => url('user/register', array('query' => drupal_get_destination())))) ?>
          <?php endif; ?>
          <?php if ($online_users): ?>
            <span class="online-fans">(<?php print l(t('@count fans online', array('@count' => $online_users)), 'profile'); ?>)</span>
          <?php endif; ?>
        </div>
  
        <div class="right">
          <div id="trb">
            <?php if ($listen): ?>
              <?php print $listen; ?>
            <?php endif; ?>
          </div>
          <?php print $search_box; ?>
        </div>
      </div>
      <?php if ($title && !$is_front): ?><h1 class="title"><?php print $title; ?></h1><?php endif; ?>
      <?php if ($tabs): ?><div class="tabs"><?php print $tabs; ?></div><?php endif; ?>

      <?php if ($content_header): ?>
        <div class="content_header">
          <?php print $content_header; ?>
        </div>
      <?php endif; ?>

      <div id="main" class="column"><div id="squeeze">
        <?php if ($mission): ?><div id="mission"><?php print $mission; ?></div><?php endif; ?>
        <?php if ($content_top):?><div id="content-top"><?php print $content_top; ?></div><?php endif; ?>
        <?php print $help; ?>
        <?php print $messages; ?>
        <?php print $content; ?>
        <?php print $feed_icons; ?>
        <?php if ($content_bottom): ?><div id="content-bottom"><?php print $content_bottom; ?></div><?php endif; ?>

      <?php if ($breadcrumb): ?>
         <div id="breadcrumb" class="clear-block"><?php print $breadcrumb ?></div>
      <?php endif; ?>
      </div></div> <!-- /squeeze /main -->

      <?php if ($right): ?>
        <div id="sidebar-right" class="column sidebar">
          <?php print $right; ?>
        </div> <!-- /sidebar-right -->
      <?php endif; ?>

      <?php if ($ad_bottom): ?>
      <div id="ad-bottom">
        <?php print $ad_bottom; ?>
      </div>
      <?php endif; ?>
    </div> <!-- /container -->

    <div id="footer-wrapper">
      <div id="footer">
        <?php print theme('sonybmg_footer') ?>
        <?php print $etrust; ?>
        <?php print $footer_message; ?>
      </div> <!-- /footer -->
    </div> <!-- /footer-wrapper -->
  </div> <!-- /page -->

  <?php print $footer; ?>
  <?php print $closure; ?>
</body>
</html>
