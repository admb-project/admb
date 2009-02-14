[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\build
OutputBaseFilename=admb-win32-vc7

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=..\..\LICENSE

[Types]
Name: "vc7"; Description: "ADMB for Microsoft Visual C++ 7"

[Components]
Name: "vc7"; Description: "ADMB for Microsoft Visual C++ 7"; Types: vc7

[Files]
Source: "..\..\build\dists\admb_vc8_win32\*"; DestDir: "{app}"; Components: vc7; Excludes: "*\SS3*\*"; Flags: recursesubdirs

;[Registry]
;Root: HKCU; Subkey: "Environment"; ValueType: string; ValueName: "ADMB_HOME"; ValueData: "{app}"
;

[Icons]
Name: "{group}\ADMB Command Prompt (VC7)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vc7.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
