@echo off

@pushd "%VS110COMNTOOLS%\..\..\VC" & call "vcvarsall.bat x86" & popd

@set "PATH=%CD%\bin;%CD%\utilities;%PATH%"

@cd "%USERPROFILE%"

@echo.
@echo ADMB Command Prompt for Microsoft Visual C++ 2012 32Bit
@echo For help, type command "admb".
