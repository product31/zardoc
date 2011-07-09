<?php
/**
 * @file
 * 
 * A separate include file to create and possibly populate the default fans nodequeue, since it may be needed in an
 * install or an upgrade.
 */

function sonybmg_fans_install_nodequeue($nid = 0) {
  // Install the nodequeue.
  $nq_return = install_nodequeue_add_nodequeue('Featured Fan Testimonials', NULL, 10, FALSE, 'Feature this fan testimonial',
    'Unfeature this testimonial', array(install_get_rid('moderator')), array('fan'));
  
  if ($nq_return) {
    $qid = (int) $nq_return;
    variable_set('sonybmg_fans_qid', $qid);
    
    if ($nid > 0) {
      $queue = nodequeue_load($qid);
      $subqueues = nodequeue_load_subqueues_by_queue(array($qid));
      if (is_array($subqueues)) {
        $subqueue = array_pop($subqueues);
        nodequeue_subqueue_add($queue, $subqueue, $nid);
      }
    }
  }
}
