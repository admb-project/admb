@echo off

REM
REM Sets the ADMB Home directory.
REM
@set ADMB_HOME=%CD%

@cd "%VS100COMNTOOLS%"\..\..\VC
@call vcvarsall.bat amd64

REM
REM Adds the bin folder to ADMB_HOME to system path.
REM
@set PATH="%ADMB_HOME%"\bin;"%ADMB_HOME%"\utilities;%PATH%
@echo Setting ADMB Home enviroment to "%ADMB_HOME%".

@cd "%USERPROFILE%"

@echo.
@echo For help, type command "admb".
