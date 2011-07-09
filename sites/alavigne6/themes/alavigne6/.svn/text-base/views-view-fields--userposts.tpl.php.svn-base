<?php
// $Id: views-view-fields.tpl.php,v 1.6 2008/09/24 22:48:21 merlinofchaos Exp $
/**
 * @file views-view-fields.tpl.php
 * Default simple view template to all the fields as a row.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->separator: an optional separator that may appear before a field.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>
<?php 
  $url =NULL; 
  $fragment =NULL;
  switch ($fields['type']->content) {
    case 'Comment':
    case 'Review':
    case 'Reply':
    if ($row->node_node_comments_nid) {
      // It's a comment! link to the parent node
      $url = drupal_get_path_alias('node/' . $row->node_node_comments_nid);
    } else {
      // this should never be the case, but put in as a safe default
      $url = drupal_get_path_alias("node/" . $row->nid);
    }
    $fragment = "comment-" . $row->nid;    
      break;
    case 'Forum Reply':
      $url = drupal_get_path_alias("node/" . $row->nid);
      break;
  case 'Forum Topic':
    $url = drupal_get_path_alias('node/' . $row->nid); 
    // Forum topics don't always have body content, so replace that with title
    if (!$fields['body']->content) {
        $fields['body']->content = $fields['title']->content;
    }
      break;
    default:
      $url = drupal_get_path_alias("node/" . $row->nid);
      break;
  } 
?>


<div class="userpost-row">
  <div class="thumb">
    <?php if($row->users_picture) {
      // if user has a photo, use imagecache to resize
      /*  Change the second parameter in the theme function to a different imagecache preset for a different photo size (admin/build/imagecache) - 
                also change in style.css for the default user's image, which is not resized by imagecache */ 
      $img = theme('imagecache', 'icon_small', $row->users_picture, $row->users_name, $row->users_name); 
    } else {
      // else print default image, css will resize
      $img = $fields['picture']->content; 
    } ?>
    <?php if ($row->users_uid > 0) {
      print l($img, 'user/' . $row->users_uid, array('html'=>TRUE)); 
    } else {
      print $img;
    } ?>
  </div>

  <div class="activity-data">
  <div class="data-type">
    <?php print l($fields['type']->content, $url, array('fragment' => $fragment, 'html' => TRUE)); ?> by <span><?php print $fields['name']->content; ?></span>
  </div>

  <div class="data-body">
    <?php 
    if (!arg(0)) { 
      /*  Change the parameter in truncate_utf8() to show more or less of the trimmed text */ 
      print l(strip_tags(truncate_utf8($fields['body']->content,33,TRUE,TRUE)), $url, array('fragment' => $fragment, 'html' => TRUE)); 
      }
    elseif (arg(0) == 'home') {
      print l(strip_tags(truncate_utf8($fields['body']->content,33,TRUE,TRUE)), $url, array('fragment' => $fragment, 'html' => TRUE));
      }
    else {
      print l(strip_tags(truncate_utf8($fields['body']->content,55,TRUE,TRUE)), $url, array('fragment' => $fragment, 'html' => TRUE));
    } ?>
  </div>
  </div>
</div>