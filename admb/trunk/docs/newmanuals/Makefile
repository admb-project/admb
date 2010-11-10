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

MANUALS: admb.pdf admbre.pdf autodif.pdf

WRITERS_GUIDE: admbmanual.pdf admb-sample.pdf

ALL: MANUALS WRITERS_GUIDE

# YOU NEED TO BE SUPERUSER TO DO THIS
INSTALLATION:
	cp -vf ./share/license.tex $(ADMBMANUAL_PATH)
	cp -vf ./share/ADMB-logo.png $(ADMBMANUAL_PATH) 
	make -C $(ADMBMANUAL_PATH) INSTALLATION

admbmanual.pdf : $(ADMBMANUAL_PATH)/admbmanual.dtx
	cp -vf ./share/license.tex $(ADMBMANUAL_PATH)
	cp -vf ./share/ADMB-logo.png $(ADMBMANUAL_PATH) 
	make -C $(ADMBMANUAL_PATH) admbmanual.pdf

admb-sample.pdf: $(SAMPLE_PATH)/admb-sample.tex
	make -C $(SAMPLE_PATH) -f ../share/Makefile.DC filename=admb-sample
	mv -v $(SAMPLE_PATH)/admb-sample.pdf $@

admbre.pdf: $(ADMB_RE_PATH)/admbre.tex
	make -C $(ADMB_RE_PATH) -f ../share/Makefile.DC filename=admbre
	mv -v $(ADMB_RE_PATH)/admbre.pdf $@

admb.pdf: $(ADMB_PATH)/admb.tex
	make -C $(ADMB_PATH) -f ../share/Makefile.DC filename=admb
	mv -v $(ADMB_PATH)/admb.pdf $@

autodif.pdf: $(AUTODIF_PATH)/autodif.tex
	make -C $(AUTODIF_PATH) -f ../share/Makefile.DC filename=autodif
	mv -v $(AUTODIF_PATH)/autodif.pdf $@

clean:
	make -C $(ADMB_PATH)    -f ../share/Makefile.DC clean filename=admb
	make -C $(AUTODIF_PATH) -f ../share/Makefile.DC clean filename=autodif
	make -C $(ADMB_RE_PATH) -f ../share/Makefile.DC clean filename=admbre
	make -C $(SAMPLE_PATH)  -f ../share/Makefile.DC clean filename=admb-sample
#	make -C $(ADMBMANUAL_PATH) clean
	rm -fv admb.pdf autodif.pdf admbre.pdf admbmanual.pdf admb-sample.pdf
