[Setup]
AppName=ADMB
AppVerName=ADMB
DefaultDirName={pf}\ADMB
DefaultGroupName=ADMB
UninstallDisplayIcon={app}\MyProg.exe
OutputDir=..\..\build
OutputBaseFilename=admb-windows-setup

AppPublisher=www.admb-project.org
AppPublisherURL=http://www.admb-project.org/

LicenseFile=..\..\LICENSE.txt

[Types]
Name: "bcc551"; Description: "ADMB for Borland C++ 5.5.1"

[Components]
Name: "bcc551"; Description: "ADMB for Borland C++ 5.5.1"; Types: bcc551

[Files]
Source: "..\..\build\dists\admb_b502_win32\*"; DestDir: "{app}"; Components: bcc551

;; Misc.
;Source: "..\src\cmdl\admb.lnk"; DestDir: "{app}";
;Source: "..\src\cmdl\*.bat"; DestDir: "{app}\bin";
;Source: "..\Blurb\admbre.pdf"; DestDir: "{app}\doc";
;Source: "..\src\doc\tutorial.html"; DestDir: "{app}\doc";
;Source: "..\src\doc\admodb.pdf"; DestDir: "{app}\doc";
;Source: "..\src\doc\examples.html"; DestDir: "{app}\doc";
;Source: "..\src\doc\simple.*"; DestDir: "{app}\doc";
;Source: "..\src\doc\cctest.cpp"; DestDir: "{app}\doc";
;Source: "..\src\div\readme.txt"; DestDir: "{app}"; Flags: isreadme
;Source: "..\src\bin\tpl2*.exe"; DestDir: "{app}\bin";
;Source: "..\src\bin\sed*"; DestDir: "{app}\bin";
;
;; Borland 5.0.2
;Source: "..\src\admb\bcc502\bat\*"; DestDir: "{app}\bin"; Components: bcc502
;Source: "..\src\admb\bcc502\lib\*"; DestDir: "{app}\lib"; Components: bcc502
;Source: "..\src\admb\bcc502\include\*"; DestDir: "{app}\include"; Components: bcc502
;Source: "..\src\admb\bcc502\version.txt*"; DestDir: "{app}"; Components: bcc502
;
;; Borland 5.2
;;Source: "..\src\admb\bcc52\bat\*"; DestDir: "{app}\bin"; Components: bcc52
;;Source: "..\src\admb\bcc52\lib\*"; DestDir: "{app}\lib"; Components: bcc52
;;Source: "..\src\admb\bcc52\include\*"; DestDir: "{app}\include"; Components: bcc52
;;Source: "..\src\admb\bcc52\version.txt*"; DestDir: "{app}"; Components: bcc52
;
;; Borland 5.5.1
;Source: "..\src\admb\bcc551\bat\*"; DestDir: "{app}\bin"; Components: bcc551
;Source: "..\src\admb\bcc551\lib\*"; DestDir: "{app}\lib"; Components: bcc551
;Source: "..\src\admb\bcc551\include\*"; DestDir: "{app}\include"; Components: bcc551
;Source: "..\src\admb\bcc551\version.txt*"; DestDir: "{app}"; Components: bcc551
;
;
;; Visual C++ 6
;Source: "..\src\admb\msvc6\bat\*"; DestDir: "{app}\bin"; Components: msvc6
;Source: "..\src\admb\msvc6\lib\*"; DestDir: "{app}\lib"; Components: msvc6
;Source: "..\src\admb\msvc6\include\*"; DestDir: "{app}\include"; Components: msvc6
;Source: "..\src\admb\msvc6\version.txt*"; DestDir: "{app}"; Components: msvc6
;
;
;; Visual C++ 8
;Source: "..\src\admb\msvc8\bat\*"; DestDir: "{app}\bin"; Components: msvc8
;Source: "..\src\admb\msvc8\lib\*"; DestDir: "{app}\lib"; Components: msvc8
;Source: "..\src\admb\msvc8\include\*"; DestDir: "{app}\include"; Components: msvc8
;Source: "..\src\admb\msvc8\version.txt*"; DestDir: "{app}"; Components: msvc8
;
;
;; mingw32 gcc345
;Source: "..\src\admb\mingw32\bat\*"; DestDir: "{app}\bin"; Components: mingw32
;Source: "..\src\admb\mingw32\lib\*"; DestDir: "{app}\lib"; Components: mingw32
;Source: "..\src\admb\mingw32\include\*"; DestDir: "{app}\include"; Components: mingw32
;Source: "..\src\admb\mingw32\version.txt*"; DestDir: "{app}"; Components: mingw32
;
;
[Registry]
Root: HKCU; Subkey: "Environment"; ValueType: string; ValueName: "ADMB_HOME"; ValueData: "{app}"
;
;[Icons]
;Name: "{group}\ADMB"; Filename: "{app}\admb.lnk"; Comment: "Launch DOS-window"
;Name: "{group}\Doc\ADMB"; Filename: "{app}\doc\admodb.pdf"; Comment: "ADMB user guide"
;Name: "{group}\Doc\ADMBRE"; Filename: "{app}\doc\admbre.pdf"; Comment: "ADMB-RE user guide"
;Name: "{group}\Doc\Examples"; Filename: "{app}\doc\examples.html"; Comment: "Online example collection"
;Name: "{group}\Uninstall"; Filename: "{uninstallexe}"; Comment: "Uninstall ADMB"
;Name: "{group}\Tutorial"; Filename: "{app}\doc\tutorial.html"; Comment: "Your first example"
