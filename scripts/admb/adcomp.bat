@echo off
setlocal EnableExtensions EnableDelayedExpansion
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP

rem Pop args until model=%1
set dll=
set safopt=-DSAFE_ALL
set sym=-O3
set i=0
:STARTLOOP
if [%2]==[] goto ENDLOOP
if %1==-d set dll=-DBUILDING_DLL & shift
if %1==-g set sym=-g& shift
if %1==-r shift
if %1==-f set safopt=-DOPT_LIB& shift
set /a i=%i%+1
if %i%==100 shift & set i=0 & echo.&echo Warning: illegal option %1 (discarded)
goto STARTLOOP
:ENDLOOP

set model=%~n1

if exist "%ADMB_HOME%"\bin\admb-cfg.bat call "%ADMB_HOME%"\bin\admb-cfg.bat
if defined CXXFLAGS (
  set CXXFLAGS=%CXXFLAGS% %ADMB_CFG_CXXFLAGS%
) else (
  set CXXFLAGS=%ADMB_CFG_CXXFLAGS%
)

set CMD=g++ -c %CXXFLAGS% %sym% -D__GNUDOS__ %dll% -Dlinux %safopt% -DUSE_LAPLACE -fpermissive -I. -I"%ADMB_HOME%\include" -I"%ADMB_HOME%\contrib\include" -o %model%.obj %model%.cpp
echo %CMD%
%CMD%

goto EOF

:HELP
echo Usage: adcomp [-d] [-g] [-r] [-f] model
echo.
echo Compile AD Model Builder C++ to object code, using the MinGW GCC compiler.
echo.
echo   -d     Build a dynamic library (dll).
echo   -g     Build with debug symbols.
echo   -r     Build Random effects program (ADMB-RE).
echo   -f     Build with Fast optimized mode (no bounds checking).
echo          By default, admb script builds with bounds checking.
echo   model  TPL file (ie 'simple.tpl' or the filename 'simple' with no .tpl extension)
echo.

:EOF

REM r982 [2011-02-16] arnima  rewrite, fixed bug when user option is not
REM                           recognized, added CXXFLAGS, fixed spaces
REM r917 [2010-12-24] johnoel pruned 'mingw' dir
REM r914 [2010-12-24] johnoel changed \\include to \include and echo off to
REM                           @echo off, moved to 'g++' dir
REM r629 [2010-05-20] johnoel changed .o to .obj
REM r623 [2010-05-20] johnoel changed /include to \\include
REM r593 [2010-04-20] johnoel quoted ADMB_HOME
REM r563 [2010-04-15] johnoel simplified echo, added -DSAFE_ALL
REM r525 [2009-08-07] arnima  added support for filename extension like
REM                           simple.cpp, unquoted ADMB_HOME, enabled warnings
REM                   johnoel split -s option into separate -g and -s options,
REM                           if -g then not -O3
REM r244 [2009-05-28] arnima  created
