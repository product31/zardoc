<?php

function m2_music_lyrics_info() {
  return array(
    'name' => 'Gracenote Lyrics',
    'namespace' => 'Music',
    'class' => 'Music::Lyrics',
    'index' => array(
      'artist_text' => t('Artist name'),
      'title' => t('Track title'),
      'content' => t('Lyric content'),
      'artist_title' => t('Artist name and Track title'),
    ),
    'fields' => array(
      'title' => 'string',
      'revision' => 'string',
      'artist_text' => 'string',
      'explicit' => 'boolean',
      'credit' => 'string',
      'keys' => 'hash',
      'content' => 'xml',
    ),
    'cck' => array(
      'label' => t('M2 Lyrics'),
      'description' => t('Store a reference to an M2/Gracenote lyrics document in the database.')
    ),
    'autocomplete_render' => 'm2_music_lyrics_autocomplete_render',
  );
}

function m2_music_lyrics_autocomplete_render($doc) {
  $output = "<strong>{$doc->title}</strong> by {$doc->artist_text}<br/>";
  $output .= "<div style=\"padding-left: 20px;\">";
  for ($i = 0; $i < count($doc->content[0]), $i < 2; $i++) {
    $output .= $doc->content[0][$i] .'<br/>';
  }
  $output .= "</p>";
  return $output;
}