@echo off

REM
REM Sets the ADMB Home directory.
REM
@set ADMB_HOME=%CD%

REM
REM Adds the bin folder to ADMB_HOME to system path.
REM
@set PATH=.;"%ADMB_HOME%"\bin;%ADMB_HOME%\utilities;%ADMB_HOME%\MinGW-gcc4.6\bin;%PATH%
@echo Setting ADMB Home enviroment to "%ADMB_HOME%".

@cd "%USERPROFILE%"

@echo.
@echo For help, type command "admb".
