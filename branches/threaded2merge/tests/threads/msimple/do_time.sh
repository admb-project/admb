#!/bin/bash
# collects run time for msimple with different numbers of threads
cp -v msimple.dat msimple.dat.save
rm -vf time.out
for T in 1 2 3  4 5 6 7 8 9 10 11 12 50
do
  echo 1000003 $T  > msimple.dat
  echo $T >> time.out
  /usr/bin/X11/time -ao time.out -f "%E " msimple -nohess
done
cp -v msimple.dat.save msimple.dat

