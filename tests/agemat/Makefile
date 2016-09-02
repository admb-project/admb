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
	@if exist agemat.dat del /Q agemat.dat
	@if exist agemat.tpl del /Q agemat.tpl

clean:
	@del /Q agemat agemat.cpp agemat.htp agemat.obj 2>nul
	@del /Q Echo.Out 2>nul
	@del /Q admodel.cov 2>nul
	@del /Q admodel.dep 2>nul
	@del /Q admodel.hes 2>nul
	@del /Q agemat.b01 2>nul
	@del /Q agemat.bar 2>nul
	@del /Q agemat.cor 2>nul
	@del /Q agemat.eva 2>nul
	@del /Q agemat.log 2>nul
	@del /Q agemat.p01 2>nul
	@del /Q agemat.par 2>nul
	@del /Q agemat.r01 2>nul
	@del /Q agemat.rep 2>nul
	@del /Q agemat.std 2>nul
	@del /Q agemat 2>nul
	@del /Q agemat.exe 2>nul
	@del /Q cmpdiff.tmp 2>nul
	@del /Q eigv.rpt 2>nul
	@del /Q fmin.log 2>nul
	@del /Q gradfil1.tmp 2>nul
	@del /Q gradfil2.tmp 2>nul
	@del /Q variance 2>nul
	@del /Q varssave.tmp 2>nul
