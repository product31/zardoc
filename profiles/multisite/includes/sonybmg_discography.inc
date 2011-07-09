<?php
/**
 * Default labeling and weight for this profile include.
 **/
function sonybmg_discography_info() {
  return array(
    'name' => st('Discography'),
    'default_value' => TRUE,
    'disabled' => FALSE,
    'weight' => 10,
  );
}

/**
 * Required modules in order for these options to be created successfully
 **/
function sonybmg_discography_modules() {
  return array('php', 'views', 'content', 'content_copy', 'nodecomment', 'sonybmg',
               'text', 'number', 'optionwidgets', 'nodereference', 'userreference', 'date_api' , 'date', 'date_timezone',
               'votingapi', 'fivestar', 'filefield', 'imagefield', 'path', 'token', 'pathauto', 'menu',
               'imagecache', 'imageapi', 'imageapi_gd', 'link', 'sonybmg_discography');
}


/**
 * Task to complete in order to activate this segment of code
 */
function sonybmg_discography_task_list() {
  return array(
    'sonybmg_discography_dummy_content' => array(
      'message' => st('Created dummy content.'),
      'weight' => 52,
    ),
  );
}

/**
 * Sample data import
 */
function sonybmg_discography_dummy_content() {
  module_load_include('inc', 'node', 'node.pages');
  module_load_include('inc', 'devel', 'devel_generate');

  //
  // Sample Albums (we need two for the discography block to appear)
  //
  for($i = 0; $i < 2; $i++) {
    $node = new stdClass();
    $node->type = 'album';
    node_object_prepare($node);
    $node->uid = 1;

    $node->title = devel_create_greeking(rand(1, 10), TRUE);
    $node->body = devel_create_content();
    $node->teaser = node_teaser($node->body);
    $node->filter = variable_get('filter_default_format', 1);
    $node->format = FILTER_FORMAT_DEFAULT;
    $node->language = '';
    $node->promote = 1;
    $node->created = time();

    $node->field_artist = array(0 => array('value' => variable_get('artist_name', 'Artist Name')));
    $node->field_album_site_url = array(0 => array('value' => 'http://www.example.com/artist'));
    $node->field_album_video_url = array(0 => array('value' => 'http://www.example.com/artist/video'));
    $node->field_release_date = array(0 => array('value' => '2008-09-23T00:00:00', 'value2' => '2008-09-23T00:00:00'));
    $node->field_label = array(0 => array('value' => 'Columbia'));
    $node->field_liner_notes = array(0 => array('value' => devel_create_greeking(10, TRUE)));
    $node->field_band_member = array(0 => array('value' => devel_create_greeking(2, TRUE)));
    $node->field_producer = array(0 => array('value' => devel_create_greeking(2, TRUE)));
    $node->field_album_download_links = array(0 => array('url' => 'http://www.amazon.com/', 'title' => 'Amazon'));

    $source = './profiles/multisite/files/album.jpg';
    $dest = file_directory_path() .'/albums/';
    $file = install_upload_file($source, array(), $dest, FILE_EXISTS_RENAME, 'image/jpeg' );

    $node->field_album_cover = array(0 => array('fid' => $file->fid));


    node_save($node);
    $album_nid = $node->nid;

    //
    // Sample Tracks
    //
    for($j = 1; $j <= 2; $j++) {
      $node = new stdClass();
      $node->type = 'track';
      node_object_prepare($node);
      $node->uid = 1;

      $node->title = devel_create_greeking(rand(1, 10), TRUE);
      $node->body = devel_create_content();
      $node->teaser = node_teaser($node->body);
      $node->filter = variable_get('filter_default_format', 1);
      $node->format = FILTER_FORMAT_DEFAULT;
      $node->language = '';
      $node->promote = 1;
      $node->created = time();

      $node->field_album = array(0 => array('nid' => $album_nid));
      $node->field_disc_number = array(0 => array('value' => '1'));
      $node->field_track_number = array(0 => array('value' => $j));
      $node->field_audio_file_url = array(0 => array('value' => 'http://www.sonybmg.com/sample/audio_file/1'));
      $node->field_lyrics = array(0 => array('value' => devel_create_greeking(rand(10, 100), TRUE)));
      $node->field_song_download_links = array(0 => array('url' => 'http://www.amazon.com/', 'title' => 'Amazon'));

      node_save($node);
    }

    //
    // Review Content
    //
    for($k = 0; $k < 2; $k++) {
      $node = new stdClass();
      $node->type = 'review';
      node_object_prepare($node);
      $node->uid = 1;

      $node->title = devel_create_greeking(rand(1, 10), TRUE);
      $node->body = devel_create_content();
      $node->teaser = node_teaser($node->body);
      $node->filter = variable_get('filter_default_format', 1);
      $node->format = FILTER_FORMAT_DEFAULT;
      $node->language = '';
      $node->promote = 1;
      $node->created = time();

      $node->field_rating = array(0 => array('rating' => (rand(0, 5) * 20)));

      $node->comment_target_nid = $album_nid;
      $node->comment_target_cid = 0;

      node_save($node);
    }

  }

}