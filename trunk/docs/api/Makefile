# $Id$
#
# Author: John Sibert
# Copyright (c) 2009 ADMB Foundation
#
.PHONY: default clean

REV=`svnversion -n ../..`
VER=`cat ../../VERSION`


default: Doxyfile ./dox-share/mainpage.txt 
	mkdir -vp dox/html
#	See Doxygen FAQ "Can I configure doxygen from the command line?"
	(cat Doxyfile ; echo -n "PROJECT_NUMBER = r"$(REV); ) | doxygen -
#(cat Doxyfile ; echo "OUTPUT_DIRECTORY = dox"; echo -n "PROJECT_NUMBER = "$(VER).$(REV); ) | doxygen -

clean:
	rm -rf dox
