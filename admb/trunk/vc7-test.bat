cd build\dists\admb_vc7_win32
pwd
call bin\set-admb-vc7.bat
cd "%ADMB_HOME%\examples\admb"
nmake
