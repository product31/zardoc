; $Id: README.txt,v 1.1.2.1 2010/04/01 19:25:35 andrewlevine Exp $

Description
------------
The winners module can be used to select users (winners of contests) based on a
view which defines the rules of how these users should be selected. The default
"winner choosing view" will choose random users that have never won any contest,
but you can configure a view with whatever rules you want to choose winners.

Winners that are selected for a contest are saved in a simple database table,
which can be accessed through views or viewed through the winners module
interface.


Instructions
-------------
1. Install the module by following the standard Drupal module installation
   instructions: http://drupal.org/getting-started/install-contrib/modules (Make
   sure to enable the "moderate winners" permission for any roles you want to be
   able to choose winners)
2. Go to /admin/user/winners, enter the name of your contest
3. Select the contest from the autocomplete dropdown if you have already entered
   it, otherwise it will be created automatically
3. Select the winner choosing view to use. If you want to create your own it may
   be easiest to clone the default view "winner_chooser_default"
4. Select the number of winners you want to pick for this contest
5. Press "Proceed to next step"
6. Verify that your winners look correct and choose "Finalize these winners"
7. Now you can view the winners of this contest at /admin/user/winners/contests