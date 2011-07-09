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

<?php # dsm($row); ?>
<?php # dsm($fields); ?>

<div class="<?php print $row->node_type; ?>">

  <?php 
    $thisdate=$row->node_created; /*use strtotime() if necessary */
    $month=format_date($thisdate, 'custom', 'M' );
    $day=format_date($thisdate, 'custom', 'd' );
    $year=format_date($thisdate, 'custom', 'Y' );
    print "<div class=\"datebox\"><div class=\"month\">" . $month . "</div><div class=\"day\">" . $day . "</div><div class=\"year\">" . $year . "</div></div>";
  ?>

  <div class="blog-wrapper">
    <h3 class="node-title">
     <?php print l($row->node_title, 'node/' . $row->nid, $options=array('attributes'=>array('class'=>'node-title'))); ?>
    </h3>

    <div class="node-body">
      <?php print $fields['teaser']->content; ?>
    </div>
    
      <div class="links">
        <?php print $links; ?>
      </div>

  </div><!-- news-content-wrapper -->

</div><!-- node-type -->
