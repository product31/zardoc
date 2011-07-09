#!/bin/bash
#
# To use this script:
# cd sites/all/modules
# sh drubb/get_modules.sh
#
# WARNING
# This script will overwrite any existing module, so you may consider
# simply using what this script does as a guide.
#
# If for some reason you keep your modules somewhere not in sites/* then
# this script will not work.
##############################################################################

GET="curl -sO"
BASE=`pwd`

patch_module()
{
  echo # New line
  echo "Patching $1 with $2..."
  cd $BASE/module_downloads
  $GET http://drupal.org/files/issues/$2
  cd ../$1
  patch -p0 < ../module_downloads/$2
}

# prepare the module download directory.
rm -rf module_downloads
mkdir module_downloads

FILES="advanced_forum-6.x-2.x-dev.tar.gz\
  nodecomment-6.x-2.x-dev.tar.gz\
  bbcode-6.x-1.2.tar.gz\
  bueditor-6.x-1.3.tar.gz\
  install_profile_api-6.x-2.x-dev.tar.gz\
  privatemsg-6.x-1.x-dev.tar.gz\
  signature_forum-6.x-1.x-dev.tar.gz\
  smileys-6.x-1.x-dev.tar.gz\
  comment_notify-6.x-1.x-dev.tar.gz\
  views-6.x-2.x-dev.tar.gz\
  draft-6.x-1.6.tar.gz\
  quote-6.x-1.x-dev.tar.gz\
  vertical_tabs-6.x-1.x-dev.tar.gz\
  ctools-6.x-1.x-dev.tar.gz\
  author_pane-6.x-1.x-dev.tar.gz\
"
# get and unpack all the modules.
cd module_downloads
for FILE in $FILES
do
  MODULE=`echo $FILE | cut -f 1 -d "-"`
  rm -rf ../$MODULE
  echo "Retrieving $MODULE"
  $GET http://ftp.drupal.org/files/projects/$FILE
  echo "Extracting $MODULE"
  tar xzf $FILE -C ../
done

# get and apply patches we know we need.
patch_module install_profile_api install-filter-remove-472558-2.patch
patch_module quote javascript-and-nodecomment_1.patch
patch_module bueditor get-out-of-tab-order.patch

cd $BASE

# copy the profile into the right location.
mkdir -p ../../../profiles/drubb
cp drubb/drubb.profile ../../../profiles/drubb
