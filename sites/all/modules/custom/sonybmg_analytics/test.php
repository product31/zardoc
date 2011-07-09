<?php
// $Id$

/**
 * @file
 * description
 */

/**
 * A simple function to create our nonce.
 */
function random_string($length = 10) {
  $characters = '0123456789abcdefghijklmnopqrstuvwxyz';
  $char_len = strlen($characters) - 1;
  $string = '';

  for ($i = 0; $i < $length; $i++) {
    $string .= $characters[mt_rand(0, $char_len)];
  }

  return $string;
}

// The method we want to call.
$method = 'stats.user.registrations';
// The predetermined domain for this application.
$domain = 'dashboard.sonymusicd2c.com';
// The shared key from the artist web site.
$shared_key = 'bfbe07a5940b2a831db885165bb4043d';
// The current timestamp.
$timestamp = (string)time();
// The nonce, a random string used to salt the hash.
$nonce = random_string();

// Build the hash_data from the defined values.
$hash_data = join(';', array($timestamp, $domain, $nonce, $method));
// Build the actual hash using the hash_data and the shared key.
$hash = hash_hmac('sha256', $hash_data, $shared_key, 0);

// Build an array of parameters to send through to the service.  The first 5
// params here are for the security token.  The rest are parameters of the
// method we are calling.
$params = array(
  'method' => $method,
  'hash' => $hash,
  'domain_name' => $domain,
  'domain_time_stamp' => $timestamp,
  'nonce' => $nonce,
  // method parameters follow
  'start' => '2009-07-16',
  'end' => '2009-07-31',
);
$request_url = 'http://www.jasonmichaelcarroll.com/services/rest?'. http_build_query($params);

// Do the actual request.
$session = curl_init($request_url);
curl_setopt($session, CURLOPT_FOLLOWLOCATION, true);
curl_setopt($session, CURLOPT_HEADER, FALSE);
curl_setopt($session, CURLOPT_RETURNTRANSFER, TRUE);
$result = curl_exec($session);
$error = curl_error($session);
curl_close($session);
if (!empty($error)) {
  print '<h1>Error</h1><pre>'.$error.'</pre>';
}
else {
  print '<h1>Success</h1><pre>'. $request_url .'</pre><textarea>'.$result.'</textarea>';

}