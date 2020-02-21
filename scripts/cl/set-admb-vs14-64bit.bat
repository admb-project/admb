@echo off

@pushd "%VS140COMNTOOLS%\..\..\VC" & call vcvarsall.bat amd64 & popd

@set "PATH=%CD%\bin;%CD%\utilities;%PATH%"

@cd "%USERPROFILE%"

@echo.
@echo ADMB Command Prompt for Microsoft Visual Studio 2015 - C++ 64Bit
@echo For help, type command "admb".
