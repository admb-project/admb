# $Id$
#
# Author: John Sibert 
# Copyright (c) 2009 ADMB Foundation
#
.PHONY=CLEAN REFCARDS

REFCARDS: ADMBrefcard-A4.pdf ADMBrefcard-USletter.pdf

ADMBrefcard-A4.pdf: ADMBrefcard-A4.tex ADMBrefcard-text.tex cropped-logo-20080527.jpeg
	pdflatex ADMBrefcard-A4
	pdflatex ADMBrefcard-A4

ADMBrefcard-USletter.pdf: ADMBrefcard-USletter.tex ADMBrefcard-text.tex cropped-logo-20080527.jpeg
	pdflatex ADMBrefcard-USletter
	pdflatex ADMBrefcard-USletter

CLEAN:
	rm -vf *.pdf
	rm -vf *.aux
	rm -vf *.log
