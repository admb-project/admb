@echo off
REM
REM Sets the Borland Home directory.
REM
@set BCC55_HOME=C:\Borland\BCC55

REM
REM Sets the ADMB Home directory.
REM
@set ADMB_HOME=%CD%

REM
REM Adds the bin folder to BCC_HOME and ADMB_HOME to system path.
REM
@set PATH=%BCC55_HOME%\bin;%ADMB_HOME%\bin;%PATH%

@echo Set Borland Home directory to %BCC55_HOME%
@echo Set ADMB Home directory to %ADMB_HOME%

@cd "%HOMEDRIVE%%HOMEPATH%"
