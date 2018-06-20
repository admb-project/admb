# Author: John Sibert
# Copyright (c) 2009 ADMB Foundation

.PHONY: default clean

REV=`git show -s --format=%h HEAD`
VER=`cat ../../VERSION`


default: Doxyfile ./dox-share/mainpage.txt 
	mkdir -vp dox/html
#	Insert some linux-specific deltails into configuration file
#	See Doxygen FAQ "Can I configure doxygen from the command line?"
	(cat Doxyfile ; echo "PROJECT_NUMBER = "$(VER)"(GitRevision: "$(REV)")"; echo "FILE_VERSION_FILTER  = ./getID.sh"; ) | doxygen -

clean:
	rm -rf dox
