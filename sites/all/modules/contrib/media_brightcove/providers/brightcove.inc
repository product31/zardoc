<?php
// $Id: brightcove.inc,v 1.1.2.15 2010/09/01 21:30:13 aaron Exp $

/**
 * @file
 *  This is an brightcove provider include file for Embedded Media Video.
 *  Use this as a base for creating new provider files.
 *
 *  When using this, first make the following global replacements:
 *    * Replace BRIGHTCOVE with the name of your provider in all caps.
 *    * Replace brightcove with the name of your provider in all lower case.
 *    * Replace Brightcove with the name (to be translated) of your provider in
 *        uppercase.
 *
 *  You then need to go through each function and modify according to the
 *  requirements of your provider's API.
 */

/**
 * hook emvideo_PROVIDER_info
 * This returns information relevant to a specific 3rd party video provider.
 *
 * @return
 *   A keyed array of strings requested by various admin and other forms.
 *    'provider' => The machine name of the provider. This must be the same as
 *      the base name of this filename, before the .inc extension.
 *    'name' => The translated name of the provider.
 *    'url' => The url to the main page for the provider.
 *    'settings_description' => A description of the provider that will be
 *      posted in the admin settings form.
 *    'supported_features' => An array of rows describing the state of certain
 *      supported features by the provider. These will be rendered in a table,
 *      with the columns being 'Feature', 'Supported', 'Notes'. In general,
 *      the 'Feature' column will give the name of the feature, 'Supported'
 *      will be Yes or No, and 'Notes' will give an optional description or
 *      caveats to the feature.
 */
function emvideo_brightcove_info() {
  $features = array(
    array(t('Autoplay'), t('Yes'), ''),
    array(t('RSS Attachment'), t('No'), ''),
    array(t('Thumbnails'), t('Yes'), t('')),
    array(t('Duration'), t('Yes'), ''),
    array(t('Full screen mode'), t('Yes'), t('')),
  );
  return array(
    'provider' => 'brightcove',
    'name' => t('Brightcove'),
    'url' => MEDIA_BRIGHTCOVE_MAIN_URL,
    'settings_description' => t('These settings specifically affect videos displayed from !brightcove. You can also read more about its !api.', array('!brightcove' => l(t('Brightcove.com'), MEDIA_BRIGHTCOVE_MAIN_URL, array('attributes' => array('target' => '_blank'))), '!api' => l(t("developer's API"), MEDIA_BRIGHTCOVE_API_URL, array('attributes' => array('target' => '_blank'))))),
    'supported_features' => $features,
  );
}

/**
 *  hook emvideo_PROVIDER_settings
 *  This should return a subform to be added to the emvideo_settings() admin
 *  settings page.
 *
 *  Note that a form field set will already be provided at $form['brightcove'],
 *  so if you want specific provider settings within that field set, you should
 *  add the elements to that form array element.
 */
function emvideo_brightcove_settings() {
  module_load_include('inc', 'media_brightcove', 'includes/media_brightcove.admin');
  $form = array();

  $form['brightcove'] = media_brightcove_admin_form();

  return $form;
}

/**
 *  hook emvideo_PROVIDER_extract
 *
 *  This is called to extract the video code from a pasted URL or embed code.
 *
 *  We'll be passed a URL or the embed code from a video when an editor pastes
 *  that in the field's textfield. We'll need to either pass back an array of
 *  regex expressions to match, or do the matching ourselves and return the
 *  resulting video code.
 *
 *  @param $parse
 *    An optional string with the pasted URL or embed code.
 *  @return
 *    Either an array of regex expressions to be tested, or a string with the
 *    video code to be used. If the hook tests the code itself, it should
 *    return either the string of the video code (if matched), or an empty
 *    array. Otherwise, the calling function will handle testing the embed code
 *    against each regex string in the returned array.
 */
function emvideo_brightcove_extract($parse = '') {
  // Here we assume that a URL will be passed in the form of
  // http://www.brightcove.com/video/text-video-title
  // or embed code in the form of <object value="http://www.brightcove.com/embed...".

  // We'll simply return an array of regular expressions for Embedded Media
  // Field to handle for us.
  return array(
    // In this expression, we're looking first for text matching the expression
    // between the @ signs. The 'i' at the end means we don't care about the
    // case. Thus, if someone enters http://www.Brightcove.com, it will still
    // match. We escape periods as \., as otherwise they match any character.
    // The text in parentheses () will be returned as the provider video code,
    // if there's a match for the entire expression. In this particular case,
    // ([^?]+) means to match one more more characters (+) that are not a
    // question mark ([^\?]), which would denote a query in the URL.

    // Brightcove v3.3 - URL style.
    '@\.brightcove\.com/services/player/bcpid.*?\?bctid=(\d+)@i',
    // Brightcove Simple RSS URL style. billk2
    '@\.brightcove\.com/services/link/bcpid.*?/bctid(\d+)@i',

    // Now we test for embedded video code, which is similar in this case to
    // the above expression, except that we can safely assume we won't have a
    // query in the URL, and that the URL will be surrounded by quotation marks,
    // and have /embed/ rather than /video/ in the URL. Note that regular
    // expressions will be tested for matches in the order provided, so you
    // may need to move this value above the other in some cases. Obviously,
    // in the case of this brightcove provider, you could easily improve the
    // regular expression to match against either a URL or embed code with
    // one expression, such as '@brightcove\.com/[watch|embed]/([^"\?]+)@i'.
    // However, many other providers have more complex requirements, so
    // we split them up for this demonstration.


    // Older blog style.
    '@\.brightcove\.com/services/viewer/.*?videoId=(\d+)@i',
    // Brightcove v3.3 - Blog style.
    '@\.brightcove\.com/services/viewer/.*?videoPlayer=(\d+)@i',
    // Brightcove v3.3 - Website style.
    '@id="myExperience(\d+)" class="BrightcoveExperience"@i',
  );
}

