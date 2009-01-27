cd build\dists\admb_vc8_win32
set ADMB_HOME=%CD%
set PATH=%ADMB_HOME%\bin;%PATH%
call "%VS90COMNTOOLS%vsvars32.bat"
nmake
