@echo off

@if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" (
@  set VSPATH="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere" -latest  -property installationPath
@  pushd "%VSPATH%\VC\Auxiliary\Build" & call vcvars64.bat & popd
@)

@if exist "%CD%\utilities\mingw64\bin\g++.exe" (
@  set "PATH=%CD%\bin;%CD%\utilities;%CD%\utilities\mingw64\bin;%PATH%"
@) else (
@  set "PATH=%CD%\bin;%CD%\utilities;%PATH%"
@)

@cd "%USERPROFILE%"

@echo.
@echo ADMB Command Prompt
@echo For help, type command "admb".
