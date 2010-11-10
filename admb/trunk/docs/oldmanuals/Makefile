# $Id:   $
#
# Author: John Sibert
# Copyright (c) 2008 ADMB Foundation
#
ADMB_PATH=admb
ADMB_RE_PATH=admb-re
AUTODIF_PATH=autodif

MANUALS: admb.pdf admb-re.pdf autodif.pdf

admb.pdf: $(ADMB_PATH)/all_ad.tex
	make -C $(ADMB_PATH) all_ad.pdf
	cp -v $(ADMB_PATH)/all_ad.pdf $@

autodif.pdf: $(AUTODIF_PATH)/all_au.tex
	make -C $(AUTODIF_PATH) all_au.pdf
	cp -v $(AUTODIF_PATH)/all_au.pdf $@

admb-re.pdf: $(ADMB_RE_PATH)/admbre.tex
	make -C $(ADMB_RE_PATH) admbre.pdf
	cp -v $(ADMB_RE_PATH)/admbre.pdf $@

clean:
	make -C $(AUTODIF_PATH) clean
