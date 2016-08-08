'Create a WshShell Object
Set WshShell = Wscript.CreateObject("Wscript.Shell")

Set WshSysEnv = WshShell.Environment("SYSTEM")

'Set the Target Path for the shortcut

If Len(WshSysEnv("VS140COMNTOOLS")) > 0 Then
  'Create a WshShortcut Object
  Set oShellLink = WshShell.CreateShortcut("ADMB Command Prompt(Visual C++ 2015 32Bit).lnk")
  oShellLink.TargetPath = "cmd"

  'Set the additional parameters for the shortcut
  oShellLink.Arguments = "/K bin\set-admb-vc14-32bit.bat"

  oShellLink.WorkingDirectory = "%CD%"

  'Save the shortcut
  oShellLink.Save

  'Clean up the WshShortcut Object
  Set oShellLink = Nothing
End If
