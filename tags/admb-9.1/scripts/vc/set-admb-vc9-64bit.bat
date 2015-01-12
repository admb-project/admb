@echo off

REM
REM Sets the ADMB Home directory.
REM
@set ADMB_HOME=%CD%

call "%VS90COMNTOOLS%..\..\VC\vcvarsall.bat" amd64

REM
REM Adds the bin folder to ADMB_HOME to system path.
REM
@set PATH=%ADMB_HOME%\bin;%PATH%

@echo Set ADMB Home directory to %ADMB_HOME%

@cd "%ADMB_HOME%/examples/admb"
