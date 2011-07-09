<?php 

//dsm($row);

$song_title = $row->node_title;
$nid = $row->nid;
$url = $row->node_data_field_album_field_audio_file_url_value;
?>

<?php print $song_title; ?>


<?php
global $user;
if (in_array('administrator', array_values($user->roles))) {
      print l(t('edit'), 'node/' . $nid . '/edit');
    }
if (in_array('translator', array_values($user->roles))) {
      print l(t('translate'), 'node/' . $nid . '/translate');
    }
?>
