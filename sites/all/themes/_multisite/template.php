<?php
// $Id: template.php,v 1.12 2006/11/16 22:36:33 jjeff Exp $

/**
 * Prepreprocess function for page.tpl.php.
 */
function _multisite_preprocess_page(&$vars) {
  global $user;

  $vars['path'] = base_path() . path_to_theme() .'/';

  // An anonymous user has a user id of zero.
  if ($user->uid > 0) {
    // The user is logged in.
    $vars['logged_in'] = TRUE;
  }
  else {
    // The user has logged out.
    $vars['logged_in'] = FALSE;
  }

  $body_classes = array();
  // classes for body element
  // allows advanced theming based on context (home page, node of certain type, etc.)
  // sniffing for the arg(0) of home and if so setting the $vars['is_front'] = TRUE and removing the override for the
  // css class so that it adds the class front only if $vars['is_front'] is true
  if (arg(0) == 'home') {
    $vars['is_front'] = TRUE;
  }
  $body_classes[] = ($vars['is_front']) ? 'front' : 'not-front';
  $body_classes[] = ($vars['logged_in']) ? 'logged-in' : 'not-logged-in';
  if (isset($vars['node']->type)) {
    $body_classes[] = 'node-page'; // we're on a single node view page
    $body_classes[] = 'ntype-'. _multisite_id_safe($vars['node']->type);
  }
  if (!empty($vars['right'])) {
    $body_classes[] = 'sidebar-right';
  }
  // we want country codes
  global $language;
  $body_classes[] = 'lang-' . strtolower(substr($language->language, 0, 2));
  $body_classes[] = 'locale-' . strtolower($language->language);

  if (!$vars['is_front']) {
    // Add unique classes for each page and website section
    $path = drupal_get_path_alias($_GET['q']);
    list($section,) = explode('/', $path, 2);
    $body_classes[] = _multisite_id_safe('page-'. $path);
    $body_classes[] = _multisite_id_safe('section-'. $section);
    if (arg(0) == 'node') {
      if (arg(1) == 'add') {
        if ($section == 'node') {
          array_pop($body_classes); // Remove 'section-node'
        }
        $body_classes[] = 'section-node-add'; // Add 'section-node-add'
      }
      elseif (is_numeric(arg(1)) && (arg(2) == 'edit' || arg(2) == 'delete')) {
        if ($section == 'node') {
          array_pop($body_classes); // Remove 'section-node'
        }
        $body_classes[] = 'section-node-'. arg(2); // Add 'section-node-edit' or 'section-node-delete'
      }
    }
  }
  // Implode with spaces.
  $vars['body_classes'] = implode(' ', $body_classes);

  // Users Online
  $vars['registered_users'] = module_invoke('sonybmg_fans', 'total');
  $vars['online_users'] = module_invoke('sonybmg_fans', 'online');

  // Switch primary_links based on country_code and language.  Looks for the most
  // appropriate menu based on a list of suggestions.
  // menu-primary-links-en-us
  // menu-primary-links-en
  // <default primary links>
  // Note: the menu- part of the name is added automatically when creating new menus
  if(module_exists('country_code')) {
    $suggestions = array(
      strtolower('menu-primary-'. $GLOBALS['language']->language .'-'. country_code()),
      strtolower('menu-primary-'. $GLOBALS['language']->language),
    );
    foreach($suggestions as $menu_name) {
      if($country_links = menu_navigation_links($menu_name)) {
        $vars['primary_links'] = $country_links;
        break;
      }
    }
  }

  // landing page support
  if (isset($vars['node']->type) && $vars['node']->type =='landingpage'){
    if ((arg(2) != 'edit') && (arg(2) != 'delete')){
      $vars['template_files'] = array('page-landingpage');
    }
  }

  // adding the eTrust logo
  $vars['etrust'] = _multisite_etrust();

}

