@echo off

pushd build

IF EXIST dist (
  move dist admb 
  call "%ProgramFiles%\7-Zip\7z" a -tzip ..\admb.zip admb
  move admb dist
) ELSE (
  IF EXIST debug (
    move debug admb
    call "%ProgramFiles%\7-Zip\7z" a -tzip ..\admb.zip admb
    move admb debug
  )
)

popd
