#!/bin/bash
INPUTDIR=$1
OUTPUTDIR=$2
echo "Copying TeX files from $INPUTDIR to $OUTPUTDIR"
mkdir -v -p $OUTPUTDIR
for path in $INPUTDIR/*.tex
do
  file=`basename $path`
  echo $file
  cat svn-insert.tex > $OUTPUTDIR/$file
  cat $path >> $OUTPUTDIR/$file
done

