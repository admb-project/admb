[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB (Microsoft Visual C++ 2010 32Bit)
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\..\build\admb-trunk-vc10-32bit
OutputBaseFilename=admb-trunk-vc10-32bit
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE

[Types]
Name: "vc10"; Description: "ADMB (Microsoft Visual C++ 2010 32Bit)"

[Files]
Source: "..\..\..\build\admb-trunk-vc10\dist\*"; DestDir: "{app}"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (Microsoft Visual C++ 2010)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vc10.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (Microsoft Visual C++ 2010 32Bit)"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
