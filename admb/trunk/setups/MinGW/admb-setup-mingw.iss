[Setup]
PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
DefaultDirName=\ADMB\MinGW
DefaultGroupName=ADMB (MinGW)
UninstallDisplayIcon={app}\uninstall.exe
OutputDir=.
OutputBaseFilename=admb-win32-mingw

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=LICENSE

AlwaysShowComponentsList=no

[Types]
Name: "mingw"; Description: "Full installation of ADMB for MinGW"

[Files]
Source: "distribution\*"; DestDir: "{app}"; Excludes: "*\SS3*\*"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (MinGW)"; Filename: "{cmd}"; Parameters: "/K ""{app}\tools\set-tools-path.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt (MinGW)"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