//<object id="flashObj" width="486" height="412" classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=9,0,47,0"><param name="movie" value="http://c.brightcove.com/services/viewer/federated_f9/31189372001?isVid=1&publisherID=59121" /><param name="bgcolor" value="#FFFFFF" /><param name="flashVars" value="@videoPlayer=13406455&playerID=31189372001&domain=embed&" /><param name="base" value="http://admin.brightcove.com" /><param name="seamlesstabbing" value="false" /><param name="allowFullScreen" value="true" /><param name="swLiveConnect" value="true" /><param name="allowScriptAccess" value="always" /><embed src="http://c.brightcove.com/services/viewer/federated_f9/31189372001?isVid=1&publisherID=59121" bgcolor="#FFFFFF" flashVars="@videoPlayer=13406455&playerID=31189372001&domain=embed&" base="http://admin.brightcove.com" name="flashObj" width="486" height="412" seamlesstabbing="false" type="application/x-shockwave-flash" allowFullScreen="true" swLiveConnect="true" allowScriptAccess="always" pluginspage="http://www.macromedia.com/shockwave/download/index.cgi?P1_Prod_Version=ShockwaveFlash"></embed></object>

/**
 *  Implement hook emvideo_PROVIDER_data_version().
 */
function emvideo_brightcove_data_version() {
  return MEDIA_BRIGHTCOVE_DATA_VERSION;
}

/**
 *  hook emvideo_PROVIDER_data
 *
 *  Provides an array to be serialised and made available with $item elsewhere.
 *
 *  This data can be used to store any extraneous information available
 *  specifically to the brightcove provider.
 */
function emvideo_brightcove_data($field, $item) {
  return media_brightcove_data($item['value']);
}

/**
 *  hook emvideo_PROVIDER_rss
 *
 *  This attaches a file to an RSS feed.
 */
function emvideo_brightcove_rss($item, $teaser = NULL) {
//   if ($item['value']) {
// //     $file['thumbnail']['filepath'] = $item['data']['thumbnail'];
//
//     return $file;
//   }
}

/**
 * hook emvideo_PROVIDER_embedded_link($video_code)
 * returns a link to view the video at the provider's site.
 *  @param $video_code
 *    The string containing the video to watch.
 *  @return
 *    A string containing the URL to view the video at the original provider's site.
 */
function emvideo_brightcove_embedded_link($video_code) {
  return media_brightcove_video_url($video_code);
}

/**
 * hook emvideo_PROVIDER_duration($item)
 * Returns the duration of the video in seconds.
 *  @param $item
 *    The video item itself, which needs the $data array.
 *  @return
 *    The duration of the video in seconds.
 */
function emvideo_brightcove_duration($item) {
  return media_brightcove_duration($item['value']);
}

/**
 * hook emvideo_PROVIDER_thumbnail
 * Returns the external url for a thumbnail of a specific video.
 *  @param $field
 *    The field of the requesting node.
 *  @param $item
 *    The actual content of the field from the requesting node.
 *  @return
 *    A URL pointing to the thumbnail.
 */
function emvideo_brightcove_thumbnail($field, $item, $formatter, $node, $width, $height, $options = array()) {
  return $item['data']['videoStillURL'] ? $item['data']['videoStillURL'] : $item['data']['thumbnailURL'];
}

/**
 *  hook emvideo_PROVIDER_video
 *  This actually displays the full/normal-sized video we want, usually on the
 *  default page view.
 *  @param $embed
 *    The video code for the video to embed.
 *  @param $width
 *    The width to display the video.
 *  @param $height
 *    The height to display the video.
 *  @param $field
 *    The field info from the requesting node.
 *  @param $item
 *    The actual content from the field.
 *  @return
 *    The html of the embedded video.
 */
function emvideo_brightcove_video($embed, $width, $height, $field, $item, $node, $autoplay, $options = array()) {
  $options['full_size'] = isset($options['full_size']) ? $options['full_size'] : TRUE;
  $options['item'] = $item;
  $options['node'] = $node;
  $options['field'] = $field;
  $options['autoplay'] = $autoplay;
  $output = theme('media_brightcove_video', $item['value'], $width, $height, $options);
  return $output;
}

/**
 *  hook emvideo_PROVIDER_video
 *
 *  This actually displays the preview-sized video we want, commonly for the
 *  teaser.
 *  @param $embed
 *    The video code for the video to embed.
 *  @param $width
 *    The width to display the video.
 *  @param $height
 *    The height to display the video.
 *  @param $field
 *    The field info from the requesting node.
 *  @param $item
 *    The actual content from the field.
 *  @return
 *    The html of the embedded video.
 */
function emvideo_brightcove_preview($embed, $width, $height, $field, $item, $node, $autoplay, $options = array()) {
  $options['full_size'] = isset($options['full_size']) ? $options['full_size'] : FALSE;
  $options['item'] = $item;
  $options['node'] = $node;
  $options['field'] = $field;
  $options['autoplay'] = $autoplay;
  $output = theme('media_brightcove_video', $item['value'], $width, $height, $options);
  return $output;
}
