<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>">

<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
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
   <div id="page-inner">


   <?php if ($ad_top): ?>
      <div id="ad-top" class="clear-block">
        <?php print $ad_top; ?>
      </div>
      <?php endif; ?>

    <div id="header-wrapper">
    <div id="header">

          <?php if ($left_header): ?>
            <div id="left-header">
              <?php print $left_header; ?>
            </div> <!-- /left-header -->
          <?php endif; ?>

           <?php if ($right_header): ?>
            <div id="right-header">
              <?php print $right_header; ?>
            </div>
          <?php endif; ?> <!-- /right-header -->

          <?php if ($flash_header): ?>
              <div id="flash-header" alt="<?php print $site_name; ?>" title="<?php print $site_name; ?>">
                  <?php print $flash_header; ?>
                </div>
            <?php else: ?>
              <div id="logo-title">
                <div id="name-and-slogan">
                  <h1 id="site-name">
                    <a href="<?php print $front_page ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
                  </h1>

                  </div> <!-- /name-and-slogan -->
                </div> <!-- /logo-title -->
                <?php endif; ?>

      </div> <!-- /header -->
    </div> <!-- /header-wrapper -->

     <div id="navigation-wrapper" class="clear-block">
      <div id="navigation" class="menu <?php if ($primary_links) { print "withprimary"; } if ($secondary_links) { print " withsecondary"; } if ($flash_nav) { print " withflashnav"; } ?> ">
      <?php if($flash_nav): ?>
                <div id="flash-nav" class="clear-block">
                  <?php print $flash_nav; ?>
                </div>
         <?php else: ?>
                <?php if ($primary_links): ?>
                    <div id="primary" class="clear-block">
                      <?php print theme('links', $primary_links); ?>
                    </div>
                  <?php endif; ?>
       <?php endif; ?><!-- /end of either flash nav or primary links -->

                <?php if ($secondary_links): ?>
                    <div id="secondary" class="clear-block">
                      <?php print theme('links', $secondary_links); ?>
                    </div><!-- /end of  secondary links -->
                  <?php endif; ?>
       </div> <!-- /navigation -->
      </div> <!-- /navigation-wrapper -->


    <div id="container-wrapper" class="clear-block">
     <div id="container" class="clear-block">

      <?php if ($listen): ?>
       <div id="trb">
        <?php print $listen; ?>
       </div><!-- /trb -->
      <?php endif; ?>

      <?php if ($search_box): ?>
      <div id="search-box">
        <?php print $search_box; ?>
       </div><!-- /search-box -->
      <?php endif; ?>

      <div id="login-bar" class="clear-block">
        <div class="login">
          <?php if ($user->uid): ?>
            <?php print t('Welcome !username', array('!username' => l($user->name, 'user'))) ?> | <span class="logout"><?php print t('Not %username? <a href="!logout">Logout</a>', array('%username' => $user->name, '!logout' => url('logout'))) ?> &nbsp;<span><?php if ($user->uid) { print l(t('My Account'), 'user'); } ?></span>
          <?php else: ?>
            <?php print t('Welcome guest! Please <a href="!login">login</a> or <a href="!register">create an account</a>.', array('!login' => url('user', array('query' => drupal_get_destination())), '!register' => url('user/register', array('query' => drupal_get_destination())))) ?>
          <?php endif; ?>
          <?php if ($online_users): ?>
            <span class="online-fans">(<?php print l(t('@count fans online', array('@count' => $online_users)), 'profile'); ?>)</span>
          <?php endif; ?>
        </div>
      </div>



      <?php if ($title && !$is_front): ?><h1 class="title"><?php print $title; ?></h1><?php endif; ?>
      <?php if ($tabs): ?><div class="tabs"><?php print $tabs; ?></div><?php endif; ?>

      <?php if ($content_header): ?>
        <div class="content_header">
          <?php print $content_header; ?>
        </div>
      <?php endif; ?>

      <?php if ($left): ?>
    <div id="sidebar-left" class="column sidebar">
          <?php print $left; ?>
        </div> <!-- /sidebar-rleft -->
      <?php endif; ?>

      <?php if ($right): ?>
        <div id="sidebar-right" class="column sidebar">
          <?php print $right; ?>
        </div> <!-- /sidebar-right -->
      <?php endif; ?>

      <div id="main" class="column">
        <div id="squeeze">
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


      <?php if ($ad_bottom): ?>
      <div id="ad-bottom">
        <?php print $ad_bottom; ?>
      </div>
      <?php endif; ?>
      </div> <!-- /container -->
    </div> <!-- /container-wrapper -->

    <div id="footer-wrapper">
      <div id="footer">

          <?php if ($left_footer): ?>
            <div id="left-footer" class="clear-block">
              <?php print $left_footer; ?>
            </div> <!-- /left-footer -->
          <?php endif; ?>

          <?php if ($right_footer): ?>
            <div id="right-footer" class="clear-block">
              <?php print $right_footer; ?>
            </div> <!-- /right-footer -->
          <?php endif; ?>

        <div id="sonybmg-footer">
          <?php print theme('sonybmg_footer') ?>
        </div>

        <div id="footer-message">
          <?php print $footer_message; ?>
        </div>

      </div> <!-- /footer -->
    </div> <!-- /footer-wrapper -->

    </div> <!-- /page-inner -->
  </div> <!-- /page -->

  <div id="sony-bar">
     <?php print theme('sonybmg_toolbar'); ?>
   </div>
  <?php print $closure; ?>
</body>
</html>
