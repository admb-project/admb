[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={commonpf}\ADMB
DefaultGroupName=ADMB Command Prompt (Rtools)
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=..\..\..\build
OutputBaseFilename=admb-rtools
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE.txt
AlwaysShowComponentsList=no

[Types]
Name: "rtools"; Description: "ADMB Command Prompt (Rtools)"

[Files]
Source: "..\..\..\build\dist\*"; DestDir: "{app}"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs
Source: "..\..\mingw\set-admb-rtools.bat"; DestDir: "{app}\bin"

[Icons]
Name: "{commondesktop}\ADMB Command Prompt (Rtools)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-rtools.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (Rtools)"
Name: "{group}\ADMB Command Prompt (Rtools)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-rtools.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (Rtools)"; OnlyBelowVersion: 6.1
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB (Rtools)"; OnlyBelowVersion: 6.1
