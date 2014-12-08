[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB Command Prompt (MinGW 32Bit)
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=..\..\..\build
OutputBaseFilename=admb-mingw32
AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/
LicenseFile=..\..\..\LICENSE.txt
AlwaysShowComponentsList=no

[Types]
Name: "mingw32"; Description: "ADMB Command Prompt (MinGW 32Bit)"

[Files]
Source: "..\..\..\build\dist\*"; DestDir: "{app}"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs
Source: "C:\mingw32\*"; DestDir: "{app}\utilities\mingw32"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs
Source: "..\..\mingw\set-admb-mingw32.bat"; DestDir: "{app}\bin"

[Icons]
Name: "{commondesktop}\ADMB Command Prompt (MinGW 32Bit)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-mingw32.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (MinGW 32Bit)"
