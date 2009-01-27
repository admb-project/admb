call "c:\Progra~1\Mid05a~1\VC\vcvarsall.bat"
cd build\dists\admb_vc8_win32
set ADMB_HOME=%CD%
set PATH=%ADMB_HOME%\bin;%PATH%
nmake
