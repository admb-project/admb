[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB (Microsoft Visual C++ 2010 64Bit)
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\..\build\admb-10.0-vc10-64bit
OutputBaseFilename=admb-10.0-vc10-64bit
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE

[Types]
Name: "vc10"; Description: "ADMB (Microsoft Visual C++ 2010 64Bit)"

[Files]
Source: "..\..\..\build\admb-10.0-vc10-64bit\dist\*"; DestDir: "{app}"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (Microsoft Visual C++ 2010 64Bit)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vc10-64bit.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (Microsoft Visual C++ 2010 64Bit)"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
