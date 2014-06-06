@echo off

@pushd "%VS110COMNTOOLS%\..\.." & call "Common7\Tools\VsDevCmd.bat" & popd

@set "PATH=%CD%\bin;%CD%\utilities;%PATH%"

@cd "%USERPROFILE%"

@echo.
@echo ADMB Command Prompt for Microsoft Visual C++ 2012
@echo For help, type command "admb".
