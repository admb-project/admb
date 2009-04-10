[Setup]

PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName=\ADMB\Microsoft\VC8
DefaultGroupName=ADMB (Microsoft Visual C++ 2005)
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=.
OutputBaseFilename=admb-win32-vc8

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=..\MinGW\LICENSE

[Types]
Name: "vc8"; Description: "ADMB for Microsoft Visual C++ 2005"

[Files]
Source: "admb_vc8_win32\*"; DestDir: "{app}"; Excludes: "*\SS3*\*"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (Microsoft Visual C++ 2005)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vc8.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
