<div class="<?php print $node_classes ?>" id="node-<?php print $node->nid; ?>">
  <?php if ($page == 0): ?>
    <div class="clear-block">
      <?php if ($cover_art): ?>
      <div class="album-teaser-cover"><?php print $cover_art ?></div>
      <?php endif; ?>
      <h2 class="node-title title">
        <a href="<?php print $node_url ?>"><?php print $title ?></a>
      </h2>
    </div>
  <?php else: ?>


    <div class="album-information clear-block">
      <?php if ($cover_art_big): ?>
      <div class="album-node-cover"><?php print $cover_art_big; ?></div>
      <?php endif; ?>

      <?php if ($release_date): ?>
        <div class="release-date row"><?php print $title ?> <?php print t('release date') . ': ' . $release_date; ?></div>
      <?php endif; ?>

      <?php if ($download_links): ?>
        <div class="download-links row"><?php print t('Buy it') . ': ' .  join(' | ', $download_links); ?></div>
      <?php endif; ?>
      
      <?php if ($musicians): ?>
      <div class="musicians row"><?php print format_plural(count($musicians), 'Musician', 'Musicians'); ?>: <?php print implode(', ',$musicians); ?></div>
      <?php endif; ?>

      <?php if ($producers): ?>
      <div class="producers row"><?php print format_plural(count($producers), 'Producer', 'Producers'); ?>: <?php print implode(', ',$producers); ?></div>
      <?php endif; ?>

      <div class="row clear-block">
        <?php if (isset($review_count)): ?>
        <div class="review-count"><?php print t('Comments') . ': ' . $review_count; ?></div>
        <div class="rate-review"><a href="<?php print url('node/add/review/' . $node->nid) ?>" class="rate-review"><?php print t('Comments'); ?></a></div>
        <?php endif; ?>
      </div>

      <?php if ($vote_display): ?>
      <div class="row clear-block">
        <div class="rating"><?php print t('Average rating') ?>: </div><?php print $vote_display; ?>
      </div>
      <?php endif; ?>

    </div>

    <?php if ($tracks): ?>
    <h2 class="title"><?php print $title ?>: <?php print t('Tracks') ?></h2>
    <div class="tracks">
      <div class="track-summary header clear-block">
        <div class="track-number">#</div>
        <div class="track-title"><?php print t('Title') ?></div>
        <div class="track-rating"><?php print t('My rating') ?></div>
        <div class="track-average"><?php print t('Average') ?></div>
      </div>
      <?php print $tracks; ?>
    </div>
    <?php endif; ?>
    <?php print $links; ?>
  <?php endif; ?>
</div>
