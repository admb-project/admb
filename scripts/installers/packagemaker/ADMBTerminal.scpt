-- main.scpt
-- Cocoa-AppleScript Applet
--
-- Copyright 2012-2021 ADMB Foundation. All rights reserved.

on isrun(name)
    tell application "System Events" to (name of processes) contains name
end isrun

set check to isrun("Terminal")

set p to path to
set pp to (POSIX path of p)
if check then
  tell application "Terminal"
    do script "export ADMB_HOME=\"" & pp & "admb-12.3\"; export PATH=\"" & pp & "admb-12.3/bin\":${PATH}"
    activate
  end tell
else
  tell application "Terminal"
    do script "export ADMB_HOME=\"" & pp & "admb-12.3\"; export PATH=\"" & pp & "admb-12.3/bin\":${PATH}" in window 1
    activate
  end tell
end if

