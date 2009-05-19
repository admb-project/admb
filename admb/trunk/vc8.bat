call "%VS80COMNTOOLS%vsvars32.bat"
call "enviroment.bat"
set MSSDK=%ProgramFiles%\Microsoft^ Platform^ SDK^ for^ Windows^ Server^ 2003^ R2

set DISK=../build/dists/admb_vc8_win32
set CCVERSION=vc8
set OSVERSION=win32

make vc
