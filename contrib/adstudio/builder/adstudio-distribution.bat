@echo off
setlocal
if [%1]==[--help] goto HELP
REM ############################################################################
REM                                                                            #
REM Script:   adstudio-distribution                                            #
REM                                                                            #
REM Purpose:  Arrange AD Studio components for distribution                    #
REM                                                                            #
REM Requires: Directory 'components' created by adstudio-components            #
REM                                                                            #
REM Returns:  Creates a directory called 'distribution'                        #
REM                                                                            #
REM History:  2018-01-18  Created for AD Studio 1.0                            #
REM                                                                            #
REM ############################################################################

set FROM=components
set TO=distribution
set CP=%SYSTEMROOT%\system32\robocopy.exe

rd /q /s %TO% 2>NUL
md %TO%

echo on
@echo.
@echo *** Populating home ...
%CP% %FROM%\admb %TO%\home\emacs\lisp\admb /e> NUL
%CP% %FROM%\auctex %TO%\home\emacs\lisp\auctex /e > NUL
%CP% %FROM%\ess %TO%\home\emacs\lisp\ess /e > NUL
%CP% %FROM% %TO%\home\emacs\lisp\markdown markdown-mode.el > NUL
%CP% %FROM%\tmb %TO%\home\emacs\lisp\tmb /e> NUL
%CP% %FROM%\icons %TO%\home\icons /e > NUL
%CP% %FROM% %TO%\home .emacs >NUL
@echo.
@echo *** Populating admb ...
@for /F "usebackq tokens=*" %%F in (`dir /ad /b %FROM%\admb*-*-*`) do @set AD=%%F
%CP% %FROM%\%AD% %TO%\admb\%AD% /e > NUL
%CP% %FROM% %TO%\admb *.pdf NEWS > NUL
@echo.
@echo *** Populating gnu ...
%CP% %FROM%\emacs %TO%\gnu\emacs /e > NUL
@echo.
@echo *** Populating Rtools ...
%CP% %FROM%\Rtools %TO%\Rtools /e > NUL
@echo.

@echo *** Compiling Emacs Lisp code
distribution\gnu\emacs\bin\emacs -Q -nw distribution/home/emacs/lisp ^
--eval "(normal-top-level-add-subdirs-to-load-path)" ^
--eval "(byte-recompile-directory default-directory 0)" ^
--eval "(kill-emacs)"
@echo.

@echo *** Renaming home to ~
move distribution\home distribution\~ >NUL
@echo.
@echo Done

@goto EOF

:HELP
echo Usage: adstudio-distribution
echo.

:EOF
