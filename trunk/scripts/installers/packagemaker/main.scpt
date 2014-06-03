-- main.scpt
-- Cocoa-AppleScript Applet
--
-- Copyright 2012 ADMB Foundation. All rights reserved.

set p to path to
tell application "Terminal"
	activate
	do script "export ADMB_HOME=\"" & p & "\"; export PATH=\"" & p & "bin\":${PATH}"
end tell
