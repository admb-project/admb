@echo off
setlocal
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP
REM #######################################################################################################################
REM                                                                                                                       #
REM Script:   admb [-d] [-r] [-s] model                                                                                   #
REM                                                                                                                       #
REM Purpose:  Build ADMB executable from TPL, using tpl2cpp/tpl2rem, adcomp, and adlink                                   #
REM                                                                                                                       #
REM Args:     -d creates DLL                                                                                              #
REM           -r creates ADMB-RE                                                                                          #
REM           -s uses safe bounds and debugging symbols                                                                   #
REM           model is the filename prefix, e.g. simple                                                                   #
REM                                                                                                                       #
REM Requires: ADMB header files and libraries, tpl2cpp, tpl2rem, adcomp, adlink                                           #
REM                                                                                                                       #
REM Returns:  Creates executable or DLL with same prefix                                                                  #
REM                                                                                                                       #
REM History:  24 May 2009  Arni Magnusson created                                                                         #
REM                                                                                                                       #
REM #######################################################################################################################

rem Pop args until model=%1
set d=
set r=
set s=
set tpl2cpp=tpl2cpp
set bounds=
set dll=
:STARTLOOP
if [%2]==[] goto ENDLOOP
if %1==-d set d=-d& set dll=-dll& shift
if %1==-r set r=-r& set tpl2cpp=tpl2rem& shift
if %1==-s set s=-s& set bounds=-bounds& shift
goto STARTLOOP
:ENDLOOP

echo.& echo *** %tpl2cpp% %bounds% %dll% %1
                %tpl2cpp% %bounds% %dll% %1
echo.& echo *** adcomp %d% %r% %s% %1
           call adcomp %d% %r% %s% %1
echo.& echo *** adlink %d% %r% %s% %1
           call adlink %d% %r% %s% %1
goto EOF

:HELP
echo Usage: admb [-d] [-r] [-s] model
echo.
echo Build AD Model Builder executable from TPL.
echo.
echo   -d     Create DLL
echo   -r     Create ADMB-RE
echo   -s     Use safe bounds and debugging symbols
echo   model  Filename prefix, e.g. simple
echo.

:EOF
