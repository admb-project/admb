ifeq ($(OS),Windows_NT)
EXT=.sh
endif

all:
	$(MAKE) changepoint.tpl
	../../admb$(EXT) changepoint.tpl
	$(MAKE) run

run: changepoint.dat
	./changepoint

changepoint.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/executables/AGEMAT.TPL > changepoint.tpl

changepoint.dat:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/doc/changepoint.dat > changepoint.dat

clean:
	@rm -vf changepoint changepoint.cpp changepoint.htp changepoint.obj
	@rm -vf Echo.Out
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf changepoint.b01
	@rm -vf changepoint.bar
	@rm -vf changepoint.cor
	@rm -vf changepoint.eva
	@rm -vf changepoint.log
	@rm -vf changepoint.p01
	@rm -vf changepoint.par
	@rm -vf changepoint.r01
	@rm -vf changepoint.rep
	@rm -vf changepoint.std
	@rm -vf cmpdiff.tmp
	@rm -vf eigv.rpt
	@rm -vf fmin.log
	@rm -vf gradfil1.tmp
	@rm -vf gradfil2.tmp
	@rm -vf variance
	@rm -vf varssave.tmp
