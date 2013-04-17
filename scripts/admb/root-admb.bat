@echo off

setlocal EnableExtensions EnableDelayedExpansion

for %%a in (%0.bat) do (
  set HAS_PATH=%%~$PATH:a
  if not "!HAS_PATH!"=="" (
    set ADMB_PATH=%%~dp$PATH:a
  ) else (
    set ADMB_PATH=%%~dpa
  )
  if exist !ADMB_PATH!build\dist\bin\admb.bat (
    set ADMB_HOME=!ADMB_PATH!build\dist
  ) else (
    pushd !ADMB_PATH!\..
    set ADMB_HOME=!CD!
    popd
  )
  if exist !ADMB_PATH!utilities\mingw\bin\g++.exe (
    PATH=!ADMB_PATH!utilities\mingw\bin;"%PATH%"
  )
  call !ADMB_HOME!\bin\admb.bat %*
)
