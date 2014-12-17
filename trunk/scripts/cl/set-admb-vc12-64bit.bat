@echo off

@pushd "%VS120COMNTOOLS%\..\..\VC" & call "vcvarsall.bat amd64" & popd

@set "PATH=%CD%\bin;%CD%\utilities;%PATH%"

@cd "%USERPROFILE%"

@echo.
@echo ADMB Command Prompt for Microsoft Visual C++ 2012 64Bit
@echo For help, type command "admb".
