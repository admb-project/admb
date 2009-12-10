#!/bin/bash
#
# reformats source code to ADMB style using indent
# see http://www.gnu.org/software/indent/
#
# Author: John Sibert
#
cp -v $1 $1.bak
indent -nbad -bap -bbo -nbc -bl -blf -bli0 -bls -c33 -cd33 -ncdb -ce -ci3 -cli0 -cp33 -cs -d0 -di1 -nfc1 -nfca -hnl -i3 -ip0 -l75 -lp -npcs -nprs -npsl -saf -sai -saw -nsc -nsob -nss $1 -o indent.out
cp -v indent.out $1
