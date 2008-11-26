#!/bin/bash

VERSION=mytest

rm -vf *.zip

if [ -e admb_gcc411_fedora8 ] ; then
  mv admb_gcc411_fedora8 admb-$VERSION-linux64-gcc3.4
  cp -vf ../scripts/bash/mygcc* admb-$VERSION-linux64-gcc3.4/bin 
fi
if [ -e admb_vc8_win32 ] ; then
  mv admb_vc8_win32 admb-$VERSION-win32-vc8
  cp -vf ../scripts/vc/*.bat admb-$VERSION-win32-vc8/bin
fi

#cp -vf scripts/bash/mygcc* admb-$VERSION-win32-mingw-gcc3.4/bin
#cp -vf scripts/bash/mygcc* $DISK/bin 
#if [ -e -d ] ; then
#cp -vf scripts/borland/*.bat admb-$VERSION-win32-bcc5.5/bin
#fi


for DIRECTORY in admb* ; do
  printf "%s\n" $DIRECTORY
  cp -vf ../README $DIRECTORY
  cp -vf ../LICENSE $DIRECTORY
  mkdir -p $DIRECTORY/docs/manuals
  #cp -vf ../docs/manuals/autodif.pdf $DIRECTORY/docs/manuals
  #cp -vf ../docs/manuals/admb.pdf $DIRECTORY/docs/manuals
  #cp -vf ../docs/manuals/admb-re.pdf $DIRECTORY/docs/manuals
done

find admb-$VERSION-* -exec touch {} . \;

for DIRECTORY in admb* ; do
  printf "%s\n" $DIRECTORY
  zip -r $DIRECTORY.zip $DIRECTORY/
done
