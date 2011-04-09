[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB (Borland 5.5)
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\..
OutputBaseFilename=admb-10.0-bcc55-32bit

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=..\..\..\LICENSE

[Types]
Name: "bcc55"; Description: "ADMB (Borland 5.5)"

[Files]
Source: "..\..\..\build\admb-10.0-bcc5.5-32bit\dist\*"; DestDir: "{app}"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (Borland 5.5)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-bcc551.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
