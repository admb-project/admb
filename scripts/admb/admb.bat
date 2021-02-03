@echo off
@REM
@REM  Copyright 2013-2020 (c) ADMB Foundation
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
) else (
  set "PATH=!ADMB_HOME!\bin;!PATH!"
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
    if "!arg!"=="-f" (
      set fast= -f
    )
    if "!arg!"=="-g" (
      set g= -g
    )
    if "!arg!"=="-r" (
      set r = -r
      set parser=tpl2rem
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

if "!CXX!"=="" (
  for /f "tokens=*" %%i in ('where cl.exe 2^>^&1 ^| findstr "cl.exe"') do (
    set CXX=cl
  )
) else (
  if "!CXX!"=="cl" (
    for /f "tokens=*" %%i in ('where cl.exe 2^>^&1 ^| findstr "Could not find file"') do (
      set CXX=
    )
  )
)
if "!CXX!"=="cl" (
  pushd !ADMB_HOME!\lib
  for /f "tokens=*" %%i in ('dir /B admb*-cl*.lib 2^>^&1 ^| findstr "File Not Found"') do (
    set CXX=
  )
  popd
)
if "!CXX!"=="cl" (
  where /Q !CXX!
  if errorlevel 1 (
    echo Error: Unable to find !CXX!
    exit /B 1
  )
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
  for /f "tokens=*" %%i in ('!CXX! 2^>^&1 ^| findstr "Compiler Version 19."') do (
    set CXXVERSION=-cl19
    for /f "tokens=*" %%i in ('!CXX! 2^>^&1 ^| findstr "x64"') do (
      set OSNAME=-win64
    )
    for /f "tokens=*" %%i in ('!CXX! 2^>^&1 ^| findstr "x86"') do (
      set OSNAME=-win32
    )
  )
  if not defined CXXVERSION (
    set CXXVERSION=-cl
  )
  if not defined OSNAME (
    set OSNAME=-win
  )
  if exist "!ADMB_HOME!\bin\admb-cfg!OSNAME!!CXXVERSION!.bat" (
    call "!ADMB_HOME!\bin\admb-cfg!OSNAME!!CXXVERSION!.bat"
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
  if defined fast (
    set CXXFLAGS=!CXXFLAGS! /nologo /DOPT_LIB
    if defined g (
      if exist "!ADMB_HOME!\lib\admb-contribo!OSNAME!!CXXVERSION!-debug.lib" (
        set libs="!ADMB_HOME!\lib\admb-contribo!OSNAME!!CXXVERSION!-debug.lib" /link
	set use_contrib_lib=yes
      ) else (
        if exist "!ADMB_HOME!\lib\admbo!OSNAME!!CXXVERSION!-debug.lib" (
          set libs="!ADMB_HOME!\lib\admbo!OSNAME!!CXXVERSION!-debug.lib" /link
        )
      )
    )
    if not defined libs (
      if exist "!ADMB_HOME!\lib\admb-contribo!OSNAME!!CXXVERSION!.lib" (
        set libs="!ADMB_HOME!\lib\admb-contribo!OSNAME!!CXXVERSION!.lib" /link
	set use_contrib_lib=yes
      ) else (
        set libs="!ADMB_HOME!\lib\admbo!OSNAME!!CXXVERSION!.lib" /link
      )
    )
  ) else (
    if defined g (
      if exist "!ADMB_HOME!\lib\admb-contrib!OSNAME!!CXXVERSION!-debug.lib" (
        set libs="!ADMB_HOME!\lib\admb-contrib!OSNAME!!CXXVERSION!-debug.lib" /link
	set use_contrib_lib=yes
      ) else (
        if exist "!ADMB_HOME!\lib\admb!OSNAME!!CXXVERSION!-debug.lib" (
          set libs="!ADMB_HOME!\lib\admb!OSNAME!!CXXVERSION!-debug.lib" /link
        )
      )
    )
    if not defined libs (
      if exist "!ADMB_HOME!\lib\admb-contrib!OSNAME!!CXXVERSION!.lib" (
        set libs="!ADMB_HOME!\lib\admb-contrib!OSNAME!!CXXVERSION!.lib" /link
	set use_contrib_lib=yes
      ) else (
        set libs="!ADMB_HOME!\lib\admb!OSNAME!!CXXVERSION!.lib" /link
      )
    )
  )
  if defined use_contrib_lib (
    set CXXFLAGS=!CXXFLAGS! /DUSE_ADMB_CONTRIBS /D_USE_MATH_DEFINES /I. /I"!ADMB_HOME!\include" /I"!ADMB_HOME!\include\contrib"
  ) else (
    set CXXFLAGS=!CXXFLAGS! /D_USE_MATH_DEFINES /I. /I"!ADMB_HOME!\include"
  )
) else (
  if "!CXX!"=="clang++" (
    for /f %%i in ('!CXX! -dumpversion ^| findstr /b 9.') do (
      set CXXMAJORNUMBER=-clang++9
      set STDCXX=-std=c++11
    )
    set LD=clang++
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
    where /Q !CXX!
    if errorlevel 1 (
      set "SHORT_SCRIPT_PATH=%~dps0"
      if exist "!SHORT_SCRIPT_PATH!..\utilities\mingw\bin\g++.exe" (
        set "PATH=!SHORT_SCRIPT_PATH!..\utilities\mingw\bin;!PATH!"
      ) else (
        echo Error: Unable to find !CXX!
        exit /B 1
      )
    )
    for /f %%i in ('!CXX! -dumpversion ^| findstr /b 4.') do (
      set CXXMAJORNUMBER=-g++4
      set STDCXX=-std=c++11
    )
    for /f %%i in ('!CXX! -dumpversion ^| findstr /b 5.') do (
      set CXXMAJORNUMBER=-g++5
      set STDCXX=-std=c++14
    )
    for /f %%i in ('!CXX! -dumpversion ^| findstr /b 6.') do (
      set CXXMAJORNUMBER=-g++6
      set STDCXX=-std=c++14
    )
    for /f %%i in ('!CXX! -dumpversion ^| findstr /b 7.') do (
      set CXXMAJORNUMBER=-g++7
      set STDCXX=-std=c++14
    )
    for /f %%i in ('!CXX! -dumpversion ^| findstr /b 8.') do (
      set CXXMAJORNUMBER=-g++8
      set STDCXX=-std=c++14
    )
    for /f %%i in ('!CXX! -dumpversion ^| findstr /b 9.') do (
      set CXXMAJORNUMBER=-g++9
      set STDCXX=-std=c++14
    )
    for /f %%i in ('!CXX! -dumpversion ^| findstr /b 10.') do (
      set CXXMAJORNUMBER=-g++10
      set STDCXX=-std=c++14
    )
  )
  if defined CXXFLAGS (
    set CXXFLAGS= -c !STDCXX! !CXXFLAGS!
  ) else (
    set CXXFLAGS= -c !STDCXX!
  )
  if defined d (
    if defined LDFLAGS (
      set LDFLAGS= -shared !LDFLAGS!
    ) else (
      set LDFLAGS= -shared
    )
  )
  if defined g (
    set CXXFLAGS=!CXXFLAGS! -g
    set LDFLAGS=!LDFLAGS! -g
  ) else (
    set CXXFLAGS=!CXXFLAGS! -O3
  )
  if "!CXX!"=="clang++" (
    for /f %%i in ('!CXX! -dumpmachine ^| findstr /b i686') do (
      set CXXVERSION=-win32!CXXMAJORNUMBER!
    )
    for /f %%i in ('!CXX! -dumpmachine ^| findstr /b x86_64') do (
      set CXXVERSION=-win64!CXXMAJORNUMBER!
    )
  ) else (
    if "!CXX!"=="g++" (
      for /f %%i in ('!CXX! -dumpmachine ^| findstr /b i686') do (
        set CXXVERSION=-mingw32!CXXMAJORNUMBER!
      )
      for /f %%i in ('!CXX! -dumpmachine ^| findstr /b x86_64') do (
        set CXXVERSION=-mingw64!CXXMAJORNUMBER!
      )
    )
  )
  if defined LDFLAGS (
    set LDFLAGS= -static !LDFLAGS!
  ) else (
    set LDFLAGS= -static
  )
  if exist "!ADMB_HOME!\bin\admb-cfg!CXXVERSION!.bat" (
    call "!ADMB_HOME!\bin\admb-cfg!CXXVERSION!.bat"
    if defined ADMB_CFG_CXXFLAGS (
      set CXXFLAGS=!CXXFLAGS! !ADMB_CFG_CXXFLAGS!
    )
    if defined ADMB_CFG_LD (
      if not defined d (
        set LD=!ADMB_CFG_LD!
      )
    )
    if defined ADMB_CFG_LDFLAGS (
      set LDFLAGS=!LDFLAGS!!ADMB_CFG_LDFLAGS:-static=!
    )
  )
  if defined g (
    if defined fast (
      set CXXFLAGS=!CXXFLAGS! -DOPT_LIB
      if exist "!ADMB_HOME!\lib\libadmb-contribo!CXXVERSION!-debug.a" (
        set libs="!ADMB_HOME!\lib\libadmb-contribo!CXXVERSION!-debug.a"
	set use_contrib_lib=yes
      ) else (
        if exist "!ADMB_HOME!\lib\libadmbo!CXXVERSION!-debug.a" (
          set libs="!ADMB_HOME!\lib\libadmbo!CXXVERSION!-debug.a"
        ) else (
          if exist "!ADMB_HOME!\lib\libadmb-contribo!CXXVERSION!.a" (
            set libs="!ADMB_HOME!\lib\libadmb-contribo!CXXVERSION!.a"
	    set use_contrib_lib=yes
          ) else (
            if exist "!ADMB_HOME!\lib\libadmbo!CXXVERSION!.a" (
              set libs="!ADMB_HOME!\lib\libadmbo!CXXVERSION!.a"
            ) else (
              echo Error: Unable to find ADMB DEBUG library 'libadmbo!CXXVERSION!.a'
              exit /B 1
            )
          )
        ) 
      )
    ) else (
      if exist "!ADMB_HOME!\lib\libadmb-contrib!CXXVERSION!-debug.a" (
        set libs="!ADMB_HOME!\lib\libadmb-contrib!CXXVERSION!-debug.a"
	set use_contrib_lib=yes
      ) else (
        if exist "!ADMB_HOME!\lib\libadmb!CXXVERSION!-debug.a" (
          set libs="!ADMB_HOME!\lib\libadmb!CXXVERSION!-debug.a"
        ) else (
          if exist "!ADMB_HOME!\lib\libadmb-contrib!CXXVERSION!.a" (
            set libs="!ADMB_HOME!\lib\libadmb-contrib!CXXVERSION!.a"
	    set use_contrib_lib=yes
          ) else (
            if exist "!ADMB_HOME!\lib\libadmb!CXXVERSION!.a" (
              set libs="!ADMB_HOME!\lib\libadmb!CXXVERSION!.a"
            ) else (
              echo Error: Unable to find ADMB DEBUG library 'libadmb!CXXVERSION!.a'
              exit /B 1
            )
          )
        ) 
      )
    )
  ) else (
    if defined fast (
      set CXXFLAGS=!CXXFLAGS! -DOPT_LIB
      if exist "!ADMB_HOME!\lib\libadmb-contribo!CXXVERSION!.a" (
        set libs="!ADMB_HOME!\lib\libadmb-contribo!CXXVERSION!.a"
	set use_contrib_lib=yes
      ) else (
        if exist "!ADMB_HOME!\lib\libadmbo!CXXVERSION!.a" (
          set libs="!ADMB_HOME!\lib\libadmbo!CXXVERSION!.a"
        ) else (
          if exist "!ADMB_HOME!\lib\libadmb-contribo!CXXVERSION!-debug.a" (
            set libs="!ADMB_HOME!\lib\libadmb-contribo!CXXVERSION!-debug.a"
	    set use_contrib_lib=yes
          ) else (
            if exist "!ADMB_HOME!\lib\libadmbo!CXXVERSION!-debug.a" (
              set libs="!ADMB_HOME!\lib\libadmbo!CXXVERSION!-debug.a"
            ) else (
              echo Error: Unable to find ADMB library 'libadmbo!CXXVERSION!.a'
              exit /B 1
            )
          )
        ) 
      )
    ) else (
      if exist "!ADMB_HOME!\lib\libadmb-contrib!CXXVERSION!.a" (
        set libs="!ADMB_HOME!\lib\libadmb-contrib!CXXVERSION!.a"
	set use_contrib_lib=yes
      ) else (
        if exist "!ADMB_HOME!\lib\libadmb!CXXVERSION!.a" (
          set libs="!ADMB_HOME!\lib\libadmb!CXXVERSION!.a"
        ) else (
          if exist "!ADMB_HOME!\lib\libadmb-contrib!CXXVERSION!-debug.a" (
            set libs="!ADMB_HOME!\lib\libadmb-contrib!CXXVERSION!-debug.a"
	    set use_contrib_lib=yes
          ) else (
            if exist "!ADMB_HOME!\lib\libadmb!CXXVERSION!-debug.a" (
              set libs="!ADMB_HOME!\lib\libadmb!CXXVERSION!-debug.a"
            ) else (
              echo Error: Unable to find ADMB library 'libadmb!CXXVERSION!.a'
              exit /B 1
            )
          )
        ) 
      )
    )
  )
  set CXXFLAGS=!CXXFLAGS! -fpermissive
  for /f %%i in ('!CXX! -dumpmachine ^| findstr x86_64') do (
    set CXXFLAGS=!CXXFLAGS! -D_FILE_OFFSET_BITS=64
  )
  if defined d (
    set CXXFLAGS=!CXXFLAGS! -DBUILDING_DLL
  )
  if defined use_contrib_lib (
    set CXXFLAGS=!CXXFLAGS! -DUSE_ADMB_CONTRIBS -D_USE_MATH_DEFINES -I. -I"!ADMB_HOME!\include" -I"!ADMB_HOME!\include\contrib"
  ) else (
    set CXXFLAGS=!CXXFLAGS! -D_USE_MATH_DEFINES -I. -I"!ADMB_HOME!\include"
  )
)
if exist "!CD!\echo" (
  echo.&echo Warning: File 'echo' should not be in !CD!.
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
  del admb.log 2> NUL
  if defined d (
    set dll= -dll
  )
  if defined g (
    set debug= -debug
  )
  where /Q sed.exe
  if errorlevel 1 (
    set "SHORT_SCRIPT_PATH=%~dps0"
    if exist "!SHORT_SCRIPT_PATH!..\utilities\sed.exe" (
      set "PATH=!SHORT_SCRIPT_PATH!..\utilities;!PATH!"
    ) else (
      if exist "!SHORT_SCRIPT_PATH!..\..\..\utilities\sed.exe" (
        set "PATH=!SHORT_SCRIPT_PATH!..\..\..\utilities;!PATH!"
      ) else (
        echo Error: Unable to find sed.exe
        exit /B 1
      )
    )
  )
  echo.&echo *** Parse: !tpl!.tpl
  if defined parser (
    set CMD=!parser! !debug! !dll! !tpl!
    echo !CMD!
    call !CMD!
  ) else (
    set CMD=tpl2cpp !debug! !dll! !tpl!
    call !CMD! 2> admb.log
    if not exist !tpl!.cpp (
      set CMD=tpl2rem !debug! !dll! !tpl!
      call !CMD! 2> admb.log
    ) 
    if exist !tpl!.cpp (
      if exist !tpl!.htp (
        echo !CMD!
      )
    )
  )
  if not exist !tpl!.cpp (
    echo.&echo Error: Unable to parse "!tpl!.tpl".
    type admb.log
    goto ERROR
  )
  del admb.log 2> NUL
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
          set CMD=!LD!!LDFLAGS! /nologo /Fe!main!.exe !objs! !libs!
        ) else (
          set CMD=!LD!!LDFLAGS! -o !main!.exe !objs! !libs!
        )
      )
      echo.&echo *** Linking: !objs!
      echo !CMD!
      call !CMD! || goto ERROR
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
          set CMD=!LD!!LDFLAGS! /nologo /Fe!tpl!.exe !tpl!.obj !objs! !libs!
        ) else (
          set CMD=!LD!!LDFLAGS! /nologo /Fe!tpl!.exe !tpl!.obj !libs!
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
    call !CMD! || goto ERROR
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
echo Release Version: 12.2
echo Location: %~dp0
echo.
echo Usage: admb [-c] [-d] [-f] [-g] [-r] model [src(s)]
echo.
echo Options:
echo  -c     Build only object file(s) (.obj).
echo  -d     Build a dynamic library (.dll).
echo  -f     Build with fast optimized mode library (no bounds checking).
echo  -g     Build with debug symbols.
echo  -p     Build portable model executable (-p has no effect in Windows).
echo  -r     Build with random effects library (ADMB-RE).
echo  model  TPL file, i.e. 'simple.tpl' or 'simple' with no .tpl extension.
echo  src(s) C/C++ source file(s) containing classes, methods and variables.
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
EXIT /B
