@echo off

setlocal EnableExtensions EnableDelayedExpansion

if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP

if defined ADMB_HOME (
  set ADMB_HOME=
)
if defined ADMB_HOME (
  echo "Error: Unable to unset ADMB_HOME=!ADMB_HOME!."
  goto EOF
)
for %%a in (%0.bat) do (
  set HAS_PATH=%%~$PATH:a
  if defined HAS_PATH (
    set ADMB_PATH="%%~dp$PATH:a"
  ) else (
    set ADMB_PATH="%%~dpa"
  )
  pushd !ADMB_PATH!\..
  set ADMB_HOME=!CD!
  popd
)
if not defined ADMB_HOME (
  echo "Error: ADMB_HOME is not defined."
  goto EOF
)
if defined MINGW_HOME (
  set PATH=!ADMB_HOME!\bin;!MINGW_HOME!\bin;!PATH!
) else (
  set PATH=!ADMB_HOME!\bin;!ADMB_HOME!\utilities\mingw\bin;!PATH!
)
set tpls=
set srcs=
set objs=
for %%a in (%*) do (
  set arg=%%a
  if "!arg:~0,1!"=="-" (
    if "!arg!"=="-d" (
      set d= -d
    )
    if "!arg!"=="-g" (
      set g= -g
    )
    if "!arg!"=="-r" (
      set r = -r
      set parser=tpl2rem
    )
    if "!arg!"=="-f" (
      set fast= -f
    )
  ) else (
    if "%%~xa"=="" (
      if not defined tpls (
        set tpls=!arg!
      ) else (
        set tpls=!tpls! !arg!
      )
    )
    if "%%~xa"==".tpl" (
      if not defined tpls (
        set tpls=%%a
      ) else (
        set tpls=!tpls! !arg!
      )
    )
    if "%%~xa"==".c" (
      if not defined srcs (
        set srcs=%%a
      ) else (
        set srcs=!srcs! !arg!
      )
    )
    if "%%~xa"==".cpp" (
      if not defined srcs (
        set srcs=%%a
      ) else (
        set srcs=!srcs! !arg!
      )
    )
    if "%%~xa"==".o" (
      if not defined objs (
        set objs=%%a
      ) else (
        set objs=!objs! !arg!
      )
    )
    if "%%~xa"==".obj" (
      if not defined objs (
        set objs=%%a
      ) else (
        set objs=!objs! !arg!
      )
    )
  )
)
if not defined tpls (
  if not defined srcs (
    if not defined objs (
      echo.&echo Error: Nothing to build
      echo.
      goto HELP
    )
    goto linker
  )
  goto compiler
) 
for %%a in (!tpls!) do (
  set tpl=%%~na
  if not exist %%~na.tpl (
    echo.&echo Error: !tpl!.tpl not found
    goto EOF
  )
  del classdef.tmp xxdata.tmp xxhtop.tmp xxhtopm.tmp xxglobal.tmp xxtopm.tmp 2> NUL
  del xxalloc.tmp xxalloc1.tmp xxalloc2.tmp xxalloc3.tmp xxalloc4.tmp xxalloc5.tmp xxalloc6.tmp header.tmp 2> NUL
  del tfile1 tfile2 tfile3 tfile4 tfile5 2> NUL
  del !tpl!.cpp !tpl!.htp !tpl!.obj !tpl!.exe 2> NUL
  if defined d (
    set dll= -dll
  )
  if defined g (
    set debug= -debug
  )
  if not defined parser (
    set parser=tpl2cpp
  )
  set CMD=!parser!!debug!!dll! !tpl!
  echo.&echo *** !CMD!
  call !CMD!
  if not exist !tpl!.cpp (
    echo.&echo Error: Unable to parse !tpl! to !tpl!.cpp.
    goto ERROR
  )
  if not exist !tpl!.htp (
    echo.&echo Error: Unable to parse !tpl! to !tpl!.htp.
    goto ERROR
  )
)
for %%b in (!tpls!) do (
  set tpl=%%~nb
  set CMD=adcomp!d!!g!!r!!fast! !tpl!
  echo.&echo *** !CMD!
  call !CMD!
  if not exist !tpl!.obj (
    echo.&echo Error: Unable to build !tpl!.obj
    goto EOF
  )
)
:compiler
if defined srcs (
  for %%a in (!srcs!) do (
    set src=%%a
    if not exist !src! (
      echo.&echo Error: !src! not found
      goto ERROR
    )
    set CMD=adcomp!d!!g!!r!!fast! !src!
    echo.&echo *** !CMD!
    call !CMD!
    set filename=%%~na
    if not exist !filename!.obj (
      echo.&echo Error: Unable to build !src! to !filename!.obj
      goto ERROR
    ) else (
      if not defined objs (
        set objs=!filename!.obj
      ) else (
        set objs=!objs! !filename!.obj
      )
    )
  )
)
:linker
if not defined tpls (
  if not defined objs (
    goto ERROR
  ) else (
    for %%a in (!objs!) do (
      set obj=%%a
      if not exist !obj! (
        echo.&echo Error: !obj! not found
        goto ERROR
      )
    )
    for %%a in (!objs!) do (
      set main=%%~na
      set CMD=adlink!d!!g!!r!!fast! !objs!
      echo.&echo *** !CMD!
      call !CMD!
      if not exist !main!.exe (
        goto ERROR
      )
      goto SUCCESS
    )
  )
) else (
  for %%a in (!tpls!) do (
    set tpl=%%~na
    set CMD=adlink!d!!g!!r!!fast! !tpl!.obj !objs!
    echo.&echo *** !CMD!
    call !CMD!
    if defined d (
      if not exist !tpl!.dll (
        goto ERROR
      )
    ) else (
      if not exist !tpl!.exe (
        goto ERROR
      )
    )
  )
)
:SUCCESS
echo.&echo Successfully built executable.
goto EOF
:ERROR
echo.&echo Error: Unable to build executable.
echo.&echo COMSPEC=%COMSPEC%.
echo.&echo PATH=%PATH%.
goto EOF
:HELP
echo Usage: admb [-d] [-g] [-r] [-f] model
echo.
echo Build AD Model Builder executable from TPL.
echo.
echo   -d     Build a dynamic library (dll).
echo   -g     Build with debug symbols.
echo   -r     Build Random effects program (ADMB-RE).
echo   -f     Build with Fast optimized mode (no bounds checking).
echo          By default, admb script builds with bounds checking.
echo   model  TPL file (ie 'simple.tpl' or the filename 'simple' with no .tpl extension)
echo.
goto EOF
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
:EOF
