g++ -w %1.cpp -I. -fpermissive -I"%ADMB_HOME%\include" -L"%ADMB_HOME%\lib" -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -O3 -ldf1b2s -ladmod -ladt -lads -ldf1b2s -ladmod -ladt -lads -o%1
