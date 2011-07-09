<?php
/**
 * This is the include to turn on boost with the standard settings.
 * To include it, put "include_once('sites/all/settings/boost.inc');" into settings.php
 */

#Drupal core settings.

# Enable normal caching.
$conf['cache'] = '1';
# Cron clears the cache every 5 minutes. Setting this to 3 minutes ensures that these pages will clear on every cron run.
$conf['cache_lifetime'] = '300';
# Our webservers are doing the gzipping so don't have Drupal double zip it.
$conf['page_compression'] = '0';
# This allows blocks to be cached for both anonymous and logged in users
$conf['block_cache'] = '1';
# Aggregate CSS
$conf['preprocess_css'] = '1';
# Don't aggregate JS, seems to cause problems with ads?
$conf['preprocess_js'] = '0';

# Boost 
# Enable boost caching.
$conf['boost_enabled'] = '1';
# Cache pages for 5-minutes to match the cron driven cache clearing interval.
$conf['boost_cache_lifetime'] = '300';
# Boost will cache pages that end with "?page=1" among others (anything with a "?" in the url). This is not necessary because we use the drupal clean url system.
$conf['boost_cache_query'] = 1;
# Boost will cache most drupal pages.
$conf['boost_cache_html'] = 1;
# Boost will cache .xml and /feed urls as xml data.
$conf['boost_cache_xml'] = 1;
# Default is 1 hour and can be increased for sites that do not change very much. The maximum cache lifetime is the maximum amount of time that will elapse before the cache is emptied. Cache lifetime gets checked on cron runs. Flushing the content before it is expired can happen, for example when a node is edited.
$conf['boost_cache_xml_lifetime'] = '3600';
# By default this section is not checked because we do not optimize or cache javascript.
$conf['boost_cache_json'] = 0;
# By default this section is disabled because we are not optimizing or caching javascript.
$conf['boost_cache_json_lifetime'] = 3600;
# We're aggregating CSS files and during the theme rebuild the CSS file name changes, letting Boost cache a copy keeps it around until pages referencing the old CSS are cleared. 
$conf['boost_cache_css'] = 1;
# By default this section is not checked because we do not optimize or cache javascript.
#$conf['boost_cache_js'] = 0;
# Enter one page per line as Drupal paths. The '' character is a wild-card. Example paths are 'blog' for the blog page and blog/ for every personal blog, is the front page. If the PHP-mode is chosen, enter PHP code between php tags.
$conf['boost_cacheability_pages'] = 'user/register
mollom/captcha/*/*
mobile/feeds/*';
$conf['boost_cacheability_option'] = '0';
# Name the directory boost will use to store files. If it does not already exist, Boost will create the directory based on this setting.
#$conf['boost_root_cache_dir'] = 'cache';
# Must enable this for i18n see http://drupal.org/node/545908#direct
$conf['boost_multisite_single_db'] = 1;
$conf['boost_normal_dir'] = '';
$conf['boost_gzip_dir'] = 'gz';
$conf['boost_perm_normal_dir'] = '';
$conf['boost_perm_gz_dir'] = 'gz';
# If this is disabled we would will need some other method of clearing cached pages. If Disabled, files have to be manually deleted from server or cleared using the administrative interface (Enable the Boost: Pages cache status block).
$conf['boost_expire_cron'] = '1';
# This helps to reduce server load by keeping cached pages that have not changed. We looked into this and Boost does this by checkin the timestamps of the following tables: (node_revisions, history, files, comments, node, node_comments_statistics and votingapi_vote) in the function boost_has_site_changed(). This function returns a true or false value that tells boost to allow cron runs to clear expired content.
$conf['boost_check_before_cron_expire'] = 1;
# This severely limits i18n support so is should be turned off, see http://drupal.org/node/545908#adv
$conf['boost_only_ascii_path'] = 0;
# Asynchronous Operation: output HTML, close connection, then store static file helps to speed up your caching process even more. Here the caching will generate the cached HTML page without paying close attention to the PHP on the page. PHP will remain running in the background, but the cache page will only pay attention to HTML. This will also help to generate faster page loads 
$conf['boost_asynchronous_output'] = 1;
# Disable this if you have to set settings for each dir/subdir, due to the way your server operates (permissions, etc...).
$conf['boost_flush_dir'] = 0;
# When a node belongs to term/1 and it gets created/updated/deleted, the cached page(s) for term/1 will be cleared.
$conf['boost_flush_node_terms'] = 1;
# Under site maintenance when the status is set to offline, boost clears its cache. If you do not want this to happen, clear this checkbox. Pages that are not cached will still send out a Site off-line message, so be smart if turning this off.
$conf['boost_clear_cache_offline'] = 0;
# Because we have selected to only expire content if there is a change and not on cron runs, We use that content to serve the user instantly.
$conf['boost_overwrite_file'] = 0;
# Selected - Do not cache the page if there are PHP errors. Not Selected - Cache pages even if it might contain errors.
$conf['boost_halt_on_errors'] = 1;
# Selected - Do not cache the page if there are drupal messages. Not Selected - Cache pages even if it might contain a drupal message.
$conf['boost_halt_on_messages'] = 1;
$conf['boost_permissions_file'] = '';
$conf['boost_permissions_dir'] = '';
# You can tell Boost to Ignore cache flushing (recommended only if you are caching CSS and JS files) and whether you want to record all Boost errors to the Drupal watchdog recent log entries. This will put the site into a static cached state. Because we are not caching JS and want the cache cleared completely we choose the first selection.
#$conf['boost_ignore_flush'] = '0';
# We are not using the cron crawler
$conf['boost_crawl_on_cron'] = 0;

# Boost Apache .htaccess settings generation
$conf['boost_server_name_http_host'] = '%{HTTP_HOST}';
