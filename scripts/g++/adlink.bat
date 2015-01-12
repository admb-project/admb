@echo off
setlocal
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP
REM #######################################################################################################################
REM                                                                                                                       #
REM Script:   adlink [-d] [-g] [-r] [-s] model                                                                            #
REM                                                                                                                       #
REM Purpose:  Link ADMB object code to executable, using the MinGW GCC compiler                                           #
REM                                                                                                                       #
REM Args:     -d creates DLL                                                                                              #
REM           -g inserts debugging symbols                                                                                #
REM           -r creates ADMB-RE model                                                                                    #
REM           -s creates model that enforces safe array bounds during runtime                                             #
REM           model is the filename with or without extension, e.g. simple or simple.o                                    #
REM                                                                                                                       #
REM Requires: ADMB libraries, g++, dllwrap                                                                                #
REM                                                                                                                       #
REM Returns:  Creates executable or DLL with same prefix                                                                  #
REM                                                                                                                       #
REM History:  24 May 2009  Arni Magnusson created                                                                         #
REM            7 Jul 2009  Arni Magnusson added support for MinGW GCC 4.4.0                                               #
REM           27 Nov 2009  Arni Magnusson added support for filename extension, e.g. simple.o                             #
REM            8 Feb 2010  Johnoel Ancheta split the -s combo option into separate -g and -s options                      #
REM           22 Feb 2010  Arni Magnusson merged forked versions                                                          #
REM                                                                                                                       #
REM #######################################################################################################################

rem Pop args until model=%1
set adlib=-lado
set linker=g++
set re=0
set s=-s
set g=
:STARTLOOP
if [%2]==[] goto ENDLOOP
if %1==-d set linker=dllwrap& shift
if %1==-g set g=-g& set s=& shift
if %1==-r set re=1& shift
if %1==-s set adlib=-lads& shift
goto STARTLOOP
:ENDLOOP

set model=%~n1

set def=
set df1b2lib=-ldf1b2stub
if %linker%==g++ (set out=-o %model%) else (set def=-def %model%.def --driver-name g++& set out=--output-lib lib%model%.a -o %model%.dll)
if %adlib%==-lado set df1b2lib=-ldf1b2o
if %adlib%==-lads set df1b2lib=-ldf1b2s

echo on
%linker% %model%.obj -static %def% -L"%ADMB_HOME%"\lib  %df1b2lib% -ladmod -ladt %adlib% %df1b2lib% -ladmod -ladt %adlib% %out%
@echo off
goto EOF

:HELP
echo Usage: adlink [-d] [-g] [-r] [-s] model
echo.
echo Link AD Model Builder object code to executable, using the MinGW GCC compiler.
echo.
echo   -d     Create DLL
echo   -g     Insert debugging symbols
echo   -r     Create ADMB-RE
echo   -s     Enforce safe bounds
echo   model  Filename prefix, e.g. simple
echo.

:EOF
