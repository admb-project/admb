[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB (MinGW G++)
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=..\..\..\build
OutputBaseFilename=admb-mingw-g++
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE.txt
AlwaysShowComponentsList=no

[Types]
Name: "mingw"; Description: "ADMB (MinGW G++)"

[Files]
Source: "..\..\..\build\dist\*"; DestDir: "{app}"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs
Source: "..\..\..\scripts\mingw\set-admb-mingwmak.bat"; DestDir: "{app}\bin"
Source: "..\..\..\scripts\g++\adcomp.bat"; DestDir: "{app}\bin"
Source: "..\..\..\scripts\g++\adlink.bat"; DestDir: "{app}\bin"
Source: "..\..\..\scripts\admb\admb.bat"; DestDir: "{app}\bin"
Source: "..\..\..\utilities\*"; DestDir: "{app}\utilities"
Source: "c:\MinGW\*"; DestDir: "{app}\MinGW\"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (MinGW G++)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-mingwmak.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (MinGW G++)"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
