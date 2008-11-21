#!/bin/bash

VERSION=mytest

#rm -rvf *.zip

cp -vf scripts/bash/mygcc* $DISK/bin 
cp -vf docs/manuals/autodif.pdf $DIRECTORY/docs/manuals
cp -vf docs/manuals/admb.pdf $DIRECTORY/docs/manuals
cp -vf docs/manuals/admb-re.pdf $DIRECTORY/docs/manuals
#zip -r $DIRECTORY.zip $DIRECTORY/
#cp -vf scripts/bash/mygcc* admb-$VERSION-linux64-gcc3.4/bin 
#cp -vf scripts/bash/mygcc* admb-$VERSION-win32-mingw-gcc3.4/bin
#cp -vf scripts/vc/*.bat admb-$VERSION-win32-vc8/bin
#cp -vf scripts/borland/*.bat admb-$VERSION-win32-bcc5.5/bin

#for DIRECTORY in admb* ; do
#  printf "%s\n" $DIRECTORY
#  cp -vf README $DIRECTORY
#  cp -vf LICENSE $DIRECTORY
#  cp -vf docs/manuals/autodif.pdf $DIRECTORY/docs/manuals
#  cp -vf docs/manuals/admb.pdf $DIRECTORY/docs/manuals
#  cp -vf docs/manuals/admb-re.pdf $DIRECTORY/docs/manuals
#done
#
#find admb-$VERSION-* -exec touch {} . \;
#
#
#for DIRECTORY in admb* ; do
#  printf "%s\n" $DIRECTORY
#  zip -r $DIRECTORY.zip $DIRECTORY/
#done
