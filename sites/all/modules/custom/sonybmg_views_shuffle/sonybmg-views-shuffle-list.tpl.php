<?php
// $Id: views-view-list.tpl.php,v 1.3 2008/09/30 19:47:11 merlinofchaos Exp $
/**
 * @file views-views-shuffle.tpl.php
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>
<div id="<?php print $shuffle_id; ?>" class="item-list">
  <?php if (!empty($title)) : ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>
  <div id="<?php print $shuffle_id; ?>-nav">
    <a class="prev" href="#">&laquo;</a>
    <a class="next" href="#">&raquo;</a>
  </div>
  <<?php print $options['type']; ?> class="views-shuffle">
    <?php foreach ($rows as $id => $row): ?>
      <li class="<?php print $classes[$id]; ?>"><?php print $row; ?></li>
    <?php endforeach; ?>
  </<?php print $options['type']; ?>>
</div>