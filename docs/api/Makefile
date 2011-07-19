# $Id: Makefile 966 2011-02-04 00:39:53Z jsibert $
#
# Author: John Sibert
# Copyright (c) 2009 ADMB Foundation
#
.PHONY: default clean

REV = `svnversion -n ../..`
VER=`cat ../../VERSION`

default: Doxyfile ./dox-share/mainpage.txt 
	mkdir -vp dox/html
	(cat Doxyfile ; echo "OUTPUT_DIRECTORY = dox"; echo -n "PROJECT_NUMBER = "$(VER).$(REV); ) | doxygen -

clean:
	rm -rf dox
