[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB Command Prompt (Microsoft Visual C++ 2010 32Bit)
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\..\build
OutputBaseFilename=admb-vc10-32bit
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE.txt

[Types]
Name: "vc10"; Description: "ADMB (Microsoft Visual C++ 2010 32Bit)"

[Files]
Source: "..\..\..\build\dist\*"; DestDir: "{app}"; Flags: recursesubdirs

[Icons]
Name: "{commondesktop}\ADMB Command Prompt (Microsoft Visual C++ 2010 32Bit)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vc10.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (Microsoft Visual C++ 2010 32Bit)"
Name: "{group}\ADMB Command Prompt (Microsoft Visual C++ 2010 32Bit)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vc10.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (Microsoft Visual C++ 2010 32Bit)"; OnlyBelowVersion: 6.1
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"; OnlyBelowVersion: 6.1
