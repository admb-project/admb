# $Id: Makefile 655M 2010-09-14 22:43:32Z (local) $
#
# Author: John Sibert
# Copyright (c) 2008, 2009, 2010 ADMB Foundation
#
.PHONY: MANUALS WRITERS_GUIDE ALL

ADMB_PATH=admb
ADMB_RE_PATH=admb-re
AUTODIF_PATH=autodif
SAMPLE_PATH=admb-sample

MANUALS: admb.pdf admb-re.pdf autodif.pdf

WRITERS_GUIDE: admbmanual.pdf admb-sample.pdf

ALL: MANUALS WRITERS_GUIDE

admbmanual.pdf : admbmanual.dtx
	pdflatex admbmanual.dtx

admb-sample.pdf: $(SAMPLE_PATH)/admb-sample.tex
	cp -f Makefile.DC  $(SAMPLE_PATH)/Makefile
	make -C $(SAMPLE_PATH) filename=admb-sample
	mv -v $(SAMPLE_PATH)/admb-sample.pdf $@

admb.pdf: $(ADMB_PATH)/admb.tex
	cp -f Makefile.DC  $(ADMB_PATH)/Makefile
	make -C $(ADMB_PATH) filename=admb
	mv -v $(ADMB_PATH)/admb.pdf $@

autodif.pdf: $(AUTODIF_PATH)/autodif.tex
	cp -f Makefile.DC  $(AUTODIF_PATH)/Makefile
	make -C $(AUTODIF_PATH) filename=autodif
	mv -v $(AUTODIF_PATH)/autodif.pdf $@

admb-re.pdf: $(ADMB_RE_PATH)/admbre.tex
	cp -f Makefile.DC  $(ADMB_RE_PATH)/Makefile
	make -C $(ADMB_RE_PATH) filename=admbre
	mv -v $(ADMB_RE_PATH)/admbre.pdf $@

admbmanual.cls : admbmanual.ins admbmanual.dtx
	pdflatex admbmanual.ins

clean:
	make -C $(ADMB_PATH) clean filename=admb
	make -C $(AUTODIF_PATH) clean filename=autodif
	make -C $(ADMB_RE_PATH) clean filename=admbre
	make -C $(SAMPLE_PATH) clean filename=admb-sample
	make -f Makefile.DC clean filename=admbmanual
	rm -fv admb.pdf autodif.pdf admb-re.pdf admbmanual.pdf admb-sample.pdf
