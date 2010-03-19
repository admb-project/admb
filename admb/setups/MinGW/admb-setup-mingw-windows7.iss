[Setup]

PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName=\ADMB\MinGW
DefaultGroupName=ADMB (MinGW GCC 4.4)
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=..\..\build\setups
OutputBaseFilename=admb-win64-mingw-gcc4.4

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=LICENSE

AlwaysShowComponentsList=no

[Types]
Name: "mingw"; Description: "ADMB with MinGW tools"

[Files]
Source: "..\..\trunk\build\dists\admb_gcc345_mingw32\*"; DestDir: "{app}"; Excludes: "*\SS3*\*"; Flags: recursesubdirs
Source: "..\..\utilities\GnuWin32\*"; DestDir: "{app}\utilities\GnuWin32"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs
Source: "..\..\utilities\MinGW-gcc4.4\*"; DestDir: "{app}\utilities\MinGW-gcc4.4"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs
Source: "..\..\utilities\set-utilities-path-gcc4.4.bat"; DestDir: "{app}\utilities"

[Icons]
Name: "{group}\ADMB Command Prompt (MinGW GCC 4.4)"; Filename: "{cmd}"; Parameters: "/K ""{app}\utilities\set-utilities-path-gcc4.4.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (MinGW)"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
