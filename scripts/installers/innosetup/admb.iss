[Setup]
PrivilegesRequired=none
AppName=ADMB-12.1
AppVerName=ADMB-12.1
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={commonpf}\ADMB-12.1
DefaultGroupName=ADMB-12.1
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=..\..\..\build
OutputBaseFilename=admb
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE.txt

[Types]
Name: "admb-12.1"; Description: "ADMB-12.1"

[Files]
Source: "..\..\..\build\admb\*"; DestDir: "{app}"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs
Source: "..\..\set-admb-command-prompt.bat"; DestDir: "{app}\bin"

[Icons]
Name: "{app}\ADMB Command Prompt"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-command-prompt.bat"""; WorkingDir: "{app}"; Comment: "ADMB-12.1 Command Prompt"; OnlyBelowVersion: 6.1
Name: "{group}\ADMB Command Prompt"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-command-prompt.bat"""; WorkingDir: "{app}"; Comment: "ADMB-12.1 Command Prompt"; OnlyBelowVersion: 6.1
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"; OnlyBelowVersion: 6.1
