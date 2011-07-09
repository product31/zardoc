<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">

<?php # dsm($node); ?>
<?php # dsm($time); ?>


  <?php 
    if ($node->field_date[0]['value']) {
      $thisdate=strtotime($node->field_date[0]['value']); /*use strtotime() if necessary */
      $month=format_date($thisdate, 'custom', 'M' );
      $day=format_date($thisdate, 'custom', 'd' );
      $year=format_date($thisdate, 'custom', 'Y' );
      print "<div class=\"datebox\"><div class=\"month\">" . $month . "</div><div class=\"day\">" . $day . "</div><div class=\"year\">" . $year . "</div></div>";
    } 
  ?>
  <div class="event-information">
    <?php  
      /* Set the venue/location as the title */
      if ($venue) {
        $thistitle=$venue;
      }
      if ($venue && $location) {
        $thistitle.=', ' . $location;
      } elseif ($location) {
        $thistitle.= $location;
      }
    ?>


    <?php if ($venue || $location): ?>
      <h3 class="node-subtitle">
        <?php
          if($node->field_venue_url[0]['value']){
            print l($thistitle, $node->field_venue_url[0]['value'], array('class' => 'node-subtitle'));
          } else {
            print $thistitle;
          }  
        ?>
      </h3>
    <?php endif; ?>

  <?php if (!$page): /* End the event information early on non-page views. */ ?>
    </div><!-- /event-information -->
  <?php else: /* Display extended event information and body on page view. */ ?>
      <?php if ($tickets && $soldout != 'Yes') print '<div class="event-tickets row clear-block">' . t('Tickets') . ': ' . l(t('Buy Tickets'), $tickets, array('class' => 'tickets', 'target' => '_blank')) . '</div>'; ?>
      <?php if ($soldout == 'Yes') print '<div class="event-tickets row clear-block">' . t('Tickets') . ': ' . t('Sold Out') . '</div>'; ?>
      
      <div class="attendee-count"><?php print t('Online attendees: !attendee_count', array('!attendee_count' => $attendee_count)) ?> <?php print $signup; ?></div>
      <div class="review-count"><?php print t('Reviews: !count', array('!count' => $review_count)) ?> <a href="<?php print url('node/add/review/' . $node->nid) ?>" class="rate-review"><?php print t('Review') ?></a></div>

      <?php if ($body): ?>
        <div class="event-body"><?php print $body ?></div>
      <?php endif; ?>

    </div><!-- /event-information -->

    <?php if ($node_pager): ?>
      <div class="event-pager event-pager-bottom"><?php print $node_pager ?></div>
    <?php endif; ?>
    
  <?php endif; /* Page view */ ?>
</div>
