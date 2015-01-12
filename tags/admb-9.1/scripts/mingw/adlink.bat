@echo off
setlocal
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP
REM #######################################################################################################################
REM                                                                                                                       #
REM Script:   adlink [-d] [-r] [-s] model                                                                                 #
REM                                                                                                                       #
REM Purpose:  Link ADMB object code to executable, using the MinGW GCC 3.4.5 compiler                                     #
REM                                                                                                                       #
REM Args:     -d creates DLL                                                                                              #
REM           -r creates ADMB-RE                                                                                          #
REM           -s uses safe bounds and debugging symbols                                                                   #
REM           model is the filename prefix, e.g. simple                                                                   #
REM                                                                                                                       #
REM Requires: ADMB libraries, g++, dllwrap                                                                                #
REM                                                                                                                       #
REM Returns:  Creates executable or DLL with same prefix                                                                  #
REM                                                                                                                       #
REM History:  24 May 2009  Arni Magnusson created                                                                         #
REM                                                                                                                       #
REM #######################################################################################################################

rem Pop args until model=%1
set re=0
set linker=g++
set s=-s
set def=
set df1b2lib=-ldf1b2stub
set adlib=-lado
:STARTLOOP
if [%2]==[] goto ENDLOOP
if %1==-d set linker=dllwrap& shift
if %1==-r set re=1& shift
if %1==-s set s=& set adlib=-lads& shift
goto STARTLOOP
:ENDLOOP
if %linker%==g++ (set out=-o %1) else (set def=-def %1.def --driver-name g++& set out=--output-lib lib%1.a -o %1.dll)
if %re%==1 if %adlib%==-lado set df1b2lib=-ldf1b2o
if %re%==1 if %adlib%==-lads set df1b2lib=-ldf1b2s

echo %linker% %s% %def% -L%ADMB_HOME%/lib %1.o %df1b2lib% -ladmod -ladt %adlib% %df1b2lib% -ladmod -ladt %adlib% %out%
     %linker% %s% %def% -L"%ADMB_HOME%\lib" %1.o %df1b2lib% -ladmod -ladt %adlib% %df1b2lib% -ladmod -ladt %adlib% %out%

REM g++ -w -o%1 -g %1.cpp -I. -fpermissive -I"%ADMB_HOME%\include" -L"%ADMB_HOME%\lib" -DUSE_LAPLACE -D__GNUDOS__ -Dlinux -DOPT_LIB -O3 -ldf1b2stub -ladmod -ladt -lado -ldf1b2stub -ladmod -ladt -lado

goto EOF

:HELP
echo Usage: adlink [-d] [-r] [-s] model
echo.
echo Link AD Model Builder object code to executable, using the MinGW GCC 3.4.5 compiler.
echo.
echo   -d     Create DLL
echo   -r     Create ADMB-RE
echo   -s     Use safe bounds and debugging symbols
echo   model  Filename prefix, e.g. simple
echo.

:EOF
