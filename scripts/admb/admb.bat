@echo off

setlocal EnableExtensions EnableDelayedExpansion

if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP

if defined ADMB_HOME (
  set "ADMB_HOME="
)
for %%a in (%0.bat) do (
  set HAS_PATH=%%~$PATH:a
  if not "!HAS_PATH!"=="" (
    set ADMB_PATH="%%~dp$PATH:a"
  ) else (
    set ADMB_PATH="%%~dpa"
  )
  pushd !ADMB_PATH!\..
  set ADMB_HOME=!CD!
  popd
)
set PATH=!ADMB_HOME!\bin;%PATH%

set srcs=
set tpls=
set objs=

for %%a in (%*) do (
  set arg=%%a
  if "!arg:~0,1!"=="-" (
    if %%a==-d (
      set d=-d 
      set dll=-dll
    )
    if %%a==-g (
      set g=-g
    )
    if %%a==-r (
      set r=-r 
      set parser=tpl2rem
    )
    if %%a==-s (
      set s=-s 
      set bounds=-bounds
    )
  ) else (
    if "%%~xa"=="" (
      set tpls=!tpls! %%a
    ) else (
      if "%%~xa"==".c" (
        set srcs=!srcs! %%a
      )
      if "%%~xa"==".cpp" (
        set srcs=!srcs! %%a
      )
      if "%%~xa"==".o" (
        set objs=!objs! %%a
      )
      if "%%~xa"==".obj" (
        set objs=!objs! %%a
      )
      if "%%~xa"==".tpl" (
        set tpls=!tpls! %%a
      )
    )
  )
)
if not defined parser set parser=tpl2cpp

for %%a in (!tpls!) do (
  set model=%%~na
  if not exist %%~na.tpl goto ERROR1
  del classdef.tmp xxdata.tmp xxhtop.tmp xxhtopm.tmp xxglobal.tmp xxtopm.tmp 2> NUL
  del xxalloc.tmp xxalloc1.tmp xxalloc2.tmp xxalloc3.tmp xxalloc4.tmp xxalloc5.tmp xxalloc6.tmp header.tmp 2> NUL
  del tfile1 tfile2 tfile3 tfile4 tfile5 2> NUL
  del !model!.cpp !model!.htp !model!.obj !model!.exe 2> NUL
  set CMD=!parser! !bounds! !dll! !model!
  echo.&echo *** !CMD!
  call !CMD!
  if not exist !model!.cpp goto ERROR2
  if not exist !model!.htp goto ERROR2
)

for %%b in (!tpls!) do (
  set model=%%~nb
  for %%a in (!model! !srcs!) do (
    set src=%%~na
    set CMD=adcomp !d! !g! !r! !s! !src!
    echo.&echo *** !CMD!
    call !CMD!
    if not exist !src!.obj (
      echo.&echo Error: Unable to build %%a
      goto EOF
    )
  )
)
for %%a in (!srcs!) do (
  set src=%%~na
  set objs=!objs! !src!.obj
)
for %%a in (!tpls!) do (
  set model=%%~na
  set CMD=adlink !d! !g! !r! !s! !model!.obj !objs!
  echo.&echo *** !CMD!
  call !CMD!
  if defined dll (
    if not exist %%~na.dll goto ERROR2
  ) else (
    if not exist %%~na.exe goto ERROR2
  )
)

echo.&echo Successfully built executable.
goto EOF

:HELP
echo Usage: admb [-d] [-g] [-r] [-s] model
echo.
echo Build AD Model Builder executable from TPL.
echo.
echo   -d     Create DLL
echo   -g     Insert debugging symbols
echo   -r     Create ADMB-RE
echo   -s     Enforce safe bounds
echo   model  Filename prefix, e.g. simple
echo.
goto EOF

:ERROR1
echo.&echo Error: !model!.tpl not found
goto EOF

:ERROR2
echo.&echo Error: Could not parse !model!.tpl
pwd
goto EOF

:EOF

REM r982 [2011-02-16] arnima  rewrite, fixed bug when user option is not
REM                           recognized, fixed spaces, improved messages
REM r927 [2010-12-24] johnoel moved to 'admb' dir
REM r917 [2010-12-24] johnoel pruned 'mingw' dir
REM r914 [2010-12-24] johnoel changed script so it deletes cpp/htp/obj/exe and
REM                           reports error or success, moved to 'g++' dir
REM r629 [2010-05-20] johnoel changed .o to .obj
REM r623 [2010-05-20] johnoel changed script so it exits if tpl/cpp/htp/o/exe do
REM                           not exist
REM r525 [2009-08-07] arnima  added support for filename extension like
REM                           simple.tpl
REM                   johnoel split -s option into separate -g and -s options
REM r244 [2009-05-28] arnima  created
