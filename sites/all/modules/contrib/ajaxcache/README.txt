$Id: README.txt,v 1.1 2010/02/17 19:18:43 andrewlevine Exp $

How to use AJAX Cache:
1. Enable the module at admin/build/modules
2. Write a function that outputs the info you want to be cached.
3. Implement hook_ajaxcache_presets(). You can see an example in
   ajaxcache.module with the function name ajaxcache_ajaxcache_presets. In this
   example, "test" is the preset name and "ajaxcache_test_callback" is the
   output function.
4. When you are adding the link which is going to be accessed by your javascript
   (whether in Drupal.settings or directly in HTML) you will want to call
   ajaxcache_get_url($preset_name, $args) where $preset_name is the name you
   used in step 3 and $args is an array of arguments you want passed to the
   callback you defined in step 3.

That's it.

A warning: AJAX Cache will not clear any caches by itself. It implements
hook_flush_caches() so it will be cleared on run of cron.php, but otherwise you
will have to clear it yourself with ajaxcache_flush_preset($preset_name).