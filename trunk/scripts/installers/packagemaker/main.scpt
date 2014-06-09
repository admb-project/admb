-- main.scpt
-- Cocoa-AppleScript Applet
--
-- Copyright 2012-2014 ADMB Foundation. All rights reserved.

set p to path to
set pp to (POSIX path of p)
tell application "Terminal"
	activate
	do script "export ADMB_HOME=\"" & pp & "\"; export PATH=\"" & pp & "bin\":${PATH}"
end tell
