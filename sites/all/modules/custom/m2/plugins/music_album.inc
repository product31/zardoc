<?php

function m2_music_album_info() {
  return array(
    'name' => 'Album',
    'namespace' => 'Music',
    'class' => 'Music::Album',
    'index' => array(
      'title' => t('Album title'),
      'year' => t('Year'),
      'tag' => t('Tag'),
    ),
    'fields' => array(
      'title' => 'string',
      'copyright' => 'string',
      'year' => 'string',
      'artist_text' => 'string',
      'advisory' => 'boolean',
      'keys' => 'hash',
    ),
  );
}