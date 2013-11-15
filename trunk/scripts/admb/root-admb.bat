@echo off
@REM 
@REM  Copyright 2013 (c) ADMB Foundation
@REM 

setlocal EnableExtensions EnableDelayedExpansion

for %%a in (%0.bat) do (
  set HAS_PATH=%%~$PATH:a
  if not "!HAS_PATH!"=="" (
    set ADMB_PATH=%%~dp$PATH:a
  ) else (
    set ADMB_PATH=%%~dpa
  )
)
if exist !ADMB_PATH!\bin\admb.bat (
  set ADMB_HOME=!ADMB_PATH!
  call "!ADMB_HOME!\bin\admb.bat" %*
) else (
  if exist !ADMB_PATH!build\dist\bin\admb.bat (
    set ADMB_HOME=!ADMB_PATH!build\dist
    call "!ADMB_HOME!\bin\admb.bat" %*
  )
)
exit 0
