@echo off
setlocal
if [%1]==[--help] goto HELP
REM ############################################################################
REM                                                                            #
REM Script:   adstudio-components                                              #
REM                                                                            #
REM Purpose:  Download AD Studio components                                    #
REM                                                                            #
REM Requires: wget                                                             #
REM                                                                            #
REM Returns:  Creates a directory called 'components'                          #
REM                                                                            #
REM History:  2018-01-15  Created for AD Studio 1.0                            #
REM                                                                            #
REM ############################################################################

set ADMB=admb120-gcc493-win64.zip
set AUCTEX=auctex121-built.zip
set EMACS=emacs-25.3_1-x86_64.zip
set ESS=ess-17.11.zip
set INNOEXTRACT=innoextract-1.6-windows.zip
set RTOOLS=Rtools34.exe

set COMPS=http://admb-project.org/tools/adstudio/components
set GITHUB=https://raw.githubusercontent.com
set WGET=..\wget -q --no-check-certificate

echo on
@echo.

@echo *** Downloading components ...
@rd /q /s components 2>NUL
@md components
@pushd components
%WGET% -P admb %GITHUB%/admb-project/admb/master/contrib/emacs/admb.el
%WGET% -P admb %GITHUB%/admb-project/admb/master/contrib/emacs/LICENSE
%WGET% -P admb %GITHUB%/admb-project/admb/master/contrib/emacs/NEWS
%WGET% -P tmb %GITHUB%/kaskr/adcomp/master/emacs/tmb.el
%WGET% -P tmb %GITHUB%/kaskr/adcomp/master/emacs/LICENSE
%WGET% -P tmb %GITHUB%/kaskr/adcomp/master/emacs/NEWS
%WGET% %GITHUB%/admb-project/admb/master/contrib/adstudio/dot/.emacs
%WGET% %COMPS%/admb.pdf
%WGET% %GITHUB%/admb-project/admb/master/contrib/adstudio/icons/admb64.ico
%WGET% %COMPS%/%ADMB%
%WGET% %COMPS%/admbre.pdf
%WGET% http://admb-project.org/tools/adstudio/adstudio.pdf
%WGET% %COMPS%/%AUCTEX%
%WGET% %COMPS%/autodif.pdf
%WGET% http://ftp.gnu.org/gnu/emacs/windows/%EMACS%
%WGET% http://ess.r-project.org/downloads/ess/%ESS%
%WGET% http://constexpr.org/innoextract/files/%INNOEXTRACT%
%WGET% https://jblevins.org/projects/markdown-mode/markdown-mode.el
%WGET% %GITHUB%/admb-project/admb/master/contrib/adstudio/NEWS
%WGET% https://cran.r-project.org/bin/windows/Rtools/%RTOOLS%
%WGET% %COMPS%/unzip.exe

@echo.

@echo *** Unpacking components ...
unzip -q -d %ADMB:.zip=% %ADMB%
unzip -q -d auctex %AUCTEX%
unzip -q -d emacs %EMACS%
unzip -q %ESS%
@rename %ESS:.zip=% ess
unzip -q -d innoextract %INNOEXTRACT%
@move innoextract\innoextract.exe . >NUL
@rd /q /s innoextract
innoextract -s -d temp %RTOOLS%
@move temp\app Rtools >NUL
@rd /q /s temp
@popd
@echo.
@echo Done

@goto EOF

:HELP
echo Usage: adstudio-components
echo.

:EOF
