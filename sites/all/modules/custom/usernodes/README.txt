********************************************************************
                     D R U P A L    M O D U L E
********************************************************************

Name:  usernodes module
Author: coyote

The purpose of this module is primarily to extend user profiles by 
allowing users to create an arbitrary number of nodes of a certain 
type and have them linked on their profile. It's original intention 
was to create an easy way to extend user profiles in complex manners, 
but it can also be used simply to limit the number of nodes a user 
can create of a certain type, or list nodes a user has created in 
their profile.


INSTALLATION:
********************************************************************

1. Place the entire usernodes directory into your Drupal modules/ 
   directory.

2. Enable this module by navigating to:

     administer > modules


Simply drop the module into the Drupal modules folder, and activate 
via the admin panel as normal. Usernode does not require any 
alterations or additions to the database.


FEATURES:
********************************************************************


-- limit the number of nodes of a certain type that users may create

-- create links on user profile pages that lead to nodes created by
   that user of various types

-- create links on nodes of various types that lead to the user's 
   profile

-- provides a simple method to allow a site administrator to add 
   "create content" links directly in a user's profile.

-- create links in a user's profile allowing them to edit or delete 
   the content they have created (as long as they have permissions).



README:
********************************************************************

Once usernodes is enabled, you may edit the settings for each content 
type that you wish to add this module's features to by navigating to 

  settings > content types

User Node Settings consist of:

1. User Node Max:
   Max number of this type of node, per user. Enter 0 for no limit.
   This setting determines whether there is a limit to how many nodes 
   of this type a user can create. It assumes that users can create 
   nodes of this type, so you will have to check and make sure that 
   the various user roles have proper access to add/update/delete, 
   etc. as normal.

2. Nodes to show:
   Number of nodes of this type to list in the user's profile. Enter 0 
   to show none in profile.

3. Display Profile Link in nodes?
   Toggles whether to display a link to the user's profile on nodes 
   of this type, when viewing the full node.


4. Display Profile Link in teasers?
   Toggles whether to display a link to the user's profile on teasers 
   for this node type.

5. Display Edit/Delete Link in profile?
   In user's profile, display links to allow editing/deleting of 
   content? (Links will not be displayed when user lacks node_access 
   permissions to edit/delete.)

6. Display Add Content Link in profile?
   In user's profile, display links to allow adding new content of 
   this type? (Link will not be displayed if user has created maximum 
   amount of that content type.)

7. Profile Category:
   Category on user profile that these nodes will be listed under. If 
   "Nodes to Show" is higher than zero, then the user's profile will 
   contain a node listing (possibly of only one node), of nodes of 
   this type.



HINTS
********************************************************************

Consider removing the standard navigation menu items for creating node 
types that are being used as user nodes in a person's profile. This can 
prevent the annoying behavior of having a create content link appear 
for a node type that the user cannot create any more nodes for.

This module contains basic functionality for allowing lists (or 
individual entries) of user nodes to appear in the user's profile. But 
if the profileplus.module is installed, you may want to disable 
usernode's functionality for such display in favor of using the 
profileplus.module's more advanced methods of displaying such data.



BACKGROUND
********************************************************************

The idea for this module came from the bio.module, which added a "bio" 
node type, and allowed users to create only a single node of that type. 
I decided that it would be even better if any type of node, especially 
flexinodes, could be added to a user's profile in the same way, and if 
the admin could set the number of such nodes that users could create.

Flexinodes are probably most ideal for this purpose, since the 
flexinode module has its own access setting to allow users to create 
or modify their own content of those types, but other node styles could 
be used as well - and another access control module, such as 
taxonomy_access.module could be used to grant create/edit/delete 
privileges.

The concept is that in addition to the more static profile elements, 
users can create complex bios or profile pages, which can appear 
on their profile.

The module can also be used simply to limit the number of nodes of
each type that users are allowed to create.

THANKS
********************************************************************
Kudos to:

q0rban for reorganizing and rewriting the README.txt file,
rendering it clearer and more sensible!

jjeff for patching several UI and usability items, and fixing the 
problem with node-type naming for CCK (and Flexinode).

David Lesieur for adding a setting to allow usernodes to be listed 
as titles, teasers, or whole nodes on profile pages.

Robert Douglass for the initial Drupal-5 port.