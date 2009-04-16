[Setup]

PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName=\ADMB\Borland\BCC551
DefaultGroupName=ADMB (Borland BCC32 5.5.1)
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\build\setups
OutputBaseFilename=admb-windows-bcc551

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=..\MinGW\LICENSE

[Types]
Name: "bcc551"; Description: "ADMB for Borland BCC32 5.5.1"

[Files]
Source: "..\..\build\dists\admb_b502_win32\*"; DestDir: "{app}"; Excludes: "*\SS3*\*"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (Borland BCC32 5.5.1)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-bcc551.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
