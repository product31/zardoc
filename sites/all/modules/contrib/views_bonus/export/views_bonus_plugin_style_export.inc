<?php
// $Id: views_bonus_plugin_style_export.inc,v 1.2 2008/10/08 05:54:07 neclimdul Exp $
/**
 * @file
 * Plugin include file for export style plugin.
 */

/**
 * Generalized style plugin for export plugins.
 */
class views_bonus_plugin_style_export_doc extends views_plugin_style {
  function attach_to($display_id, $path, $title) {
    $display = $this->view->display[$display_id]->handler;
    $url_options = array();
    $input = $this->view->get_exposed_input();
    if ($input) {
      $url_options['query'] = $input;
    }

    $url = url($this->view->get_url(NULL, $path), $url_options);
    if ($display->has_path()) {
      if (empty($this->preview)) {
        drupal_add_feed($url, $title);
      }
    }
    else {
      if (empty($this->view->feed_icon)) {
        $this->view->feed_icon = '';
      }

      $this->view->feed_icon .= theme('feed_icon', $url, $title);
      drupal_add_link(array(
        'rel' => 'alternate',
        'type' => 'application/rss+xml',
        'title' => $title,
        'href' => $url
      ));
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['filename'] = array(
      'default' => 'view-%view.csv',
      'translatable' => FALSE,
    );
    $options['headers'] = array(
      'default' => TRUE,
      'translatable' => TRUE,
    );
    $options['quote'] = array(
      'default' => TRUE,
      'translatable' => TRUE,
    );

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['filename'] = array(
      '#type' => 'textfield',
      '#title' => t('CSV filename'),
      '#default_value' => $this->options['filename'],
      '#description' => t('The filename that will be suggested to the browser for downloading purposes. %view will be replaced with the view name.'),
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-style-options-override' => array(FALSE)),
    );
    $form['headers'] = array(
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['headers']),
      '#title' => t('Output field name headers with the file.'),
    );
    $form['quote'] = array(
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['quote']),
      '#title' => t('Quote values. Useful for output that might have commas as part of one of the values.'),
    );
  }
}
