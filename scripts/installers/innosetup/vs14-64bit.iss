[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={commonpf}\ADMB
DefaultGroupName=ADMB (Microsoft Visual Studio 2015 - C++ 64Bit)
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=..\..\..\build
OutputBaseFilename=admb-vs14
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE.txt

[Types]
Name: "vs14"; Description: "ADMB (Microsoft Visual Studio 2015 - C++ 64Bit)"

[Files]
Source: "..\..\..\build\dist\*"; DestDir: "{app}"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs
Source: "..\..\cl\set-admb-vs14-64bit.bat"; DestDir: "{app}\bin"

[Icons]
Name: "{commondesktop}\ADMB Command Prompt (Microsoft Visual Studio 2015 - C++ 64Bit)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vs14-64bit.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (Microsoft Visual Studio 2015 - C++ 64Bit)"
Name: "{group}\ADMB Command Prompt (Microsoft Visual Studio 2015 - C++ 64Bit)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vs14-64bit.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (Microsoft Visual Studio 2015 - C++ 64Bit)"; OnlyBelowVersion: 6.1
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"; OnlyBelowVersion: 6.1
