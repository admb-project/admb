@echo off
setlocal
REM if [%1]==[] goto HELP
if [%1]==[--help] goto HELP
REM ####################################################################################################################
REM                                                                                                                    #
REM Script:   admb-ide-build ADMB GCC WIN                                                                              #
REM                                                                                                                    #
REM Purpose:  Build ADMB-IDE as a zip file                                                                             #
REM                                                                                                                    #
REM Args:     ADMB is the ADMB version number, e.g. 101                                                                #
REM           GCC is the GCC version number, e.g. 452                                                                  #
REM           WIN is the Windows platform, e.g. win32                                                                  #
REM                                                                                                                    #
REM Notes:    Uses a temporary directory called 'temp'                                                                 #
REM                                                                                                                    #
REM Requires: The zip.exe program, as well as the following directories                                                #
REM             c:/~/emacs/lisp/admb                                                                                   #
REM             c:/~/emacs/lisp/auctex                                                                                 #
REM             c:/~/emacs/lisp/ess                                                                                    #
REM             c:/~/icons                                                                                             #
REM             c:/gnu/emacs                                                                                           #
REM             c:/gnu/gcc%GCC%-%WIN%                                                                                  #
REM             c:/gnu/gdb                                                                                             #
REM             admb, ../*.pdf (core manuals, not ide), ../dot, ../manual                                              #
REM                                                                                                                    #
REM Returns:  Creates admb-ide-%ADMB%-%WIN%.zip in the current directory                                               #
REM                                                                                                                    #
REM History:  12 Jan 2015 Arni Magnusson added auctex and ess                                                          #
REM            1 Mar 2012 Arni Magnusson generalized to three args and win32/win64 builds, added admb-ide.texi         #
REM           17 Feb 2011 Arni Magnusson adapted to GCC 4.5.0, moved admb-ide.pdf to 'admb' dir                        #
REM           18 Mar 2010 Arni Magnusson added admb-ide-build.bat and admb-ide-build.iss                               #
REM           14 Mar 2010 Arni Magnusson adapted to GCC 4.4.0                                                          #
REM            7 Jul 2009 Arni Magnusson added ADMB and ADMB-RE manuals, renamed 'release' to 'temp'                   #
REM            3 Jun 2009 Arni Magnusson created                                                                       #
REM                                                                                                                    #
REM ####################################################################################################################

rd /q /s admb-ide \ 2>NUL
mkdir /p admb-ide\admb\ide\
echo.
echo *** Populating ~ ...
copy /Y dot\_emacs admb-ide\.emacs
@REM xcopy /iq  c:\~\emacs\lisp\admb     temp\~\emacs\lisp\admb
@REM xcopy /iqs c:\~\emacs\lisp\auctex   temp\~\emacs\lisp\auctex
@REM xcopy /iqs c:\~\emacs\lisp\ess      temp\~\emacs\lisp\ess
xcopy /E /Y icons admb-ide\
echo.
echo *** Populating admb ...
@REM xcopy /iq  ..\*.pdf                 temp\admb
xcopy /E /Y ..\..\build\dist\* admb-ide\admb\
@REM xcopy /iq  ..\manual\admb-ide.pdf*  temp\admb
@REM xcopy /iq  ..\manual\admb-ide.texi* temp\admb\ide\inst
@REM xcopy /iq  admb-ide-build.*         temp\admb\ide\inst
xcopy /E /Y NEWS admb-ide\
echo.
echo *** Populating emacs and Rtools ...
xcopy /E /Y c:\emacs admb-ide\
xcopy /E /Y c:\Rtools admb-ide\
echo.
echo *** Creating admb-ide.zip
7z a -tzip -mx9 admb-dist.zip admb-ide
rd /q /s admb-ide 2>NUL
echo Done
goto EOF

:HELP
set ADMB=%1
set GCC=%2
set WIN=%3
echo Usage: admb-ide-build ADMB GCC WIN
echo.
echo ADMB is the ADMB version number, e.g. 101
echo GCC is the GCC version number, e.g. 452
echo WIN is the ADMB version number, e.g. win32
echo.

:EOF
