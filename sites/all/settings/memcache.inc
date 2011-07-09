<?php
if (!empty($conf['memcache_key_prefix'])) {
  $conf['cache_inc'] = './sites/all/modules/contrib/memcache/memcache.inc';
  $conf['memcache_servers'] = array(
    '172.25.0.108:11811' => 'default',         # Recommended 256M
    '172.25.0.108:11812' => 'block',           # Recommended 128M
    '172.25.0.108:11813' => 'filter',          # Recommended 256M
    '172.25.0.108:11814' => 'form',            # Recommended 5GB
    '172.25.0.108:11815' => 'menu',            # Recommended 1.5GB
    '172.25.0.108:11816' => 'page',            # Recommended 700M
    '172.25.0.108:11817' => 'updates',         # Recommended 8M
    '172.25.0.108:11818' => 'views',           # Recommended 512M
    '172.25.0.108:11819' => 'content',         # Recommended 256M
    '172.25.0.108:11820' => 'views_data',      # Recommended 1G
    '172.25.0.108:11821' => 'mollom',          # Recommended 256M
    #    '172.25.0.108:11822' => 'pathsrc',         # Recommended 8M
    #    '172.25.0.108:11823' => 'pathdst',         # Recommended 8M
  );
  $conf['memcache_bins'] = array(
    'cache' => 'default',
    'cache_block' => 'block',
    'cache_filter' => 'filter',
    'cache_form' => 'form',
    'cache_menu' => 'menu',
    'cache_page' => 'page',
    'cache_updates' => 'updates',
    'cache_views' => 'views',
    'cache_content' => 'content',
    'cache_views_data' => 'views_data',
    'cache_mollom' => 'mollom',
    #    'cache_pathsrc' => 'pathsrc',
    #    'cache_pathdst' => 'pathdst',
  );
}