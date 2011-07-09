<?php

function theme_m2_js_album_links($links, $text) {
  return theme('sonybmg_dropdown_links', $links, $text);
}

function theme_m2_js_album_link($m2id, $type, $add = NULL, $remove = NULL) {
  $types = array(
    'digital_album' => t('Digital Album'),
    'compact_disc' => t('CD'),
  );
  $m2id = (int) $m2id;
  $add = empty($add) ? t('Add album') : check_plain($add);
  $remove = empty($add) ? t('In cart') : check_plain($remove);
  return <<<HTML
<span class='m2-product-button-wrapper'>
  <span class='m2-type'>{$types[$type]}</span>
  <span class='m2-price-placeholder' product_id='$m2id'></span>
  <span class='m2-button-placeholder' product_id='$m2id' add_text='$add' remove_text='$remove'></span>
</span>
HTML;
}

function theme_m2_js_track_price($m2id) {
  $m2id = (int) $m2id;
  return "<span class='m2-price-placeholder' product_id='$m2id'></span>";
}

function theme_m2_js_track_button($m2id, $add = NULL, $remove = NULL) {
  $m2id = (int) $m2id;
  $add = empty($add) ? t('Add track') : check_plain($add);
  $remove = empty($remove) ? t('In cart') : check_plain($remove);
  return <<<HTML
<span class='m2-product-button-wrapper'>
  <span class='m2-button-placeholder' product_id='$m2id' add_text='$add' remove_text='$remove'></span>
</span>
HTML;
}