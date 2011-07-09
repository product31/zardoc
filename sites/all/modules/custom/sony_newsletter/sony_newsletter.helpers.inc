<?php
// $Id$

/**
 * @file
 * file_description
 */

/**
 * Element validator to find phone number fields and clean them up for
 * submission.
 */
function sony_newsletter_clean_phone_fields($element, &$form_state) {
  // Sanitize any phone numbers.
  $phone_fields = array('phone_day', 'phone_evening', 'phone_mobile', 'fax_number');
  foreach ($phone_fields as $field) {
    if (!empty($form_state['values']['demographics'][$field])) {
      $form_state['values']['demographics'][$field] = sony_newsletter_phone_cleanup($form_state['values']['demographics'][$field]);
    }
  }
}

/**
 * Element validate callback to copy the Sony COPPA birth date field into the
 * format expected by Sony CRM.
 */
function sony_newsletter_copy_coppa_dob_value($element, &$form_state) {
  // For some stupid reason they don't use numeric months.
  $months = array(
    0 => '',
    1 => 'JAN',
    2 => 'FEB',
    3 => 'MAR',
    4 => 'APR',
    5 => 'MAY',
    6 => 'JUN',
    7 => 'JUL',
    8 => 'AUG',
    9 => 'SEP',
    10 => 'OCT',
    11 => 'NOV',
    12 => 'DEC',
  );
  $form_state['values']['demographics']['birth_day'] = (int) $element['day']['#value'];
  $form_state['values']['demographics']['birth_month'] = $months[(int) $element['month']['#value']];
  $form_state['values']['demographics']['birth_year'] = (int) $element['year']['#value'];
}

/**
 * Element validate callback to copy the country profile field into the
 * format and location expected by Sony CRM.
 */
function sony_newsletter_copy_profile_country_value($element, &$form_state) {
  // Needed for _sony_newsletter_country_lookup() below.
  module_load_include('inc', 'sony_newsletter', 'sony_newsletter.helpers');

  // The country values are keyed differently from those in  _sony_newsletter_country_lookup()
  // so we need to look up the country code.
  $key = array_search($form_state['values'][$element['#parents'][0]], _sony_newsletter_country_lookup());
  if ($key !== FALSE) {
    $form_state['values']['demographics']['country'] = $key;
  }
  else {
    form_error($element, t('!name field is required.', array('!name' => $element['#title'])));
  }
}

/**
 * Element validate callback to copy the zip code field into the location
 * expected by Sony CRM.
 */
function sony_newsletter_copy_profile_zip_value($element, &$form_state) {
  $element_name = $element['#parents'][0];
  $form_state['values']['demographics']['zip_postal_code'] = $form_state['values'][$element_name];
}

function sony_newsletter_mail_validate($element, &$form_state) {
  // Regex provided by the SonyCRM people.
  $email_regex = "/^([a-z0-9_\-\.])+([a-z0-9_\-\.+]*)@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.)|(([a-z0-9\-]+\.)+))([a-z]{2,4}|[0-9]{1,3})(\]?)$/";
  if (!empty($element['#value']) && !preg_match($email_regex, $element['#value'], $matches)) {
    form_error($element, t('The e-mail address is not valid.'));
  }
}

function sony_newsletter_phone_validate($element, &$form_state) {
  if ($element['#value']) {
    $number = sony_newsletter_phone_cleanup($element['#value']);
    if (strlen($number) < 10) {
      form_error($element, t('The phone number entered does not appear to be valid. The number must be at least a 10 digit phone number with area code.'));
    }
  }
}

function sony_newsletter_phone_cleanup($number) {
  $number = preg_replace('/[^0-9]/', '', $number);
  if (strpos($number, '1') === 0) {
    $number = substr($number, 1);
  }
  return $number;
}

/**
 * Helper function; translates country names into country codes.
 */
