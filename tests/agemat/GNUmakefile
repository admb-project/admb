ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifeq ($(findstring bash.exe,$(shell where bash.exe 2>&1 | findstr bash.exe)),bash.exe)
      EXT=.sh
    else
      CMDSHELL=cmd
    endif
  endif
endif

all: agemat.tpl

ifeq ($(CMDSHELL),cmd)
	..\\..\\admb agemat.tpl
else
	../../admb$(EXT) agemat.tpl
endif
	$(MAKE) run

run:
ifeq ($(CMDSHELL),cmd)
	agemat
else
	./agemat
endif


agemat.tpl: agemat.dat
	cp rforge-nwfscassmt/pkg/nwfscAgeingError/inst/executables/AGEMAT.TPL agemat.tpl

agemat.dat: rforge-nwfscassmt
	cp rforge-nwfscassmt/pkg/nwfscAgeingError/inst/doc/agemat.dat .

rforge-nwfscassmt:
	git clone --depth 1 https://github.com/rforge/nwfscassmt rforge-nwfscassmt

total-clean: clean
ifeq ($(CMDSHELL),cmd)
else
	@rm -vf agemat.dat
	@rm -vf agemat.tpl
	@rm -rvf rforge-nwfscassmt
endif

clean:
ifeq ($(CMDSHELL),cmd)
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
ifeq ($(CMDSHELL),cmd)
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
