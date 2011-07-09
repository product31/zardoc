<?php
$base_url = $GLOBALS['base_url'];

$bro = new stdClass;

// The id used to reference this config.
$bro->id = 'wyclef';

// Always v1 for now.
$bro->version = 'v1';

// An administrative description.
$bro->description = 'Wyclef Jean';

// The chat domain to use.
$bro->domain = 'j.sonymusicdigital.com';

// The chatroom base name to use
$bro->chatroom = 'wyclef';
$bro->guest_chat = FALSE;

// The secret key to hash on
$bro->secret_key = 'SECRET_KEY';

$bro->forbidden_names = array(
													'tgrayson',
													'zroger',
													'gtaylor',
													'admin',
													'administrator',
													'wyclef',
													'wjean',
													'wyclefjean'
													);


// Is this a REAC artist? TRUE|FALSE
$bro->REAC = FALSE;

// The ad code for the upper sponsorship spot.
$bro->ad1 = '<a href="http://www.sony.com/index.php" target="_blank"><img src="'. $base_url .'/sites/all/modules/custom/broserver/config/wyclef/adbox300x50.png" /></a>';

// The ad code for the lower sponsorship spot.bor:0
$bro->ad2 = '<a href="http://www.sony.com/index.php" target="_blank"><img src="'. $base_url .'/sites/all/modules/custom/broserver/config/wyclef/makedotbelieve468x60.jpg" /></a>';

// The embed code for the media player.
$bro->media = <<<EOD
<!-- Start of Brightcove Player -->

<div style="display:none">

</div>

<!--
By use of this code snippet, I agree to the Brightcove Publisher T and C 
found at http://corp.brightcove.com/legal/terms_publisher.cfm. 
-->

<script language="JavaScript" type="text/javascript" src="http://admin.brightcove.com/js/BrightcoveExperiences.js"></script>

<object id="myExperience" class="BrightcoveExperience">
  <param name="bgcolor" value="#FFFFFF" />
  <param name="width" value="475" />
  <param name="height" value="475" />
  <param name="playerID" value="57165213001" />
  <param name="publisherID" value="59121"/>
  <param name="isVid" value="true" />
  <param name="isUI" value="true" />
  <param name="wmode" value="transparent" />
</object>

<!-- End of Brightcove Player -->
EOD;

// Location of the logo, relative to this file.
$bro->artist_logo = 'watch-now-wycleftop425x45.png';
$bro->countdown_image = 'watch-now-wycleftop175x45.png';  

  // Timestamp for the countdown.
  // $bro->countdown = $time;

// Or an image
//$bro->countdown_image = 'wycleftop175x45.png';

$url = urlencode('http://www.wyclef.com/#auto-open');
$title = urlencode('Wyclef Jean Live Sets');
$bro->links = array(
  'facebook' => "http://www.facebook.com/sharer.php?u=$url&t=$title",
  'myspace' => "http://www.myspace.com/index.cfm?fuseaction=postto&t=$title&u=$url",
  'twitter' => "http://twitter.com/home?status=$title - $url",
  'digg' => "http://digg.com/submit?phase=2&url=$url&title=$title",
  'delicious' => "http://del.icio.us/post?url=$url&title=$title",
);

