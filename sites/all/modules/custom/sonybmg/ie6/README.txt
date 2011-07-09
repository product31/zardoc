These files are designed to provide a popup for IE6 users to inform them that
the internet has moved on and they're going to have a sub-par experience.

To use them add the following snippet to the page.tpl.php file below the point
where the $scripts variable is printed:

  <!--[if lte IE 6]>
    <?php // Let IE 6 users know the internet has moved on and left them behind. ?>
    <style type="text/css" media="all">@import "<?php print $base_path . drupal_get_path('module', 'sonybmg'); ?>/ie6/makes_us_sad.css";</style>
    <script type="text/javascript" src="<?php print $base_path . drupal_get_path('module', 'sonybmg'); ?>/ie6/makes_us_sad.js"></script>
  <![endif]-->