function _sony_newsletter_country_lookup($name = NULL) {
  $external = array(
    'US' => 'United States',
    'GB' => 'United Kingdom',
    'CA' => 'Canada',
    'AF' => 'Afghanistan',
    'AL' => 'Albania',
    'DZ' => 'Algeria',
    'AS' => 'American Samoa',
    'AD' => 'Andorra',
    'AO' => 'Angola',
    'AI' => 'Anguilla',
    'AQ' => 'Antarctica',
    'AG' => 'Antigua and Barbuda',
    'AR' => 'Argentina',
    'AM' => 'Armenia',
    'AW' => 'Aruba',
    'AU' => 'Australia',
    'AT' => 'Austria',
    'AZ' => 'Azerbaijan',
    'BS' => 'Bahamas',
    'BH' => 'Bahrain',
    'BD' => 'Bangladesh',
    'BB' => 'Barbados',
    'BY' => 'Belarus',
    'BE' => 'Belgium',
    'BZ' => 'Belize',
    'BJ' => 'Benin',
    'BM' => 'Bermuda',
    'BT' => 'Bhutan',
    'BO' => 'Bolivia',
    'BA' => 'Bosnia and Herzegovina',
    'BW' => 'Botswana',
    'BV' => 'Bouvet Island',
    'BR' => 'Brazil',
    'IO' => 'British Indian Ocean Territory',
    'BN' => 'Brunei Darussalam',
    'BG' => 'Bulgaria',
    'BF' => 'Burkina Faso',
    'BI' => 'Burundi',
    'KH' => 'Cambodia',
    'CM' => 'Cameroon',
    'CV' => 'Cape Verde',
    'KY' => 'Cayman Islands',
    'CF' => 'Central African Republic',
    'TD' => 'Chad',
    'CL' => 'Chile',
    'CN' => 'China',
    'CX' => 'Christmas Island',
    'CC' => 'Cocos (Keeling) Islands',
    'CO' => 'Colombia',
    'KM' => 'Comoros',
    'CG' => 'Congo',
    'CD' => 'Congo, The Democratic Republic Of The',
    'CK' => 'Cook Islands',
    'CR' => 'Costa Rica',
    'CI' => "Cote D'Ivoire",
    'HR' => 'Croatia',
    'CU' => 'Cuba',
    'CY' => 'Cyprus',
    'CZ' => 'Czech Republic',
    'DK' => 'Denmark',
    'DJ' => 'Djibouti',
    'DM' => 'Dominica',
    'DO' => 'Dominican Republic',
    'EC' => 'Ecuador',
    'EG' => 'Egypt',
    'SV' => 'El Salvador',
    'GQ' => 'Equatorial Guinea',
    'ER' => 'Eritrea',
    'EE' => 'Estonia',
    'ET' => 'Ethiopia',
    'FK' => 'Falkland Islands (Malvinas)',
    'FO' => 'Faroe Islands',
    'FJ' => 'Fiji',
    'FI' => 'Finland',
    'FR' => 'France',
    'GF' => 'French Guiana',
    'PF' => 'French Polynesia',
    'TF' => 'French Southern Territories',
    'GA' => 'Gabon',
    'GM' => 'Gambia',
    'GE' => 'Georgia',
    'DE' => 'Germany',
    'GH' => 'Ghana',
    'GI' => 'Gibraltar',
    'GR' => 'Greece',
    'GL' => 'Greenland',
    'GD' => 'Grenada',
    'GP' => 'Guadeloupe',
    'GU' => 'Guam',
    'GT' => 'Guatemala',
    'GN' => 'Guinea',
    'GW' => 'Guinea-Bissau',
    'GY' => 'Guyana',
    'HT' => 'Haiti',
    'HM' => 'Heard Island and McDonald Islands',
    'HN' => 'Honduras',
    'HK' => 'Hong Kong',
    'HU' => 'Hungary',
    'IS' => 'Iceland',
    'IN' => 'India',
    'ID' => 'Indonesia',
    'IR' => 'Iran: Islamic Republic Of',
    'IQ' => 'Iraq',
    'IE' => 'Ireland',
    'IL' => 'Israel',
    'IT' => 'Italy',
    'JM' => 'Jamaica',
    'JP' => 'Japan',
    'JO' => 'Jordan',
    'KZ' => 'Kazakhstan',
    'KE' => 'Kenya',
    'KI' => 'Kiribati',
    'KP' => "Korea: Democratic People's Republic Of",
    'KR' => 'Korea: Republic Of',
    'KW' => 'Kuwait',
    'KG' => 'Kyrgyzstan',
    'LA' => "Lao People's Democratic Republic",
    'LV' => 'Latvia',
    'LB' => 'Lebanon',
    'LS' => 'Lesotho',
    'LR' => 'Liberia',
    'LY' => 'Libyan Arab Jamahiriya',
    'LI' => 'Liechtenstein',
    'LT' => 'Lithuania',
    'LU' => 'Luxembourg',
    'MO' => 'Macao',
    'MK' => 'Macedonia: The Former Yugoslav Republic of',
    'MG' => 'Madagascar',
    'MW' => 'Malawi',
    'MY' => 'Malaysia',
    'MV' => 'Maldives',
    'ML' => 'Mali',
    'MT' => 'Malta',
    'MH' => 'Marshall Islands',
    'MQ' => 'Martinique',
    'MR' => 'Mauritania',
    'MU' => 'Mauritius',
    'YT' => 'Mayotte',
    'MX' => 'Mexico',
    'FM' => 'Micronesia: Federated States of',
    'MD' => 'Moldova: Republic of',
    'MC' => 'Monaco',
    'MN' => 'Mongolia',
    'MS' => 'Montserrat',
    'MA' => 'Morocco',
    'MZ' => 'Mozambique',
    'MM' => 'Myanmar',
    'NA' => 'Namibia',
    'NR' => 'Nauru',
    'NP' => 'Nepal',
    'NL' => 'Netherlands',
    'AN' => 'Netherlands Antilles',
    'NC' => 'New Caledonia',
    'NZ' => 'New Zealand',
    'NI' => 'Nicaragua',
    'NE' => 'Niger',
    'NG' => 'Nigeria',
    'NU' => 'Niue',
    'NF' => 'Norfolk Island',
    'MP' => 'Northern Mariana Islands',
    'NO' => 'Norway',
    'OM' => 'Oman',
    'PK' => 'Pakistan',
    'PW' => 'Palau',
    'PS' => 'Palestinian Territory: Occupied',
    'PA' => 'Panama',
    'PG' => 'Papua New Guinea',
    'PY' => 'Paraguay',
    'PE' => 'Peru',
    'PH' => 'Philippines',
    'PN' => 'Pitcairn',
    'PL' => 'Poland',
    'PT' => 'Portugal',
    'PR' => 'Puerto Rico',
    'QA' => 'Qatar',
    'RE' => 'Reunion',
    'RO' => 'Romania',
    'RU' => 'Russian Federation',
    'RW' => 'Rwanda',
    'SH' => 'Saint Helena',
    'KN' => 'Saint Kitts And Nevis',
    'LC' => 'Saint Lucia',
    'PM' => 'Saint Pierre And Miquelon',
    'VC' => 'Saint Vincent and The Grenadines',
    'WS' => 'Samoa',
    'SM' => 'San Marino',
    'ST' => 'Sao Tome and Principe',
    'SA' => 'Saudi Arabia',
    'SN' => 'Senegal',
    'CS' => 'Serbia and Montenegro',
    'SC' => 'Seychelles',
    'SL' => 'Sierra Leone',
    'SG' => 'Singapore',
    'SK' => 'Slovakia',
    'SI' => 'Slovenia',
    'SB' => 'Solomon Islands',
    'SO' => 'Somalia',
    'ZA' => 'South Africa',
    'GS' => 'South Georgia and The South Sandwich Islands',
    'ES' => 'Spain',
    'LK' => 'Sri Lanka',
    'SD' => 'Sudan',
    'SR' => 'Suriname',
    'SJ' => 'Svalbard and Jan Mayen',
    'SZ' => 'Swaziland',
    'SE' => 'Sweden',
    'CH' => 'Switzerland',
    'SY' => 'Syrian Arab Republic',
    'TW' => 'Taiwan',
    'TJ' => 'Tajikistan',
    'TZ' => 'Tanzania: United Republic of',
    'TH' => 'Thailand',
    'TL' => 'Timor-Leste',
    'TG' => 'Togo',
    'TK' => 'Tokelau',
    'TO' => 'Tonga',
    'TT' => 'Trinidad and Tobago',
    'TN' => 'Tunisia',
    'TR' => 'Turkey',
    'TM' => 'Turkmenistan',
    'TC' => 'Turks and Caicos Islands',
    'TV' => 'Tuvalu',
    'UG' => 'Uganda',
    'UA' => 'Ukraine',
    'AE' => 'United Arab Emirates',
    'UM' => 'United States Minor Outlying Islands',
    'UY' => 'Uruguay',
    'UZ' => 'Uzbekistan',
    'VU' => 'Vanuatu',
    'VA' => 'Vatican City State',
    'VE' => 'Venezuela',
    'VN' => 'Viet Nam',
    'VG' => 'Virgin Islands: British',
    'VI' => 'Virgin Islands: U.S.',
    'WF' => 'Wallis and Futuna',
    'EH' => 'Western Sahara',
    'YE' => 'Yemen',
    'ZM' => 'Zambia',
    'ZW' => 'Zimbabwe',
  );
  !$name ? $value = $external : $value = $external[$name];
  return $value;
}

