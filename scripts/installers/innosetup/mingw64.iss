[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={commonpf}\ADMB
DefaultGroupName=ADMB Command Prompt (MinGW-w64)
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=..\..\..\build
OutputBaseFilename=admb-mingw64
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE.txt
AlwaysShowComponentsList=no

[Types]
Name: "mingw64"; Description: "ADMB Command Prompt (MinGW-w64)"

[Files]
Source: "..\..\..\build\dist\*"; DestDir: "{app}"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs
Source: "..\..\mingw\set-admb-mingw64.bat"; DestDir: "{app}\bin"
Source: "C:\msys64\mingw64\*"; DestDir: "{app}\utilities\mingw64"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs

[Icons]
Name: "{commondesktop}\ADMB Command Prompt (MinGW-w64)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-mingw64.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (MinGW-w64)"
Name: "{group}\ADMB Command Prompt (MinGW-w64)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-mingw64.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (MinGW-w64)"; OnlyBelowVersion: 6.1
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB (MinGW-w64)"; OnlyBelowVersion: 6.1
