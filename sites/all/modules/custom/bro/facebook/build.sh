#!/bin/sh

FILES="
javascripts/jquery.countdown.min.js
javascripts/jquery.cookie.js
javascripts/analytics.js
javascripts/sony_bro.js
javascripts/main.js
"

OUTPUT="bro.min.js"

echo "" > $OUTPUT
for F in $FILES; do
  cat $F >> $OUTPUT
done
