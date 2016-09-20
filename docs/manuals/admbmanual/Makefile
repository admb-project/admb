# $Id: Makefile 655 2010-06-09 01:10:00Z jsibert $
#
# Author: John Sibert
# Copyright (c) 2008, 2009, 2010 ADMB Foundation
#
#
# see http://en.wikibooks.org/wiki/LaTeX/Packages/Installing_Extra_Packages
# The (perhaps) only installation dependenciecs are the LaTeX path and
# the LaTeX indexing utility.
# The wikibooks entry lists the main variants as follows:
#   - teTeX, TeX Live, fpTeX: texhash
#   - web2c: mktexlsr
#   - MikTeX: initexmf --update-fndb (or use the GUI)
#   - MiKTeX 2.7 ot later versions, installed on Widows XP or later versions of Windows, blah ...
# On my lucid ubuntu, texhash is a softlink to mktexlsr

LATEX_PATH=/usr/share/texmf/tex/latex
INDEXER=mktexlsr

.PHONY: INSTALLATION clean

all: admbmanual.pdf admbmanual.cls

admbmanual.pdf: admbmanual.dtx 
	pdflatex admbmanual.dtx
	mv admbmanual.pdf ..

admbmanual.cls: admbmanual.ins admbmanual.dtx 
	latex admbmanual.ins 

# YOU NEED TO BE SUPERUSER TO DO THIS
INSTALLATION: admbmanual.cls admbmanual.ins admbmanual.dtx 
	pdflatex admbmanual.dtx
	mkdir -pv $(LATEX_PATH)/admbmanual
	cp -v admbmanual.* $(LATEX_PATH)/admbmanual
	cp -v license.tex $(LATEX_PATH)/admbmanual
	cp -v ADMB-logo.png $(LATEX_PATH)/admbmanual
	$(INDEXER)

clean:
	rm -fv admbmanual.pdf
	rm -fv admbmanual.log
	rm -fv admbmanual.idx
	rm -fv admbmanual.glo
	rm -fv admbmanual.aux
	rm -fv admbmanual.cls  
	rm -fv license.tex
	rm -rv ADMB-logo.png
