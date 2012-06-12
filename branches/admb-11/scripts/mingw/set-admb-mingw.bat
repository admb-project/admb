@echo off

REM
REM Sets the ADMB Home directory.
REM
@set ADMB_HOME=%CD%

REM
REM
REM
@set GNUWIN32_HOME=%ProgramFiles%\GNUWIN32

REM
REM
REM
@set MINGW_HOME=C:\MinGW


REM
REM Adds the bin folder to ADMB_HOME to system path.
REM
REM set PATH=.;"%ADMB_HOME%"\bin;%GNUWIN32_HOME%\bin;%MINGW_HOME%\bin;%PATH%
@set PATH=.;"%ADMB_HOME%"\bin;%MINGW_HOME%\bin;%PATH%
@echo Setting ADMB Home enviroment to "%ADMB_HOME%".

@cd "%USERPROFILE%"

@echo.
@echo For help, type command "admb -help".
