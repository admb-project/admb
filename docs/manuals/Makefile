#!/bin/bash
# $Id: Makefile 655 2010-06-09 01:10:00Z jsibert $
#
# Author: John Sibert
# Copyright (c) 2008, 2009, 2010 ADMB Foundation
#
.PHONY: MANUALS WRITERS_GUIDE ALL INSTALLATION clean

ADMB_PATH=admb
ADMB_RE_PATH=admb-re
AUTODIF_PATH=autodif
SAMPLE_PATH=admb-sample
ADMBMANUAL_PATH=admbmanual

all: admb.pdf admbre.pdf autodif.pdf
	mkdir -p ../../build/manuals
	mv -v admb.pdf ../../build/manuals
	mv -v admbre.pdf ../../build/manuals
	mv -v autodif.pdf ../../build/manuals

WRITERS_GUIDE: admbmanual.pdf admb-sample.pdf

MANUALS: admb.pdf admbre.pdf autodif.pdf

# YOU NEED TO BE SUPERUSER TO DO THIS
INSTALLATION:
	cp -vf ./share/license.tex $(ADMBMANUAL_PATH)
	cp -vf ./share/ADMB-logo.png $(ADMBMANUAL_PATH) 
	$(MAKE) -C $(ADMBMANUAL_PATH) INSTALLATION

admbmanual.pdf : $(ADMBMANUAL_PATH)/admbmanual.dtx
	cp -vf ./share/license.tex $(ADMBMANUAL_PATH)
	cp -vf ./share/ADMB-logo.png $(ADMBMANUAL_PATH) 
	$(MAKE) -C $(ADMBMANUAL_PATH) all

admb-sample.pdf: $(SAMPLE_PATH)/admb-sample.tex
	cp -vf $(ADMBMANUAL_PATH)/admbmanual.cls $(SAMPLE_PATH) 
	cp -vf ./share/ADMB-logo.png $(SAMPLE_PATH) 
	$(MAKE) -C $(SAMPLE_PATH) -f ../share/Makefile.DC filename=admb-sample
	mv -v $(SAMPLE_PATH)/admb-sample.pdf $@

admbre.pdf: $(ADMB_RE_PATH)/admbre.tex $(ADMBMANUAL_PATH)/admbmanual.cls
	cp -vf $(ADMBMANUAL_PATH)/admbmanual.cls $(ADMB_RE_PATH) 
	cp -vf ./share/ADMB-logo.png $(ADMB_RE_PATH) 
	$(MAKE) -C $(ADMB_RE_PATH) -f ../share/Makefile.DC filename=admbre
	mv -v $(ADMB_RE_PATH)/admbre.pdf $@

admb.pdf: $(ADMB_PATH)/admb.tex $(ADMBMANUAL_PATH)/admbmanual.cls
	cp -vf $(ADMBMANUAL_PATH)/admbmanual.cls $(ADMB_PATH) 
	cp -vf ./share/ADMB-logo.png $(ADMB_PATH) 
	$(MAKE) -C $(ADMB_PATH) -f ../share/Makefile.DC filename=admb
	mv -v $(ADMB_PATH)/admb.pdf $@

autodif.pdf: $(AUTODIF_PATH)/autodif.tex $(ADMBMANUAL_PATH)/admbmanual.cls
	cp -vf $(ADMBMANUAL_PATH)/admbmanual.cls $(AUTODIF_PATH) 
	cp -vf ./share/ADMB-logo.png $(AUTODIF_PATH) 
	$(MAKE) -C $(AUTODIF_PATH) -f ../share/Makefile.DC filename=autodif
	mv -v $(AUTODIF_PATH)/autodif.pdf $@

$(ADMBMANUAL_PATH)/admbmanual.cls:
	$(MAKE) --directory=admbmanual admbmanual.cls

clean:
	@$(MAKE) -C $(ADMB_PATH)    -f ../share/Makefile.DC clean filename=admb
	@$(MAKE) -C $(AUTODIF_PATH) -f ../share/Makefile.DC clean filename=autodif
	@$(MAKE) -C $(ADMB_RE_PATH) -f ../share/Makefile.DC clean filename=admbre
	@$(MAKE) -C $(SAMPLE_PATH)  -f ../share/Makefile.DC clean filename=admb-sample
#	$(MAKE) -C $(ADMBMANUAL_PATH) clean
	@rm -rvf pdfs
	@rm -fv admb.pdf autodif.pdf admbre.pdf admbmanual.pdf admb-sample.pdf
	@rm -vf admbmanual/admbmanual.cls
	@rm -vf admbmanual/admbmanual.glo
	@rm -vf admbmanual/admbmanual.log
	@rm -vf admbmanual/license.tex
	@rm -vf admbmanual/ADMB-logo.png
	@rm -vf admbmanual/admbmanual.idx
	@rm -vf admbmanual/admbmanual.aux
	@rm -vf admb-sample/admb-sample.1.log
	@rm -vf admb-sample/admbmanual.cls
	@rm -vf admb-sample/admb-sample.2.log
	@rm -vf admb-sample/ADMB-logo.png
	@rm -vf admb/admbmanual.cls
	@rm -vf admb/admb.1.log
	@rm -vf admb/admb.2.log
	@rm -vf admb/ADMB-logo.png
	@rm -vf admb-re/admbmanual.cls
	@rm -vf admb-re/ADMB-logo.png
	@rm -vf admb-re/admbre.1.log
	@rm -vf admb-re/admbre.2.log
	@rm -vf autodif/admbmanual.cls
	@rm -vf autodif/ADMB-logo.png
	@rm -vf autodif/autodif.1.log
	@rm -vf autodif/autodif.2.log
