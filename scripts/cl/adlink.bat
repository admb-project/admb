@echo off

REM History:  24 May 2009  Arni Magnusson created
REM           23 May 2013  Chris Grandin fix DLL creation, got rid of deprecated MSSDK

setlocal EnableExtensions EnableDelayedExpansion
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP
set OBJS=
for %%a in (%*) do (
  set arg=%%a
  if "!arg:~0,1!"=="-" (
    if "!arg!"=="-s" (
      set LIBS="%ADMB_HOME%"\lib\admb.lib "%ADMB_HOME%"\contrib\lib\contrib.lib
    )
    if "!arg!"=="-g" (
      set DEBUG="/DEBUG"
    )
    if "!arg!"=="-d" (
      set DLL="/DLL"
      set FN="/OUT:%~n3.dll"
    )
  ) else (
    if "%%~xa"=="" (
      set OBJS=!OBJS! !arg!.obj
    ) else (
      set OBJS=!OBJS! !arg!
    )
  )
)

if not defined LIBS set LIBS="%ADMB_HOME%"\lib\admbo.lib "%ADMB_HOME%"\contrib\lib\contribo.lib

@echo on
cl %OBJS% %LIBS% /link %DEBUG% %DLL% %FN%
@echo off

goto EOF

:HELP
echo Usage: adlink [-d] [-r] [-s] model
echo.
echo Link AD Model Builder object code to executable, using the Microsoft Visual C++ compiler.
echo.
echo   -d     Create DLL
echo   -r     Create ADMB-RE
echo   -s     Use safe bounds and debugging symbols
echo   model  Filename prefix, e.g. simple
echo.

:EOF
