@echo off
setlocal
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP
REM #######################################################################################################################
REM                                                                                                                       #
REM Script:   adcomp [-d] [-g] [-r] [-s] model                                                                            #
REM                                                                                                                       #
REM Purpose:  Compile ADMB C++ to object code, using the MinGW GCC compiler                                               #
REM                                                                                                                       #
REM Args:     -d creates object file for DLL                                                                              #
REM           -g inserts debugging symbols                                                                                #
REM           -r creates object file for ADMB-RE                                                                          #
REM           -s creates object file that enforces safe array bounds during runtime                                       #
REM           model is the filename with or without extension, e.g. simple or simple.cpp                                  #
REM                                                                                                                       #
REM Requires: ADMB header files, g++                                                                                      #
REM                                                                                                                       #
REM Returns:  Creates object file with same prefix                                                                        #
REM                                                                                                                       #
REM History:  24 May 2009  Arni Magnusson created                                                                         #
REM            7 Jul 2009  Arni Magnusson added support for MinGW GCC 4.4.0                                               #
REM           27 Nov 2009  Arni Magnusson added support for filename extension, e.g. simple.cpp                           #
REM            8 Feb 2010  Johnoel Ancheta split the -s combo option into separate -g and -s options                      #
REM           22 Feb 2010  Arni Magnusson merged forked versions                                                          #
REM                                                                                                                       #
REM #######################################################################################################################

rem Pop args until model=%1
set g=-O3
set dll=
set opt=-DOPT_LIB
:STARTLOOP
if [%2]==[] goto ENDLOOP
if %1==-d set dll=-DBUILDING_DLL& shift
if %1==-g set g=-g& shift
if %1==-r shift
if %1==-s set opt=-DSAFE_ALL& shift
goto STARTLOOP
:ENDLOOP

set model=%~n1

echo on
g++ -c %g% -Wno-deprecated -D__GNUDOS__ %dll% -Dlinux %opt% -DUSE_LAPLACE -fpermissive -I. -I"%ADMB_HOME%"\include -o %model%.obj %model%.cpp
@echo off

goto EOF

:HELP
echo Usage: adcomp [-d] [-g] [-r] [-s] model
echo.
echo Compile AD Model Builder C++ to object code, using the MinGW GCC compiler.
echo.
echo   -d     Create DLL
echo   -g     Insert debugging symbols
echo   -r     Create ADMB-RE
echo   -s     Enforce safe bounds
echo   model  Filename prefix, e.g. simple
echo.

:EOF
