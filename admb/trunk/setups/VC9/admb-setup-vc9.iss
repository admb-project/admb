[Setup]

PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName=\ADMB\Microsoft\VC9
DefaultGroupName=ADMB (Microsoft VC9)
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=.
OutputBaseFilename=admb-win32-vc9

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=..\MinGW\LICENSE

[Types]
Name: "vc9"; Description: "ADMB for Microsoft Visual C++ 9"

[Files]
Source: "admb_vc8_win32\*"; DestDir: "{app}"; Excludes: "*\SS3*\*"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (Microsoft VC9)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vc9.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
