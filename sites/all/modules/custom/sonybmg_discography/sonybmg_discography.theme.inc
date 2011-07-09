<?php
// $Id$
/**
 * @file
 * Default theming functions for discography content
 */

/**
 * Theme Album Cover Art block
 *
 * @param $node
 *   The node for the album or track to display album cover information
 */
function theme_sonybmg_discography_album_cover($node) {
  if ($node->field_album_cover[0]['filepath']) {
    if ($node->field_artist[0]['value']) {
      $output = '<div class="album-cover">'. theme('imagecache', 'block', $node->field_album_cover[0]['filepath'], $node->field_artist[0]['value'] . ' - ' . $node->title) .'</div>';
    }
    else {
      $output = '<div class="album-cover">'. theme('imagecache', 'block', $node->field_album_cover[0]['filepath'], $node->title) .'</div>';
    }
    $output .= '<div class="album-title">'. $node->title .'</div>';
    $output = '<div class="album-block">'. $output .'</div>';
    return $output;
  }
}

/**
 * Theme Albums block, listing all the albums by an artist, reverse
 * chronological
 *
 * @param $album_nids
 *   An array of album nids to include in the discography
 */
function theme_sonybmg_discography_albums($album_nids) {
  $output = "";
  if (count($album_nids) > 1) {
    foreach ($album_nids as $delta => $nid) {
      $node = node_load($nid);
      $last = (count($album_nids) == $delta+1) ? ' last' : '';
      $output .= '<div class="album'. $last .' clear-block">';
      if ($node->field_artist[0]['value']) {
        $output .= '<div class="album-cover"><a href="'. url('node/'. $node->nid) .'">'. theme('imagecache', 'discography_small', $node->field_album_cover[0]['filepath'], $node->field_artist[0]['value'] . ' - ' . $node->title) .'</a></div>';
      }
      else {
        $output .= '<div class="album-cover"><a href="'. url('node/'. $node->nid) .'">'. theme('imagecache', 'discography_small', $node->field_album_cover[0]['filepath'], $node->title) .'</a></div>';
      }
      $output .= '<div class="album-title">'. l($node->title, 'node/'. $node->nid) .'</div>';
      if ($node->field_release_date[0]['value']) {
        //TODO - this needs to be revisited the format_date(strtotime(..) solution is a stop gap
        $timestamp = is_numeric($node->field_release_date[0]['value']) ? $node->field_release_date[0]['value'] : strtotime($node->field_release_date[0]['value']);
        $output .= '<div class="album-release">('. format_date($timestamp, 'custom', 'F j, Y', 0) .')</div>';
      }
      $output .= '</div>';
    }
    $output = '<div class="album-discography">'. $output .'</div>';
  }
  return $output;
}

/**
 * Theme Buy It block, displaying link information for the specified album
 *
 * @param $node
 *   The node for the album or track to display buy information
 */
function theme_sonybmg_discography_buy_it($node) {
  $output = '';
  if (is_array($node->field_album_download_links)) {
    foreach ($node->field_album_download_links as $link) {
      $output .= '<li>'. content_format('field_album_download_links', $link, 'default', $node) .'</li>';
    }
  }
  if ($output) {
    $output = '<ul>'. $output .'</ul>';
    $cover = content_format('field_album_cover', $node->field_album_cover[0], 'discography_small_linked', $node);
    $output = '<div class="album-cover">'. $cover .'</div><h3>'. t('Buy It') .'</h3>'. $output;
    $output = '<div class="buy-it">'. $output .'</div>';
  }
  return $output;
}
