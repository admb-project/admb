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
REM History:  26 Aug 2017 Arni Magnusson created                               #
REM                                                                            #
REM ############################################################################

set ADMB=admb120-gcc493-win64.zip
set AUCTEX=auctex-1191-texsite.zip
set EMACS=emacs-25.2-x86_64.zip
set ESS=ess-1610-github.zip
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
%WGET% %COMPS%/%ADMB%
%WGET% %COMPS%/admb.pdf
%WGET% %COMPS%/admbre.pdf
%WGET% %COMPS%/autodif.pdf
%WGET% http://admb-project.org/tools/adstudio/adstudio.pdf
%WGET% %COMPS%/%AUCTEX%
%WGET% %COMPS%/%ESS%
%WGET% %COMPS%/unzip.exe
%WGET% http://ftp.gnu.org/gnu/emacs/windows/%EMACS%
%WGET% http://constexpr.org/innoextract/files/%INNOEXTRACT%
%WGET% https://jblevins.org/projects/markdown-mode/markdown-mode.el
%WGET% https://cran.r-project.org/bin/windows/Rtools/%RTOOLS%
%WGET% %GITHUB%/admb-project/admb/master/contrib/emacs/admb.el
%WGET% %GITHUB%/admb-project/admb/master/contrib/emacs/LICENSE
%WGET% %GITHUB%/admb-project/admb/master/contrib/emacs/NEWS
%WGET% %GITHUB%/admb-project/admb/master/contrib/adstudio/dot/.emacs
%WGET% %GITHUB%/admb-project/admb/master/contrib/ide/dot/LICENSE
%WGET% %GITHUB%/admb-project/admb/master/contrib/ide/dot/NEWS
%WGET% %GITHUB%/admb-project/admb/master/contrib/adstudio/icons/admb64.ico
%WGET% %GITHUB%/admb-project/admb/master/contrib/adstudio/NEWS
%WGET% %GITHUB%/kaskr/adcomp/master/emacs/tmb.el
%WGET% %GITHUB%/kaskr/adcomp/master/emacs/LICENSE
%WGET% %GITHUB%/kaskr/adcomp/master/emacs/NEWS
@echo.

@echo *** Unpacking components ...
unzip -q -d %ADMB:.zip=% %ADMB%
unzip -q -d auctex %AUCTEX%
@rename %AUCTEX% temp.zip
@move auctex* auctex >NUL
@rename temp.zip %AUCTEX%
unzip -q -d emacs %EMACS%
unzip -q -d ess %ESS%
@rename %ESS% temp.zip
@move ess* ess >NUL
@rename temp.zip %ESS%
unzip -q %INNOEXTRACT%
innoextract -q -dtemp %RTOOLS%
@move temp\{app} Rtools >NUL
@rd /q /s temp
@popd
@echo.
@echo Done

@goto EOF

:HELP
echo Usage: adstudio-components
echo.

:EOF
