@echo off
setlocal
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP
REM Returns:  Creates object file with same prefix.

for %%a in (%*) do (
  set arg=%%a
  if "!arg:~0,1!"=="-" (
    if "%%a"=="-d" set dll=/DBUILDING_DLL
    @REM if "%%a"=="-r" shift
    if "%%a"=="-s" set opt=/DSAFE_ALL
    if "%%a"=="-g" set DEBUG=/Z7
  ) else (
    if "%%~xa"=="" (
      set file=%%a.cpp
    ) else (
      set file=%%a
    )
  )
)
if not defined file goto HELP
if not defined opt set opt=/DOPT_LIB 

@echo on
cl /c /EHsc /O2 %DEBUG% /DUSE_LAPLACE /DWIN32 %opt% %dll% /D__MSVC32__=8 /I. /I"%ADMB_HOME%"\include /I"%ADMB_HOME%"\contrib\include %file%
@echo off

goto EOF

:HELP
echo Usage: adcomp [-d] [-r] [-s] model
echo.
echo Compile AD Model Builder C++ to object code, using the MinGW GCC 3.4.5 compiler.
echo.
echo   -d     Create object file for DLL
echo   -r     Create object file for ADMB-RE
echo   -s     Create object file with safe bounds and debugging symbols
echo   model  Filename prefix, e.g. simple
echo.

:EOF
