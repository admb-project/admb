@echo off
@REM r244 [2009-05-28] arnima  created

setlocal EnableExtensions EnableDelayedExpansion

if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP

rem Pop args until model=%1
set objects=
set sym=-s & rem space
set linker=g++
for %%a in (%*) do (
if %%~xa==.obj (
set objects=!objects! %%a
if not defined model set model=%%~na
)
if %%~xa==.o (
set objects=!objects! %%a
if not defined model set model=%%~na
)
if %%a==-d set linker=dllwrap
if %%a==-g set sym=
if %%a==-r set r=
if %%a==-f (
  set libs="%ADMB_HOME%\contrib\lib\libcontribo.a" "%ADMB_HOME%\lib\libadmbo.a" 
)
)
if not defined libs set libs="%ADMB_HOME%\contrib\lib\libcontrib.a" "%ADMB_HOME%\lib\libadmb.a" 

if %linker%==g++ (set out=-o %model%) else (set def=-def %model%.def^
 --driver-name g++ --output-lib %model%.dll & set out=--output-lib lib%model%.a -o %model%.dll)

if exist "%ADMB_HOME%"\bin\admb-cfg.bat call "%ADMB_HOME%"\bin\admb-cfg.bat
if defined LDFLAGS (
  set LDFLAGS=%LDFLAGS% %ADMB_CFG_LDFLAGS%
) else (
  set LDFLAGS=%ADMB_CFG_LDFLAGS%
)

set CMD=%linker% %LDFLAGS% %sym% -static %def% -o %model%.exe %objects% %libs%
echo %CMD%
%CMD%

goto EOF

:HELP
echo Usage: adlink [-d] [-g] [-r] [-f] model
echo.
echo Link AD Model Builder object code to executable, using the MinGW GCC^
 compiler.
echo.
echo   -d     Build a dynamic library (dll).
echo   -g     Build with debug symbols.
echo   -r     Build Random effects program (ADMB-RE).
echo   -f     Build with Fast optimized mode (no bounds checking).
echo          By default, admb script builds with bounds checking.
echo   model  TPL file (ie 'simple.tpl' or the filename 'simple' with no .tpl extension)
echo.

:EOF
