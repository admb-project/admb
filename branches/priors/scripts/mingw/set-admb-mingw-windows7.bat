@echo off

REM
REM Sets the ADMB Home directory.
REM
@set ADMB_HOME=%CD%

REM
REM
REM
@set GNUWIN32_HOME=%ProgramFiles(x86)%\GnuWin32

REM
REM
REM
@set MINGW_HOME=C:\MinGW


REM
REM Adds the bin folder to ADMB_HOME to system path.
REM
@set PATH=.;%ADMB_HOME%\bin;%GNUWIN32_HOME%\bin;%MINGW_HOME%\bin;%PATH%

@echo Set ADMB Home directory to %ADMB_HOME%

@cd "%HOMEDRIVE%%HOMEPATH%"
