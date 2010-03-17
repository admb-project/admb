#!/bin/bash

function output {
  for FOLDER in $1/admb $1/admb-re ; do
    for FILE in `find $FOLDER | grep ".tpl$" | sort` ; do
      BASENAME=`basename $FILE .tpl`
      DIRNAME=`dirname $FILE`

      printf "#File(tpl) $FILE\n"
      if test -f $DIRNAME/$BASENAME.par ; then
        printf "#File(par)\n"
        cat $DIRNAME/$BASENAME.par
      fi
      ##printf "#File(cor)\n"
      ##cat $DIRNAME/$BASENAME.cor
      if test -f $DIRNAME/$BASENAME.std ; then
        printf "#File(std)\n"
        cat $DIRNAME/$BASENAME.std
      fi
    done
  done
}
readonly -f output

output $1
