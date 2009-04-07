rem # linking in libpthread first because of multithreading problems
rem # you may not want this

gcc  -Xlinker -s -Xlinker -L /admodel/lib  $1.obj -o $1  -ladmod -ladt -lado -lado -lpthread -lstdc++ -ldl -lm

rem # if not try removing the -lpthread as in
rem # gcc -O3 -Xlinker -s -Xlinker -L /admodel/lib  $1.obj -o $1 -ladmod -ladt -lado -lstdc++ -ldl -lm
rem # use this instead for debugging 
rem #gcc -g -Xlinker -L /admodel/lib  $1.obj -o $1 -ladmod -ladt -lado -lpthread -lstdc++ -ldl -lm
