[Setup]
PrivilegesRequired=none
AppName=ADMB-11
AppVerName=ADMB-11
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={pf}\ADMB-11
DefaultGroupName=ADMB-11 (MinGW G++)
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=..\..\..\build
OutputBaseFilename=admb-mingw-g++
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE.txt
AlwaysShowComponentsList=no

[Types]
Name: "mingw"; Description: "ADMB-11 (MinGW G++)"

[Files]
Source: "..\..\..\build\mingw\*"; DestDir: "{app}"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB-11 Command Prompt (MinGW G++)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-mingw.bat"""; WorkingDir: "{app}"; Comment: "ADMB-11 Command Prompt (MinGW G++)"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB-11"
