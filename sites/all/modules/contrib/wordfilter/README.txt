// $Id: README.txt,v 1.3.4.1 2008/05/21 16:56:37 jaydub Exp $

Module description
==================

This is a simple word filter that allows site administrators to filter
certain words on a Drupal site. In addition to filtering words in the
body of a node or comment, you can also filter a node or comment title.

Installation and Configuration
==============================

1) Copy the wordfilter module files to your Drupal modules 
   directory (e.g. /sites/all/modules)

2) To install, enable the wordfilter module on the Drupal
   modules page /admin/build/modules

3) Grant the 'administer words filtered' permission to the
   roles desired on the Drupal user permissions page
   /admin/user/access

4) Once the wordfilter module has been installed you can configure
   the settings at /admin/settings/wordfilter

  a) Check 'Enable word filtering on node titles' and 
     'Enable word filtering on comment titles' if you wish
     to filter titles

  b) Enter the default replacement word to use for filtering

5) Add new word filters at /admin/settings/wordfilter/add

  a) Enter a word or phrase you want to filter followed 
     by '|' and the replacement word or phrase. You can 
     enter multiple word and replacement word pairs by hitting 
     return and adding more word pairs. Any word or phrases that 
     do not have a replacement word or phrase will use the default 
     replacement word.

6) Word fitles can be edited or deleted on the wordfilter
   settings page

7) Word filtering on the body text of a node or comment is done
   via a filter enabled for an input format. To enable the wordfilter
   fiter, goto  /admin/settings/filters and then click the configure 
   link for each input format for which you want to enable the 
   wordfilter filter.

   NOTE: From the individual input format configuration pages you can
   click the Rearrange tab to adjust the filter order to resolve any filter
   conflicts.


Original Author
Allen Cook <pyro@gamerswithjobs.com>

Current Project Owner
Steve McKenzie http://drupal.org/user/45890

Current Maintainer
Jeff Warrington http://drupal.org/user/46257
