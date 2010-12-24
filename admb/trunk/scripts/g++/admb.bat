@echo off
setlocal
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP
REM #######################################################################################################################
REM                                                                                                                       #
REM Script:   admb [-d] [-g] [-r] [-s] model                                                                              #
REM                                                                                                                       #
REM Purpose:  Build ADMB executable from TPL, using tpl2cpp/tpl2rem, adcomp, and adlink                                   #
REM                                                                                                                       #
REM Args:     -d creates DLL                                                                                              #
REM           -g inserts debugging symbols                                                                                #
REM           -r creates ADMB-RE model                                                                                    #
REM           -s creates model that enforces safe array bounds during runtime                                             #
REM           model is the filename with or without extension, e.g. simple or simple.tpl                                  #
REM                                                                                                                       #
REM Notes:    The same admb.bat script is used for all Windows compilers: Borland, GCC, and Microsoft Visual C++          #
REM                                                                                                                       #
REM Requires: tpl2cpp, tpl2rem, adcomp, adlink                                                                            #
REM                                                                                                                       #
REM Returns:  Creates executable or DLL with same prefix                                                                  #
REM                                                                                                                       #
REM History:  24 May 2009  Arni Magnusson created                                                                         #
REM           27 Nov 2009  Arni Magnusson added support for filename extension, e.g. simple.tpl                           #
REM            8 Feb 2010  Johnoel Ancheta split the -s combo option into separate -g and -s options                      #
REM           22 Feb 2010  Arni Magnusson merged forked versions                                                          #
REM                                                                                                                       #
REM #######################################################################################################################

rem Pop args until model=%1
set bounds=
set d=
set dll=
set g=
set r=
set s=
set tpl2cpp=tpl2cpp
:STARTLOOP
if [%2]==[] goto ENDLOOP
if %1==-d set d=-d& set dll=-dll& shift
if %1==-g set g=-g& shift
if %1==-r set r=-r& set tpl2cpp=tpl2rem& shift
if %1==-s set s=-s& set bounds=-bounds& shift
goto STARTLOOP
:ENDLOOP

set model=%~n1

if not exist %model%.tpl (
  goto ERROR
)

if exist %model%.htp (
  del /Q %model%.htp
)
if exist %model%.cpp (
  del /Q %model%.cpp
)
if exist %model%.obj (
  del /Q %model%.obj
)
if exist %model%.exe (
  del /Q %model%.exe
)

echo *** Parsing: %model%.tpl
echo.
%tpl2cpp% %bounds% %dll% %model%
if not exist %model%.htp (
  goto ERROR
)
if not exist %model%.cpp (
  goto ERROR
)
echo.
echo *** Compiling: adcomp %d% %g% %r% %s% %model%
call adcomp %d% %g% %r% %s% %model%
if not exist %model%.obj (
  goto ERROR
)
echo.
echo *** Linking: adlink %d% %g% %r% %s% %model%
call adlink %d% %g% %r% %s% %model%
if not exist %model%.exe (
  goto ERROR
)
echo.
echo Successful build of executable: %model%.exe

goto EOF

:HELP
echo Usage: admb [-d] [-g] [-r] [-s] model
echo.
echo Build AD Model Builder executable from TPL.
echo.
echo   -d     Create DLL
echo   -g     Insert debugging symbols
echo   -r     Create ADMB-RE
echo   -s     Enforce safe bounds
echo   model  Filename prefix, e.g. simple
echo.
goto EOF

:ERROR
echo.
echo Error: Failed to build executable.
:EOF
