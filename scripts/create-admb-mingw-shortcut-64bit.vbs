'Create a WshShell Object
Set WshShell = Wscript.CreateObject("Wscript.Shell")

Set WshSysEnv = WshShell.Environment("SYSTEM")

'Set the Target Path for the shortcut

'Create a WshShortcut Object
Set oShellLink = WshShell.CreateShortcut("ADMB Command Prompt (MinGW 64Bit).lnk")
oShellLink.TargetPath = "cmd"

'Set the additional parameters for the shortcut
oShellLink.Arguments = "/K bin\set-admb-mingw64.bat"

oShellLink.WorkingDirectory = "%CD%"

'Save the shortcut
oShellLink.Save

'Clean up the WshShortcut Object
Set oShellLink = Nothing
