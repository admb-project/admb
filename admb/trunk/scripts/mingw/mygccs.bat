rem # for compiling from tpl2rem
rem if [ ! -n "$ADMB_HOME" ]; then
rem     echo you must define the environment string ADMB_HOME
rem else

g++ -Wno-deprecated %1.cpp -I. -fpermissive -I%ADMB_HOME%/include -L%ADMB_HOME%/lib -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -O3 -ldf1b2s -ladmod -ladt -lads -ldf1b2s -ladmod -ladt -lads -o%1

rem fi
