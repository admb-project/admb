@echo off

REM History:  24 May 2009  Arni Magnusson created

setlocal EnableExtensions EnableDelayedExpansion
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP
set objs=
for %%a in (%*) do (
  set arg=%%a
  if "!arg:~0,1!"=="-" (
    if "!arg!"=="-s" (
      set libs="%ADMB_HOME%"\lib\admb.lib "%ADMB_HOME%"\contrib\lib\contrib.lib
    )
  ) else (
    if "%%~xa"=="" (
      set objs=!objs! !arg!.obj
    ) else (
      set objs=!objs! !arg!
    )
  )
)

if not defined libs set libs="%ADMB_HOME%"\lib\admbo.lib "%ADMB_HOME%"\contrib\lib\contribo.lib
set LIBPATH_MSSDK=/libpath:"%MSSDK%"\lib

@echo on
cl %objs% %libs% /link
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
