@echo off
@REM
@REM  Copyright 2013 (c) ADMB Foundation
@REM

setlocal EnableExtensions EnableDelayedExpansion

set SCRIPT_PATH=%~dp0
if not defined SCRIPT_PATH (
  for %%a in (%0) do (
    set SCRIPT_PATH=%%~dp$PATH:a
  )
) 
if not defined SCRIPT_PATH (
  echo "SCRIPT_PATH: !SCRIPT_PATH!"
  goto ERROR
)
pushd !SCRIPT_PATH!
set ADMB_PATH=!CD!
popd
if exist !ADMB_PATH!\bin\admb.cmd (
  set ADMB_HOME=!ADMB_PATH!
) else (
  if exist !ADMB_PATH!\build\debug\bin\admb.cmd (
    set ADMB_HOME=!ADMB_PATH!\build\debug
  )
)
if not defined ADMB_HOME (
  echo "ADMB_HOME: !ADMB_HOME!"
  goto ERROR
)
call "!ADMB_HOME!\bin\admb" %*
goto EOF
:ERROR
echo Error: Unable to find 'bin\admb.cmd'.
:EOF
