<div id="bro-main">
  <div class="bro-exposed">
    <div class="bro-artist-logo">
      <?php print $artist_logo; ?>
    </div>

    <!--<div class="bro-countdown">
      <?php print $countdown; ?>
    </div>-->

    <!--div class="bro-online-users">
      <?php print $online_users; ?>
    </div-->

    <div class="bro-sponsor-1">
      <?php print $sponsor_1; ?>
    </div>

    <div class="bro-toggle">
      <a href="#" class="bro-toggle-link"></a>
    </div>
  </div>

  <div class="bro-content">
    <div class="bro-left">
      <div class="bro-media">
        <!-- Start of Brightcove Player -->
        <div style="display:none">
        </div>

        <script language="JavaScript" type="text/javascript" src="http://admin.brightcove.com/js/BrightcoveExperiences_all.js"></script>

        <object id="myExperience275273534001" class="BrightcoveExperience">
          <param name="bgcolor" value="#FFFFFF" />
          <param name="width" value="640" />
          <param name="height" value="360" />
          <param name="playerID" value="275273534001" />
          <param name="publisherID" value="59121"/>
          <param name="isVid" value="true" />
          <param name="isUI" value="true" />
          <param name="dynamicStreaming" value="true" />
        </object>

        <script type="text/javascript">
          brightcove.createExperiences();

          function onTemplateLoaded(experienceId) {
            if (experienceId =='myExperience275273534001') {
              var player = brightcove.getExperience(experienceId);
              // I can't figure out how to use BrightCove's load event so we'll
              // just work around it.
              $('#bro-main').takersBro('onVideoLoad');
              var video = player.getModule(APIModules.VIDEO_PLAYER);
//              video.addEventListener(BCContentEvent.CHANGE, function() {
//                console.log('asdf'); $('#bro-main').takersBro('onVideoLoad');
//              });
              video.addEventListener(BCMediaEvent.PLAY, function() {
                $('#bro-main').takersBro('onVideoStart');
              });
            }
          }

          $(function() {
            if (window.SME$Analytics$Loaded) {
              reportBroEventToGA(BRO_ID, GA_EVENT_BRO_IMPRESSION, aUtil ? aUtil.getConfig("site") : document.location.hostname);
            }
          });
        </script>
        <!-- End of Brightcove Player -->
      </div>
      <div class="bro-sponsor-4">
       <?php print $sponsor_4; ?>
     </div>
    </div>

    <div class="bro-right">
      <div class="bro-sponsor-2">
       <?php print $sponsor_2; ?>
     </div>
      <div class="bro-sponsor-3">
       <?php print $sponsor_3; ?>
     </div>
      <div class="bro-share">
        <?php print $share; ?>
      </div>
    </div>
<a href="http://clk.atdmt.com/ULA/go/249659186/direct/01/"><img src="http://view.atdmt.com/ULA/view/249659186/direct/01/" /></a>
  </div>

</div>
