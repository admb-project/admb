[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB (MinGW64)
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=..\..\..\build
OutputBaseFilename=admb-mingw64
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE.txt
AlwaysShowComponentsList=no

[Types]
Name: "mingw"; Description: "ADMB (MinGW64)"

[Files]
Source: "..\..\..\build\dist\*"; DestDir: "{app}"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs
Source: "..\..\..\scripts\mingw\set-admb-mingw.bat"; DestDir: "{app}\bin"
Source: "..\..\..\scripts\admb\adcomp.bat"; DestDir: "{app}\bin"
Source: "..\..\..\scripts\admb\adlink.bat"; DestDir: "{app}\bin"
Source: "..\..\..\scripts\admb\admb.bat"; DestDir: "{app}\bin"
Source: "..\..\..\utilities\*"; DestDir: "{app}\utilities"

[Icons]
Name: "{group}\ADMB Command Prompt (MinGW64)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-mingw.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (MinGW64)"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB (MinGW64)"
