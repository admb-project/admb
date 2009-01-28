call "%VS80COMNTOOLS%vsvars32.bat"
cd build\dists\admb_vc8_win32
set ADMB_HOME=%CD%
set PATH=%ADMB_HOME%\bin;%PATH%
set MSSDK=%ProgramFiles%\Microsoft^ Platform^ SDK^ for^ Windows^ Server^ 2003^ R2
nmake
