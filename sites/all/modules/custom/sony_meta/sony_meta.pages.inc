<?php

function sony_meta_add(){

  if (!user_access('add meta')) {
    return;
  }

  // First off, load in custom values if they've been set for this path
  $meta = sony_meta_get();
  global $language;

  // If no custom values, load defaults
  $title = ($meta && $meta->title) ? $meta->title : drupal_get_title();
  $keywords = ($meta && $meta->keywords) ? $meta->keywords : variable_get('artist_name', NULL ); // could add more defaults here
  $description = ($meta && $meta->description) ? $meta->description : ''; // TODO *****
  $current_language = ($meta && $meta->language) ? $meta->language : $language->language;
  $path = ($meta && $meta->path) ? $meta->path : drupal_get_path_alias($_GET['q']);
  $save_text = ($meta && $meta->mid) ? t('Update Meta Information') : t('Add New Meta Information');

  // add a default value based on $teaser?
  // for views, could I pull in the raw text somehow?
  // @todo - deal with paths
  // $pid = $meta->pid ? $meta->pid : '';

  if(!empty($meta->mid)){
    $form['mid'] = array(
    '#type' => 'hidden',
    '#value' => $meta->mid,
    );
    // @TODO: Figure out a better way to do this.
    $form['#meta'] = $meta;
    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Use Defaults'),
      '#submit' => array('sony_meta_delete_form'),
      '#weight' => 1,
    );
  }

  // @todo - deal with paths
  /*
  if($pid){
    $form['pid'] = array(
    '#type' => 'hidden',
    '#value' => $pid,
    );
  } */

  $form['path'] = array(
    '#type' => 'hidden',
    '#value' => $path,
  );

  $form['title'] = array(
    '#title' => t('HTML Title'),
    '#type' => 'textfield',
    '#default_value' => $title,
    '#validation_rules' => array(
      'maxlength' => 225,
    ),
    '#description' => t('The HTML title does three things: it defines a title in the browser toolbar; it provides a title for the page when it is added to favorites; it displays a title for the page in search-engine results. ') . '<br />' .
                      t('By default the title is the same as the page title.') . '<br />' .
                      t('Recommenation: Keep your title no more than 6 to 10 words long.'),
  );

  $form['keywords'] = array(
    '#title' => t('Meta Keywords'),
    '#type' => 'textarea',
    '#default_value' => $keywords,
    '#validation_rules' => array(
      'maxlength' => 500,
    ),
    // add a default value based on artist name, taxonomy, etc?
    '#description' => t('Add keywords and key phrases separated by commas. Try not to repeat words as that damages search engine ranking. ') . '<br />' .
                      t('Recommendation: limit to between 200 and 500 characters.'),
  );

  $form['description'] = array(
    '#title' => t('Meta Description'),
    '#type' => 'textarea',
    '#default_value' => $description,
    '#validation_rules' => array(
      'maxlength' => 250,
    ),
    '#description' => t('Add a description. This appears on search engine result pages.') . '<br />' .
                      t('Recommendation: limit to 200 characters'),
  );

  $form['ogtoggle'] = array(
    '#title' => t('Toggle display of the Facebook og:image'),
    '#type' => 'checkbox',
    '#default_value' => isset($meta->ogtoggle) ? $meta->ogtoggle : 1,
    '#description' => t('Uncheck this box to not use an og:image metatag on this page') . '<br />' .
                      t("Uncheck to select the image via facebook's default behavior"),
  );

  $form['ogimage'] = array(
    '#title' => t('Facebook og:image'),
    '#type' => 'textfield',
    '#default_value' => $meta->ogimage,
    '#description' => t('Enter an image url to override the default facbook og:image meta tag associated with this page.') . '<br />' .
                      t("If left blank, the og:image metatag will inherit it's default value"),
  );

  $form['ogtitle'] = array(
    '#title' => t('Facebook og:title'),
    '#type' => 'textfield',
    '#default_value' => $meta->ogtitle,
    '#description' => t('Use this field to override the default facbook og:title meta tag associated with this page.') . '<br />' .
                      t("If left blank, the og:title metatag will inherit it's default value"),
  );

  $form['ogdescription'] = array(
    '#title' => t('Facebook og:description'),
    '#type' => 'textarea',
    '#default_value' => $meta->ogdescription,
    '#description' => t('Use this field to override the facebook og:description meta tag associated with this page.') . '<br />' .
                      t("If left blank, the og:description metatag will inherit it's default value"),
  );

  $form['language'] = array(
    '#type' => 'hidden',
    '#value' => $current_language,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $save_text,
  );

  return $form;
}

function sony_meta_delete_form($form, &$form_state) {
  $meta = $form['#meta'];
  $form_state['redirect'] = array('sony_meta/delete/' . $meta->mid);
}

function sony_meta_add_submit($form, &$form_state) {
  $mid = isset($form_state['values']['mid']) ? $form_state['values']['mid'] : FALSE;
  $keys = empty($mid) ? array() : 'mid';
  drupal_write_record('sony_meta', $form_state['values'], $keys);
  // clear cache
  cache_clear_all();

  drupal_set_message(t('The meta information has been saved.'));
}