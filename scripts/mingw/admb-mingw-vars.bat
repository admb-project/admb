@echo off

REM
REM Sets the ADMB Home directory.
REM
@set ADMB_HOME=C:\\admb

REM
REM Set the GnuWin32 Home directory.
REM
@set GNUWIN32_HOME=C:\\Progra~1\\GnuWin32

REM
REM Sets the MinGW Home directory.
REM
@set MINGW_HOME=C:\\MinGW

REM
REM Adds the bin folder to ADMB_HOME, GNUWIN32_HOME and MINGW_HOME
REM to the system path.
REM
@set PATH=%ADMB_HOME%\bin;%GNUWIN32_HOME%\bin;%MINGW_HOME%\bin;%PATH%

@echo Set the ADMB HOME directory to %ADMB_HOME%
@echo Set the GNUWIN32 Home directory to %GNUWIN32_HOME%
@echo Set the MinGW Home directory to %MINGW_HOME%
