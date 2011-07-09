<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>"<?php print $namespaces; ?>>

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

      <?php if ($is_front){ ?>
        <h1 id="site-name"><?php print $site_name; ?></h1>
      <?php } else { ?>
        <div id="site-name">
          <a href="<?php print $front_page ?>" title="<?php print t('Avril Lavigne Home'); ?>"><?php print $site_name; ?></a>
        </div>
      <?php } ?>


      <div id="top">
        <?php print $languages_newsletter_region; ?>

        <div id="login">
          <?php print $login; ?>
        </div>

        <?php print $top; ?>
      </div> <!-- /top -->

    </div> <!-- /header -->

    <div id="navigation">
      <?php print $navigation; ?>
    </div> <!-- /navigation -->
    
    <div id="banner">
      <?php print $banner; ?>
    </div> <!-- /banner -->

    <div id="container-wrapper">
    <div id="container" class="clear-block">
     
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

      <?php /* if ($breadcrumb): ?>
         <div id="breadcrumb" class="clear-block"><?php print $breadcrumb ?></div>
      <?php endif; */ ?>
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
    </div> <!-- /container-wrapper -->
    <div id="footer-wrapper">
      <div id="footer-right">
        <?php print $footer_right; ?>
      </div>
      <div id="footer">
        <?php print $footer; ?>
        <?php print theme('sonybmg_footer') ?>
        <?php print $footer_message; ?>
        <?php print $etrust; ?>
      </div> <!-- /footer -->
    </div> <!-- /footer-wrapper -->
  </div> <!-- /page -->

  <?php if ($admin): ?>
  <div id="admin-region">
    <div class="admin-inner">
      <a href="#" class="admin-trigger"><?php print t('Admin Region'); ?></a>
      <div id="admin-content">
        <?php print $admin; ?>
      </div>
    </div>
  </div>
  <?php endif; ?>

  <?php print $closure; ?>
</body>
</html>
