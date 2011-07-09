<?php
/**
 * Theme include function for sonybmg_events module.
 */

/**
 * Theme the user display for event attendee - single.
 */
function theme_sonybmg_events_attendee_user_display($user = NULL) {
  $output = '';
  if ($user->uid) {
    if ($user->picture) { 
      $imgpath = $user->picture;
    }
    // To display users that don't have a custom avatar uncomment this 
    // "else" section 
    else {
      // Assumes sonybmg_profiles_user_picture_default() has been 
      // called to ensure the images are in the files directory.
    #  $imgpath = file_create_path('pictures/user-default.jpg');
    }	
    
    if (!empty($imgpath)) {
      $img = theme('imagecache', 'icon_large', $imgpath, $user->name, $user->name);
      $output .= '<li><div class="userpicture">' . l($img, 'user/' . $user->uid, array('html'=>TRUE)) . '</div><div class="username">' . theme('username', $user) . '</div></li>';
    } 	
  }
  return $output;
}


/**
 * Theme the attendee list page display wrapper.
 */
function theme_sonybmg_events_attendee_users_wrapper($html = '') {
  global $user;
  $output = '<div class="attendee-list">';
  if ($user->uid && empty($user->picture)){ 
    $output .= '<div class="attendee-list-header">';
    $output .= t('Are you attending this event but not seeing your photo here? <a href="!link">Then go to your profile page and upload one!</a>', array('!link' => url('user')));
    $output .= '</div>'; 	
  }
  if (!empty($html)) {
    $output .= '<ul>' . $html . '</ul>';
  }
  $output .= '</div>';
  return $output;
}


/**
 * Theme the user display for event attendee block - single.
 */
function theme_sonybmg_events_attendee_user_display_block($user = NULL) {
  $output = '';
    if ($user->uid) {
      $output = '<li>' . theme('username', $user) . '</li>';
    }
  return $output;
}


/**
 * Theme the attendee list page display wrapper block.
 */
function theme_sonybmg_events_attendee_users_wrapper_block($html = '') {
  $output = '';
  
  if (!empty($html)) {
    $output = '<ul>' . $html . '</ul>';
  }
  
  return $output;
}

/**
 * Display the signup button for a particular nid.
 */
function theme_sonybmg_events_signup($nid) {
  global $user;
  if ($user->uid){
    $flag = flag_get_flag('signup');
    return $flag->theme($flag->is_flagged($nid) ? 'unflag' : 'flag', $nid);
    }else {
	$login_text = l(t("Login"),"user/login");
	$login_text .= t(" or ");
	$login_text .= l(t("register"),"user/register");
	$login_text .= t(" to add yourself to this event");
	return  '<span class="please-log-in">'. $login_text.'</span>';
    }
}
