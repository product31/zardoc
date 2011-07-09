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


  <?php if ($fields['field_video_embed']->content || $fields['field_photo_fid']->content){
      if ($fields['field_video_embed']->content) {
          $pic=$fields['field_video_embed']->content;
          $pic.="<div class='playvideo'>" . l(t('Play Video') , 'node/' . $row->nid, $options=array('attributes'=>array('class'=>'playvideolink'))) . "</div>";
        } else {
          $pic=$fields['field_photo_fid']->content;
          }
    print "<div class=\"pic\">" . $pic . "</div>";
    } 

  ?>
  <div class="news-content-wrapper">
    <h3 class="node-title">
     <?php print l($row->node_title, 'node/' . $row->nid, $options=array('attributes'=>array('class'=>'node-title'))); ?>
    </h3>

    <div class="node-body">

      
      <?php 
      if (strlen($fields['teaser']->content)) {
        if (strlen($fields['teaser']->content)<strlen($fields['body']->content)) {
          $fields['teaser']->content .= ' ' . l(t('More...'), 'node/' . $row->nid, $options=array('attributes'=>array('class'=>'node-title'))); 
        }
        print $fields['teaser']->content;
      }
      ?>
      
      
      
    </div>
    

    <?php if ($row->node_type=='news' || $row->node_type=='video'): ?>
      <div class="links">
        <?php print $links; ?>
      </div>
    <?php endif; ?>    
  </div><!-- news-content-wrapper -->

</div><!-- node-type -->
