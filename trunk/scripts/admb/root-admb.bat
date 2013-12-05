@echo off
@REM
@REM  Copyright 2013 (c) ADMB Foundation
@REM

setlocal EnableExtensions EnableDelayedExpansion

for %%a in (%0) do (
  set HAS_PATH=%%~$PATH:a
  if defined HAS_PATH (
    set ADMB_PATH=%%~dp$PATH:a
  ) else (
    set ADMB_PATH=%%~dpa
  )
  if exist !ADMB_PATH!bin\admb.cmd (
    set ADMB_HOME=!ADMB_PATH:~0,-1!
    call "!ADMB_HOME!\bin\admb" %*
  ) else (
    if exist !ADMB_PATH!build\dist\bin\admb.cmd (
      set ADMB_HOME=!ADMB_PATH!build\dist
      call "!ADMB_HOME!\bin\admb" %*
    ) else (
      echo "Error: Unable to find ADMB_HOME\bin\admb.cmd."
      goto EOF
    )
  )
  goto EOF
)
:EOF
