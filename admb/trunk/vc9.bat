call "%VS90COMNTOOLS%vsvars32.bat"
call "enviroment.bat"

set DISK=../build/dists/admb_vc9_win32
set CCVERSION=vc9
set OSVERSION=win32

make vc
