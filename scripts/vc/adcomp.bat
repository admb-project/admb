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
REM if %1==-s set g=-g& set opt=& shift
if %1==-s set g=-g& shift
goto STARTLOOP
:ENDLOOP

@echo on
cl -c /EHsc -DUSE_LAPLACE -DWIN32 %opt% /Ox -D__MSVC32__=8 -I. -I"%MSSDK%"\include -I"%ADMB_HOME%"\include %1.cpp
@echo off

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
