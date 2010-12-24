[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB (Microsoft Visual C++ 2010)
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\..
OutputBaseFilename=admb-10.0-vc10
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE

[Types]
Name: "vc10"; Description: "ADMB (Microsoft Visual C++ 2010)"

[Files]
Source: "..\..\..\build\*"; DestDir: "{app}"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (Microsoft Visual C++ 2010)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vc10.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (Microsoft Visual C++ 2010)"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
