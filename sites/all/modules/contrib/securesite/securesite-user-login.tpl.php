<?php
// $Id: securesite-user-login.tpl.php,v 1.1.2.2 2008/10/31 21:24:59 darrenoh Exp $

/**
 * @file
 * Template for Secure Site log-in form.
 */
?>
<h1><?php print t('Log in') ?></h1>
<?php print $messages ?>
<p><?php print $title ?></p>
<?php print drupal_render($form['openid_identifier']); ?>
<?php print drupal_render($form['name']); ?>
<?php print drupal_render($form['pass']); ?>
<?php print drupal_render($form['submit']); ?>
<?php print drupal_render($form['openid_links']); ?>
<?php print drupal_render($form); ?>
<span></span>

