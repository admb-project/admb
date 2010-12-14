gcc -g -Xlinker -L. -L"%ADMB_HOME%"/lib  $1.obj -o $1 -ladmod -ladt -lads -lado -lstdc++ -ldl -lm
