[Setup]
PrivilegesRequired=none
AppName=ADMB-11
AppVerName=ADMB-11
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={pf}\ADMB-11
DefaultGroupName=ADMB-11 (Borland 5.5)
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\..\build
OutputBaseFilename=admb-bcc55-32bit

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=..\..\..\LICENSE.txt

[Types]
Name: "bcc55"; Description: "ADMB-11 (Borland 5.5)"

[Files]
Source: "..\..\..\build\admb-bcc5.5-32bit\dist\*"; DestDir: "{app}"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB-11 Command Prompt (Borland 5.5)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-bcc551.bat"""; WorkingDir: "{app}"; Comment: "ADMB-11 Command Prompt"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB-11"
