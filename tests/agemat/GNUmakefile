ifeq ($(OS),Windows_NT)
EXT=.sh
endif

all:
	$(MAKE) agemat.tpl
	../../admb$(EXT) agemat.tpl
	$(MAKE) run

run: agemat.dat
	./agemat

agemat.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/executables/AGEMAT.TPL > agemat.tpl

agemat.dat:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/doc/agemat.dat > agemat.dat

clean:
	@rm -vf agemat agemat.cpp agemat.htp agemat.obj
	@rm -vf Echo.Out
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf agemat.b01
	@rm -vf agemat.bar
	@rm -vf agemat.cor
	@rm -vf agemat.eva
	@rm -vf agemat.log
	@rm -vf agemat.p01
	@rm -vf agemat.par
	@rm -vf agemat.r01
	@rm -vf agemat.rep
	@rm -vf agemat.std
	@rm -vf cmpdiff.tmp
	@rm -vf eigv.rpt
	@rm -vf fmin.log
	@rm -vf gradfil1.tmp
	@rm -vf gradfil2.tmp
	@rm -vf variance
	@rm -vf varssave.tmp
