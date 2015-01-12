@echo off
setlocal
if [%1]==[] goto HELP
if [%1]==[-help] goto HELP
if [%1]==[--help] goto HELP

rem Pop args until model=%1
set bounds=
set d=
set dll=
set g=
set r=
set s=
set tpl2cpp=tpl2cpp
set i=0
:STARTLOOP
if [%2]==[] goto ENDLOOP
if %1==-d set d=-d & set dll=-dll & shift
if %1==-g set g=-g & shift
if %1==-r set r=-r & set tpl2cpp=tpl2rem& shift
if %1==-s set s=-s & set bounds=-bounds & shift
set /a i=%i%+1
if %i%==100 shift & set i=0 & echo.&echo Warning: illegal option %1 (discarded)
goto STARTLOOP
:ENDLOOP

set model=%~n1
if not exist %model%.tpl goto ERROR1
del %model%.cpp %model%.htp %model%.obj %model%.exe 2> NUL

set CMD=%tpl2cpp% %bounds%%dll%%model%
echo.&echo *** %CMD%
%CMD%
if not exist %model%.cpp set ext=cpp& goto ERROR2
if not exist %model%.htp set ext=htp& goto ERROR2

set CMD=adcomp %d%%g%%r%%s%%model%
echo.&echo *** %CMD%
call %CMD%
if not exist %model%.obj set ext=obj& goto ERROR2

set CMD=adlink %d%%g%%r%%s%%model%
echo.&echo *** %CMD%
call %CMD%
if defined dll (if not exist %model%.dll set ext=dll& goto ERROR2)
if not defined dll (if not exist %model%.exe set ext=exe& goto ERROR2)

echo.&echo Done
goto EOF

:HELP
echo Usage: admb [-d] [-g] [-r] [-s] model
echo.
echo Build AD Model Builder executable from TPL.
echo.
echo   -d     Create DLL
echo   -g     Insert debugging symbols
echo   -r     Create ADMB-RE
echo   -s     Enforce safe bounds
echo   model  Filename prefix, e.g. simple
echo.
goto EOF

:ERROR1
echo.&echo Error: %model%.tpl not found
goto EOF

:ERROR2
echo.&echo Error: could not create %model%.%ext%
goto EOF

:EOF

REM r982 [2011-02-16] arnima  rewrite, fixed bug when user option is not
REM                           recognized, fixed spaces, improved messages
REM r927 [2010-12-24] johnoel moved to 'admb' dir
REM r917 [2010-12-24] johnoel pruned 'mingw' dir
REM r914 [2010-12-24] johnoel changed script so it deletes cpp/htp/obj/exe and
REM                           reports error or success, moved to 'g++' dir
REM r629 [2010-05-20] johnoel changed .o to .obj
REM r623 [2010-05-20] johnoel changed script so it exits if tpl/cpp/htp/o/exe do
REM                           not exist
REM r525 [2009-08-07] arnima  added support for filename extension like
REM                           simple.tpl
REM                   johnoel split -s option into separate -g and -s options
REM r244 [2009-05-28] arnima  created
