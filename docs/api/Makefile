# $Id$
#
# Author: John Sibert
# Copyright (c) 2009 ADMB Foundation
#
.PHONY: default sunsys all clean

#location of the files downloaded from http://dox.narechk.net/content/main.html
ifeq ($(HOSTNAME),kolea)
  # confugration on John's laptop
  SUNSYS_HOME=~/admb/sunsys-dox
  SUNSYS_PATH=$(SUNSYS_HOME)/bin
  #SUNSYS_SHARE=$(SUNSYS_HOME)/share
  SUNSYS_SHARE= ./sunsys-share
else
  SUNSYS_HOME=~/admb/sunsys-dox
  SUNSYS_PATH=$(SUNSYS_HOME)/bin
  SUNSYS_SHARE=$(SUNSYS_HOME)/share
endif

# from the doxygen manual; doxygen reads configure information from stdin
#( cat Doxyfile ; echo "PROJECT_NUMBER=1.0" ) | doxygen -

default:
	mkdir -vp dox/html
	(cat Doxyfile ; echo "OUTPUT_DIRECTORY = dox"; echo "GENERATE_XML = NO"; echo -n "PROJECT_NUMBER = A";svnversion ../..) | doxygen -

sunsys:
	mkdir -vp sunsys-dox/html
	mkdir -vp sunsys-dox/html/resources
	mkdir -vp sunsys-dox/temp
	mkdir -vp sunsys-dox/temp/xml
	cp -fv $(SUNSYS_SHARE)/DoxConfig.xml sunsys-dox
	cp -fv $(SUNSYS_SHARE)/*.txt sunsys-dox
	cp -fv $(SUNSYS_SHARE)/*.html sunsys-dox/html
	cp -fv $(SUNSYS_SHARE)/resources/*.* sunsys-dox/html/resources
	(cat Doxyfile ; echo "OUTPUT_DIRECTORY = sunsys-dox/temp"; echo "GENERATE_XML = YES"; echo -n "PROJECT_NUMBER = ";svnversion ../..) | $(SUNSYS_PATH)/doxygen-nk -
	(cat Doxyfile ; echo "OUTPUT_DIRECTORY = sunsys-dox/temp"; echo "GENERATE_XML = YES"; echo -n "PROJECT_NUMBER = ";svnversion ../..) | $(SUNSYS_PATH)/dox sunsys-dox -

all: default sunsys

clean:
	rm -rf dox
	rm -rf sunsys-dox
