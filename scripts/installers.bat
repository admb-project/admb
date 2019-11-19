@echo off

IF EXIST dist (
  move dist admb 
  call "%C:\Program Files\7-Zip\7z" a -tzip ..\admb.zip admb
  move admb dist
) ELSE (
  IF EXIST debug (
    move debug admb
    call "C:\Program Files\7-Zip\7z" a -tzip ..\admb.zip admb
    move admb debug
  )
)
