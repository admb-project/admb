[Setup]

PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName=\ADMB\MinGW
DefaultGroupName=ADMB (MinGW GCC 3.4)
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=..\..\build\setups
OutputBaseFilename=admb-win32-mingw

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=LICENSE

AlwaysShowComponentsList=no

[Types]
Name: "mingw"; Description: "ADMB with MinGW tools"

[Files]
Source: "..\..\trunk\build\dists\admb_gcc345_mingw32\*"; DestDir: "{app}"; Excludes: "*\SS3*\*"; Flags: recursesubdirs
Source: "..\..\utilities\*"; DestDir: "{app}\utilities"; Excludes: ".svn,*\.svn"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (MinGW GCC 3.4)"; Filename: "{cmd}"; Parameters: "/K ""{app}\utilities\set-utilities-path.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (MinGW)"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
