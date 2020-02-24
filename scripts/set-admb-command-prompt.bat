@echo off

if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" (
  for /f "usebackq delims=" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere" -latest  -property installationPath`) do (
    pushd "%%i\VC\Auxiliary\Build" & call vcvars64.bat > NUL & popd
  )
)

if exist "%CD%\utilities\mingw64\bin\g++.exe" (
  set "PATH=%CD%\bin;%CD%\utilities\mingw64\bin;%PATH%"
) else (
  set "PATH=%CD%\bin;%PATH%"
)

@cd "%USERPROFILE%"

@echo.
@echo ADMB Command Prompt
@echo For help, type command "admb".
