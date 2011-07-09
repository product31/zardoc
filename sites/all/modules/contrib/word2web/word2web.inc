<?php
// $Id$
/**
 * @file
 * Helper functions standard word2web modules.
 *
 * TODO: It'd be nice to allow users to toggle between simple quotes and the
 * html entities as show on http://shiflett.org/blog/2005/oct/convert-smart-quotes-with-php
 */

/**
 * Utility function to replace microsoft "smart" characters into usable
 * UTF-8. From http://shiflett.org/blog/2005/oct/convert-smart-quotes-with-php
 */
function _word2web_convert_chr($string) {
  $search = array(
    chr(145),
    chr(146),
    chr(147),
    chr(148),
    chr(151),
  );

  $replace = array(
    "'",
    "'",
    '-',
    '"',
    '-',
  );

  return str_replace($search, $replace, $string);
}

/**
 * Helper function that strips out MS Word tags.
 *
 * @param $html
 * A raw HTML string containing MS Word tags.
 * @param $strip_images
 * Optional. Boolean value that triggers the stripping of image tags.
 * @return
 * Cleaned up HTML.
 */
function _word2web_filter($html, $strip_images = FALSE) {

  preg_match('/charset=([\w-]+)/', $html, $matches);
  if (!empty($match) && $matches[1] == 'windows-1256') {
    $html = iconv('windows-1256', 'utf-8', $html);
  }
  elseif (!empty($match) && $matches[1] == 'windows-1252') {
    $html = iconv('windows-1252', 'utf-8', $html);
  }
  else {
    // This is useful but breaks other utf8 characters. We also don't really
    // need it if we're good at keeping utf8 characters through processing.
    // TODO - Add this back as optional?
    // $html = _word2web_convert_chr($html);
  }

  // Make real sure everything is utf-8. We really don't trust out input.
  $html = iconv('UTF-8', 'UTF-8//IGNORE', $html);
  $html = mb_convert_encoding($html, 'HTML-ENTITIES', 'UTF-8');

  // If we want to strip images we just skip converting them.
  if (!$strip_images) {
    // Convert MS Word image tags into more HTML standard tags so they aren't
    // filtered out below. They still exists in the html for now.
    $html = _word2web_covert_image_tags($html);
  }

  // Load our XML into an object. By loading it once and the keeping the object
  // we can keep any encoding information in the meta tags attached to the
  // object through out processing.
  $html_dom = new DOMDocument();
  // This is guaranteed not to be entirely valid HTML so suppress the errors
  // reminding us of this fact.
  @$html_dom->loadHTML($html);

  // Apply our XSL transformations.
  $path = drupal_get_path('module', 'word2web') . '/';
  $html_dom = _word2web_xslt_transform($html_dom, $path .'empty.xsl');
  $html_dom = _word2web_xslt_transform($html_dom, $path .'w2html.xslt');

  return $html_dom->saveHTML();
}

/**
 * Finds word image tags and converts them into html style image tags.
 *
 * Note: Old tag is not removed and expected to be cleaned up by the caller.
 *
 * @param $html
 * HTML string containing MS Word tags.
 * @return
 * HTML string.
 */
function _word2web_covert_image_tags($html) {
  //
  $html_dom = new DOMDocument();
  // This is guaranteed not to be entirely valid HTML so suppress the errors
  // reminding us of this fact.
  @$html_dom->loadHTML($html);

  // TODO do something with v:imagedata information?
  // $vimages = $html->getElementsByTagName("v:imagedata");

  /*
   * This little bit changes img tags into image tags so that they aren't wiped
   * out by the (validating) XSL transformations.
   */
  $images = $html_dom->getElementsByTagName('img');
  foreach ($images as $im) {
    $image_node = $html_dom->createElement('image');
    $image_node->setAttribute('src', $im->getAttribute('src'));
    $im->parentNode->insertBefore($image_node, $im);
  }
  return $html_dom->saveXML();
}

/**
 * Utility function for crunching XML through XSLT
 */
function _word2web_xslt_transform(&$xml, $xsl_file, $params = array()) {
  // load specified stylesheet and set any parameters
  // Without Domdocument charsets: french breaks, arabic remains broken
  $xsl = new DOMDocument();
  $xsl->load($xsl_file);
  $xslt = new XSLTProcessor();
  $xslt->importStylesheet($xsl);
  if (is_a($xml,'DOMNode')) {
    // return transformed xml dom into another dom document.
    return @$xslt->transformToDoc($xml);
  }

  $html_dom = new DOMDocument();
  // This is guaranteed not to be entirely valid HTML so suppress the errors
  // reminding us of this fact.
  @$html_dom->loadHTML($html);

  // Return transformed XML as an XML document(string).
  return $xslt->transformToXML($html_dom);
}

