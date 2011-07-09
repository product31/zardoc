<?php
/**
 * @file
 * Create our "biography" page.
 */
function pages_help_info() {
  return array(
    'name' => st('Help Section'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 0,
  );
}

/**
 * Required modules.
 */
function pages_help_modules() {
  return array('menu', 'token', 'content', 'pathauto');
}

function pages_help_task_list() {
  return array(
    'pages_help_help_page' => array(
      'message' => st('Created biography page section.'),
      'weight' => 0,
    ),
    'pages_help_menu' => array(
      'message' => st('Created biography menu item.'),
      'weight' => 0,
    ),
  );
}

/**
 * Generate help page.
 */
function pages_help_help_page() {
  module_load_include('inc', 'node', 'node.pages');

  $node = new stdClass();
  $node->type = 'page';
  node_object_prepare($node);
  $node->status = 1;
  $node->title = t('Help & FAQ (Frequently Asked Questions)');
  $node->body = pages_help_content();
  $node->teaser = node_teaser($node->body);
  $node->promote = 1;
  $node->uid = 1;
  $node->filter = variable_get('filter_default_format', 1);
  $node->format = 3;
  $node->language = '';
  $node->path = 'help';
  node_save($node);
}

/**
 * Adds content relating to sonybmg module.
 */
function pages_help_content() {
  $output = <<<EOF
<div class="faq">
<h2 class="title">I keep trying to log in but the confirmation email doesn't arrive at my email account.</h2>
<p>Check your junk mail filters. Many service providers (AOL and Yahoo! in particular) incorrectly identify email from this site as junk.</p>

<h2 class="title">I was a member of the Forums before the new site launched and my password no longer works here.  Why? What happened to the old message boards?</h2>
<p>The new site features one login for the all of our new features. One password for forums, your personal profile page and blog, contest entries and more! Sorry to ask you to re-register if you'd done it before, but we hope you'll enjoy all of the new features this brings.</p>

<h2 class="title">Why can't I access the "Read My Messages" link on my profile page?</h2>
<p>To access Private Messages:
<ol><li>Click on the EDIT tab of your profile</li>
<li>Scroll down to the "Private message settings"</li>
<li>Check the box next to "Allow private messages"</li>
<li>Click the SUBMIT button to save your changes</li></ol></p>

<h2 class="title">How can I add an Avatar to my profile and posts?</h2>
<p>A small version of the photo you attach to your profile page is automatically created and used as your "avatar" on our forums.</p>

<h2 class="title">How do I customize my profile/add an avatar/set my signature?</h2>
<p>To personalize your profile:

<ol>
<li>Navigate to your profile page by clicking on your user name (you'll need to be logged in)</li>
<li>Click the EDIT tab</li>
<li>Click the PERSONAL INFORMATION link</li>
<li>Make your changes</li>
<li>Click the SUBMIT button to save your changes</li>
</ol>
</p>
<p>
Clicking EDIT allows you to:

<ul>
<li>Include your favorite lyric on your page</li>
<li>Upload your profile photo</li>
<li>Customize your signature (which will automatically appear at the bottom of your posts)</li>
<li>And more!</li>
</ul>
</p>

<h2 class="title">I uploaded a picture, but I don't see it in the photo gallery that I chose.  Why not? </h2>
<p>Uploaded photos and videos must first be approved by a moderator before they are published to the site to insure a safe, quality experience for all of our members. Photos are moderated several times a day. You'll generally see your photo appear within a few hours or less.</p>

<h2 class="title">What web browsers work best for this site?</h2>
<p>We support all modern web browsers and computer operating systems (Mac, Windows, Linux, etc.) We recommend the free Mozilla Firefox browser for Windows, Macintosh or Linux. It is available in many languages, and can be obtained from:
http://www.mozilla.com</p>

</div>
EOF;
  return $output;
}

/**
 * Create menu item.
 */
function pages_help_menu() {
  $path = drupal_get_normal_path('help');
  install_menu_create_menu_item($path, 'Help', NULL, 'Primary Links', 0, 10);
}
