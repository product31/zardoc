<?php
// $Id$

$info = array(

  // Pre-defined color schemes.
  'schemes' => array(
    '#ffffff,#669934,#ffffff,#ffffff,#222222' => t('Green (Default)'),
    '#ffffff,#d71d11,#ffffff,#ffffff,#222222' => t('Red'),
    '#ffffff,#008bd7,#ffffff,#ffffff,#222222' => t('Blue'),
  ),

  // Images to copy over.
  'copy' => array(
    'images/body.bg.png',
    'images/header.bg.png',
    'images/lullacons/large-alert.png',
    'images/lullacons/large-info.png',
    'images/lullacons/large-stop.png',
  ),

  // CSS files (excluding @import) to rewrite with new color scheme.
  'css' => array(
    'css/style.css',
  ),

);
