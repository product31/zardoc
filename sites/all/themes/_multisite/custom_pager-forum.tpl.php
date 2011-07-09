<?php
if (is_numeric($nav_array['prev'])) {
  $prev = node_load($nav_array['prev']);
}
if (is_numeric($nav_array['next'])) {
  $next = node_load($nav_array['next']);
}

$output = '<div class="node-navigation clear-block">';

if ($prev) {
  $output .= l($prev->title, 'node/'. $prev->nid, array('class' => 'node-previous arrow', 'title' => $prev->title));
}
else {
  $output .= '<span class="node-previous-disabled arrow">Previous</span>';
}

$output .= l(t('Forum index'), 'forum', array('class' => 'node-up arrow', 'title' => $prev->title));


if ($next) {
  $output .= l($next->title, 'node/'. $next->nid, array('class' => 'node-next arrow', 'title' => $next->title));
}
else {
  $output .= '<span class="node-next-disabled arrow">Next</span>';
}

if (module_exists('fivestar')) {
  $output .= '<div class="node-rating">';
  $output .= '<div class="rate-it">Rate It:</div>';
  $output .= fivestar_widget_form($node);
  $output .= '</div>';
  $output .= '</div>';
}
print $output;