// $Id$

SonyBMG Offensive

This module gives site users the ability to flag a piece of content as 
offensive.  After a number of users have flagged a node, it is unpublished and 
an email is sent to a moderator.

Technical Details
- Implements hook_flag_default_flags() to define the offensive flag.
- In hook_enable(), adds flag actions to the offensive flag to unpublish the 
  node and email a moderator after 10 flags.
- Provides a default view that lists all content which have been flagged. The
  view uses views_bulk_operations to allow the moderator to quickly delete or
  restore content.