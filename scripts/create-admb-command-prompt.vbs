'Create a WshShell Object
Set WshShell = Wscript.CreateObject("Wscript.Shell")

Set WshSysEnv = WshShell.Environment("SYSTEM")

'Set the Target Path for the shortcut

'Create a WshShortcut Object
Set oShellLink = WshShell.CreateShortcut("ADMB Command Prompt.lnk")
oShellLink.TargetPath = "cmd"

if WScript.Arguments.Count = 0 then
  'Set the additional parameters for the shortcut
  oShellLink.Arguments = "/K bin\set-admb-command-prompt.bat"
else
  Dim args
  Set args = WScript.Arguments
  'Set the additional parameters for the shortcut
  oShellLink.Arguments = "/K args(0)\bin\set-admb-command-prompt.bat"
end if

oShellLink.WorkingDirectory = "%CD%"

'Save the shortcut
oShellLink.Save

'Clean up the WshShortcut Object
Set oShellLink = Nothing
