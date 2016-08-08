'Create a WshShell Object
Set WshShell = Wscript.CreateObject("Wscript.Shell")

Set WshSysEnv = WshShell.Environment("SYSTEM")

'Set the Target Path for the shortcut

If Len(WshSysEnv("VS100COMNTOOLS")) > 0 Then
  'Create a WshShortcut Object
  Set oShellLink = WshShell.CreateShortcut("ADMB (Visual C++ 2010).lnk")
  oShellLink.TargetPath = "cmd"

  'Set the additional parameters for the shortcut
  oShellLink.Arguments = "/K set ADMB_HOME=%CD%& set PATH=%CD%\bin;%PATH%& call ""%VS100COMNTOOLS%\vsvars32.bat"""

  oShellLink.WorkingDirectory = "%CD%"

  'Save the shortcut
  oShellLink.Save

  'Clean up the WshShortcut Object
  Set oShellLink = Nothing
End If