function _multisite_preprocess_node(&$vars) {
  // set a new $is_admin variable
  // this is determined by looking to see if the user has administer nodes privileges
  $vars['is_admin'] = user_access('administer nodes');

  $node_classes = array('node');
  if ($vars['sticky']) {
    $node_classes[] = 'sticky';
  }
  if (!$vars['node']->status) {
    $node_classes[] = 'node-unpublished';
  }
  $node_classes[] = 'nodetype-'. _multisite_id_safe($vars['node']->type);
  // implode with spaces
  $vars['node_classes'] = implode(' ', $node_classes);

  if (arg(0) == 'user' && $vars['node']->uid == arg(1)) {
    $vars['hide_attribution'] = true;
  }

  switch ($vars['node']->type) {
    case 'forum':
    case 'forum_reply':
      $author = user_load(array('uid' => $vars['node']->uid));
      profile_load_profile($author);
      $vars['user_city'] = check_plain($author->profile_city);
      if ($vars['user_city'] && $author->profile_province) {
        $vars['user_city'] .= ', ';
      }
      $vars['user_city'] .= check_plain($author->profile_province);
      $vars['user_country'] = check_plain($author->profile_country);

      $vars['picture'] = theme('user_picture', $vars['node'], 'icon_large');
      $vars['user_since'] = format_date($author->created, 'custom', 'M Y');
      if (module_exists('user_titles')) {
        $vars['user_posts'] = user_titles_get_posts($vars['node']->uid);
        $vars['user_title'] = filter_xss_admin(user_titles_get_user_title($author));
      }
      break;

    case 'album':
      if ($vars['page'] && isset($vars['node']->field_artist[0]['view'])) { drupal_set_title($vars['node']->field_artist[0]['view'] . ': ' . $vars['node']->title); }
      $vars['cover_art_big'] = theme('imagecache', 'discography_large', $vars['node']->field_album_cover[0]['filepath'], $vars['node']->field_artist[0]['view'] . ': ' . $vars['node']->title);
      $vars['cover_art'] = l(theme('imagecache', 'icon_small', $vars['node']->field_album_cover[0]['filepath'], NULL), $vars['node']->path, array('html' => TRUE));

      $vars['release_date'] = $vars['node']->field_release_date[0]['view'];
      $vars['review_count'] = $vars['node']->comment_count;
      $results = votingapi_select_results(array('content_type' => 'node', 'content_id' => $vars['node']->nid, 'value_type' => 'percent', 'tag' => 'vote', 'function' => 'average'));
      $vars['current_rating'] = isset($results[0]) ? $results[0] : 0;
      $vars['vote_display'] = theme('fivestar_static', $vars['current_rating']['value']);
      drupal_add_js(drupal_get_path('theme', '_multisite') .'/js/album_rate.js', 'theme');

      if ($vars['page'] != 0 && module_exists('views')) {
        $vars['tracks'] = views_embed_view('music_tracks', 'default', $vars['node']->nid);
      }

      if (is_array($vars['node']->field_album_download_links) && !empty($vars['node']->field_album_download_links[0]['url'])) {
        foreach ($vars['node']->field_album_download_links as $link) {
          $vars['download_links'][] = $link['view'];
        }
      }

      if (is_array($vars['node']->field_producer) && !empty($vars['node']->field_producer[0]['value'])) {
        foreach ($vars['node']->field_producer as $producer) {
          $vars['producers'][] = $producer['view'];
        }
      }

      if (is_array($vars['node']->field_band_member) && !empty($vars['node']->field_band_member[0]['value'])) {
        foreach ($vars['node']->field_band_member as $delta => $member) {
          if (isset($vars['node']->field_band_username[$delta]['uid'])) {
            $uid = $vars['node']->field_band_username[$delta]['uid'];
            $vars['musicians'][] = l($member['value'], 'user/'.$uid) . ($vars['node']->field_band_position[$delta]['value'] ? ': ' . $vars['node']->field_band_position[$delta]['value'] : '');
          }
          elseif (isset($vars['node']->field_band_position[$delta]['value'])) {
            $vars['musicians'][] = $member['value'] . ($vars['node']->field_band_position[$delta]['value'] ? ': ' . $vars['node']->field_band_position[$delta]['value'] : '');
          }
        }
      }
      break;

    case 'track':
      $vars['album'] = $vars['node']->field_album[0]['view'];
      $vars['track_url'] = $vars['node']->field_audio_file_url[0]['view'];
      $vars['video_url'] = $vars['node']->field_track_video_url[0]['view'];
      $vars['track_num'] = $vars['node']->field_track_number[0]['view'];
      $vars['review_count'] = $vars['node']->comment_count;
      $results = votingapi_select_results(array('content_type' => 'node', 'content_id' => $vars['node']->nid, 'value_type' => 'percent', 'tag' => 'vote', 'function' => 'average'));
      $vars['current_rating'] = isset($results[0]) ? $results[0] : 0;
      $vars['vote_display'] = theme('fivestar_static', $vars['current_rating']['value']);
      if ($vars['node']->field_gracenote_lyrics[0]['view']) {
        $vars['content'] = $vars['node']->field_gracenote_lyrics[0]['view'];
      }
      //else {
      //  $vars['content'] = $vars['node']->field_lyrics[0]['view'];
      //}
      if (is_array($vars['node']->content['custom_pager_top'])) {
        $pager = array_shift($vars['node']->content['custom_pager_top']);
        $vars['pager'] = $pager['#value'];
      }
      elseif (is_array($vars['node']->content['custom_pager_bottom'])) {
        $pager = array_shift($vars['node']->content['custom_pager_bottom']);
        $vars['pager'] = $pager['#value'];
      }

      break;

    case 'news':
    case 'blog':
      $vars['hide_attribution'] = TRUE;
      break;

    case 'page':
      $vars['hide_attribution'] = TRUE;
      break;

    case 'poll':
      $vars['hide_attribution'] = TRUE;
      $vars['submitted'] = NULL;
      break;

    case 'fan':
      if ($vars['is_front']) {
        $vars['template_file'] = 'node-fan-home';
        $vars['picture'] = theme('user_picture', $vars['node'], 'icon_small');
      }
      break;

    case 'photo':
      if (module_exists('fivestar')) {
        $vars['vote_widget'] = fivestar_widget_form($vars['node']);
      }
      $vars['node_pager'] = $vars['node']->content['custom_pager_bottom'][variable_get('photo_gallery_user_pager', 5)]['#value'];
      foreach ($vars['node']->taxonomy as $tid => $term) {
        if ($term->vid == 6) {
          drupal_set_title($term->name);
          break;
        }
      }
      break;

    case 'official_photo':
      $vars['hide_attribution'] = TRUE;
      $vars['photographer'] = trim($vars['node']->field_photographer_first[0]['value'] . ' ' . $vars['node']->field_photographer_last[0]['value']);
      if (module_exists('fivestar')) {
        $vars['vote_widget'] = fivestar_widget_form($vars['node']);
      }
      $vars['node_pager'] = $vars['node']->content['custom_pager_bottom'][variable_get('photo_gallery_official_pager', 3)]['#value'];
      $vars['template_file'] = 'node-photo';
      drupal_set_title('Official Photos');
      break;

    case 'date':
      $vars['attendee_count'] = $vars['node']->attendee_count;
      $vars['signup'] = theme('sonybmg_events_signup', $vars['node']->nid);
      $vars['review_count'] = $vars['node']->comment_count;
      $results = votingapi_select_results(array('content_type' => 'node', 'content_id' => $vars['node']->nid, 'value_type' => 'percent', 'tag' => 'vote', 'function' => 'average'));
      $vars['current_rating'] = isset($results[0]) ? $results[0] : 0;
      $vars['vote_display'] = theme('fivestar_static', $vars['current_rating']['value']);
      $vars['date'] = $vars['node']->field_date[0]['view'];
      $vars['time'] =  $vars['node']->field_time[0]['view'];
      $vars['location'] =  $vars['node']->field_location[0]['view'];
      $vars['venue'] =  $vars['node']->field_venue[0]['view'];
      $vars['body'] =  $vars['node']->content['body']['#value'];
      $vars['node_pager'] = $vars['node']->content['custom_pager_top'][variable_get('events_date_pager', 6)]['#value'];

      $vars['tickets'] = strip_tags($vars['node']->field_ticket_sales_url[0]['value']);
      $vars['soldout'] = $vars['node']->field_sold_out[0]['view'];
      break;

    case 'comment':
    case 'review':
      if ($vars['node']->revision_uid && !$vars['node']->uid) {
        $vars['node']->uid = $vars['node']->revision_uid;
      }

      // Add the parent link to comment types when not displayed in context
      if ($vars['node']->comment_target_nid && (arg(0) != 'node' || arg(1) != $vars['node']->comment_target_nid)) {
        $parent_nid = $vars['node']->comment_target_nid;
        $parent_title = db_result(db_query('SELECT title t FROM {node} WHERE nid = %d', $parent_nid));
        $vars['parent_link'] = t('on <a href="!link">@title</a>', array('!link' => url('node/'. $vars['node']->comment_target_nid), '@title' => $parent_title));
        $vars['subject'] = l($vars['node']->title, 'node/'.$vars['node']->nid);
      }
      else {
        $query = $_GET['page'] ? 'page=' . $_GET['page'] : NULL;
        $fragment = 'comment-'. $vars['node']->nid;
        $vars['subject'] = l($vars['node']->title, $_GET['q'], array('query' => $query, 'fragment' => $fragment)) .' '. theme('mark', $vars['node']->new);
      }
      $vars['template_file'] = 'node-comment';
      break;
  }
}

