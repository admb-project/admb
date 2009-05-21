#!/bin/bash
INPUTDIR=$1
OUTPUTDIR=$1-rev
mkdir -p $OUTPUTDIR
for path in $INPUTDIR/*.cpp
do
# echo $path
# echo "Basename of $path = `basename $path`"
# echo "Dirname of $path = `dirname $path`"
  file=`basename $path`
  echo $file
  sed -f cleanup.sed  $path > $OUTPUTDIR/$file
# echo $path "->"$OUTPUTDIR/$file
done

