[Setup]
OutputBaseFilename=admb-ide-112-win64
AppName=ADMB-IDE
AppVerName=ADMB-IDE 11.2 win64
ChangesAssociations=yes
ChangesEnvironment=yes
DefaultDirName=c:\admb\ide
DefaultGroupName=ADMB
OutputDir=.
DisableDirPage=yes
DisableProgramGroupPage=yes
UninstallDisplayIcon=c:\~\icons\admb.ico

[Types]
Name: full;   Description: "Full installation"
Name: custom; Description: "Custom installation"; Flags: iscustom

[Components]
Name: admb;   Description: "AD Model Builder for GCC [c:/admb]";         Types: full
Name: gcc;    Description: "GCC C++ compiler [c:/gnu/gcc492-win64]";     Types: full
Name: gdb;    Description: "GDB debugger [c:/gnu/gdb]";                  Types: full
Name: emacs;  Description: "GNU Emacs editor [c:/gnu/emacs]";            Types: full
Name: mode;   Description: "ADMB mode for Emacs [c:/~/emacs/lisp/admb]"; Types: full
Name: auctex; Description: "AUCTeX for Emacs [c:/~/emacs/lisp/auctex]";  Types: full
Name: ess;    Description: "ESS for Emacs [c:/~/emacs/lisp/ess]";        Types: full
Name: ide;    Description: "ADMB-IDE settings [c:/~]";                   Types: full

[Tasks]
Name: desktop;   Description: "Create Desktop shortcut to ADMB-IDE";                                              GroupDescription: "Shortcuts:"
Name: startmenu; Description: "Create Start Menu shortcut to ADMB-IDE";                                           GroupDescription: "Shortcuts:"
Name: assoc1;    Description: "Associate ADMB files (cor, ctl, dat, par, pin, psv, rep, std, tpl) with ADMB-IDE"; GroupDescription: "Registry:"
Name: assoc2;    Description: "Associate Emacs files (el, elc, emacs) with ADMB-IDE";                             GroupDescription: "Registry:"
Name: path;      Description: "Add ADMB, GCC, GDB, and Emacs to PATH, so they can find each other";               GroupDescription: "Registry:"
Name: admbhome;  Description: "Define ADMB_HOME as c:/admb/admb112-gcc492-win64, so ADMB scripts work";           GroupDescription: "Registry:"
Name: home;      Description: "Define HOME directory as c:/~, to store configuration files";                      GroupDescription: "Registry:"

[Files]
Source: "..\dot\.emacs";            DestDir: "c:\~";                   Components: ide;    Flags: confirmoverwrite
Source: "c:\~\emacs\lisp\admb\*";   DestDir: "c:\~\emacs\lisp\admb";   Components: mode
Source: "c:\~\emacs\lisp\auctex\*"; DestDir: "c:\~\emacs\lisp\auctex"; Components: auctex; Flags: recursesubdirs
Source: "c:\~\emacs\lisp\ess\*";    DestDir: "c:\~\emacs\lisp\ess";    Components: ess;    Flags: recursesubdirs
Source: "c:\~\icons\admb*";         DestDir: "c:\~\icons";             Components: ide
Source: "..\*.pdf";                 DestDir: "c:\admb";                Components: admb
Source: "admb\*";                   DestDir: "c:\admb";                Components: admb;   Flags: recursesubdirs
Source: "..\manual\admb-ide.pdf";   DestDir: "c:\admb";                Components: ide
Source: "..\manual\admb-ide.texi";  DestDir: "c:\admb\ide\inst";       Components: ide
Source: "..\NEWS";                  DestDir: "c:\admb\ide";            Components: ide
Source: "admb-ide-build.*";         DestDir: "c:\admb\ide\inst";       Components: ide
Source: "c:\gnu\emacs\*";           DestDir: "c:\gnu\emacs";           Components: emacs;  Flags: recursesubdirs
Source: "c:\gnu\gcc492-win64\*";    DestDir: "c:\gnu\gcc492-win64";    Components: gcc;    Flags: recursesubdirs
Source: "c:\gnu\gdb\*";             DestDir: "c:\gnu\gdb";             Components: gdb;    Flags: recursesubdirs

