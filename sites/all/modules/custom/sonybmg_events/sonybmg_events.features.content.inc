<?php

/**
 * Implementation of hook_content_default_fields().
 */
function sonybmg_events_content_default_fields() {
  $fields = array();

  // Exported field: field_date
  $fields['date-field_date'] = array(
    'field_name' => 'field_date',
    'type_name' => 'date',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'field_date_default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'field_date_default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'field_date_default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'date',
    'required' => '1',
    'multiple' => '0',
    'module' => 'date',
    'active' => '1',
    'granularity' => array(
      'year' => 'year',
      'month' => 'month',
      'day' => 'day',
    ),
    'timezone_db' => '',
    'tz_handling' => 'none',
    'todate' => 'optional',
    'repeat' => 0,
    'repeat_collapsed' => '',
    'default_format' => 'field_date_default',
    'widget' => array(
      'default_value' => 'blank',
      'default_value_code' => '',
      'default_value2' => 'same',
      'default_value_code2' => '',
      'input_format' => 'm/d/Y - g:i:sa',
      'input_format_custom' => '',
      'increment' => '1',
      'text_parts' => array(),
      'year_range' => '-8:+8',
      'label_position' => 'above',
      'label' => 'Date',
      'weight' => '-2',
      'description' => '',
      'type' => 'date_select',
      'module' => 'date',
    ),
  );

  // Exported field: field_location
  $fields['date-field_location'] = array(
    'field_name' => 'field_location',
    'type_name' => 'date',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 1,
      'size' => 60,
      'label' => 'Location',
      'weight' => '1',
      'description' => 'City, State, Country (if outside the U.S.A.)',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_sold_out
  $fields['date-field_sold_out'] = array(
    'field_name' => 'field_sold_out',
    'type_name' => 'date',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '5',
    'allowed_values' => 'No
Yes',
    'allowed_values_php' => '',
    'widget' => array(
      'label' => 'Sold Out',
      'weight' => '4',
      'description' => 'Select \'Yes\' if the show is sold out - this will override the ticket sales link.',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_ticket_sales_url
  $fields['date-field_ticket_sales_url'] = array(
    'field_name' => 'field_ticket_sales_url',
    'type_name' => 'date',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => 2048,
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 1,
      'size' => 60,
      'label' => 'Ticket sales url',
      'weight' => '3',
      'description' => 'Please enter the full url beginning with http://',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_venue
  $fields['date-field_venue'] = array(
    'field_name' => 'field_venue',
    'type_name' => 'date',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 1,
      'size' => 60,
      'label' => 'Venue',
      'weight' => '-1',
      'description' => 'City, State, Country (if outside the U.S.A.)',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_venue_notes
  $fields['date-field_venue_notes'] = array(
    'field_name' => 'field_venue_notes',
    'type_name' => 'date',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '255',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '2',
      'size' => 60,
      'label' => 'Notes',
      'weight' => '2',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_venue_url
  $fields['date-field_venue_url'] = array(
    'field_name' => 'field_venue_url',
    'type_name' => 'date',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => 2048,
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 1,
      'size' => 60,
      'label' => 'Venue URL',
      'weight' => 0,
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Date');
  t('Location');
  t('Notes');
  t('Sold Out');
  t('Ticket sales url');
  t('Venue');
  t('Venue URL');

  return $fields;
}
