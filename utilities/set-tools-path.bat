@echo off

REM
REM Sets the ADMB Home directory.
REM
@set ADMB_HOME=%CD%

REM
REM
REM
@set GNUWIN32_HOME=%ADMB_HOME%\tools\GnuWin32

REM
REM
REM
@set MINGW_HOME=%ADMB_HOME%\tools\MinGW


REM
REM Adds the bin folder to ADMB_HOME to system path.
REM
@set PATH=.;%ADMB_HOME%\bin;%GNUWIN32_HOME%\coreutils-5.3.0-bin\bin;%GNUWIN32_HOME%\make-3.81-bin\bin;%MINGW_HOME%\bin;%PATH%

@echo Set ADMB Home directory to %ADMB_HOME%

@cd "%ADMB_HOME%\examples\admb"
