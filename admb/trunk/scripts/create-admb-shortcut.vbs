'Create a WshShell Object
Set WshShell = Wscript.CreateObject("Wscript.Shell")


'Create a WshShortcut Object
strAdmbHome = WshShell.SpecialFolders("Desktop") & "\ADMB"
Set oShellLink = WshShell.CreateShortcut(strAdmbHome + "\ADMB (Visual C++ 2010).lnk")

Set WshSysEnv = WshShell.Environment("SYSTEM")

'Set the Target Path for the shortcut
oShellLink.TargetPath = "cmd"

If Len(WshSysEnv("VS100COMNTOOLS")) > 0 Then

'Set the additional parameters for the shortcut
'oShellLink.Arguments = "/K call ""%VS100COMNTOOLS%\vsvars32.bat"" & set ADMB_HOME=" & strAdmbHome & "& set PATH=" & strAdmbHome & "\bin;%PATH%"
oShellLink.Arguments = "/K call ""%VS100COMNTOOLS%\vsvars32.bat"" & set ADMB_HOME=""%CD%"" & set PATH=""%CD%""\bin;%PATH%"

End If

oShellLink.WorkingDirectory = strAdmbHome

'Save the shortcut
oShellLink.Save

'Clean up the WshShortcut Object
Set oShellLink = Nothing

