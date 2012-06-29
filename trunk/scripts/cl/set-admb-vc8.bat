@echo off

@set MSSDK=%ProgramFiles%\Microsoft^ Platform^ SDK^ for^ Windows^ Server^ 2003^ R2

REM
REM Sets the ADMB Home directory.
REM
@set ADMB_HOME=%CD%

@call "%VS80COMNTOOLS%vsvars32.bat"

REM
REM Adds the bin folder to ADMB_HOME to system path.
REM
@set PATH="%ADMB_HOME%"\bin;%PATH%
@echo Setting ADMB Home enviroment to "%ADMB_HOME%".

@cd "%USERPROFILE%"

@echo.
@echo For help, type command "admb -help".
