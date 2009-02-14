[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\build
OutputBaseFilename=admb-windows-bcc551

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=..\..\LICENSE.txt

[Types]
Name: "bcc551"; Description: "ADMB for Borland C++ 5.5.1"

[Components]
Name: "bcc551"; Description: "ADMB for Borland C++ 5.5.1"; Types: bcc551

[Files]
Source: "..\..\build\dists\admb_b502_win32\*"; DestDir: "{app}"; Components: bcc551; Excludes: "*\SS3*\*"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (Borland C++ Builder 5.5.1)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-bcc551.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt"
