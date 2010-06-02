#!/bin/bash

function par2csv {
  cat $3 | awk '
  BEGIN {
    commentline=-1
  }

  NR == 1 {
    printf("\"%s\",\"%s\",\"ObjectiveFunctionValue\",%s\n", BuilderId, ModelId, $11)
    printf("\"%s\",\"%s\",\"MaximumFunctionComponent\",%s\n", BuilderId, ModelId, $16)
  }

  NR > 1 && /^#/ {
    if (commentline == 0) {
      printf("\n")
    }
    commentline=1
    printf("\"%s\",\"%s\",\"%s\"", BuilderId, ModelId, substr($NF, 1, length($NF) - 1))
  }

  /^[^#]/ {
    if (commentline == 1) {
      printf(",")
    }
    commentline=0
    for (i = 1; i < NF; i++) {
      printf("%s,", $i)
    }
    printf("%s", $NF)
  }

  END {
    printf("\n")
  }' BuilderId=$1 ModelId=$2
}
readonly -f par2csv

function std2csv {
  cat $3 | awk '
  BEGIN {
  }

  NR == 1 {
  }

  NR > 1 {
    printf("\"%s\",\"%s\",", BuilderId, ModelId)
    printf("%s,", $1)
    printf("\"%s\",", $2)
    printf("%s,", $3)
    printf("%s\n", $NF)
  }

  END {
  }' BuilderId=$1 ModelId=$2
}
readonly -f par2csv

function output {
  rm -f ../par.csv
  touch ../par.csv

  rm -f ../std.csv
  touch ../std.csv


  for FOLDER in $1/admb $1/admb-re ; do
    for FILE in `find $FOLDER | grep ".tpl$" | sort` ; do
      BASENAME=`basename $FILE .tpl`
      DIRNAME=`dirname $FILE`

      printf "#File(tpl) $FILE\n"
      if test -f $DIRNAME/$BASENAME.par ; then
        printf "#File(par)\n"
        cat $DIRNAME/$BASENAME.par
        par2csv builderid $BASENAME $DIRNAME/$BASENAME.par >> ../par.csv
      fi
      ##printf "#File(cor)\n"
      ##cat $DIRNAME/$BASENAME.cor
      if test -f $DIRNAME/$BASENAME.std ; then
        printf "#File(std)\n"
        cat $DIRNAME/$BASENAME.std
        std2csv builderid $BASENAME $DIRNAME/$BASENAME.std >> ../std.csv
      fi
    done
  done
}
readonly -f output


output $1
