<?php

/**
 * Prepreprocess function for page.tpl.php.
 */
function vanilla_preprocess_page(&$vars) {

}

/**
 * Preprocess function for all node.tpl.php files.
 */
function vanilla_preprocess_node(&$vars) {
  // Add any needed variables.
  switch ($vars['node']->type) {
    case 'album':
      break;
    case 'track':
      break;
  }
}

/**
 * Override of theme_breadcrumb(). Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */
function vanilla_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb) && strlen(drupal_get_title()) > 0) {
    $breadcrumb[] = drupal_get_title();
    return '<div class="breadcrumb">'. implode(' » ', $breadcrumb) .'</div>';
  }
}


/**
 * Override of theme_panels_pane(). Return a themed panel.
 *
 * @param $content
 *   An array containing the panel.
 * @param $pane
 *   An array containing 
 * @param $display
 *   An array containing how the panel should be displayed.
 * @return
 *   A string containing the themed panel.
 */

function vanilla_panels_pane($content, $pane, $display) {
  if (!empty($content->content)) {
    $idstr = $classstr = '';
    if (!empty($content->css_id)) {
      $idstr = ' id="' . $content->css_id . '"';
    }
    if (!empty($content->css_class)) {
      $classstr = ' ' . $content->css_class;
    }

    $output = "<div class=\"panel-pane$classstr\"$idstr>\n";

    $output .= "<div class=\"panel-pane-header-bg\">\n";
    $output .= "<div class=\"panel-pane-content\">\n";
    
    if (user_access('view pane admin links') && !empty($content->admin_links)) {
      $output .= "<div class=\"admin-links panel-hide\">" . theme('links', $content->admin_links) . "</div>\n";
    }
    if (!empty($content->title)) {
      $output .= "<h2 class=\"title\">$content->title</h2>\n";
    }

    if (!empty($content->feeds)) {
      $output .= "<div class=\"feed\">" . implode(' ', $content->feeds) . "</div>\n";
    }

    $output .= "<div class=\"content\">$content->content</div>\n";

    if (!empty($content->links)) {
      $output .= "<div class=\"links\">" . theme('links', $content->links) . "</div>\n";
    }


    if (!empty($content->more)) {
      if (empty($content->more['title'])) {
        $content->more['title'] = t('more');
      }
      $output .= "<div class=\"more-link\">" . l($content->more['title'], $content->more['href']) . "</div>\n";
    }
    $output .= "</div>\n"; // end of .panel-pane-content
    $output .= "</div>\n"; // end of .panel-pane-header-bg
    $output .= "<div class=\"panel-pane-footer-bg\">&nbsp; </div>"; 
    $output .= "</div>\n"; // end of .panel-pane
    return $output;
  }
}