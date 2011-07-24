del %ADMB32_HOME%\include\statsLib.h

del %ADMB32_HOME%\lib\stats.lib

pushd "%~dp0"
cd %ADMB32_HOME%
del /q ..\objects\stats-slp\*.*
del /q ..\objects\stats-olp\*.*
popd
