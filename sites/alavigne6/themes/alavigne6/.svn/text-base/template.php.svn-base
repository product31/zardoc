<?php

/**
 * Prepreprocess function for page.tpl.php.
 */
function alavigne6_preprocess_page(&$vars) {

 // Login block with Sony Connect links (if enabled)
  if (user_is_logged_in()) {
    $vars['login'] = '<div class="logged-in">' . t('<a href="!userlink">My Account</a> / <a href="!logout">Logout</a>', array(
      '!userlink' => url('user'),
      '!logout' => url('logout')
    )) . '</div>';
  }
  else {
    $vars['login'] = '<div class="login-popup"><div class="signin">';
    $vars['login'] .= t('<a class="button" href="!login">Log in</a>', array('!login' => url('user/login', array('query' => drupal_get_destination()))));
    $vars['login'] .= 'Already a member?</div><div class="reg">';
    $vars['login'] .= t('<a class="button" href="!register">Sign-up</a>', array('!register' => url('user/register', array('query' => drupal_get_destination()))));
    $vars['login'] .= 'Not a member yet?';
    $vars['login'] .= '</div></div>';

    /* $vars['login'] .= t('<a class="login-link" href="!login">Sign in <strong>@count Online</strong></a>', array( */
    $vars['login'] .= t('<a class="login-link" href="!login">Sign in</a>', array(
      /*'@count' => $vars['online_users'],*/
      '!login' => url('user/login', array('query' => drupal_get_destination())),
      '!register' => url('user/register', array('query' => drupal_get_destination())))
    );

  }

  // Retitle video taxonomy pages
/*  if (arg(0)=='videos'){
    if (arg(1)){
       $thistax=taxonomy_get_term(arg(1));
       $vars['title']='Avril Lavigne\'s ' . $thistax->name;
    }
  }
*/

  // sizing the eTrust logo
  $vars['etrust'] = _multisite_etrust('s');

}

/**
 * Preprocess function for all node.tpl.php files.
 */
function alavigne6_preprocess_node(&$vars) {
  // Add any needed variables.
  switch ($vars['node']->type) {
    case 'video':
      $vars['node']->links['node_replies'] = array(
        'title' => format_plural($vars['node']->comment_count, 'Reply (1)', 'Replies (@count)'),
        'href' => "node/add/comment/". $vars['node']->nid
      );

      $vars['node']->links['node_permalink'] = array(
        'title' => t('Permalink'),
        'href' => "node/". $vars['node']->nid
      );

      $vars['links'] = theme('links', $vars['node']->links);

      //custom video breadcrumb
      //$vars['bc'] = l(t('Videos'), 'videos') . ' / ';
      foreach($vars['node']->taxonomy as $item => $name){
        $vars['bc'] .= l($vars['node']->taxonomy[$item]->name, "videos/" . $vars['node']->taxonomy[$item]->tid) . ' / ';
      }
      $vars['bc'] .= $vars['node']->title;
      break;
    case 'photo':
    case 'official_photo':
      $vars['node']->links['supersize']['title'] =  t('View Full Size Image');
      $vars['node']->links['supersize']['attributes']['class'] = 'new-window';
      //dsm($vars['node']->links['supersize']['attributes']);
      $vars['links'] = theme('links', $vars['node']->links);

      //custom photo breadcrumb
      $gal = (!empty($vars['node']->field_gallery_official[0]['nid'])) ? $vars['node']->field_gallery_official[0]['nid'] : $vars['node']->field_gallery[0]['nid'];
      $vars['bc']  = l(t('Photos'), 'photos') . ' / ';
      $vars['bc'] .= l(t('Gallery'), "node/" . $gal) . ' / ';
      $vars['bc'] .= $vars['node']->title;

      break;
    case 'album':
      /* add jplayer js */
      drupal_add_js('sites/all/libraries/jQuery.jPlayer.1.2.0/jquery.jplayer.min.js', 'theme');

      /* m2 cart */
      if (m2_js_cart_enabled()) {
        $vars['m2_links'] = array();
        foreach ($vars['node']->m2api_products as $m2id => $product) {
          $vars['m2_links'][] =  theme('m2_js_album_link', $m2id, $product->type, t('Add'), t('In Cart'));
        }
      }
            /* track listing and count */
      $view = views_get_view('alavigne6_tracks');
      $vars['tracks'] = $view->preview('default', array($vars['node']->nid));
      $vars['track_count'] = $view->total_rows;

            /* date format */
      $vars['release_date'] = strtotime($vars['node']->field_release_date[0]['value']);

      //custom video breadcrumb
      $vars['bc'] = l(t('Music'), 'music') . ' / ';
      $vars['bc'] .= $vars['node']->title;

      break;
    case 'date':
      break;
    case 'media':
    drupal_set_title(t('Avril Lavigne\'s Media'));
      break;
    case 'gallery':
      /* photo listing and count */
      $display = (!empty($vars['node']->taxonomy[20])) ? 'block_1' : 'block_2';
      $view = views_get_view('alavigne6_photos');
      $vars['photo_thumbs'] = $view->preview($display, array($vars['node']->nid));
      $vars['photo_count'] = $view->total_rows;

      //custom video breadcrumb
      $vars['bc'] = l(t('Photos'), 'photos') . ' / ';
      $vars['bc'] .= $vars['node']->title;

      break;
  }
}

