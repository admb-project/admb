cd build\dists\admb_b502_win32
set ADMB_HOME=%CD%
set BCC55_HOME=C:\borland\bcc55
set PATH=%ADMB_HOME%\bin;%BCC55_HOME%\bin;%PATH%
make 
