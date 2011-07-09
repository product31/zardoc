<?php
function sony_ads_pubsidefiles($op, $name = NULL) {
  $pubsidefiles = array (
    'pointroll' => array(
      'path' => '',
      'file' => 'PointRollAds.htm',
    ),
    'dart_matif' => array(
      'path' => 'doubleclick',
      'file' => 'DARTIframe.html',
    ),
    'eyeblaster' => array(
      'path' => 'eyeblaster',
      'file' => 'addineyeV2.html',
    ),
    'eyewonder' => array(
      'path' => 'eyewonder',
      'file' => 'interim.html',
    ),
    'videoegg' => array(
      'path' => 'videoegg',
      'file' => 'ad.html',
    ),
    'eyeengage' => array(
      'path' => 'trafficmp',
      'file' => 'eyengage.html'
    ),
  ); 
  
  switch($op) {
    case 'hook_menu':
      $items = array();
      foreach($pubsidefiles as $name => $psf) {
        $path =  empty($psf['path']) ? $psf['file'] : $psf['path'] .'/'. $psf['file'];
        
        $items[$path] = array(
          'title' => '',
          'title callback' => FALSE,
          'type' => MENU_CALLBACK,
          'access arguments' => array('access content'),
          'page callback' => 'sony_ads_pubsidefiles',
          'page arguments' => array('view',$name),
        );
      }
      return $items;

    case 'view':
      // Prevent devel shutdown showing log, etc. 
      $GLOBALS['devel_shutdown'] = FALSE;
      
      $file = drupal_get_path('module', 'sony_ads') . '/pubsidefiles/'.  $pubsidefiles[$name]['file'];
      $file_stat = stat($file); 
      
      // Check to make sure that the file exists, and 404 if not.
      if(is_array($file_stat)) {
        // Set headers to cache files longer.
        drupal_set_header("Cache-Control: max-age=31536000 public");
        
        // Set Expires header to 1 year in the future (max per RFC).
        drupal_set_header("Expires: " . gmdate("D, d M Y H:i:s", time() + (60*60*24*365)) . " GMT");
        
        // Set Last Modified to the last time the file was modified. 
        drupal_set_header("Last-Modified: " . gmdate("D, d M Y H:i:s", $file_stat['mtime']) . " GMT");
        
        print(file_get_contents($file));
      }  
      else {
        drupal_set_header("HTTP/1.0 404 Not Found");
      }
      exit;
 
  }
}  