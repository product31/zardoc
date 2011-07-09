<?php
// $Id: views_bonus_plugin_style_export_xml.inc,v 1.1 2008/10/28 02:18:32 neclimdul Exp $
/**
 * @file
 * Plugin include file for export style plugin.
 */

/**
 * Generalized style plugin for export plugins.
 */
class views_bonus_plugin_style_export_xml extends views_plugin_style {
  function attach_to($display_id, $path, $title) {
    //...
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['filename'] = array(
      'default' => 'view-%view.xml',
      'translatable' => FALSE,
    );

    return $options;
  }

  function options_form(&$form, &$form_state) {

    $form['filename'] = array(
      '#type' => 'textfield',
      '#title' => t('XML filename'),
      '#default_value' => $this->options['filename'],
      '#description' => t('The filename that will be suggested to the browser for downloading purposes. %view will be replaced with the view name.'),
      '#process' => array('views_process_dependency'),
      '#dependency' => array('edit-style-options-override' => array(FALSE)),
    );
  }
}