function _multisite_preprocess_comment(&$vars) {
  // Load the node object that the current comment is attached to.
  $node = node_load($vars['comment']->nid);

  $comment_classes = array('comment');
  if ($vars['comment']->status == COMMENT_NOT_PUBLISHED) {
    $comment_classes[] = 'comment-unpublished';
  }
  // Implode with spaces.
  $vars['comment_classes'] = implode(' ', $comment_classes);

  // If the author of this comment is equal to the author of the node,
  // then in our theme we can theme this comment differently to stand out.
  $vars['author_comment'] = $vars['comment']->uid == $node->uid ? TRUE : FALSE;
}

function _multisite_preprocess_user_profile(&$vars) {
  global $user;
  drupal_set_title('<strong>'.$vars['account']->name.'</strong>&rsquo;s Profile');

  $vars['reviews_written'] = sonybmg_profiles_comment_count($vars['account']->uid, 'review');
  $vars['comments_made'] = sonybmg_profiles_comment_count($vars['account']->uid, 'comment');
  // fails - fixed in tpl $vars['member_since'] = format_date($vars['account']->created, 'custom', "F j, Y");

  if (module_exists('friendlist_ui')) {
    $additional_vars = sonybmg_profiles_friendlist_vars($vars['account']->uid);
    $vars = array_merge($vars, $additional_vars);
  }

  if (module_exists('privatemsg') && $user->uid) {
    if ($user->uid == $vars['account']->uid) {
      $vars['privatemsg'] = l(t('Read my messages'), 'messages');
    }
    else {
      $vars['privatemsg'] = l(t('Message Me'), 'messages/new/'. $vars['account']->uid, array(
        'query' => "destination=$_GET[q]",
      ));
    }
  }
  if (module_exists('views')) {
    $vars['user_activity'] = views_embed_view('user_activity', 'default', $vars['account']->uid);
  }
  // There is currently not a buddylist solution installed.
  //$vars['buddylist'] = theme('user_buddylist', $vars['account']->uid);

  // Check if the Favorite Lyric is from an available 'track' and link to it
  if ($vars['account']->profile_lyric_title != '') {
    $vars['artist_lyric_title_nid'] = sonybmg_profiles_favorite_lyric($vars['account']->profile_lyric_title);
  }
}

