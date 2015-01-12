g++ -w -o%1 -g %1.cpp -I. -fpermissive -I"%ADMB_HOME%\include" -L"%ADMB_HOME%\lib" -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2stub -ladmod -ladt -lado -ldf1b2stub -ladmod -ladt -lado
