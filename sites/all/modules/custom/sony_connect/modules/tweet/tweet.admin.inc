<?php
// $Id: 

function tweet_admin_settings() {
  $languages = language_list();
  $form = array();

  $form['button'] = array(
    '#type' => 'fieldset',
    '#title' => t('Choose your button. Customize it'),
  );

  $button_elements = tweet_button_settings_form();
  foreach($button_elements as $key => $value){
    $form['button'][$key] = $value;
  }

  $form['follow'] = array(
    '#type' => 'fieldset',
    '#title' => t('Recommend people to follow'),
  );

  $follow_elements = tweet_follow_settings_form();
  foreach($follow_elements as $key => $value){
    $form['follow'][$key] = $value;
  }
  
  $form['node_settings'] = array(
  '#type' => 'fieldset',
  '#title' => t('Node Settings'),
  );

  $node_settings = tweet_node_settings();
  foreach($node_settings as $key => $value){
    $form['node_settings'][$key] = $value;
  }
    
  $form['locale'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tweet Button Language'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  
  $form['locale']['tweet_language'] = array(
    '#title' => t('Language'),
    '#description' => t('This is the language that the button will render in on your website. People will see the Tweet dialog in their selected language for Twitter.com.'),
    '#type' => 'select',
    '#options' => _get_tweet_locale(),
    '#default_value' => variable_get('tweet_language',''),
  );

  $form['locale']['mapping'] = array(
    '#type' => 'fieldset',
    '#title' => t('Language mapping'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['locale']['mapping']['tweet_locale_auto'] = array(
    '#title' => t('Enable Language Mapping'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('tweet_locale_auto', 0),
    '#description' => t('Check to override the default facebook application locale set above and use locale based on the mappings below. Uncheck this to force the node to use the default facebook locale set above.'),
   );

  foreach ($languages as $language) {
    $form['locale']['mapping']['tweet_language_'. $language->language] = array(
      '#type' => 'select',
      '#title' => 'Mapping for ' . $language->name . ' (' . $language->language . ')',
      '#description' => t('Select the equivalent language code in the twitter locale'),
      '#default_value' => variable_get('tweet_language_' . $language->language, 'en_US'),
      '#options' => _get_tweet_locale(),
    );
  }

  $form['preview'] = array(
    '#type' => 'fieldset',
    '#title' => t('Preview'),
  );
  

  $attributes = tweet_get_attributes();
  
  $markup = '<div id="tweet-preview"><a href="http://twitter.com/share" class="twitter-share-button" '. drupal_attributes($attributes).'>Tweet</a></div>';
  $form['preview']['tweet_preview'] = array(
    '#type' => 'markup',
    '#value' => $markup, 
  );

  drupal_set_html_head('<script type="text/javascript" src="http://platform.twitter.com/widgets.js"></script>'); 
  drupal_add_css(drupal_get_path('module', 'tweet').'/tweet.css');
  return system_settings_form($form);
}

function tweet_node_settings() {
  $form = array();
  
  $node_types = node_get_types();
  foreach($node_types as $node_type) {
    $types[$node_type->type] = $node_type->name;
  }
  
  $form['tweet_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Node Types'),
    '#options' => $types,
    '#default_value' => variable_get('tweet_node_types', array('article')),
  );
  
//  $form['tweet_node_location'] = array(
//    '#type'    => 'checkboxes',
//    '#title'   => t('Locations'),
//    '#options' => array(
//      'full'    => t('Full View'),
//      'teaser'  => t('Teasers'),
//    ),
//    '#default_value' => variable_get('tweet_node_location', array('full')),
//  );
  
  $form['tweet_node_location'] = array(
    '#type' => 'radios',
    '#title' => t('Widget display location'),
    '#default_value' => variable_get('tweet_node_location', 0),
    '#options' => array(t('Node links'), t('Node content')),
    '#description' => t('The tweet button can be printed in the "links" array of the node or as part of the node content'),
  );

  $form['tweet_display_teasers'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show on teasers'),
    '#default_value' => variable_get('tweet_display_teasers', 1),
    '#description' => t('Should the tweet button be displayed in node teasers?'),
  );

  $form['tweet_node_weight'] = array(
    '#type'          => 'weight',
    '#title'         => t('Weight'),
    '#default_value' => variable_get('tweet_node_weight', -5),
    '#description'   => t('Heavier weight will sink button to bottom on node view'),
  );
  
  return $form;
}

function tweet_button_settings_form() {
  $form = array();
  $form['tweet_button'] = array(
    '#type' => 'select',
    '#options' => array(
      'vertical' => t('Vertical Count'),
      'horizontal' => t('Horizontal Count'),
      'none'   => t('No count'),
    ),
    '#default_value' => variable_get('tweet_button', 'horizontal'),
    '#id' => 'tweet-button',
  );

  $form['tweet_tweet_text'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Tweet Text'),
    '#default_value' => variable_get('tweet_tweet_text','Check out !title at !node_url.'),
    '#description'   => t('This is the text that people will include in their Tweet when they share from your website. If left empty title will be used. ' .
      'Available tokens are: !title, !author_name, !node_type, !node_url (NOTE: Twitter will generate short url for the node)'),
  );

  $form['tweet_tweet_url'] = array(
    '#type'          => 'textfield',
    '#title'         => t('URL'),
    '#default_value' => variable_get('tweet_tweet_url',''),
    '#description'   => t('Leave blank for using the URL of the node the button is on.'),
  );

  return $form;
}

function tweet_follow_settings_form() {
  $form = array();
  $form['tweet_account'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter account to follow'),
    '#description' => t('This user will be @mentioned in the suggested'),
    '#default_value' => variable_get('tweet_account',''),
    '#id' => 'tweet-account',
  );

  $form['tweet_rel_account_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Related Account'),
    '#default_value' => variable_get('tweet_rel_account_name',''),
  );

  $form['tweet_rel_account_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Related Account Description'),
    '#default_value' => variable_get('tweet_rel_account_description',''),
  );
  return $form;
}

function _get_tweet_locale() {

  $options = array(
      'en' => t('English'),
      'fr' => t('French'),
      'de' => t('German'),
      'es' => t('Spanish'),
      'ja' => t('Japanese'),
    );
  return $options;
  }