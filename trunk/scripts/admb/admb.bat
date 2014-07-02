@echo off
@REM
@REM  Copyright 2013 (c) ADMB Foundation
@REM

if [%1]==[] goto HELP
if [%1]==[-h] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP

VERIFY OTHER 2>nul
SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
if ERRORLEVEL 1 (
  echo "Error[%COMSPEC%]: setlocal is unable to EnableExtensions and EnableDelayedExpansion."
  goto EOF
)

set ADMB_HOME=
if not defined ADMB_HOME (
  set "SCRIPT_PATH=%~dp0"
  if defined SCRIPT_PATH (
    pushd !SCRIPT_PATH!
    pushd ..
    set "ADMB_HOME=!CD!"
    popd
    popd
  ) else (
    for %%a in (admb.cmd) do (
      set "HAS_PATH=%%~dp$PATH:a"
      if defined HAS_PATH (
        pushd !HAS_PATH!
        pushd ..
        set "ADMB_HOME=!CD!"
        popd
        popd
      )
    )
  )
) else (
  pushd !ADMB_HOME!
  set "ADMB_HOME=!CD!"
  popd
)

if not defined ADMB_HOME (
  echo "Error: ADMB_HOME is not defined."
  goto EOF
)

set tpls=
set srcs=
set objs=
for %%a in (%*) do (
  set arg=%%a
  if "!arg:~0,1!"=="-" (
    if "!arg!"=="-c" (
      set compileonly= -c
    )
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
        set tpls=!arg!
      ) else (
        set tpls=!tpls! !arg!
      )
    )
    if "%%~xa"==".c" (
      if not defined srcs (
        set srcs=!arg!
      ) else (
        set srcs=!srcs! !arg!
      )
    )
    if "%%~xa"==".cpp" (
      if not defined srcs (
        set srcs=!arg!
      ) else (
        set srcs=!srcs! !arg!
      )
    )
    if "%%~xa"==".o" (
      if not defined objs (
        set objs=!arg!
      ) else (
        set objs=!objs! !arg!
      )
    )
    if "%%~xa"==".obj" (
      if not defined objs (
        set objs=!arg!
      ) else (
        set objs=!objs! !arg!
      )
    )
  )
)
if exist "!ADMB_HOME!\bin\admb-cfg.bat" (
  call "!ADMB_HOME!\bin\admb-cfg.bat"
  if defined ADMB_CFG_CXX (
    set CXX=!ADMB_CFG_CXX!
  )
  if defined ADMB_CFG_CXXFLAGS (
    set CXXFLAGS=!CXXFLAGS! !ADMB_CFG_CXXFLAGS!
  )
  if defined ADMB_CFG_LD (
    if not defined d (
      set LD=!ADMB_CFG_LD!
    )
  )
  if defined ADMB_CFG_LDFLAGS (
    set LDFLAGS=!LDFLAGS! !ADMB_CFG_LDFLAGS!
  )
)
if "!CXX!"=="cl" (
  set LD=!CXX!
  if defined CXXFLAGS (
    set CXXFLAGS= /c /nologo /EHsc !CXXFLAGS!
  ) else (
    set CXXFLAGS= /c /nologo /EHsc
  )
  if defined g (
    set CXXFLAGS=!CXXFLAGS! /Z7
  ) else (
    set CXXFLAGS=!CXXFLAGS! /O2
  )
  if defined fast (
    set CXXFLAGS=!CXXFLAGS! /DOPT_LIB
    if not exist "!ADMB_HOME!\contrib\lib\contribo.lib" (
      set libs="!ADMB_HOME!\lib\admbo.lib" /link
    ) else (
      set libs="!ADMB_HOME!\contrib\lib\contribo.lib" "!ADMB_HOME!\lib\admbo.lib" /link
    )
  ) else (
    if not exist "!ADMB_HOME!\contrib\lib\contrib.lib" (
      set libs="!ADMB_HOME!\lib\admb.lib" /link
    ) else (
      set libs="!ADMB_HOME!\contrib\lib\contrib.lib" "!ADMB_HOME!\lib\admb.lib" /link
    )
  )
  if not exist "!ADMB_HOME!\contrib\lib\contrib.lib" (
    set CXXFLAGS=!CXXFLAGS! /I. /I"!ADMB_HOME!\include" /I"!ADMB_HOME!\include\contrib"
  ) else (
    set CXXFLAGS=!CXXFLAGS! /I. /I"!ADMB_HOME!\include" /I"!ADMB_HOME!\contrib\include"
  )
) else (
  if not defined CXX (
    set CXX=g++
  )
  if not defined LD (
    if not defined d (
      set LD=g++
    ) else (
      set LD=g++
    )
  )
  if defined CXXFLAGS (
    set CXXFLAGS= -c !CXXFLAGS!
  ) else (
    set CXXFLAGS= -c
  )
  if defined d (
    if defined LDFLAGS (
      set LDFLAGS= -shared !LDFLAGS!
    ) else (
      set LDFLAGS= -shared
    )
  )
  if defined LDFLAGS (
    set LDFLAGS= -static !LDFLAGS!
  ) else (
    set LDFLAGS= -static
  )
  if defined g (
    set CXXFLAGS=!CXXFLAGS! -g
    set LDFLAGS=!LDFLAGS! -g
  ) else (
    set CXXFLAGS=!CXXFLAGS! -O3
  )
  if defined fast (
    set CXXFLAGS=!CXXFLAGS! -DOPT_LIB
    if not exist "!ADMB_HOME!\contrib\lib\libcontribo.a" (
      set libs="!ADMB_HOME!\lib\libadmbo.a"
    ) else (
      set libs="!ADMB_HOME!\contrib\lib\libcontribo.a" "!ADMB_HOME!\lib\libadmbo.a"
    )
  ) else (
    if not exist "!ADMB_HOME!\contrib\lib\libcontrib.a" (
      set libs="!ADMB_HOME!\lib\libadmb.a"
    ) else (
      set libs="!ADMB_HOME!\contrib\lib\libcontrib.a" "!ADMB_HOME!\lib\libadmb.a"
    )
  )
  if defined d (
    set CXXFLAGS=!CXXFLAGS! -DBUILDING_DLL
  )
  if not exist "!ADMB_HOME!\contrib\lib\libcontrib.a" (
    set CXXFLAGS=!CXXFLAGS! -fpermissive -I. -I"!ADMB_HOME!\include" -I"!ADMB_HOME!\include\contrib"
  ) else (
    set CXXFLAGS=!CXXFLAGS! -fpermissive -I. -I"!ADMB_HOME!\include" -I"!ADMB_HOME!\contrib\include"
  )
)
set "PATH=!ADMB_HOME!\bin;!ADMB_HOME!\utilities\mingw\bin;!PATH!"
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
  echo.&echo *** Parsing !tpl!.tpl:
  if defined parser (
    set CMD=!parser! !dll! !tpl!
    echo !CMD!
    call !CMD!
  ) else (
    set CMD=tpl2cpp !dll! !tpl!
    call !CMD! 2> !tpl!-error.log
    if not exist !tpl!.cpp (
      unset CMD
      set CMD=tpl2rem !dll! !tpl!
      call !CMD! 2> !tpl!-re-error.log
    fi
    if exist !tpl!.cpp (
      if exist !tpl!.htp(
        echo !CMD!
      )
    )
  )
  if not exist !tpl!.cpp (
    echo.&echo Error: Unable to parse !tpl!.tpl to !tpl!.cpp.
    type !tpl!-error.log
    goto ERROR
  )
  if not exist !tpl!.htp (
    echo.&echo Error: Unable to parse !tpl!.tpl to !tpl!.htp as a random effects model.
    type !tpl!-re-error.log
    goto ERROR
  )
)
for %%b in (!tpls!) do (
  set tpl=%%~nb
  @REM set CMD=adcomp!d!!g!!r!!fast! !tpl!
  if "!CXX!"=="cl" (
    set CMD=!CXX!!CXXFLAGS! /Fo!tpl!.obj !tpl!.cpp
  ) else (
    set CMD=!CXX!!CXXFLAGS! -o !tpl!.obj !tpl!.cpp
  )
  echo.&echo *** Compile: !tpl!.cpp
  echo !CMD!
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
    set filename=%%~na
    @REM set CMD=adcomp!d!!g!!r!!fast! !src!
    if "!CXX!"=="cl" (
      set CMD=!CXX!!CXXFLAGS! /Fo!filename!.obj !filename!.cpp
    ) else (
      set CMD=!CXX!!CXXFLAGS! -o !filename!.obj !filename!.cpp
    )
    echo.&echo *** Compile: !src!
    echo !CMD!
    call !CMD!
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
if defined compileonly (
  echo.&echo Compiled !objs!.
  goto EOF
)
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
      @REM set CMD=adlink!d!!g!!r!!fast! !objs!
      if defined d (
        set CMD=!LD!!LDFLAGS! -o !main!.dll !objs! !libs!
      ) else (
        if "!CXX!"=="cl" (
          set CMD=!LD!!LDFLAGS! /Fe!main!.exe !objs! !libs!
        ) else (
          set CMD=!LD!!LDFLAGS! -o !main!.exe !objs! !libs!
        )
      )
      echo.&echo *** Linking: !objs!
      echo !CMD!
      call !CMD!
      if defined d (
        if not exist !main!.dll (
          goto ERROR
        )
        echo.&echo Successfully built '!main!.dll'.
        goto SUCCESS
      ) else (
        if not exist !main!.exe (
          goto ERROR
        )
        echo.&echo Successfully built '!main!.exe'.
        goto EOF
      )
    )
  )
) else (
  for %%a in (!tpls!) do (
    set tpl=%%~na
    @REM set CMD=adlink!d!!g!!r!!fast! !tpl!.obj !objs!
    if defined d (
      if "!CXX!"=="cl" (
        set CMD=!LD!!LDFLAGS! -o !tpl!.dll !objs! !libs!
      ) else (
        if defined objs (
          set CMD=!LD!!LDFLAGS! -o !tpl!.dll !tpl!.obj !objs! !libs!
        ) else (
          set CMD=!LD!!LDFLAGS! -o !tpl!.dll !tpl!.obj !libs!
        )
      )
    ) else (
      if "!CXX!"=="cl" (
        if defined objs (
          set CMD=!LD!!LDFLAGS! /Fe!tpl!.exe !tpl!.obj !objs! !libs!
        ) else (
          set CMD=!LD!!LDFLAGS! /Fe!tpl!.exe !tpl!.obj !libs!
        )
      ) else (
        if defined objs (
          set CMD=!LD!!LDFLAGS! -o !tpl!.exe !tpl!.obj !objs! !libs!
        ) else (
          set CMD=!LD!!LDFLAGS! -o !tpl!.exe !tpl!.obj !libs!
        )
      )
    )
    if defined objs (
      echo.&echo *** Linking: !tpl!.obj !objs!
    ) else (
      echo.&echo *** Linking: !tpl!.obj
    )
    echo !CMD!
    call !CMD!
    if defined d (
      if not exist !tpl!.dll (
        goto ERROR
      )
      echo.&echo Successfully built '!tpl!.dll'.
      goto SUCCESS
    ) else (
      if not exist !tpl!.exe (
        goto ERROR
      )
      echo.&echo Successfully built '!tpl!.exe'.
      goto SUCCESS
    )
  )
)
:SUCCESS
goto EOF
:ERROR
echo.&echo Error: Unable to build.
echo.&echo COMSPEC=%COMSPEC%.
echo.&echo PATH=%PATH%.
echo.&echo ADMB_HOME: !ADMB_HOME!
goto EOF
:HELP
echo Builds AD Model Builder executable or library.
echo.
echo Usage: admb [-c] [-d] [-g] [-r] [-f] model [src(s)]
echo.
echo  -c     Build only object file(s) (.obj).
echo  -d     Build a dynamic library (.dll).
echo  -g     Build with debug symbols.
echo  -r     Build Random effects library (ADMB-RE).
echo  -f     Build with Fast optimized mode library (no error checking).
echo         By default, admb script will include error checking in the build.
echo  model  TPL file (ie 'simple.tpl' or the filename 'simple' with no .tpl
echo         extension)
echo  src(s) C/C++ Source file(s) containing classes, methods and variables that
echo         are used in model.
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
