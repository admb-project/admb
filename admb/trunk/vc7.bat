call "%VS71COMNTOOLS%vsvars32.bat"
call "enviroment.bat"

set DISK=build/dists/admb_vc7_win32
set CCVERSION=vc7
set OSVERSION=win32
make vc