/**
 * Override of preprocess_views_view_fields
 */
function alavigne6_preprocess_views_view_fields(&$vars) {
  $links = array();
  if (isset($vars['row']->node_comment_statistics_comment_count)) {
    $links['comments_link'] = array(
      'title' => t('Comments ') . '<span class="comment-count">(' . $vars['row']->node_comment_statistics_comment_count . ')</span>',
      'href' => 'node/' . $vars['row']->nid,
      'fragment' => 'comments',
      'html' => 'TRUE'
    );
  }

  /* You need the nid to create a permalink or get service links */ 
  if (!empty($vars['row']->nid)) {
    $links['permalink_link'] = array(
      'title' => t('Permalink'),
      'href' => 'node/' . $vars['row']->nid
    );
    
    // Service links requires a fake node object.
    if (!empty($vars['row']->node_title)){
      $node->title = $vars['row']->node_title;
    }
    else {
      $node->title = 'Avril Lavigne';
    }
    $node->nid = $vars['row']->nid;
    $links += service_links_render($node, TRUE);
  }
  $vars['links'] = theme('links', $links, array('class' => 'links inline'));

  switch ($vars['view']->name) {
    case 'alavigne6_gallery':
      /* photo thumb and count */
      $display = ($vars['row']->term_data_tid == '20') ? 'block_1' : 'block_2';
      $view = views_get_view('alavigne6_photos');
      $vars['photos'] = $view->preview($display, array($vars['row']->nid));
      $vars['photo_count'] = $view->total_rows;
      if (!empty($vars['fields']['field_galleryimage_fid']->content)) {
        $vars['photo_thumb'] = $vars['fields']['field_galleryimage_fid']->content;
        $vars['photo_title'] = $vars['fields']['field_galleryimagetitle_value']->content;
      } else {
        $vars['photo_thumb'] = $view->style_plugin->rendered_fields[0]['field_photo_fid_1'];
        $vars['photo_title'] = strip_tags($view->style_plugin->rendered_fields[0]['title']);
      }
      break;
    case 'alavigne6_videos':
    //custom video breadcrumb
      $vars['bc'] = l(t('Videos'), 'videos') . ' / ';
      $vars['bc'] .= $vars['row']->term_data_name;
    break;
    case 'alavigne6_album':
      // adding M2 product id in order to get price to display on page 
      if ($vars['view']->current_display == 'block_2'){
        m2api_include('api');
        $products = m2api_product_load_references($vars['row']->nid);
        $product = reset($products); // grab first item in array 
        $vars['product_id'] = $product ? $product->id : NULL;
      }
      
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
function alavigne6_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb) && strlen(drupal_get_title()) > 0) {
    $breadcrumb[] = drupal_get_title();
    return '<div class="breadcrumb">'. implode(' » ', $breadcrumb) .'</div>';
  }
}

function alavigne6_m2_js_album_links($links, $text) {
  $text = t('Add to cart');
  return theme('sonybmg_dropdown_links', $links, $text);
}

function alavigne6_m2_js_track_button($m2id, $add = NULL, $remove = NULL) {
  $m2id = (int) $m2id;
  $add = empty($add) ? t('Buy') : check_plain($add);
  $remove = empty($remove) ? t('Remove') : check_plain($remove);
  return "<span class='m2-product-button-wrapper'><span class='m2-button-placeholder' product_id='$m2id' add_text='$add' remove_text='$remove'></span></span>";
}
