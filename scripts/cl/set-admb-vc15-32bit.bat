@echo off

@pushd "%VS150COMNTOOLS%\..\..\VC\Auxiliary\Build" & call vcvarsall.bat x86 & popd

@set "PATH=%CD%\bin;%CD%\utilities;%PATH%"

@cd "%USERPROFILE%"

@echo.
@echo ADMB Command Prompt for Microsoft Visual C++ 2017 (32 Bit)
@echo For help, type command "admb".
