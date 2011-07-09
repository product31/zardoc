<?php
//$Id: 

/**
 * Settings form
 */
function fb_comments_settings_form(){
  $form = array();

  $form['node_types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content types'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['node_types']['fb_comments_node_types'] = array(
    '#type' => 'checkboxes',
    '#description' => t('Select the content types that will use fb_comments. NOTE: Drupal comment settings will be ignored for the selected content types'),
    '#default_value' => variable_get('fb_comments_node_types', array()),
    '#options' => node_get_types('names'),
  );
  

  $form['widget_setings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Widget settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['widget_setings']['fb_comments_numposts'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of posts'),
    '#description' => t('The maximum number of posts to display. You can set numposts to 0 to not display any comments. (Default value is 10.)'),
    '#default_value' => variable_get('fb_comments_numposts', 10),
  );
  
  $form['widget_setings']['fb_comments_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#description' => t('The width of the Comments Box in pixels. (Default value is 550px.)'),
    '#default_value' => variable_get('fb_comments_width', 550),
  );
  
  $form['widget_setings']['fb_comments_css'] = array(
    '#type' => 'textfield',
    '#title' => t('The URL to your own stylesheet.'),
    '#description' => t('Note: To provide you with better performance, we cache your stylesheet. If you update your stylesheet, you should use a cachebreaker in the URL to the stylesheet, typically by appending a version number to the .CSS file extension, as in http://www.example.com/my.css?2'),
    '#default_value' => variable_get('fb_comments_css', ''),
  );
  
  $form['widget_setings']['fb_comments_simple'] = array(
    '#type' => 'radios',
    '#title' => 'Simple',
    '#description' => t('When true, a rounded box does not appear around each post on your site. (Default value is false.)'),
    '#default_value' => variable_get('fb_comments_simple', 0),
    '#options' => array(t('False'), t('True')),
  );
  
  $form['widget_setings']['fb_comments_reverse'] = array(
    '#type' => 'radios',
    '#title' => 'Reverse',
    '#description' => t('When true, reverses order of comments so the most recent one appears at the bottom of the list and the composer appears at the bottom of the page.'),
    '#default_value' => variable_get('fb_comments_reverse', 0),
    '#options' => array(t('False'), t('True')),
  );
  
  $form['widget_setings']['fb_comments_publish_feed'] = array(
    '#type' => 'radios',
    '#title' => 'Publish feed',
    '#description' => t('Indicates whether the Post comment to my Facebook profile check box is checked. If false, the user must check the check box before the comment can be published to a user\'s Feed'),
    '#default_value' => variable_get('fb_comments_publish_feed', 0),
    '#options' => array(t('False'), t('True')),
  );
  
  

  
  $form = system_settings_form($form);
  return $form;
}