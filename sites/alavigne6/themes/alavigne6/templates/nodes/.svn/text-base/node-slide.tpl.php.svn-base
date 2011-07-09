<?php //dsm($node);

$path = $node->field_slideimage[0]['filepath'];
$alt = $node->title;
$link = $node->field_slidelink[0]['value'];
$desc = $node->field_description[0]['value'];

if($path){
$output = theme('image', $path, $alt, $alt, NULL, FALSE);
$output = l($output, $link, array('html' => TRUE));
print $output;

} else {

print $desc;

}

?>
