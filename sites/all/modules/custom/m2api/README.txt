This module provides methods for interacting with the new M2 API and some
tools for ingesting the provided data into Drupal nodes.

At the time of this writing there are quite a few unfinished and unimplemented
parts of the system. They should be easily found with TODO statements. More
general problems have been placed in function documentation or file headers.

There are several parts to the module. The first part is code surrounding
making requests to the api and abstraction of those requests. It is mostly
all located in "includes/api.inc" and can be easily included for use with
"m2api_include('api');" There are several functions for the abstraction of
some api requests and they are general wrappers around the _m2api_request
function which builds standardized requests against the api.

The second part of the module makes use of the api to sync data. There are
2 conceptual types of data being synced which correspond to 2 tables in the
database.
  1) Products
   These are attached to both albums and tracks. Tracks have a 1:1
   relationship where as albums don't necessarily. There can be digital
   and physical versions of an album on the m2 side.
  2) Albums
   Albums have a share object in m2 that we sync directly to our albums.

Product syncing uses a rough ctools plugin system so a lot of logic can be
shared with callbacks at certain points to adjust and add data. This is all
mostly working except for the data mapping on nodes. See the TODO's in the
plugins.

There is a central function for triggering a sync(_m2api_update_site) which runs
through all the needed steps to update the site. For larger sites it could run
long and time out on the first run, but the MD5 that is placed in front of writes
should alleviate that and allow it to recover and not happen on later runs.

There are a couple methods for salting the MD5 used to salt the cache value that
I've provided to make cache rebuilds easier to trigger. There is a global that can
be used for code level changes that are might not be automatically triggered, an
update to 0 of the MD5 field in the database will work for database level changes,
and a variable to allow refreshes through a UI.

I've also included a file with some test page callbacks. The menu entries are
commented out in hook_menu() and should be on production sites but it can be
very useful for testing synchronization and api calls.
