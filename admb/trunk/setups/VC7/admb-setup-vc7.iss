[Setup]

PrivilegesRequired=none
AppName=ADMB
AppVerName=ADMB
UsePreviousAppDir=no
UsePreviousGroup=no
DefaultDirName=\ADMB\Microsoft\VC7
DefaultGroupName=ADMB (Microsoft Visual Studio .NET 2003)
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=.
OutputBaseFilename=admb-win32-vc7

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=..\MinGW\LICENSE

[Types]
Name: "vc7"; Description: "ADMB for Microsoft Visual Studio .NET 2003"

[Files]
Source: "admb_vc8_win32\*"; DestDir: "{app}"; Excludes: "*\SS3*\*"; Flags: recursesubdirs

[Icons]
Name: "{group}\ADMB Command Prompt (Microsoft Visual Studio .NET 2003)"; Filename: "{cmd}"; Parameters: "/K ""{app}\bin\set-admb-vc7.bat"""; WorkingDir: "{app}"; Comment: "ADMB Command Prompt"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
