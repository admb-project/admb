[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\build
OutputBaseFilename=admb-win32-mingw

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=..\..\LICENSE

[Types]
Name: "mingw"; Description: "ADMB for MinGW"

[Components]
Name: "mingw"; Description: "ADMB for MinGW"; Types: mingw

[Files]
Source: "..\..\build\dists\admb_gcc345_mingw32\*"; DestDir: "{app}"; Components: mingw; Excludes: "*\SS3*\*"; Flags: recursesubdirs

;[Registry]
;Root: HKCU; Subkey: "Environment"; ValueType: string; ValueName: "ADMB_HOME"; ValueData: "{app}"
;

[Icons]
Name: "{group}\ADMB Command Prompt (MinGW)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-mingw.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
