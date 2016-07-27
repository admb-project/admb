ifeq ($(TERM),cygwin)
else
ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif
endif

all: agemat.tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb agemat.tpl
else
	../../admb$(EXT) agemat.tpl
endif
	$(MAKE) run

run: agemat.dat
ifeq ($(SHELL),cmd)
	agemat
else
	./agemat
endif

agemat.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/executables/AGEMAT.TPL > agemat.tpl

agemat.dat:
	svn cat svn://scm.r-forge.r-project.org/svnroot/nwfscassmt/pkg/nwfscAgeingError/inst/doc/agemat.dat > agemat.dat

total-clean: clean
ifeq ($(SHELL),cmd)
else
	@rm -vf agemat.dat
	@rm -vf agemat.tpl
endif

clean:
ifeq ($(SHELL),cmd)
else
	@rm -vf agemat.exe
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
	@rm -vf agemat
	@rm -vf cmpdiff.tmp
	@rm -vf eigv.rpt
	@rm -vf fmin.log
	@rm -vf gradfil1.tmp
	@rm -vf gradfil2.tmp
	@rm -vf variance
	@rm -vf varssave.tmp
endif

get-outputs:
ifeq ($(SHELL),cmd)
	type agemat.bar
	type agemat.cor
	type agemat.eva
	type agemat.p01
	type agemat.par
	type agemat.r01
	type agemat.rep
	type agemat.std
	type Echo.Out
else
	cat agemat.bar
	cat agemat.cor
	cat agemat.eva
	cat agemat.p01
	cat agemat.par
	cat agemat.r01
	cat agemat.rep
	cat agemat.std
	cat Echo.Out
endif
