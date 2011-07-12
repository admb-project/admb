del %ADMB32_HOME%\include\oclutils.h
del %ADMB32_HOME%\include\shrutils.h
del %ADMB32_HOME%\include\cmd_arg_reader.h
del %ADMB32_HOME%\include\adpar32.h

del %ADMB32_HOME%\lib\oclutils32.lib
del %ADMB32_HOME%\lib\shrutils32.lib
del %ADMB32_HOME%\lib\adpar32.lib
del %ADMB32_HOME%\lib\OpenCL.lib

del /q %ADMB32_HOME%\examples\admb\simple-gpu\*.*
del /q %ADMB32_HOME%\include\CL\*.*

pushd "%~dp0"
cd %ADMB32_HOME%
del /q ..\objects\openCL\*.*
popd