[Icons]
Name: "{userdesktop}\ADMB-IDE";     Filename: "c:\gnu\emacs\bin\runemacs.exe"; IconFilename: "c:\~\icons\admb64.ico"; Tasks: desktop
Name: "{group}\ADMB-IDE";           Filename: "c:\gnu\emacs\bin\runemacs.exe"; IconFilename: "c:\~\icons\admb.ico";   Tasks: startmenu
Name: "{group}\Manual (ADMB)";      Filename: "c:\admb\admb.pdf";                                                     Tasks: startmenu
Name: "{group}\Manual (ADMB-IDE)";  Filename: "c:\admb\admb-ide.pdf";                                                 Tasks: startmenu
Name: "{group}\Manual (ADMB-RE)";   Filename: "c:\admb\admb-re.pdf";                                                  Tasks: startmenu
Name: "{group}\Manual (AUTODIF)";   Filename: "c:\admb\autodif.pdf";                                                  Tasks: startmenu
Name: "{group}\Uninstall ADMB-IDE"; Filename: "{uninstallexe}";                                                       Tasks: startmenu

[Registry]
; Environment variables
Root: HKCU; Subkey: "Environment"; ValueType: string; ValueName: "PATH";      ValueData: "c:/ADMB/admb112-gcc492-win64/bin;c:/gnu/GCC492-win64/bin;c:/gnu/GDB/bin;c:/gnu/EMACS/bin"; Tasks: path;     Flags: uninsdeletevalue
Root: HKCU; Subkey: "Environment"; ValueType: string; ValueName: "HOME";      ValueData: "c:/~";                                                                                     Tasks: home;     Flags: uninsdeletevalue
Root: HKCU; Subkey: "Environment"; ValueType: string; ValueName: "ADMB_HOME"; ValueData: "c:/ADMB/admb112-gcc492-win64";                                                             Tasks: admbhome; Flags: uninsdeletevalue
; File associations
Root: HKCR; Subkey: ".cor";                                           ValueType: string; ValueName: ""; ValueData: "ADMB Correlation";                    Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB Correlation";                               ValueType: string; ValueName: ""; ValueData: "ADMB Correlation";                    Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB Correlation\DefaultIcon";                   ValueType: string; ValueName: ""; ValueData: "shell32.dll,105";                     Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: "ADMB Correlation\Shell\Open\command";            ValueType: string; ValueName: ""; ValueData: "c:\gnu\emacs\bin\runemacs ""%1""";    Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".ctl";                                           ValueType: string; ValueName: ""; ValueData: "Control File";                        Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "Control File";                                   ValueType: string; ValueName: ""; ValueData: "Control File";                        Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "Control File\DefaultIcon";                       ValueType: string; ValueName: ""; ValueData: "shell32.dll,211";                     Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Control File\Shell\Open\command";                ValueType: string; ValueName: ""; ValueData: "c:\gnu\emacs\bin\runemacs ""%1""";    Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".dat";                                           ValueType: string; ValueName: ""; ValueData: "Data File";                           Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "Data File";                                      ValueType: string; ValueName: ""; ValueData: "Data File";                           Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "Data File\DefaultIcon";                          ValueType: string; ValueName: ""; ValueData: "shell32.dll,217";                     Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Data File\Shell\Open\command";                   ValueType: string; ValueName: ""; ValueData: "c:\gnu\emacs\bin\runemacs ""%1""";    Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".par";                                           ValueType: string; ValueName: ""; ValueData: "ADMB Point Estimates";                Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB Point Estimates";                           ValueType: string; ValueName: ""; ValueData: "ADMB Point Estimates";                Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB Point Estimates\DefaultIcon";               ValueType: string; ValueName: ""; ValueData: "shell32.dll,99";                      Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: "ADMB Point Estimates\Report\Shell\Open\command"; ValueType: string; ValueName: ""; ValueData: "c:\gnu\emacs\bin\runemacs ""%1""";    Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".pin";                                           ValueType: string; ValueName: ""; ValueData: "ADMB Initial Values";                 Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB Initial Values";                            ValueType: string; ValueName: ""; ValueData: "ADMB Initial Values";                 Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB Initial Values\DefaultIcon";                ValueType: string; ValueName: ""; ValueData: "shell32.dll,211";                     Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: "ADMB Initial Values\Shell\Open\command";         ValueType: string; ValueName: ""; ValueData: "c:\gnu\emacs\bin\runemacs ""%1""";    Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".psv";                                           ValueType: string; ValueName: ""; ValueData: "ADMB MCMC Binary";                    Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB MCMC Binary";                               ValueType: string; ValueName: ""; ValueData: "ADMB MCMC Binary";                    Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB MCMC Binary\DefaultIcon";                   ValueType: string; ValueName: ""; ValueData: "shell32.dll,165";                     Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".rep";                                           ValueType: string; ValueName: ""; ValueData: "ADMB Report";                         Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB Report";                                    ValueType: string; ValueName: ""; ValueData: "ADMB Report";                         Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB Report\DefaultIcon";                        ValueType: string; ValueName: ""; ValueData: "shell32.dll,21";                      Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: "ADMB Report\Shell\Open\command";                 ValueType: string; ValueName: ""; ValueData: "c:\gnu\emacs\bin\runemacs ""%1""";    Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".std";                                           ValueType: string; ValueName: ""; ValueData: "ADMB Standard Error";                 Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB Standard Error";                            ValueType: string; ValueName: ""; ValueData: "ADMB Standard Error";                 Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB Standard Error\DefaultIcon";                ValueType: string; ValueName: ""; ValueData: "shell32.dll,99";                      Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: "ADMB Standard Error\Report\Shell\Open\command";  ValueType: string; ValueName: ""; ValueData: "c:\gnu\emacs\bin\runemacs ""%1""";    Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".tpl";                                           ValueType: string; ValueName: ""; ValueData: "ADMB Source Code";                    Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB Source Code";                               ValueType: string; ValueName: ""; ValueData: "ADMB Source Code";                    Tasks: assoc1; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "ADMB Source Code\DefaultIcon";                   ValueType: string; ValueName: ""; ValueData: "shell32.dll,84";                      Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: "ADMB Source Code\Shell\Open\command";            ValueType: string; ValueName: ""; ValueData: "c:\gnu\emacs\bin\runemacs ""%1""";    Tasks: assoc1; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".el";                                            ValueType: string; ValueName: ""; ValueData: "Emacs Lisp Code";                     Tasks: assoc2; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "Emacs Lisp Code";                                ValueType: string; ValueName: ""; ValueData: "Emacs Lisp Code";                     Tasks: assoc2; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "Emacs Lisp Code\DefaultIcon";                    ValueType: string; ValueName: ""; ValueData: "c:\gnu\emacs\etc\icons\gnu2a32t.ico"; Tasks: assoc2; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Emacs Lisp Code\Shell\Open\command";             ValueType: string; ValueName: ""; ValueData: "c:\gnu\emacs\bin\runemacs ""%1""";    Tasks: assoc2; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".elc";                                           ValueType: string; ValueName: ""; ValueData: "Emacs Lisp Binary";                   Tasks: assoc2; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "Emacs Lisp Binary";                              ValueType: string; ValueName: ""; ValueData: "Emacs Lisp Binary";                   Tasks: assoc2; Flags: uninsdeletevalue uninsdeletekeyifempty
Root: HKCR; Subkey: "Emacs Lisp Binary\DefaultIcon";                  ValueType: string; ValueName: ""; ValueData: "c:\gnu\emacs\etc\icons\gnu3b32t.ico"; Tasks: assoc2; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Emacs Lisp Binary\Shell\Open\command";           ValueType: string; ValueName: ""; ValueData: "c:\gnu\emacs\bin\runemacs ""%1""";    Tasks: assoc2; Flags: uninsdeletevalue
Root: HKCR; Subkey: ".emacs";                                         ValueType: string; ValueName: ""; ValueData: "Emacs Lisp Code";                     Tasks: assoc2; Flags: uninsdeletevalue uninsdeletekeyifempty
