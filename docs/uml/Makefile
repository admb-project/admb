all: admb-component.pdf admb-seqdiag.png admb-blockdiag.png

admb-component.pdf: admb-component.tex
	pdflatex admb-component

admb-seqdiag.png: admb-seqdiag
	seqdiag admb-seqdiag

admb-blockdiag.png: admb-blockdiag
	blockdiag admb-blockdiag

clean:
	@rm -vf admb-blockdiag.png
	@rm -vf admb-seqdiag.png
	@rm -vf admb-component.aux
	@rm -vf admb-component.log
	@rm -vf admb-component.pdf

