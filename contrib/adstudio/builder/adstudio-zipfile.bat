@echo off
setlocal
if [%1]==[--help] goto HELP
REM ############################################################################
REM                                                                            #
REM Script:   adstudio-zipfile                                                 #
REM                                                                            #
REM Purpose:  Build AD Studio as a zip file                                    #
REM                                                                            #
REM Requires: wget, directory 'distribution' created by adstudio-distribution  #
REM                                                                            #
REM Returns:  Creates adstudio.zip in the current directory                    #
REM                                                                            #
REM History:  2018-01-18  Created for AD Studio 1.0                            #
REM                                                                            #
REM ############################################################################

echo on
@echo.

@pushd distribution

@echo *** Zipping %ZIPFILE% ...
..\wget -q http://admb-project.org/tools/adstudio/components/zip.exe
zip -rS ..\adstudio.zip ~ admb gnu Rtools
del zip.exe
@popd
@echo.
@echo Done

@goto EOF

:HELP
echo Usage: adstudio-zipfile
echo.

:EOF
