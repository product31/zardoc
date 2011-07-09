<?php

// this line needs to be outside of any function!!!
_sonyadmin_initialize_theme_settings();

/**
 * Initialize theme settings
 */
function _sonyadmin_initialize_theme_settings() {
  if (is_null(theme_get_setting('_sonyadmin_color_scheme'))) {
    global $theme_key;
  
    // The default values for the theme variables. Make sure $defaults exactly
    // matches the $defaults in the theme-settings.php file.
    $defaults = array(
      '_sonyadmin_color_scheme' => 'green',
    );
      
    // Get default theme settings.
    $settings = theme_get_settings($theme_key);
    // Don't save the toggle_node_info_ variables.
    if (module_exists('node')) {
      foreach (node_get_types() as $type => $name) {
        unset($settings['toggle_node_info_' . $type]);
      }
    }
    
    // Save default theme settings.
    variable_set(
      str_replace('/', '_', 'theme_'. $theme_key .'_settings'),
      array_merge($defaults, $settings)
    );
    
    // Force refresh of Drupal internals.
    theme_get_setting('', TRUE);
  }
}

/**
 * Implementation of hook_preprocess_page().
 */
function _sonyadmin_preprocess_page(&$variables) {
  $variables['body_class'] = 'color-scheme-'. theme_get_setting('_sonyadmin_color_scheme');  
  // Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
}

/**
 * Override of theme_breadcrumb().
 */
function phptemplate_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    $item = menu_get_item();
    $breadcrumb[] = '<span>'. $item['title'] .'</span>';
    return '<div class="breadcrumb">'. implode(' / ', $breadcrumb) .'</div>';
  }
}

/**
 * Override of theme_admin_block().
 */
function phptemplate_admin_block($block) {
  // Don't display the block if it has no content to display.
  if (empty($block['content'])) {
    return '';
  }

  $class = strtolower(preg_replace('/[^a-zA-Z0-9]/', '-', $block['title']));
  $output = <<< EOT
  <div class="admin-panel $class">
    <h3>
      $block[title]
    </h3>
    <div class="body">
      <p class="description">
        $block[description]
      </p>
      $block[content]
    </div>
  </div>
EOT;
  return $output;
}