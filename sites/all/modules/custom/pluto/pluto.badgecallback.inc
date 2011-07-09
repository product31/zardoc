<?php

function pluto_badge_view($achievement) {
  $output = theme('pluto_badge_popup_view', $achievement);

  print $output;
  
  // return nothing so that the page doesn't get themed
  return;
  
}