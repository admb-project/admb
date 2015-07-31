@echo off

@pushd "%VS140COMNTOOLS%\..\..\VC" & call vcvarsall.bat amd64 & popd

@set "PATH=%CD%\bin;%CD%\utilities;%PATH%"

@cd "%USERPROFILE%"

@echo.
@echo ADMB Command Prompt for Microsoft Visual C++ 14.0 (64 Bit)
@echo For help, type command "admb".
