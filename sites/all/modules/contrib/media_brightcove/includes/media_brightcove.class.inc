<?php
// $Id: media_brightcove.class.inc,v 1.1.2.2 2010/06/11 12:49:02 aaron Exp $

/**
 * @file
 * Media: Brightcove provider object.
 */

class MediaBrightcove extends EmapiMedia {
  // The provider; matches the scheme:// of the $uri.
  public $provider = 'media_brightcove';

  // Regex patterns for matching while parsing a URL.
  public $patterns = array(
    // Brightcove v3.3 - URL style.
    '@\.brightcove\.com/services/player/bcpid.*?\?bctid=(\d+)@i',
    // Brightcove Simple RSS URL style. billk2
    '@\.brightcove\.com/services/link/bcpid.*?/bctid(\d+)@i',
    // Older blog style.
    '@\.brightcove\.com/services/viewer/.*?videoId=(\d+)@i',
    // Brightcove v3.3 - Blog style.
    '@\.brightcove\.com/services/viewer/.*?videoPlayer=(\d+)@i',
    // Brightcove v3.3 - Website style.
    '@id="myExperience(\d+)" class="BrightcoveExperience"@i',
  );
}
