set ADMB_HOME=..\..\build\dists\admb_gcc345_mingw32
set GNUWIN32_HOME=%ProgramFiles%\GNUWIN32
set MINGW_HOME=C:\MinGW
set CYGWIN_HOME=C:\cygwin
set PATH=%ADMB_HOME%\bin;%GNUWIN32_HOME%\bin;%MINGW_HOME%\bin;%CYGWIN_HOME%\bin;%PATH%

tpl2cpp simple
tpl2cpp simple-eof
