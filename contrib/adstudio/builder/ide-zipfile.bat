@echo off
setlocal
if [%1]==[--help] goto HELP
REM ############################################################################
REM                                                                            #
REM Script:   ide-zipfile                                                      #
REM                                                                            #
REM Purpose:  Build ADMB-IDE as a zip file                                     #
REM                                                                            #
REM Requires: wget, directory 'distribution' created by ide-distribution       #
REM                                                                            #
REM Returns:  Creates admb-ide-%ADMB%-%WIN%.zip in the current directory       #
REM                                                                            #
REM 2017-08-26  Aligned with new workflow (components -> distribution -> zip), #
REM             added tmb-mode                                                 #
REM 2015-01-12  Added auctex and ess                                           #
REM 2012-03-01  Generalized to three args and win32/win64 builds               #
REM 2011-02-17  Adapted to GCC 4.5.0, moved admb-ide.pdf to 'admb' dir         #
REM 2010-03-18  Added admb-ide-build.bat and admb-ide-build.iss                #
REM 2010-03-14  Adapted to GCC 4.4.0                                           #
REM 2009-07-07  Added ADMB and ADMB-RE manuals, renamed 'release' to 'temp'    #
REM 2009-06-03  Created                                                        #
REM                                                                            #
REM ############################################################################

pushd distribution
for /F "usebackq tokens=*" %%F in (`dir /ad /b admb\admb*-*-*`) do set AD=%%F
set ZIPFILE=admb-ide-%AD:~4,3%-win64.zip

echo *** Zipping %ZIPFILE% ...
..\wget -q http://www.admb-project.org/tools/admb-ide/components/zip.exe
zip -rS ..\%ZIPFILE% ~ admb gnu Rtools
del zip.exe
popd
echo.
echo Done

goto EOF

:HELP
echo Usage: ide-zipfile
echo.

:EOF
