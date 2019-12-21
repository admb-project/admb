@echo off

@set VSPATH="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere" -latest  -property installationPath
@pushd "%VSPATH%\VC\Auxiliary\Build" & call vcvars64.bat & popd

@set "PATH=%CD%\bin;%CD%\utilities;%PATH%"

@cd "%USERPROFILE%"

@echo.
@echo ADMB Command Prompt for Microsoft Visual Studio 64Bit
@echo For help, type command "admb".
