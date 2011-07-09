<?php
// $Id$
/**
 * @file
 * Extends the Brightcove3 Parser to add some Sony-specific functionality
 *
 */

/**
 * Eparse JSON type parsing plugin.
 */
class FeedapiEparserTypeSonyVideo extends FeedapiEparserTypeBrightcove3 {

  /**
   * Retrieve the items collection from the feed.
   * The only difference between this function in
   * FeedapiEparserTypeSonyVideo and FeedapiEparserTypeBrightcove3 is the
   * array_reverse below
   */
  function getItems() {
    if (isset($this->json->videos) && is_array($this->json->videos)) {
      // We're reversing the array because brightcove sorts playlists from
      // front to back and newest is usually front. In our array we want newest
      // to be last so it gets the greatest creation date/NID.
      return array_reverse($this->json->videos);
    }
    // Could not find an item list, return empty list
    return array();
  }
  
  /**
   * Parse feed items.
   */
  function parseItem(&$source_item, &$item) {
    parent::parseItem($source_item, $item);
    //Parse title from name. Only works for our specific implementation of BC
    if ($source_item->name) {
      $item->title = trim($source_item->name);
      if (preg_match('/^.*"(.*)"$/', $item->title, $matches)) {
        $item->title = $matches[1];
      }
        //$item->title = substr($item->title, strpos($item->title, '"')+1, -1);
    }
    // Generate Progressive download URL from FLV streaming URL
    if ($source_item->FLVFullLength && isset($source_item->FLVFullLength->url)) {
      $item->sony_bc_pd_url = $this->generatePDURL($source_item->FLVFullLength->url);
    }
  }
  
  /**
   * We are overriding the download function so we can inject our own URL
   */
  function download() {
    $playlist_id = variable_get('sony_video_bc3_playlist_id', '');
    if (!$playlist_id) {
      watchdog('FeedAPI Eparser', 'Download failed for !feed. No Playlist ID specified !setup_link', array('!feed' => l($node->title, 'node/' . $node->nid), '!setup_link' => l('here', 'admin/sony/setup_video_import')), WATCHDOG_ERROR);
      return FALSE;
    }
    $this->feed->url = $this->generateFeedURL($playlist_id);
    return parent::download();
  }
  
  function generateFeedURL($playlist_id) {
    return 'http://api.brightcove.com/services/library?command=find_playlist_by_id&token=6eUYhfyQNKfGGwY1oxrb62z4Nd6FaYbq7DK2LmhpwFY.&playlist_id=' . $playlist_id;
  }
  
  function generatePDURL($streaming_url) {
    if (strpos($streaming_url, 'rtmp://') !== 0) {
      return $streaming_url;
    }
    $pd_host = 'http://brightcove.vo.llnwd.net/';
    $streaming_paths = array('a500/o2/', 'a500/d2/', 'a500/d3/', 'a500/d4/', 'a500/d5/', 'a500/d6/', 'a500/d7/',);
    $pd_paths = array('pd1/media/', 'pd2/media/', 'pd3/media/', 'pd4/media/', 'pd5/media/', 'pd6/media/', 'pd7/media/');

    $file_ext = strpos($streaming_url, "&mp4:") ? '' : '.flv';
    // Basic formatting of RTMP URLs
	// rtmp://domain/path/&media/pubId/filename&additional_parameters
    // skip rtmp:// and explode URL
    // remember "path" has  2 /s in it
    $url_parts = explode('/', substr($streaming_url, strlen("rtmp://")));
    $pubId = $url_parts[4];
    $filename = substr($url_parts[5], 0, strpos($url_parts[5], '&'));
    
    foreach ($streaming_paths as $key => $path) {
      if (strpos($streaming_url, $path)) {
        return $pd_host . $pd_paths[$key] . $pubId . '/' . $filename . $file_ext;
      }
    }
    watchdog('FeedAPI Eparser', 'Could not find PD path for Sony video feed !feed.', array('!feed' => l($node->title, 'node/' . $node->nid),), WATCHDOG_ERROR);
    return '';
  }
}
