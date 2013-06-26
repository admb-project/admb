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
if %%a==-s (
  set libs="%ADMB_HOME%\contrib\lib\libcontrib.a" "%ADMB_HOME%\lib\libadmb.a" 
)
)
if not defined libs set libs="%ADMB_HOME%\contrib\lib\libcontribo.a" "%ADMB_HOME%\lib\libadmbo.a" 

if %linker%==g++ (set out=-o %model%) else (set def=-def %model%.def^
 --driver-name g++ & set out=--output-lib lib%model%.a -o %model%.dll)

set CMD=%linker% %sym% -static %def% -o %model%.exe %objects% %libs%
echo %CMD%
%CMD%

goto EOF

:HELP
echo Usage: adlink [-d] [-g] [-r] [-s] model
echo.
echo Link AD Model Builder object code to executable, using the MinGW GCC^
 compiler.
echo.
echo   -d     Create DLL
echo   -g     Insert debugging symbols
echo   -r     Create ADMB-RE
echo   -s     Enforce safe bounds
echo   model  Filename prefix, e.g. simple
echo.

:EOF