/**
 * Helper function; provide a list of states
 */
function _sony_newsletter_state_list() {
  return array(
    '' => '',
    'AL' => 'Alabama',
    'AK' => 'Alaska',
    'AB' => 'Alberta',
    'AS' => 'American Samoa',
    'AZ' => 'Arizona',
    'AR' => 'Arkansas',
    'AE' => 'Armed Forces Africa',
    'AA' => 'Armed Forces Americas',
    'AE' => 'Armed Forces Canada',
    'AE' => 'Armed Forces Europe',
    'AE' => 'Armed Forces Middle East',
    'AP' => 'Armed Forces Pacific',
    'BC' => 'British Columbia',
    'CA' => 'California',
    'CO' => 'Colorado',
    'CT' => 'Connecticut',
    'DE' => 'Delaware',
    'DC' => 'District Of Columbia',
    'FM' => 'Federated States Of Micronesia',
    'FL' => 'Florida',
    'GA' => 'Georgia',
    'GU' => 'Guam',
    'HI' => 'Hawaii',
    'ID' => 'Idaho',
    'IL' => 'Illinois',
    'IN' => 'Indiana',
    'IA' => 'Iowa',
    'KS' => 'Kansas',
    'KY' => 'Kentucky',
    'LA' => 'Louisiana',
    'ME' => 'Maine',
    'MB' => 'Manitoba',
    'MH' => 'Marshall Islands',
    'MD' => 'Maryland',
    'MA' => 'Massachusetts',
    'MI' => 'Michigan',
    'MN' => 'Minnesota',
    'MS' => 'Mississippi',
    'MO' => 'Missouri',
    'MT' => 'Montana',
    'NE' => 'Nebraska',
    'NV' => 'Nevada',
    'NB' => 'New Brunswick',
    'NH' => 'New Hampshire',
    'NJ' => 'New Jersey',
    'NM' => 'New Mexico',
    'NY' => 'New York',
    'NL' => 'Newfoundland And Labrador',
    'NC' => 'North Carolina',
    'ND' => 'North Dakota',
    'MP' => 'Northern Mariana Islands',
    'NT' => 'Northwest Territories',
    'NS' => 'Nova Scotia',
    'NU' => 'Nunavut',
    'OH' => 'Ohio',
    'OK' => 'Oklahoma',
    'ON' => 'Ontario',
    'OR' => 'Oregon',
    'PW' => 'Palau',
    'PA' => 'Pennsylvania',
    'PE' => 'Prince Edward Island',
    'PR' => 'Puerto Rico',
    'QC' => 'Quebec',
    'RI' => 'Rhode Island',
    'SK' => 'Saskatchewan',
    'SC' => 'South Carolina',
    'SD' => 'South Dakota',
    'TN' => 'Tennessee',
    'TX' => 'Texas',
    'UT' => 'Utah',
    'VT' => 'Vermont',
    'VI' => 'Virgin Islands',
    'VA' => 'Virginia',
    'WA' => 'Washington',
    'WV' => 'West Virginia',
    'WI' => 'Wisconsin',
    'WY' => 'Wyoming',
    'YT' => 'Yukon',
  );
}

