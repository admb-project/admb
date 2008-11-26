#!/bin/bash

VERSION=9.0.xrc3

rm -vf *.zip

if [ -e admb_gcc411_fedora8 ] ; then
  mv admb_gcc411_fedora8 admb-$VERSION-linux64-gcc3.4
  cp -vf ../../scripts/bash/mygcc* admb-$VERSION-linux64-gcc3.4/bin 
fi
if [ -e admb_vc8_win32 ] ; then
  mv admb_vc8_win32 admb-$VERSION-win32-vc8
  cp -vf ../../scripts/vc/*.bat admb-$VERSION-win32-vc8/bin
fi
if [ -e admb_gcc345_mingw32 ] ; then
  mv admb_gcc345_mingw32  admb-$VERSION-win32-mingw-gcc3.4
  cp -vf ../../scripts/vc/*.bat admb-$VERSION-win32-mingw-gcc3.4/bin
fi
if [ -e admb_b502_win32 ] ; then
  mv admb_b502_win32 admb-$VERSION-win32-bcc5.5
  cp -vf ../../scripts/borland/*.bat admb-$VERSION-win32-bcc5.5/bin
fi


for DIRECTORY in admb* ; do
  printf "%s\n" $DIRECTORY
  cp -vf ../../README $DIRECTORY
  cp -vf ../../LICENSE $DIRECTORY
  mkdir -p $DIRECTORY/docs/manuals
  cp -vf ../../docs/manuals/autodif/autodif.pdf $DIRECTORY/docs/manuals
  cp -vf ../../docs/manuals/admb/admb.pdf $DIRECTORY/docs/manuals
  cp -vf ../../docs/manuals/admb-re/admb-re.pdf $DIRECTORY/docs/manuals
done

find admb-$VERSION-* -exec touch {} . \;

for DIRECTORY in admb* ; do
  printf "%s\n" $DIRECTORY
  zip -r $DIRECTORY.zip $DIRECTORY/
done
