<?php
// $Id: securesite-user-pass.tpl.php,v 1.1.2.3 2008/12/22 20:14:16 darrenoh Exp $

/**
 * @file
 * Template for Secure Site password reset form.
 */
?>
<h1><?php print t('Password reset') ?></h1>
<p><?php print $title ?></p>
<?php print drupal_render($form['name']); ?>
<?php print drupal_render($form['submit']); ?>
<?php print drupal_render($form) ?>

