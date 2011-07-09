<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>" <?php print $namespaces; ?> >

<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
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
            Welcome <?php print l($user->name, 'user'); ?> | <span class="logout">Not <em><?php print $user->name; ?></em>? <a href="<?php print url('logout'); ?>">Log Out</a> &nbsp;<span ><?php if ($user->uid) { print l('My Account', 'user'); } ?></span></span>
          <?php else: ?>
            Welcome guest! Please <a href="<?php print url('user', array('query' => drupal_get_destination())); ?>">login</a> or <a href="<?php print url('user/register'); ?>">create an account</a>.

          <?php endif; ?>
          <?php if ($online_users): ?>
            <span class="online-fans">(<?php print $online_users . ' ' . l('fans online', 'profile'); ?>)</span>
          <?php endif; ?>
        </div>

    <span class="right">
      <div id="trb">
        <?php if ($listen): ?>
          <?php print $listen; ?>
        <?php endif; ?>
      </div>
      <?php print $search_box; ?>
    </span>
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
