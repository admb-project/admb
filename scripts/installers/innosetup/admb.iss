#define ADMB_VERSION "ADMB-13.0"
#define ADMB_VERSION2 "admb-13.0"

[Setup]
PrivilegesRequired=none
AppName={#ADMB_VERSION}
AppVerName={#ADMB_VERSION}
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={sd}\{#ADMB_VERSION}
DefaultGroupName={#ADMB_VERSION}
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=..\..\..\build
OutputBaseFilename={#ADMB_VERSION2}-windows
AppPublisher=ADMB Project
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE.txt
Compression=lzma2/ultra64

[Types]
Name: {#ADMB_VERSION2}; Description: {#ADMB_VERSION}

[Files]
Source: "..\..\..\build\admb-13.0\*"; DestDir: "{app}"; Flags: recursesubdirs
Source: "..\..\set-admb-command-prompt.bat"; DestDir: "{app}\bin"
Source: "..\..\..\CHANGES.md"; DestDir: "{app}"; DestName: "CHANGES.txt"
Source: "..\..\..\LICENSE.txt"; DestDir: "{app}"
Source: "..\..\..\README.md"; DestDir: "{app}"; DestName: "README.txt"
Source: "..\..\..\VERSION"; DestDir: "{app}"; DestName: "Version.txt"
Source: "..\..\..\examples\*"; DestDir: "{app}\examples"; Flags: recursesubdirs
Source: "..\..\..\utilities\*"; DestDir: "{app}\utilities"; Flags: recursesubdirs
Source: "C:\rtools40\mingw64\*"; DestDir: "{app}\utilities\mingw64"; Flags: recursesubdirs

[Icons]
Name: "{app}\{#ADMB_VERSION} Command Prompt"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-command-prompt.bat"""; WorkingDir: "{app}"; Comment: "{#ADMB_VERSION} Command Prompt"
Name: "{group}\{#ADMB_VERSION} Command Prompt"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-command-prompt.bat"""; WorkingDir: "{app}"; Comment: "{#ADMB_VERSION} Command Prompt"
Name: "{group}\Uninstall {#ADMB_VERSION}"; Filename: "{uninstallexe}"; Comment: "Uninstall {#ADMB_VERSION}"
