blockregion.module README
=========================

$Id$


Description
-----------

Some users have complained that block configuration is difficult for 
multi-themes, because the settings for block status, region, weight, and 
throttle need to be made separately for each enabled theme. This simple 
module provides a fix, allowing the optional configuration of blocks for 
all themes at once. Enable this module and go to admin/build/block (the 
bottom).

Project page: <http://drupal.org/project/blockregion>


Notes
-----

Block Region is used to propagate block settings to all installed and active
themes. This is a useful functionality for multi-theme sites (eg: a site where
each different user can theme his own blog keeping displayed blocks intact).
The module not only shares block settings, it also tries to guess where the
block is most likely to be set in other themes (eg: “left section” matches to 
“Left Sidebar 1″ more than “Footer”). Right or not, a choice is made and the
block is placed. You still can edit its position manually from the same admin
page, after switching to the problematic theme.

Two are the possible sharing options:

    * Apply all settings except "Region" to all themes' blocks: will copy block
      title, its status, visibility options, etc for each block set in the current
      theme to all the active themes on the site
    * Apply "Region" to all themes matching that region names are similar to current
      theme ones: will try to match region placement for each block of
      the current theme within all the regions of each active themes



Credits
-------

Nedjo Rogers, nedjo <http://drupal.org/user/4481>
  Original Author, Drupal 4.7 version
Axel Kollmorgen, ax <http://drupal.org/user/8>
  Drupal 5 port, added "copying" of regions (to all themes with the same 
  regions), made scope of settings customizable, cut code to half the size
Adriano Dalpane, dalad <http://drupal.org/user/388175>
	Drupal 6 port, improved share (matches all themes with similar region
  names), fixed settings selector position in blocks admin page
[feel free to add]
