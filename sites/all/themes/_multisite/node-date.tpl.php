<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">

    <div class="event-information">
      <?php if ($date || count($taxonomy)): ?>
        <div class="row clear-block">
          <?php if ($node_pager && $page): ?>
            <div class="event-pager event-pager-top"><?php print $node_pager ?></div>
          <?php endif; ?>

          <?php if ($date && $time): ?>
            <div class="event-date"><?php print t('Date: !date at !time', array('!date' => $date, '!time' => $time)) ?></div>
          <?php elseif ($date): ?>
            <div class="event-date"><?php print t('Date: !date', array('!date' => $date)) ?></div>
          <?php endif; ?>

          <?php if (count($taxonomy)): ?>
            <div class="taxonomy"><?php print $terms ?></div>
          <?php endif; ?>
        </div>
      <?php endif; ?>

      <?php if ($location): ?>
        <div class="event-location row clear-block">
          <?php print t('Location: !location', array('!location' => $location)) ?>
        </div>
      <?php endif; ?>

      <?php if ($venue): ?>
        <div class="event-venue row clear-block">
          <?php print t('Venue: ') ?> 
          <?php 
            if($node->field_venue_url[0]['value']){
              print l($venue, $node->field_venue_url[0]['value'], array('class' => 'venue'));
            } else {
              print $venue;
            }  
          ?>
        </div>
      <?php endif; ?>

  <?php if (!$page): /* End the event information early on non-page views. */ ?>
    </div><!-- /event-information -->
  <?php else: /* Display extended event information and body on page view. */ ?>
      <?php if ($tickets && $soldout != 'Yes') print '<div class="event-tickets row clear-block">' . t('TICKETS') . ': ' . l(t('Buy Tickets'), $tickets, array('class' => 'tickets', 'target' => '_blank')) . '</div>'; ?>
      <?php if ($soldout == 'Yes') print '<div class="event-tickets row clear-block">' . t('TICKETS') . ': <strong>' . t('Sold Out') . '</strong></div>'; ?>
      
      <div class="row clear-block">
        <div class="attendee-count"><?php print t('Online attendees: !attendee_count', array('!attendee_count' => $attendee_count)) ?></div>
        <?php print $signup; ?>
      </div>

      <div class="row clear-block">
        <div class="review-count"><?php print t('Reviews: !count', array('!count' => $review_count)) ?></div>
        <div class="rating"><?php print t('Average rating:') ?></div> <?php print $vote_display ?>
        <div class="rate-review"><a href="<?php print url('node/add/review/' . $node->nid) ?>" class="rate-review"><?php print t('Rate + Review') ?></a></div>
      </div>
    </div><!-- /event-information -->

    <?php if ($body): ?>
      <div class="event-body"><?php print $body ?></div>
    <?php endif; ?>

  <?php endif; /* Page view */ ?>
</div>
