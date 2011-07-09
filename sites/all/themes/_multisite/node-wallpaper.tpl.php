<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">
  <?php /*if ($page == 0): 
  <div class="content-type">
    <?php print drupal_strtoupper($node->type); ?>
  </div>
  <h2 class="node-title title">
    <a href="<?php print $node_url ?>"><?php print $title; ?></a>
  </h2>
 endif; */?>
  
  <?php if (count($taxonomy)): ?>
    <div class="taxonomy"><?php print t(' in ') . $terms ?></div>
  <?php endif; ?>
  
  <div class="content">
    <?php print theme('imagecache', 'thumbnail', $node->field_wallpaper[0]['filepath']); ?>
    <?php //print $content; ?>
  </div>
  
<?php
  // Print links to various resolutions.
  if (!empty($node->field_wallpaper[0])) {
    $sizes = array('800x600', '1024x768', '1280x960');
    $links = array();
    foreach ($sizes as $size) {
      $links[] = array(
        'title' => $size,
        'href' => imagecache_create_url($size, $node->field_wallpaper[0]['filepath']),
      );
    }
    print theme('links', $links);
  }
?>
 
</div>