/**
 * Preprocess function for views-view-fields--music-tracks.tpl.php.
 */
function _multisite_preprocess_views_view_fields__music_tracks(&$vars) {
  $album_nid = $vars['view']->args[0];
  $track_nid = $vars['fields']['nid']->raw;
  $uid = $vars['user']->uid;

  $vars['track_number'] = $vars['fields']['field_track_number_value']->content;
  $vars['audio_file_url'] = $vars['fields']['field_audio_file_url_value']->content;
  $vars['title'] = check_plain($vars['row']->node_title);
  $vars['rating_widget'] = drupal_get_form('sonybmg_discography_track_rating_form', $album_nid, $track_nid, $uid);
  $vars['rating_average'] = round($vars['fields']['value']->raw/20, 1);
}

function _multisite_preprocess_views_view__events (&$vars) {

  $limit = $vars['view']->pager['items_per_page'];
  $element = $vars['view']->pager['element'];
  $resultcount = count($vars['view']->result);

  if(is_numeric($vars['view']->result[0]->node_data_field_date_field_date_value)) {
    $start = format_date($vars['view']->result[0]->node_data_field_date_field_date_value, 'custom', 'F d Y', 0);
    $end = format_date($vars['view']->result[$resultcount -1 ]->node_data_field_date_field_date_value, 'custom', 'F d Y', 0);
  }
  else {
    $start = format_date(strtotime($vars['view']->result[0]->node_data_field_date_field_date_value), 'custom', 'F d Y', 0);
    $end = format_date(strtotime($vars['view']->result[$resultcount -1 ]->node_data_field_date_field_date_value), 'custom', 'F d Y', 0);
  }
  $parameters = array (
                'previous_text' => 'Earlier Events',
                'start_text'    => $start,
                'end_text'      => $end,
                'is_event_page' => 'yes',
  );
  $vars['pager'] = theme ('pager', NULL, $limit, $element, $parameters);


}

function _multisite_preprocess_views_view_fields__events_active (&$vars) {
  $output = array();

  $output['date'] = $vars['fields']['field_date_value']->content;
  $output['title'] = $vars['fields']['title']->content;
  $output['reviews'] = $vars['fields']['comment_count']->content;

  $vars['event'] = $output;
}

function _multisite_preprocess_views_view_fields__events_upcoming (&$vars) {
  $output = array();

  if (isset($vars['fields']['field_date_value'])) {
    $output['date'] = $vars['fields']['field_date_value']->content;
  }

  if (isset($vars['fields']['field_location_value']) && isset($vars['fields']['field_venue_value'])) {
    $output['title'] = $vars['fields']['field_location_value']->content .' @ '. $vars['fields']['field_venue_value']->content;
  }
  elseif (isset($vars['fields']['field_venue_value'])) {
    $output['title'] = $vars['fields']['field_venue_value']->content;
  }
  else {
    $output['title'] = $vars['fields']['title']->content;
  }

  $vars['upcoming_event'] = $output;
}

function _multisite_theme() {
  return array(
    // The form ID.
    'friendlist_ui_relation_form' => array(
      // Forms always take the form argument.
      'arguments' => array('form' => NULL),
    ),
    'links_dropdown_list' => array(
      'arguments' => array('links' => array(), 'title' => NULL, 'attributes' => array()),
    ),
  );
}

