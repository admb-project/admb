.SUFFIXES: .pdf .tex .png

all: admb-seqdiag.png admb-blockdiag.png

admb-seqdiag.png: admb-seq.diag
	seqdiag -f /Library/Fonts/Verdana\ Bold.ttf admb-seq.diag

admb-blockdiag.png: admb-block.diag
	blockdiag -f /Library/Fonts/Verdana\ Bold.ttf admb-block.diag

tex: big-admb-component.png admb-component.pdf

%.pdf:%.tex
	pdflatex $^

admb-component.pdf: admb-component.tex
	pdflatex admb-component

big-admb-component.png: big-admb-component.pdf
#	extract page 2
	gs -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -dFirstPage=2 -dLastPage=2 -sOutputFile=t1.pdf $*.pdf
#	crop page 2
	pdfcrop --verbose --margins 0 --clip t1.pdf t2.pdf
#	convert to 300 dpi png
	convert -antialias -density 600 t2.pdf $@

clean:
	@rm -vf *.png
	@rm -vf *.aux
	@rm -vf *.aux
	@rm -vf *.out
	@rm -vf *.log
	@rm -vf *.pdf
	@rm -vf simple
	@rm -vf simple.bar
	@rm -vf simple.cor
	@rm -vf simple.cpp
	@rm -vf simple.eva
	@rm -vf simple.htp
	@rm -vf simple.log
	@rm -vf simple.obj
	@rm -vf simple.par
	@rm -vf simple.rep
	@rm -vf simple.std
	@rm -vf admodel.hes
	@rm -vf simple.def
	@rm -vf variance
	@rm -vf admodel.cov
	@rm -vf eigv.rpt
	@rm -vf fmin.log
	@rm -vf admodel.dep
	@rm -vf trace.log

