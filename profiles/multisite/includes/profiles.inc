<?php

/**
 * Default labelling and weight for this profile include.
 */
function profiles_info() {
  return array(
    'name' => st('User Profiles'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 0,
  );
}

/**
 * Required modules.
 */
function profiles_modules() {
  return array('profile', 'profile_privacy', 'views', 'path', 'token', 'pathauto', 'menu', 'sonybmg_profiles', 'imageapi', 'imagecache');
}

function profiles_task_list() {
  return array(
    'profiles_setup' => array(
      'message' => st('Setup user profiles.'),
      'weight' => 0,
    ),
    'profiles_privacy' => array(
      'message' => st('Setup user profiles privacy.'),
      'weight' => 0,
    ),
    'profiles_variables' => array(
      'message' => st('Setup default settings.'),
      'weight' => 0,
    ),
    'profiles_blocks' => array(
      'message' => st('Setup profile blocks.'),
      'weight' => 0,
    ),
  );
}

function profiles_setup() {

  $fields = array(
    array(
      'title' => st('First Name'),
      'name' => 'profile_first_name',
      'category' => 'Personal information',
      'type' => 'textfield',
      'weight' => -4,
      'register' => 0,
      'visibility' => 1,
    ),
    array(
      'title' => st('Last Name'),
      'name' => 'profile_last_name',
      'category' => 'Personal information',
      'type' => 'textfield',
      'weight' => -3,
      'register' => 0,
      'visibility' => 1,
    ),
    array(
      'category' => st('Personal information'),
      'title' => st('Gender'),
      'name' => 'profile_gender',
      'type' => 'selection',
      'options' => array('Male', 'Female'),
      'visibility' => 3,
      'register' => 0,
      'weight' => -2,
    ),
    /*
    array(
      'category' => st('Personal information'),
      'title' => st('Date of Birth'),
      'name' => 'profile_dob',
      'type' => 'date',
      'visibility' => 2,
      'register' => 0,
    ),*/
    array(
      'category' => st('Personal information'),
      'title' => st('City'),
      'name' => 'profile_city',
      'type' => 'textfield',
      'visibility' => 2,
      'register' => 0,
      'weight' => 2,
    ),
    array(
      'category' => st('Personal information'),
      'title' => st('State/Province'),
      'name' => 'profile_province',
      'type' => 'textfield',
      'visibility' => 3,
      'register' => 0,
      'weight' => 3,
    ),
    array(
      'category' => 'Personal information',
      'title' => 'Zip Code',
      'name' => 'profile_zip_code',
      'type' => 'textfield',
      'visibility' => 3,
      'register' => 1,
      'weight' => 4,
    ),
    array(
      'category' => st('Personal information'),
      'title' => st('Country'),
      'name' => 'profile_country',
      'type' => 'selection',
      'options' => profiles_countries(),
      'visibility' => 3,
      'register' => 1,
      'weight' => 5,
    ),
    array(
      'category' => st('Favorite lyric'),
      'title' => st('Song Title'),
      'name' => 'profile_lyric_title',
      'type' => 'textfield',
      'visibility' => 2,
      'register' => 0,
      'weight' => 0,
    ),
    array(
      'category' => st('Favorite lyric'),
      'title' => st('Attributed Artist'),
      'name' => 'profile_lyric_artist',
      'type' => 'textfield',
      'visibility' => 2,
      'register' => 0,
      'weight' => 1,
    ),
    array(
      'category' => st('Favorite lyric'),
      'title' => st('Lyric Content'),
      'name' => 'profile_lyric_body',
      'type' => 'textarea',
      'visibility' => 2,
      'register' => 0,
      'weight' => 2,
    ),
    array(
      'category' => st('Subscriptions'),
      'title' => st(' Yes, I want to receive the latest news & updates'),
      'name' => 'profile_newsletter',
      'type' => 'checkbox',
      'visibility' => 1,
      'register' => 0,
      'weight' => 4,
    ),
    array(
      'category' => st('Subscriptions'),
      'title' => st('MyPlay Newsletter'),
      'name' => 'profile_myplay_newsletter',
      'type' => 'checkbox',
      'weight' => 5,
      'register' => 0,
      'visibility' => 1,
    ),
    array(
      'category' => st('Subscriptions'),
      'title' => st('Cell Phone Number'),
      'name' => 'profile_mobile_phone',
      'type' => 'textfield',
      'visibility' => 1,
      'register' => 0,
      'weight' => 5,
      'explanation' => st('If you would also like to have SMS (text messages) sent to your cell phone, please fill out the information above. The following information is not required to join the email list. There can be costs associated with receiving SMS (text) messages depending on your wireless carrier and plan.'),
    ),
    array(
      'category' => st('Subscriptions'),
      'title' => st('Mobile Carrier'),
      'name' => 'profile_mobile_carrier',
      'type' => 'selection',
      'options' => array(
        '2' => 'Alltel PCS',
        '6' => 'Bell Mobility',
        '41' => 'Cincinnati Bell Wireless',
        '9' => 'AT&T',
        '40' => 'Dobson Cellular Systems',
        '45' => 'Leap Wireless',
        '46' => 'Midwest Wireless',
        '14' => 'Nextel',
        '19' => 'Sprint',
        '20' => 'Suncom',
        '21' => 'T-Mobile',
        '29' => 'U.S. Cellular',
        '27' => 'Verizon Wireless',
      ),
      'visibility' => 1,
      'register' => 0,
    ),
  );

  foreach ($fields as $field) {
    install_profile_field_add($field);
  }
}

/**
 * Set up our private profile fields.
 */
function profiles_privacy() {
  return _sonybmg_profiles_add_profile_privacy();
}

/**
 * Enable and setup our default user pictures settings.
 */
function profiles_variables() {
  variable_set('user_pictures', 1);
  variable_set('user_picture_path', 'pictures');
  variable_set('user_picture_dimensions', '1600x1400');
  variable_set('user_picture_file_size', '800');
  variable_set('pathauto_user_pattern', 'user/[user-raw]');

  // Set up block position
  $theme = variable_get('artist_key', '_starter');

  install_add_block('sonybmg_profiles', 0, $theme, TRUE, 2, 'right', 1, 'user/*');

  // Create our pictures directory
  $pic_path = variable_get('user_picture_path', 'pictures');
  file_check_directory(file_create_path($pic_path), 1);
  drupal_set_message(st('The user pictures directory has been created.'));
}

/**
 * Return a list of all countries in the world.
 */
function profiles_countries() {
  return array(
    'United States',
    'Afghanistan',
    'Aland Islands',
    'Albania',
    'Algeria',
    'American Samoa',
    'Andorra',
    'Angola',
    'Anguilla',
    'Antarctica',
    'Antigua and Barbuda',
    'Argentina',
    'Armenia',
    'Aruba',
    'Australia',
    'Austria',
    'Azerbaijan',
    'Bahamas',
    'Bahrain',
    'Bangladesh',
    'Barbados',
    'Belarus',
    'Belgium',
    'Belize',
    'Benin',
    'Bermuda',
    'Bhutan',
    'Bolivia',
    'Bosnia and Herzegovina',
    'Botswana',
    'Bouvet Island',
    'Brazil',
    'British Indian Ocean Territory',
    'Brunei Darussalam',
    'Bulgaria',
    'Burkina Faso',
    'Burundi',
    'Cambodia',
    'Cameroon',
    'Canada',
    'Cape Verde',
    'Cayman Islands',
    'Central African Republic',
    'Chad',
    'Chile',
    'China',
    'Christmas Island',
    'Cocos (Keeling) Islands',
    'Colombia',
    'Comoros',
    'Congo',
    'Congo, The Democratic Republic of the',
    'Cook Islands',
    'Costa Rica',
    'Cote d\'Ivoire',
    'Croatia',
    'Cuba',
    'Cyprus',
    'Czech Republic',
    'Denmark',
    'Djibouti',
    'Dominica',
    'Dominican Republic',
    'Ecuador',
    'Egypt',
    'El Salvador',
    'Equatorial Guinea',
    'Eritrea',
    'Estonia',
    'Ethiopia',
    'Falkland Islands (Malvinas)',
    'Faroe Islands',
    'Fiji',
    'Finland',
    'France',
    'French Guiana',
    'French Polynesia',
    'French Southern Territories',
    'Gabon',
    'Gambia',
    'Georgia',
    'Germany',
    'Ghana',
    'Gibraltar',
    'Greece',
    'Greenland',
    'Grenada',
    'Guadeloupe',
    'Guam',
    'Guatemala',
    'Guinea',
    'Guinea-Bissau',
    'Guyana',
    'Haiti',
    'Heard Island and Mcdonald Islands',
    'Honduras',
    'Hong Kong',
    'Hungary',
    'Iceland',
    'India',
    'Indonesia',
    'Iran: Islamic Republic of',
    'Iraq',
    'Ireland',
    'Israel',
    'Italy',
    'Jamaica',
    'Japan',
    'Jordan',
    'Kazakhstan',
    'Kenya',
    'Kiribati',
    'Korea: Democratic People\'s Republic of',
    'Korea: Republic of',
    'Kuwait',
    'Kyrgyzstan',
    'Lao People\'s Democratic Republic',
    'Latvia',
    'Lebanon',
    'Lesotho',
    'Liberia',
    'Libyan Arab Jamahiriya',
    'Liechtenstein',
    'Lithuania',
    'Luxembourg',
    'Macao',
    'Macedonia: The former Yugoslav Republic of',
    'Madagascar',
    'Malawi',
    'Malaysia',
    'Maldives',
    'Mali',
    'Malta',
    'Marshall Islands',
    'Martinique',
    'Mauritania',
    'Mauritius',
    'Mayotte',
    'Mexico',
    'Micronesia: Federated States of',
    'Moldova: Republic of',
    'Monaco',
    'Mongolia',
    'Montserrat',
    'Morocco',
    'Mozambique',
    'Myanmar',
    'Namibia',
    'Nauru',
    'Nepal',
    'Netherlands',
    'Netherlands Antilles',
    'New Caledonia',
    'New Zealand',
    'Nicaragua',
    'Niger',
    'Nigeria',
    'Niue',
    'Norfolk Island',
    'Northern Mariana Islands',
    'Norway',
    'Oman',
    'Pakistan',
    'Palau',
    'Palestinian Territory: Occupied',
    'Panama',
    'Papua New Guinea',
    'Paraguay',
    'Peru',
    'Philippines',
    'Pitcairn',
    'Poland',
    'Portugal',
    'Puerto Rico',
    'Qatar',
    'Reunion',
    'Romania',
    'Russian Federation',
    'Rwanda',
    'Saint Helena',
    'Saint Kitts and Nevis',
    'Saint Lucia',
    'Saint Pierre and Miquelon',
    'Saint Vincent and the Grenadines',
    'Samoa',
    'San Marino',
    'Sao Tome and Principe',
    'Saudi Arabia',
    'Senegal',
    'Serbia and Montenegro',
    'Seychelles',
    'Sierra Leone',
    'Singapore',
    'Slovakia',
    'Slovenia',
    'Solomon Islands',
    'Somalia',
    'South Africa',
    'South Georgia and the South Sandwich Islands',
    'Spain',
    'Sri Lanka',
    'Sudan',
    'Suriname',
    'Svalbard and Jan Mayen',
    'Swaziland',
    'Sweden',
    'Switzerland',
    'Syrian Arab Republic',
    'Taiwan',
    'Tajikistan',
    'Tanzania: United Republic Of',
    'Thailand',
    'Timor-leste',
    'Togo',
    'Tokelau',
    'Tonga',
    'Trinidad and Tobago',
    'Tunisia',
    'Turkey',
    'Turkmenistan',
    'Turks and Caicos Islands',
    'Tuvalu',
    'Uganda',
    'Ukraine',
    'United Arab Emirates',
    'United Kingdom',
    'United States Minor Outlying Islands',
    'Uruguay',
    'Uzbekistan',
    'Vanuatu',
    'Vatican City State',
    'Venezuela',
    'Viet nam',
    'Virgin Islands: British',
    'Virgin Islands: U.S.',
    'Wallis and Futuna',
    'Western Sahara',
    'Yemen',
    'Zambia',
    'Zimbabwe',
  );
}

function profiles_blocks() {
  $theme = variable_get('artist_key', '_starter');
  $status = TRUE;
  $region = 'right';
  $custom = FALSE;
  $visibility = 1; //0 = show on every page except ; 1 = show only on these pages, 2 = php

  // The users page "Why I'm A Fan" views block.
  install_add_block('sonybmg_profiles', '1', $theme, $status, 0, $region,
    $visibility, 'user/*');
  // The users page "My buddies" block.
  install_add_block('sonybmg_profiles', '2', $theme, $status, 0, $region,
    $visibility, 'user/*');
}

