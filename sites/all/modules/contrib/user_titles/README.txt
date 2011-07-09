// $Id: README.txt,v 1.5.2.2 2010/02/02 11:20:15 agileware Exp $

---------------------DESCRIPTION-------------------------------------------

This module allows the administrator to assign titles to users based upon
their role and  the number of nodes they have created.
It also has the ability to use other modules point schemes to assign titles.
For example the userpoints module.
Images can also be assigned to the titles.
Titles and/or their images can be displayed anywhere in your theme using
the supplied functions and node/comment template variables.

---------------------INSTALLATION------------------------------------------

1. Copy the user_titles directory to sites/all/modules
2. On the modules page (admin/build/modules) enable the user titles module
3. If you want to integrate with userpoints you now have to enable the user
titles userpoints module also

----------------------UPGRADING--------------------------------------------

If you are upgrading from a pre-roles-based version you won't lose your
existing titles.  They will be put under the authenticated user role and
that role will be placed at the top of the role priority table.
This means that your site will continue working the same after upgrading
without you having to change any settings.

NOTE: If you were previously using userpoints to calculate your titles
you must now enable the user titles userpoints sub module.

------------------------USAGE----------------------------------------------

After the module is installed you need to set up your titles:
1. Go to the user titles setttings page (admin/user/user-titles)
---Settings:---
* If you are using an another module to calculate points this is
where you select the module to use.
* Counted node types is only used if you are using user titles
to calculate the points.
* The images directory is a subdirectory of the file directory
(sites/default/files) where you want user titles images stored.
---Role priority:---
User titles are based on roles.  This makes it possible to have different
titles for each role (or no titles for a specific role) but it also
makes things a bit more complicated.
* If a user has one role (authenticated user) then they will get whatever
titles are assigned to that role.
* If a user has multiple roles, this is where you set which one gets used.
The table is for weighting the roles.
If a user has multiple roles these weights are checked against the user's
roles and the role with the lightest weight is used.

An example usage of this is:
You have a moderator role and an administrator role and you want moderators
to have different titles to regular authenticated users and admins to have
no titles.
Order the roles like this:
  administrator
  moderator
  authenticated user
Then set no titles for the administrator role and different titles for the
moderator and authenticated user roles.

You can then use the "Add title" tab (admin/user/user-titles/add/title) to
add titles to your roles.
And you can use the "Titles" tab (admin/user/user-titles/titles) to view
your titles.

After all this has been done the module still won't appear to do anything.
This is because it assigns titles to users but doesn't print them.
To print the user titles you need to add some code to your theme.

This module will automatically populate the
$user_title and $user_title_image variables into your nodes and comments.

In your node.tpl.php and/or your comment.tpl.php, choose where you would
like the user title to appear, and place this code:

  <?php if ($user_title): ?>
    <div class="user-title">
      <?php
        print $user_title;
        print $user_title_image ? $user_title_image : '';
      ?>
    </div>
  <?php endif; ?>


If you need the user titles elsewhere you can get them using these functions:
  user_titles_get_user_title($user) returns the user's title.
  user_titles_get_user_image($user) returns the user's image.
The $user parameter can be either a user object or uid integer.

----------------------DEVELOPERS-------------------------------------------

This module is developed and maintained by Agileware (www.agileware.net)
