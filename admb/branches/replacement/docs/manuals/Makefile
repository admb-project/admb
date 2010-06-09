# $Id$
#
# Author: John Sibert
# Copyright (c) 2008, 2009, 2010 ADMB Foundation
#
.PHONY: MANUALS

ADMB_PATH=admb
ADMB_RE_PATH=admb-re
AUTODIF_PATH=autodif

MANUALS: admb.pdf admb-re.pdf autodif.pdf

admb.pdf: $(ADMB_PATH)/admb.tex
	make -C $(ADMB_PATH) filename=admb
	mv -v $(ADMB_PATH)/admb.pdf $@

autodif.pdf: $(AUTODIF_PATH)/autodif.tex
	make -C $(AUTODIF_PATH) filename=autodif
	mv -v $(AUTODIF_PATH)/autodif.pdf $@

admb-re.pdf: $(ADMB_RE_PATH)/admbre.tex
	make -C $(ADMB_RE_PATH) filename=admbre
	mv -v $(ADMB_RE_PATH)/admbre.pdf $@

clean:
	make -C $(ADMB_PATH) clean filename=admb
	make -C $(AUTODIF_PATH) clean filename=autodif
	make -C $(ADMB_RE_PATH) clean filename=admbre
	rm -fv admb.pdf autodif.pdf admb-re.pdf
