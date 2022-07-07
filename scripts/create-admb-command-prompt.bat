@echo off

if exist "build\admb\bin\admb.cmd" (
  scripts\create-admb-command-prompt.vbs %CD%\build\admb
) else (
  if exist "bin\admb.cmd" (
    ..\..\scripts\create-admb-command-prompt.vbs %CD%
  )
)
