<?php
// $Id: views-view-fields.tpl.php,v 1.5 2008/05/05 23:51:47 merlinofchaos Exp $
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

<div class="track-summary clear-block">
  <div class="track-number"><?php print $track_number ?></div>
  <div class="track-title">
    <?php if ($audio_file_url): ?>
      <a href="<?php print $audio_file_url; ?>" onclick="popUpAudio(this.href); return false;"><?php print $title; ?></a>
    <?php else: ?>
      <span class="no-link"><?php print $title; ?></span>
    <?php endif; ?>
   </div>
   <?php if (module_exists('fivestar')): ?>
     <div class="track-rating fivestar-small"><?php print $rating_widget ?></div>
     <div class="track-average" id="fivestar-average-<?php print $row->nid ?>"><?php print $rating_average . ' &nbsp; '; ?></div>
  <?php endif; ?>
</div>
