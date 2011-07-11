@echo off
setlocal
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP

rem Pop args until model=%1
set adlib=-lado
set df1b2lib=-ldf1b2o
set linker=g++
set sym=-s & rem space
set i=0
:STARTLOOP
if [%2]==[] goto ENDLOOP
if %1==-d set linker=dllwrap& shift
if %1==-g set sym=& shift
if %1==-r shift
if %1==-s set adlib=-lads& set df1b2lib=-ldf1b2s& shift
set /a i=%i%+1
if %i%==100 shift & set i=0 & echo.&echo Warning: illegal option %1 (discarded)
goto STARTLOOP
:ENDLOOP

set def=
set model=%~n1
if %linker%==g++ (set out=-o %model%) else (set def=-def %model%.def^
 --driver-name g++ & set out=--output-lib lib%model%.a -o %model%.dll)

set CMD=%linker% %sym%-static %def%-L"%ADMB_HOME%\lib" %model%.obj %df1b2lib%^
 -ladmod -ladt %adlib% %df1b2lib% -ladmod -ladt %adlib% %out%
echo %CMD%
%CMD%

goto EOF

:HELP
echo Usage: adlink [-d] [-g] [-r] [-s] model
echo.
echo Link AD Model Builder object code to executable, using the MinGW GCC^
 compiler.
echo.
echo   -d     Create DLL
echo   -g     Insert debugging symbols
echo   -r     Create ADMB-RE
echo   -s     Enforce safe bounds
echo   model  Filename prefix, e.g. simple
echo.

:EOF

REM r985 [2011-02-17] arnima  changed sym=-g to sym=[space], fixed spaces
REM r982 [2011-02-16] arnima  rewrite, fixed bug when user option is not
REM                           recognized, enabled strip and debug, fixed spaces
REM r917 [2010-12-24] johnoel pruned 'mingw' dir
REM r914 [2010-12-24] johnoel changed \\lib to \lib and echo off to @echo off,
REM                           moved to 'g++' dir
REM r629 [2010-05-20] johnoel changed .o to .obj
REM r623 [2010-05-20] johnoel changed /lib to \\lib, disabled strip
REM r593 [2010-04-20] johnoel quoted ADMB_HOME
REM r567 [2010-04-16] johnoel fixed bugs in r563
REM r564 [2010-04-15] johnoel fixed bugs in r563
REM r563 [2010-04-15] johnoel simplified echo, disabled -ldf1b2stub
REM r525 [2009-08-07] arnima  added support for filename extension like
REM                           simple.obj, unquoted ADMB_HOME, added -static
REM                   johnoel split -s option into separate -g and -s options
REM r244 [2009-05-28] arnima  created
