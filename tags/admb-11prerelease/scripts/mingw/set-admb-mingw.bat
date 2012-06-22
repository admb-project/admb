@echo off

REM
REM Sets the ADMB Home directory.
REM
@set ADMB_HOME=%CD%
@echo Setting ADMB Home enviroment to "%ADMB_HOME%".

REM
REM
REM
@set MINGW_HOME=C:\MinGW
@echo Setting MinGW Home enviroment to "%MINGW_HOME%".

REM
REM Adds the bin folder to ADMB_HOME to system path.
REM
@set PATH=.;"%ADMB_HOME%"\bin;"%ADMB_HOME%"\utilities;%MINGW_HOME%\bin;%PATH%

@cd "%USERPROFILE%"

@echo.
@echo For help, type command "admb".
