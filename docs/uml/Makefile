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

