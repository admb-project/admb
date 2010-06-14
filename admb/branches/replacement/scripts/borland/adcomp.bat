@echo off
setlocal
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP
REM #######################################################################################################################
REM                                                                                                                       #
REM Script:   adcomp [-d] [-g] [-r] [-s] model                                                                            #
REM                                                                                                                       #
REM Purpose:  Compile ADMB C++ to object code, using the Borland 5.5.1 compiler                                           #
REM                                                                                                                       #
REM Args:     -d creates object file for DLL                                                                              #
REM           -g inserts debugging symbols                                                                                #
REM           -r creates object file for ADMB-RE                                                                          #
REM           -s creates object file that enforces safe array bounds during runtime                                       #
REM           model is the filename with or without extension, e.g. simple or simple.cpp                                  #
REM                                                                                                                       #
REM Requires: ADMB header files, bcc32                                                                                    #
REM                                                                                                                       #
REM Returns:  Creates object file with same prefix                                                                        #
REM                                                                                                                       #
REM History:  24 May 2009  Arni Magnusson created                                                                         #
REM            6 Nov 2009  Johnoel Ancheta removed -Vd flag                                                               #
REM           27 Nov 2009  Arni Magnusson added support for filename extension, e.g. simple.cpp                           #
REM           22 Feb 2010  Arni Magnusson merged forked versions and synchronized -g -s options with GCC scripts          #
REM                                                                                                                       #
REM #######################################################################################################################

rem Pop args until model=%1
set dll=
set opt=;OPT_LIB
set v=
:STARTLOOP
if [%2]==[] goto ENDLOOP
if %1==-d set dll=;__SPDLL& shift
if %1==-g set v=-v& shift
if %1==-r shift
if %1==-s set opt=& shift
goto STARTLOOP
:ENDLOOP

set model=%~n1

@echo on
bcc32 -c -O2 %v% -DDOS386;USE_LAPLACE%opt%%dll% -I. -I%BCC55_HOME%\include -I"%ADMB_HOME%"\include %model%.cpp
@echo off
goto EOF

:HELP
echo Usage: adcomp [-d] [-g] [-r] [-s] model
echo.
echo Compile AD Model Builder C++ to object code, using the Borland 5.5.1 compiler.
echo.
echo   -d     Create DLL
echo   -g     Insert debugging symbols
echo   -r     Create ADMB-RE
echo   -s     Enforce safe bounds
echo   model  Filename prefix, e.g. simple
echo.

:EOF
