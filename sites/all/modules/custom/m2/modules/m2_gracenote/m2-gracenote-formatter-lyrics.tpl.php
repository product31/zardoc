<div class="gracenote-lyrics">

<?php //print t('Title:') ?>
<?php //print $title ?>

<?php //print t('Performed by:') ?>
<?php //print $performer ?>

  <div class="gracenote-lyrics-content">
    <?php print $lyrics ?>
  </div>

  <?php if ($writer): ?>
  <div class="gracenote-lyrics-writer">
    <?php print t('Songwriter(s)') ?>: <?php print $writer ?>
  </div>
  <?php endif; ?>

  <?php if ($copyright): ?>
  <div class="gracenote-lyrics-copyright">
    <?php print t('Copyright') ?>: <?php print $copyright ?>
  </div>
  <?php endif; ?>

  <div class="gracenote-lyrics-branding">
    <?php print $branding ?>
  </div>
</div>

<noscript>
  <?php print t('Javascript support is required to display lyrics.'); ?>
</noscript>

<div class="gracenote-lyrics-print">
  <?php print $print_message ?>
</div>

