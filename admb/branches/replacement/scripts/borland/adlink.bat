@echo off
setlocal
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP
REM #######################################################################################################################
REM                                                                                                                       #
REM Script:   adlink [-d] [-g] [-r] [-s] model                                                                            #
REM                                                                                                                       #
REM Purpose:  Link ADMB object code to executable, using the Borland 5.5.1 compiler                                       #
REM                                                                                                                       #
REM Args:     -d creates DLL                                                                                              #
REM           -g inserts debugging symbols                                                                                #
REM           -r creates ADMB-RE model                                                                                    #
REM           -s creates model that enforces safe array bounds during runtime                                             #
REM           model is the filename with or without extension, e.g. simple or simple.o                                    #
REM                                                                                                                       #
REM Requires: ADMB libraries, bcc32                                                                                       #
REM                                                                                                                       #
REM Returns:  Creates executable or DLL with same prefix                                                                  #
REM                                                                                                                       #
REM History:  24 May 2009  Arni Magnusson created                                                                         #
REM           27 Nov 2009  Arni Magnusson added support for filename extension, e.g. simple.o                             #
REM           22 Feb 2010  Arni Magnusson merged forked versions and synchronized -g -s options with GCC scripts          #
REM                                                                                                                       #
REM #######################################################################################################################

rem Pop args until model=%1
set adlib=ado32.lib
set re=0
set v=
set wd=
:STARTLOOP
if [%2]==[] goto ENDLOOP
if %1==-d set wd=-WD& shift
if %1==-g set v=-v& shift
if %1==-r set re=1& shift
if %1==-s set adlib=ads32.lib& shift
goto STARTLOOP
:ENDLOOP

set model=%~n1

set df1b2lib=df1b2stub.lib
if %adlib%==ado32.lib set df1b2lib=df1b2o.lib
if %adlib%==ads32.lib set df1b2lib=df1b2s.lib

@echo on
bcc32 %v% %wd% -L%BCC55_HOME%\lib -L"%ADMB_HOME%"\lib %model%.obj admod32.lib adt32.lib %adlib% %df1b2lib%
@echo off
goto EOF

:HELP
echo Usage: adlink [-d] [-g] [-r] [-s] model
echo.
echo Link AD Model Builder object code to executable, using the Borland 5.5.1 compiler.
echo.
echo   -d     Create DLL
echo   -g     Insert debugging symbols
echo   -r     Create ADMB-RE
echo   -s     Enforce safe bounds
echo   model  Filename prefix, e.g. simple
echo.

:EOF
