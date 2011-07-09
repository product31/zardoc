<?php
// $Id:


/**
 * Settings form
 */
function fb_like_settings_form(){
  $languages = language_list();

  $form = array();
  $fb = sony_connect_get_network('facebook');
  $form['fb_like_appid'] = array(
      '#type' => 'fieldset',
      '#title' => 'Facebook Application ID',
      '#collapsible' => FALSE,
      '#description' => !empty($fb['conf']['application_id']) ? 'Facebook App ID: '.$fb['conf']['application_id'].'<p>'.t('!fb-tab', array('!fb-tab' => l('Change ID', 'admin/sony/connect/facebook'))).'</p>' : t('You have not enetered a Facebook application Id. Please enter the Facebook application Id for this site here: !fb. <p> If you do not have an ID, register your application on Facebook to get a Facebook App Id: !url.</p>
      <p>Go on your facebook app page (Applications > Developer > My Applications)
      click "Edit Settings". Then click "Connect".</p> <p>Make sure that the "Connect URL" matches your domain exactly.</p>', array('!url' => l('Register here', 'http://developers.facebook.com/setup/'), '!fb' => l('Facebook setup', 'admin/sony/connect/facebook')))
    );

  $form['widget_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Widget settings'),
    '#description' => t('Configure the like button style. The Facebook Like block will inherit these settings by default.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $widget_elements = fb_like_widget_settings_form();
  foreach($widget_elements as $key => $value){
    $form['widget_settings'][$key] = $value;
  }
  
  $form['node_types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content types'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['node_types']['fb_like_node_types'] = array(
    '#type' => 'checkboxes',
    '#description' => t('Select types that will use the facebook like plugin'),
    '#default_value' => variable_get('fb_like_node_types', array()),
    '#options' => node_get_types('names'),
  );

  $form['widget_location'] = array(
    '#type' => 'fieldset',
    '#title' => t('Widget location and display'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['widget_location']['fb_like_location'] = array(
    '#type' => 'radios',
    '#title' => t('Widget display location'),
    '#default_value' => variable_get('fb_like_location', 0),
    '#options' => array(t('Node links'), t('Node content')),
    '#description' => t('The widget can be printed in the "links" array of the node or as part of the node content'),
  );

  $form['widget_location']['fb_like_display_teasers'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show on teasers'),
    '#default_value' => variable_get('fb_like_display_teasers', 1),
    '#description' => t('Should the widget be displayed in node teasers?'),
  );

  $form['fb_like_urls'] = array(
    '#type' => 'fieldset',
    '#title' => t('Submitted Url Mode'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['fb_like_urls']['fb_like_urls_mode'] = array(
    '#type' => 'radios',
    '#title' => t('Url alias mode'),
    '#default_value' => variable_get('fb_like_urls_mode', 0),
    '#options' => array(t('aliased'), t('Unaliased')),
    '#description' => t('The url version of your post you want to be shown in fb. Aliased - http://example.com/mypage, Unaliased - http://example.com/node/34')
  );

  $form['fb_language'] = array(
    '#type' => 'fieldset',
    '#title' => t('Facebook Language'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['fb_language']['fb_like_locale'] = array(
      '#title' => t('Default facebook application locale'),
      '#type' => 'select',
      '#default_value' => variable_get('fb_like_locale', 'en_US'),
      '#description' => t('Configure Language Mapping below for all global sites.'),
      '#options' => _get_facebook_locale()
  );

  $form['fb_language']['fb_like_languages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Language mapping'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['fb_language']['fb_like_languages']['fb_like_locale_auto'] = array(
    '#title' => t('Enable Language Mapping'),
    '#type' => 'checkbox', 
    '#default_value' => variable_get('fb_like_locale_auto', 0),
    '#description' => t('Check to override the default facebook application locale set above and use locale based on the mappings below. Uncheck this to force the node to use the default facebook locale set above.'),
   );

  foreach ($languages as $language) {
    $form['fb_language']['fb_like_languages']['fb_like_language_'. $language->language] = array(
      '#type' => 'select',
      '#title' => 'Mapping for ' . $language->name . ' (' . $language->language . ')',
      '#description' => t('Select the equivalent language code in the facebook locale'),
      '#default_value' => variable_get('fb_like_language_' . $language->language, 'en_US'),
      '#options' => _get_facebook_locale(),
    );
  }
  
  $form = system_settings_form($form);
  return $form;
}

function fb_like_widget_settings_form(){
  $form = array();
  $form['fb_like_layout_style'] = array(
    '#type' => 'select',
    '#title' => t('Layout style'),
    '#description' => t('Determines the size and the amount of the social context next to the button'),
    '#default_value' => variable_get('fb_like_layout_style', 'button_count'),
    '#options' => array('standard' => t('standard'), 'button_count' => t('button_count'), 'box_count' => t('box_count') ),
  );
  
  $form['fb_like_show_faces'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show faces'),
    '#description' => t('Show profiles pictures below the button'),
    '#default_value' => variable_get('fb_like_show_faces', 0),
  );
  
  $form['fb_like_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#description' => t('The width of the plugin in pixel'),
    '#default_value' => variable_get('fb_like_width', 90),
  );
  
  $form['fb_like_verb'] = array(
    '#type' => 'select',
    '#title' => t('Verb'),
    '#description' => t('The verb to display in the button'),
    '#default_value' => variable_get('fb_like_verb', 'like'),
    '#options' => array('like' => t('like'), 'recommend' => t('recommend') )
  );
  
  $form['fb_like_font'] = array(
    '#type' => 'select',
    '#title' => t('Font'),
    '#description' => t('The font of the plugin'),
    '#default_value' => variable_get('fb_like_font', 'verdana'),
    '#options' => array('arial' => t('arial'), 'verdana' => t('verdana') )
  );
  
  $form['fb_like_color'] = array(
    '#type' => 'select',
    '#title' => t('Color'),
    '#description' => t('The color scheme of the plugin'),
    '#default_value' => variable_get('fb_like_color', 'light'),
    '#options' => array('dark' => t('dark'), 'light' => t('light'))
  );
  
  return $form;
}

function _get_facebook_locale(){
  $fb_locale = array();
  $cache = cache_get('fb_like');
  if (empty($cache->data)) {
    $xml = simplexml_load_file("http://www.facebook.com/translations/FacebookLocales.xml");
    foreach ( $xml->locale as $line ) {
      $representation = ( array ) $line->codes->code->standard->representation;
      $name = ( array ) $line->englishName;
      $key = $representation[0];
      $value = $name[0];
      $fb_locale[$key] = $value;
    }
    asort($fb_locale);
    cache_set('fb_like', serialize($fb_locale), 'cache');
  }
  else {
    $fb_locale = unserialize($cache->data);
  }
  return $fb_locale;
}