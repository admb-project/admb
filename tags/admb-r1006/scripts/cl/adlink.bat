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
set s=
set df1b2lib=df1b2stubo.lib
set adlib=ado32.lib
:STARTLOOP
if [%2]==[] goto ENDLOOP
if %1==-r set re=1& shift
if %1==-s set adlib=ads32.lib& set s=s& shift
goto STARTLOOP
:ENDLOOP

if %adlib%==ado32.lib set df1b2lib=df1b2o.lib
if %adlib%==ads32.lib set df1b2lib=df1b2s.lib
set LIBPATH_MSSDK=/libpath:"%MSSDK%"\lib

@echo on
cl  %1.obj %df1b2lib% admod32%s%.lib %adlib% adt32%s%.lib /link /libpath:"%ADMB_HOME%"\lib /libpath:"%MSSDK%"\lib
@echo off

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
