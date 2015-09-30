@echo off
@REM
@REM  Copyright 2013 (c) ADMB Foundation
@REM
setlocal EnableExtensions EnableDelayedExpansion
set args=
for %%a in (%*) do (
  set arg=%%a
  if "!arg:~0,1!"=="-" (
      set args=!args! !arg!
  ) else (
    if "%%~xa"=="" (
      set args=!args! !arg!.obj
    ) else (
      set args=!args! !arg!
    )
  )
)
call admb !args!
