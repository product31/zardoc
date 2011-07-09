<div class="user-info clear-block">
  <div class="user-photo">
    <?php print theme('user_picture', $account, 'icon_huge', array('class' => 'reflected')); ?>
  </div>
  <div class="user-profile">
    <?php
      if ($account->profile_gender || $account->profile_marital_status) {
        print "<div>";
        print $account->profile_gender ? drupal_ucfirst(check_plain($account->profile_gender)) : "";
        print $account->profile_gender && $account->profile_marital_status ? ", " : "";
        print $account->profile_marital_status ? drupal_ucfirst(check_plain($account->profile_marital_status)) : "";
        print "</div>";
      }
      /*
      if ($account->age && !$account->hide_age) {
        print '<div>'. $account->age .' years old </div>';
      }
      */
    ?>

    <?php
      if ($account->profile_city || $account->profile_state) {
        print "<div>";
        // Drupal doesn't have a drupal_ucwords function, so need to split string into an array
        // of words and ucfirst each word.
        if ($account->profile_city) {
          $words = explode(' ', $account->profile_city);
          foreach ($words as $word) {
           print drupal_ucfirst(strtolower(check_plain($word))) .' ';
          }
        }
        print $account->profile_city && $account->profile_providence ? ", " : "";
        print $account->profile_providence ? drupal_strtoupper(check_plain($account->profile_providence)) : "";
        print "</div>";
      }
    ?>
    <?php print $account->profile_country ? "<div>" . check_plain($account->profile_country) . "</div>" : ""?>
    <?php print ($privatemsg) ? '<div>'. $privatemsg .'</div>' : ''; ?>
    <?php if (module_exists('friendlist_ui')): ?>
      <?php
        global $user;
        if ($user->uid != $account->uid):
      ?>
        <div>
        <?php
          if ($buddy_of_user) {
            print l(t('Remove me from friends'), 'friendlist/delete/' . $account->uid .'/'. variable_get('sonybmg_friendlist_buddy_rtid', 11),
              array('class' => 'add-friend', 'query' => drupal_get_destination()));
          }
          else {
            print l(t('Add me to friends'), 'friendlist/add/' . $account->uid .'/'. variable_get('sonybmg_friendlist_buddy_rtid', 11),
              array('class' => 'add-friend', 'query' => drupal_get_destination()));
          }
        ?>
        </div>
      <?php
        endif;
      ?>
      <div><?php print t('<strong>@buddy_of_others</strong> have added me to friends', array('@buddy_of_others' => $buddy_of_others)); ?></div>
    <?php endif; ?>
    <div><?php print t('REVIEWS WRITTEN: @reviews', array('@reviews' => ($reviews_written) ? $reviews_written : 0)); ?></div>
    <div><?php print t('COMMENTS MADE: @comments', array('@comments' => ($comments_made) ? $comments_made : 0)); ?></div>
    <div><?php print t('MEMBER SINCE: @date', array('@date' => format_date($account->created, 'custom', "F j, Y"))); ?></div>
  </div>
</div>
<?php
  global $user;
  if ($user->uid == $account->uid):
?>
  <div class = "profile-new-blog-post">
      <?php print l(t('WRITE A NEW BLOG POST'), 'node/add/blog') ?>
  </div>
<?php endif; ?>
<?php if ($user_activity): ?>
<div class="user-activity">
  <h2 class="title"><?php print t('My Reviews &amp; Blog') ?></h2>
  <?php print $user_activity; ?>
</div>
<?php endif; ?>
