.SUFFIXES: .pdf .tex .png
all: admb-seqdiag.png admb-blockdiag.png
all2: big-admb-component.png admb-component.pdf admb-seqdiag.png admb-blockdiag.png

%.pdf:%.tex
	pdflatex $^

big-admb-component.png: big-admb-component.pdf
#	extract page 2
	gs -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -dFirstPage=2 -dLastPage=2 -sOutputFile=t1.pdf $*.pdf
#	crop page 2
	pdfcrop --verbose --margins 0 --clip t1.pdf t2.pdf
#	convert to 300 dpi png
	convert -antialias -density 600 t2.pdf $@

admb-component.pdf: admb-component.tex
	pdflatex admb-component

admb-seqdiag.png: admb-seqdiag
	seqdiag -f /Library/Fonts/Verdana\ Bold.ttf admb-seqdiag

admb-blockdiag.png: admb-blockdiag
	blockdiag admb-blockdiag

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

