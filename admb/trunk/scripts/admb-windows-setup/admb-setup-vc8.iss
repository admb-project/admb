[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\build
OutputBaseFilename=admb-win32-vc8

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=..\..\LICENSE

[Types]
Name: "vc8"; Description: "ADMB for Microsoft Visual C++ 8"

[Components]
Name: "vc8"; Description: "ADMB for Microsoft Visual C++ 8"; Types: vc8

[Files]
Source: "..\..\build\dists\admb_vc8_win32\*"; DestDir: "{app}"; Components: vc8; Excludes: "*\SS3*\*"; Flags: recursesubdirs

;[Registry]
;Root: HKCU; Subkey: "Environment"; ValueType: string; ValueName: "ADMB_HOME"; ValueData: "{app}"
;

[Icons]
Name: "{group}\ADMB Command Prompt (VC8)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vc8.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