function _multisite_friendlist_ui_relation_form($form) {
  // Change the title to match the old buddylist module
  $user = user_load($form['#parameters'][2]['requestee_id']);
  if ($form['#parameters'][2]['op'] == 'add') {
    $new_title = t('Add user !username to your buddy list?', array('!username' => $user->name));
  }
  else {
    $new_title = t('Remove user !username from your buddy list?', array('!username' => $user->name));
  }

  // Kill the message for an add.
  unset($form['message']);

  // Change the submit button to read "Yes!"
  $form['submit']['#value'] = t('Yes');
  $form['submit']['#submit'] = $form['#submit'];

  $form['#submit'] = array();

  // Add a cancel button. (Modified from cancel_form().)
  $cancel = l(t('Cancel'), urldecode(str_replace('destination=', '', drupal_get_destination())));
  $form['cancel'] = array(
    '#value' => $cancel,
  );

  drupal_set_title($new_title);

  return drupal_render($form);
}

/**
 * Return a themed pager
 */
function _multisite_pager($tags = array(), $limit = 10, $element = 0, $parameters = array(), $quantity = 9) {
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $previous_text = '‹ Previous';
  if (isset($parameters['previous_text'])) {
    $previous_text = $parameters['previous_text'];
  }
  $is_an_event_pager = 'no';
  if (isset($parameters['is_event_page'])) {
    $is_an_event_pager = $parameters['is_event_page'];
  }
  $li_first = theme('pager_first', (isset($tags[0]) ? $tags[0] : t('« First')), $limit, $element, $parameters);
  $li_previous = theme('pager_previous', (isset($tags[1]) ? $tags[1] : t($previous_text)), $limit, $element, 1, $parameters);
  $li_next = theme('pager_next', (isset($tags[3]) ? $tags[3] : t('Next ›')), $limit, $element, 1, $parameters);
  $li_last = theme('pager_last', (isset($tags[4]) ? $tags[4] : t('Last »')), $limit, $element, $parameters);

  if ($pager_total[$element] > 1) {
    if ($li_first && $is_an_event_pager != 'yes') {
      $items[] = array(
        'class' => 'pager-first',
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => 'pager-previous',
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => 'pager-ellipsis',
          'data' => '…',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current && $is_an_event_pager != 'yes') {
          $items[] = array(
            'class' => 'pager-item',
            'data' => theme('pager_previous', $i, $limit, $element, ($pager_current - $i), $parameters),
          );
        }
        if ($i == $pager_current) {

          $i_text = $i;
          if (isset($parameters['start_text'])) {
                $i_text = $parameters['start_text'] . ' - '. $parameters['end_text'];
            }
          $items[] = array(
            'class' => 'pager-current',
            'data' => $i_text,
          );


        }
        if ($i > $pager_current && $is_an_event_pager != 'yes') {
          $items[] = array(
            'class' => 'pager-item',
            'data' => theme('pager_next', $i, $limit, $element, ($i - $pager_current), $parameters),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => 'pager-ellipsis',
          'data' => '…',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => 'pager-next',
        'data' => $li_next,
      );
    }
    if ($li_last && $is_an_event_pager != 'yes') {
      $items[] = array(
        'class' => 'pager-last',
        'data' => $li_last,
      );
    }
    return theme('item_list', $items, NULL, 'ul', array('class' => 'pager'));
  }
}

/**
 * Theme override for user.module.
 *
 * Utilize imagecache module to scale down large uploaded profile pictures
 *
 * @param $size
 *   Image size to scale to. Options: thumb (default) and large
 * @param $attributes
 *   Attributes to append to the img tag
 */
function _multisite_user_picture($account, $size = 'icon_large', $attributes = array()) {
  global $user;
  if (variable_get('user_pictures', 0)) {

    // Display the user's photo if available
    if ($account->picture && file_exists($account->picture)) {
      $picture = '<div>' . theme('imagecache', $size, $account->picture, '', '', $attributes) . '</div>';
    }
    // Display default image for user's with no pic or anonymous users
    else {
      module_invoke('sonybmg_profiles', 'user_picture_default'); // Ensure the images are in the files directory
      if ($account->uid == $user->uid && $user->uid > 0) {
        $picture = theme('imagecache', $size, file_create_path('pictures/user-upload.jpg'), '', '', $attributes);
      }
      else {
        $picture = theme('imagecache', $size, file_create_path('pictures/user-default.jpg'), '', '', $attributes);
      }
    }

    if ($account->uid == $user->uid && $user->uid > 0 && !$account->picture) {
      $picture = l($picture, "user/$account->uid/edit", array('html' => TRUE, 'attributes' => array('title' => t('Edit user profile.'))));
    }
    elseif (!empty($account->uid) && user_access('access user profiles')) {
      $picture = l($picture, "user/$account->uid", array('html' => TRUE, 'attributes' => array('title' => t('View user profile.'))));
    }

    return '<div class="picture">'.$picture.'</div>';
  }
}

/**
 * Theme display of entire content area, adding a headline between the comments
 * and the page body
 */
function _multisite_comment_wrapper($content, $node) {
  $types = node_get_types('names');
  $type = $types[$node->type];
  $comment_type = t($types[$node->comment_type]);

  $output = '';
  $output .= '<div id="comments">';

  if ($comment_type == "Reply") {
    $comment_type = t("Replies");
  }
  elseif ($comment_type == "Review") {
    $comment_type = t("Reviews");
  }
  else {
    $comment_type = t("Comments");
  }

  $output .= '<h1 class="comment-headline">' . t('@Comments for this @type', array('@Comments' => $comment_type, '@type' => $type)) . '</h1>';
  if ($node->comment_count == 0) {
    // Note that nodecomments by default returns an empty string when there are no nodes
    // in order for this code to be executed the node_comments view must be overridden and
    // an empty space or text entered in the 'Empty Text' field
    global $user;
    $types = node_get_types('names');
    $comment_type = t($types[$node->comment_type]);

    if ($user->uid == 0){
      $alias = drupal_get_path_alias('node/' . $node->nid);
      $comment_url = url('user/login' , array('fragment' => '', 'query' => array('destination' => $alias)));

    } else{
    $comment_url = variable_get('comment_form_location', 0) ? url('node/'.$node->nid, array('fragment' => 'node-form')) : url('node/add/'. str_replace('_', '-', $node->comment_type) .'/'.$node->nid);
    }
    $output .= t('Be the first to <a href="!url">post a !type</a>.', array('!url' => $comment_url, '!type' => $comment_type));
  }
  $output .= $content;
  $output .= '</div>';
  return $output;
}

/**
* Converts a string to a suitable html ID attribute.
* - Preceeds initial numeric with 'n' character.
* - Replaces space and underscore with dash.
* - Converts entire string to lowercase.
* - Works for classes too!
*
* @param string $string
*  the string
* @return
*  the converted string
*/
function _multisite_id_safe($string) {
  if (is_numeric($string{0})) {
    $string = 'n'. $string;
  }
  return strtolower(preg_replace('/[^a-zA-Z0-9-]+/', '-', $string));
}

/**
 * theme_form_element() modified to output even/odd classes on all elements and
 * remove the colon from the end of titles if other punctuation is present.
 */

function _multisite_form_element($element, $value) {
  static $odd = FALSE;
  $odd = !$odd;


  // This is also used in the installer, pre-database setup.
  $t = get_t();

  $output = '<div class="form-item '. (($odd) ? 'odd' : 'even') .'"';
  if (!empty($element['#id'])) {
    $output .= ' id="'. $element['#id'] .'-wrapper"';
  }
  $output .= ">\n";
  $required = !empty($element['#required']) ? '<span class="form-required" title="'. $t('This field is required.') .'">*</span>' : '';

  if (!empty($element['#title'])) {
    $punctuations = array('.', '!', '?');
    $terminal = '';
    if (!in_array(substr($element['#title'], strlen($element['#title']) - 1), $punctuations)) {
      $terminal = ':'; // Append a colon to the end of a title if $punctuations aren't found.
    }
    $title = $element['#title'];
    if (!empty($element['#id'])) {
      $output .= ' <label for="'. $element['#id'] .'">'. t('!title!terminal !required', array('!title' => filter_xss_admin($title), '!terminal' => $terminal, '!required' => $required)) ."</label>\n";
    }
    else {
      $output .= ' <label>'. t('!title!terminal !required', array('!title' => filter_xss_admin($title), '!terminal' => $terminal, '!required' => $required)) ."</label>\n";
    }
  }

  $output .= " $value\n";

  if (!empty($element['#description'])) {
    $output .= ' <div class="description">'. $element['#description'] ."</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

/**
 * theme_user_list() modified to output comma delimited listing
 */
function _multisite_user_list($users, $title = NULL) {
  if (!empty($users)) {
    foreach ($users as $user) {
      $items[] = theme('username', $user);
    }
  }
  return '<div class="user-list">'. implode(', ', $items) .'</div>' . l(t('See all users'), 'profile');
}

/**
 * Rewrite of theme_poll_bar
 */
function _multisite_poll_bar($title, $votes, $total_votes, $block) {

  // Drupal 6 upgrade.
  $percentage = intval(($votes / $total_votes) * 100);

  if ($block) {
    $output  = '<div class="text">';
    //if ($percentage) { // don't output if percentage is 0
      $output .= '<div class="percent">'. $percentage .'%</div>';
    //}
    $output .= $title .'</div>';
    $output .= '<div class="bar"><div style="width: '. $percentage .'%;" class="foreground"></div></div>';
  }
  else {
    $output  = '<div class="text">';
    //if ($percentage) { // don't output if percentage is 0
      $output .= '<div class="percent">'. $percentage .'%</div>';
    //}
    $output .= $title .'</div>';
    $output .= '<div class="bar"><div style="width: '. $percentage .'%;" class="foreground"></div></div>';
  }

  return $output;
}

/**
 * theme_username() with added argument for uppercase
 */
function _multisite_username($object, $upper = FALSE) {

  if ($object->uid && $object->name) {
    // Shorten the name when it is too long or it will break many tables.
    if (drupal_strlen($object->name) > 20) {
      $name = drupal_substr($object->name, 0, 15) .'...';
    }
    else {
      $name = $object->name;
    }

    if ($upper) {
      $name = drupal_strtoupper($name);
    }

    if (user_access('access user profiles')) {
      $output = l($name, 'user/'. $object->uid, array('title' => t('View user profile.')));
    }
    else {
      $output = check_plain($name);
    }
  }
  else if ($object->name) {
    // Sometimes modules display content composed by people who are
    // not registered members of the site (e.g. mailing list or news
    // aggregator modules). This clause enables modules to display
    // the true author of the content.
    if ($object->homepage) {
      $output = l($object->name, $object->homepage);
    }
    else {
      $output = check_plain($object->name);
    }

    //$output .= ' ('. t('not verified') .')';
  }
  else {
    $output = variable_get('anonymous', t('Anonymous'));
  }

  return $output;
}

/**
 * Slightly modified theme_nodeforum_topic_list so we can
 * wordfilter the topic list
 *
 * @ingroup themeable
 */
function _multisite_nodeforum_topic_list($tid, $topics, $sortby, $forum_per_page) {
  global $forum_topic_list_header;

  if ($topics) {

    foreach ($topics as $topic) {
      if (module_exists('wordfilter')) {
        $topic->title = wordfilter_filter_process($topic->title);
      }
      // folder is new if topic is new or there are new comments since last visit
      if ($topic->tid != $tid) {
        $rows[] = array(
          array('data' => theme('nodeforum_icon', $topic->new, $topic->num_comments, $topic->comment_mode, $topic->sticky), 'class' => 'icon'),
          array('data' => check_plain($topic->title), 'class' => 'title'),
          array('data' => l(t('This topic has been moved'), "forum/$topic->tid"), 'colspan' => '3')
        );
      }
      else {
        $rows[] = array(
          array('data' => theme('nodeforum_icon', $topic->new, $topic->num_comments, $topic->comment_mode, $topic->sticky), 'class' => 'icon'),
          array('data' => l($topic->title, "node/$topic->nid"), 'class' => 'topic'),
          array('data' => $topic->num_comments . ($topic->new_replies ? '<br />'. l(format_plural($topic->new_replies, '1 new', '@count new'), "node/$topic->nid", array('fragment' => 'new')) : ''), 'class' => 'replies'),
          array('data' => _nodeforum_format($topic), 'class' => 'created'),
          array('data' => _nodeforum_format(isset($topic->last_reply) ? $topic->last_reply : NULL), 'class' => 'last-reply')
        );
      }
    }
  }

  $output = theme('table', $forum_topic_list_header, $rows);
  $output .= theme('pager', NULL, $forum_per_page, 0);

  return $output;
}

/**
 * Remove next/previous links because they are too expensive to generate.
 *
 * @ingroup themeable
 */
function _multisite_nodeforum_topic_navigation($nid, $tid) {
  $output = '';
  /*
   * Commented out code is to just point back to the forum topic instead.
  $topic = taxonomy_get_term($tid);
  $topic_name = $topic->name;
  if (module_exists('i18ntaxonomy')) {
    $topic_name = tt("taxonomy:term:{$topic->tid}:name", $topic->name);
  }
  $output = l(t('‹ Return to !topic', array('!topic' => $topic_name)), 'forum/'. $topic->tid, array('attributes' => array('class' => 'topic-previous', 'title' => t('Return to forum topic list'))));
  */
  return $output;
}

function _multisite_submitagain_message(&$node) {
  // this space intentionally left blank
  // this function overrides the default in the submitagain module
  // so that users, submitting photos, don't get a link to their moderated photo
}

function _multisite_modr8_message($teaser = FALSE, $nodetype = 'page', $op = 'view') {
  if ($teaser) {
    return ' <div class="marker">'. t('Pending moderation') .'</div>';
  }
  elseif ($op == 'insert' || $op == 'update') {
    drupal_set_message(t("The post has been submitted for moderation and won't be listed until it has been approved."), 'error');
  }
}

/**
 * Add classes to the links themselves, like Drupal 5.
 */
function _multisite_links($links, $attributes = array('class' => 'links')) {
  $i = '';
  foreach($links as $key => $link) {
    $links[$key]['attributes']['class'] = isset($links[$key]['attributes']['class']) ? $links[$key]['attributes']['class'] : '';
    $links[$key]['attributes']['class'] .= ' menu-item-'. _multisite_id_safe($link['title']);
    $links[$key]['attributes']['class'] .= ($i++ % 2 == 0) ? ' odd': ' even';
  }
  return theme_links($links, $attributes);
}


/**
 * Generate the HTML representing a given menu item ID.
 *
 * An implementation of theme_menu_item_link()
 *
 * @param $link
 *   array The menu item to render.
 * @return
 *   string The rendered menu item.
 */
function _multisite_menu_item_link($link) {
  if (empty($link['options'])) {
    $link['options'] = array();
  }

  // If an item is a LOCAL TASK, render it as a tab
  if ($link['type'] & MENU_IS_LOCAL_TASK) {
    $link['title'] = '<span class="tab">'. check_plain($link['title']) .'</span>';
    $link['options']['html'] = TRUE;
  }

  if (empty($link['type'])) {
    $true = TRUE;
  }

  return l($link['title'], $link['href'], $link['options']);
}

/**
 * Duplicate of theme_menu_local_tasks() but adds clear-block to tabs.
 */
function _multisite_menu_local_tasks() {
  $output = '';

  if ($primary = menu_primary_local_tasks()) {
    $output .= '<ul class="tabs primary clear-block">'. $primary .'</ul>';
  }
  if ($secondary = menu_secondary_local_tasks()) {
    $output .= '<ul class="tabs secondary clear-block">'. $secondary .'</ul>';
  }

  return $output;
}

// Add sIFR if needed. This is intentionally outside of any functions to
// prevent duplicate processing of the CSS and JS arrays.
if (!defined('MAINTENANCE_MODE') && !empty($GLOBALS['theme_info']->info['sifr'])) {
  $path = drupal_get_path('theme', '_multisite');
  $theme_path = drupal_get_path('theme', $GLOBALS['theme_info']->name);
  $base_path = base_path();
  $sifrs = $GLOBALS['theme_info']->info['sifr'];

  drupal_add_js($path . '/js/sifr.js', 'module');
  drupal_add_css($path .'/css/sIFR-print.css', 'module', 'print');
  drupal_add_css($path .'/css/sIFR-screen.css', 'module', 'screen');

  // Manually assemble activation JavaScript.
  $script  = '';
  $script .= "$(document).ready(function() {\n";
  $script .= "if(typeof sIFR == 'function'){\n";

  foreach ($sifrs as $id => $sifr) {
    if ($sifr['sFlashSrc'] && $sifr['sSelector']) {
      $sifr['sFlashSrc'] = $base_path . $theme_path .'/'. $sifr['sFlashSrc'];
      $config = drupal_to_js($sifr);
      $script .= "sIFR.replaceElement(named($config));\n";
    }
  }

  $script .= "}";
  $script .= "});";

  drupal_add_js($script, 'inline');
}

/**
 * Thanks to http://drupal.org/node/99721#comment-887231 for this.
 */
function _multisite_views_build_view($view_name, $args = array()) {
  $view = views_get_view($view_name);
  $view->set_arguments($args);
  $view->execute();
  return $view;
}

/**
 * Javscript links dropdown list.
 * See http://admin.gdb-dev.com/node/1031
 *
 * DEPRECATED - Use theme('sonybmg_dropdown_links') instead.
 */
function _multisite_links_dropdown_list($links = array(), $title = NULL, $attributes = array()) {
  return theme('sonybmg_dropdown_links', $links, $title, $attributes);
}

/**
 * this function returns the markup for the eTrust logo. We put this here so we can change it in one place :)
 * possible args to pass for $sml are 's" for small, and 'l" for large
 * this function also uses the site base url to find the right image :)
 */
function _multisite_etrust($sml = 'm') {
  // let's snag the base url and bring it into scope
  global $base_url;
  // this is going to be used for paths, so, we need to removed the http://
  $parse = parse_url($base_url);
  $url = $parse['host'];
  // now let's make sure we can use this for the dev sites; we substitue the rm one
  if (strstr( $base_url, "gdb-dev" )){
    // pinch the logo from the documentation site on dev http://docs.gdb-dev.com/sites/docs.gdb-dev.com/files/seal_l.png
    $link  =  '<a href="'.$base_url.'"><img style="border: none" src="http://docs.gdb-dev.com/sites/docs.gdb-dev.com/files/seal_'.$sml.'.png" alt="TRUSTe online privacy certification"/></a>';
  }
  else {
    $link  =   '<a href="//privacy-policy.truste.com/click-with-confidence/wps/en/'.$url.'/seal_m" title="TRUSTe online privacy certification" target="_blank"><img style="border: none" src="//privacy-policy.truste.com/certified-seal/wps/en/'.$url.'/seal_'.$sml.'.png" alt="TRUSTe online privacy certification"/></a> ';
  }
  // now let's build the markup we will use
  $output = ' <div id="trust-e"> ';
  $output .= $link;
  $output .= ' </div> ';

  return $output;
 }

/**
 * Implementation of theme_preprocess_maintenance_page().
 *
 * Adding this so that maintenance pages get variables.
 * Core does not do this on it's own.
 */
function _multisite_preprocess_maintenance_page(&$variables) {
  template_preprocess_maintenance_page($variables);
}
