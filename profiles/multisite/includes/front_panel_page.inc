<?php
/**
* Default labeling and weight for this profile include.
*/
function front_panel_page_info() {
  return array(
    'name' => st('Front Panel Page'),
    'default_value' => TRUE,
    'disabled' => TRUE,
    'weight' => 0,
  );
}

/**
 * Required modules in order for these options to be created successfully.
 */
function front_panel_page_modules() {
  return array('panels', 'page_manager', 'views_content', 'sonybmg');
}