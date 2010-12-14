@echo off
setlocal
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP
REM #######################################################################################################################
REM                                                                                                                       #
REM Script:   adcomp [-d] [-r] [-s] model                                                                                 #
REM                                                                                                                       #
REM Purpose:  Compile ADMB C++ to object code, using the MinGW GCC 3.4.5 compiler                                         #
REM                                                                                                                       #
REM Args:     -d creates object file for DLL                                                                              #
REM           -r creates object file for ADMB-RE                                                                          #
REM           -s creates object file with safe bounds and debugging symbols                                               #
REM           model is the filename prefix, e.g. simple                                                                   #
REM                                                                                                                       #
REM Requires: ADMB header files, g++                                                                                      #
REM                                                                                                                       #
REM Returns:  Creates object file with same prefix                                                                        #
REM                                                                                                                       #
REM History:  24 May 2009  Arni Magnusson created                                                                         #
REM                                                                                                                       #
REM #######################################################################################################################

rem Pop args until model=%1
set g=
set dll=
set opt=-DOPT_LIB 
:STARTLOOP
if [%2]==[] goto ENDLOOP
if %1==-d set dll=-DBUILDING_DLL& shift
if %1==-r shift
if %1==-s set g=-g& set opt=& shift
goto STARTLOOP
:ENDLOOP

echo g++ -c %g% -O3 -Wno-deprecated -D__GNUDOS__ %dll% -Dlinux %opt% -DUSE_LAPLACE -fpermissive -I. -I%ADMB_HOME%/include %1.cpp
g++ -c -w %g% -O3 -Wno-deprecated -D__GNUDOS__ %dll% -Dlinux %opt% -DUSE_LAPLACE -Dlinux -fpermissive -I. -I"%ADMB_HOME%\include" %1.cpp

REM g++ -c -w -o%1 %g% -O3 -Wno-deprecated %1.cpp -I. -fpermissive -I"%ADMB_HOME%\include" -L"%ADMB_HOME%\lib" -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2stub -ladmod -ladt -lado -ldf1b2stub -ladmod -ladt -lado


goto EOF

:HELP
echo Usage: adcomp [-d] [-r] [-s] model
echo.
echo Compile AD Model Builder C++ to object code, using the MinGW GCC 3.4.5 compiler.
echo.
echo   -d     Create object file for DLL
echo   -r     Create object file for ADMB-RE
echo   -s     Create object file with safe bounds and debugging symbols
echo   model  Filename prefix, e.g. simple
echo.

:EOF
