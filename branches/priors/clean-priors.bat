del %ADMB32_HOME%\include\priorsLib.h

del %ADMB32_HOME%\lib\priors.lib

pushd "%~dp0"
cd %ADMB32_HOME%
del /q ..\objects\priors-slp\*.*
del /q ..\objects\priors-olp\*.*
popd
