all: 
	$(MAKE) agemat.tpl
	..\\..\\admb agemat.tpl
	$(MAKE) run

run: agemat.dat
	agemat

agemat.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/executables/AGEMAT.TPL > agemat.tpl

agemat.dat:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/doc/agemat.dat > agemat.dat

total-clean:
	@del /Q agemat.dat
	@del /Q agemat.tpl

clean:
	@del /Q agemat agemat.cpp agemat.htp agemat.obj
	@del /Q Echo.Out
	@del /Q admodel.cov
	@del /Q admodel.dep
	@del /Q admodel.hes
	@del /Q agemat.b01
	@del /Q agemat.bar
	@del /Q agemat.cor
	@del /Q agemat.eva
	@del /Q agemat.log
	@del /Q agemat.p01
	@del /Q agemat.par
	@del /Q agemat.r01
	@del /Q agemat.rep
	@del /Q agemat.std
	@del /Q agemat
	@del /Q agemat.exe
	@del /Q cmpdiff.tmp
	@del /Q eigv.rpt
	@del /Q fmin.log
	@del /Q gradfil1.tmp
	@del /Q gradfil2.tmp
	@del /Q variance
	@del /Q varssave.tmp
