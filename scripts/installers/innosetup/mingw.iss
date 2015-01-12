[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB (MinGW GCC 4.5.0)
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=..\..\..
OutputBaseFilename=admb-10.0-mingw-gcc4.5.0-32bit
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE
AlwaysShowComponentsList=no

[Types]
Name: "mingw"; Description: "ADMB (MinGW GCC 4.5.0)"

[Files]
Source: "..\..\..\build\admb-10.0-mingw-gcc4.5.0-32bit\admb-10.0-mingw-gcc4.5.0-32bit\*"; DestDir: "{app}"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (MinGW GCC 4.5.0)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-mingw.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (MinGW GCC 4.5.0)"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
