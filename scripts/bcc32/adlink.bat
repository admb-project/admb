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
      set libs=df1b2s.lib admod32s.lib ads32.lib adt32s.lib contribs.lib
    )
  ) else (
    set objs=!objs! !arg!
  )
)

if not defined libs set libs=df1b2o.lib admod32.lib ado32.lib adt32.lib contribo.lib
set LIBPATH_MSSDK=/libpath:"%MSSDK%"\lib

@echo on
bcc32 %v% %wd% -L%BCC55_HOME%\lib -L"%ADMB_HOME%"\lib %objs% %libs%
@echo off

goto EOF

:HELP
echo Usage: adlink [-d] [-r] [-s] model
echo.
echo Link AD Model Builder object code to executable.
echo.
echo   -d     Create DLL
echo   -r     Create ADMB-RE
echo   -s     Use safe bounds and debugging symbols
echo   model  Filename prefix, e.g. simple
echo.

:EOF
