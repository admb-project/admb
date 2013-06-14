@REM @setlocal

@for /F %%a in ('type ..\VERSION') do @set Version=%%a

@set checkpath=%PATH:;=" "%
@for %%i in ("%checkpath%") do @if exist %%~isvnversion.exe @for /F %%a in ('svnversion') do @set SvnVersion=.%%a

@REM @set Compiler=unknown
@REM @if "%VSINSTALLDIR%"=="%ProgramFiles%\Microsoft Visual Studio 10.0\" set Compiler=vc10

@set Arch=32bit
@if defined FrameworkDIR64 set Arch=64bit

@set DEST=build\admb-%Version%%SvnVersion%-%Compiler%-%Arch%

:end
@REM @endlocal
