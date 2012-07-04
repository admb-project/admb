[Setup]
PrivilegesRequired=none
AppName=ADMB-11
AppVerName=ADMB-11
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={pf}\ADMB-11
DefaultGroupName=ADMB-11 (Microsoft Visual C++ 2010 64Bit)
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\..\build
OutputBaseFilename=admb-vc10-64bit
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE.txt

[Types]
Name: "vc10"; Description: "ADMB-11 (Microsoft Visual C++ 2010 64Bit)"

[Files]
Source: "..\..\..\build\admb-vc10\dist\*"; DestDir: "{app}"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB-11 Command Prompt (Microsoft Visual C++ 2010 64Bit)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vc10-64bit.bat"""; WorkingDir: "{app}"; Comment: "ADMB-11 Command Prompt (Microsoft Visual C++ 2010 64Bit)"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB-11"
