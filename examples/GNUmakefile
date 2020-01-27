.ONESHELL:

ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
      CMDSHELL=cmd
  else
    ifneq ($(findstring bash.exe,$(shell where bash.exe 2>&1 | findstr bash.exe)),bash.exe)
      CMDSHELL=cmd
    endif
  endif
  ifeq ($(CMDSHELL),cmd)
    ADMB_HOME=..\\..\\..
  else
    EXT=.sh
  endif
endif
ifndef ADMB_HOME
    ADMB_HOME=../../..
endif

ifdef ADMB_OPTIONS
OPTIONS:= $(ADMB_OPTIONS)
endif
ifeq ($(DEBUG),yes)
OPTIONS:= $(OPTIONS) -g
endif
ifdef FAST_OPTION
OPTIONS:= $(OPTIONS) -f
endif

ifndef PROG
  ifneq ($(CMDSHELL),cmd)
    PROG=time
  endif
endif

ADMB_TPLS=\
 buscycle\
 catage\
 chem_eng\
 forest\
 finance\
 pella_t\
 robreg\
 truncreg\
 simple\
 vol

ADMB_RE_TPLS=\
 bcb\
 biglog\
 bvprobit\
 glmmadmb\
 caest\
 gamma\
 kidney\
 lidar\
 logistic\
 nbmm\
 nested4\
 orange\
 orange2\
 orange_cor\
 pheno\
 polio\
 sdv\
 skewed\
 socatt\
 spatial\
 union\
 weights

default: simple

all: admb admb-re autodif

admb: $(ADMB_TPLS)

buscycle:
	$(MAKE) ham4 
	$(MAKE) ham5
ham4:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\buscycle && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb/buscycle && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

ham5:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\buscycle && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb/buscycle && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

catage:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

chem_eng:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

finance:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

forest:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

pella_t:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

robreg:
	$(MAKE) vonb
	$(MAKE) vonbr
vonb:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\robreg && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb/robreg && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

vonbr:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\robreg && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb/robreg && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

simple-version:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\simple && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ -version && popd
else
	cd admb/simple && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@ -version
endif

simple:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

truncreg:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\$@ && $(ADMB_HOME)\\admb$(EXT) $(OPTIONS) $@ && $(PROG) $@ -ams 2000000 && $(PROG) $@ -ams 2000000 -gbs 6000000 -cbs 4000000 && popd
else
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@ -ams 2000000 && $(PROG) ./$@ -ams 2000000 -gbs 6000000 -cbs 4000000
endif

vol: n2mvol
n2mvol:
ifeq ($(CMDSHELL),cmd)
	pushd admb\\vol && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb/vol && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@ -iprint 1
endif

admb-re: $(ADMB_RE_TPLS)

bcb:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

biglog:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT)  $(OPTIONS) $@ && $(PROG) ./$@
endif

bvprobit:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\glmmadmb && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/glmmadmb && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

glmmadmb:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ -maxph 5 -noinit -shess -crit 1.e-6 && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@ -maxph 5 -noinit -shess -crit 1.e-6
endif

caest:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

gamma:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) liver_$@ && $(PROG) liver_$@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) liver_$@ && $(PROG) ./liver_$@
endif

kidney:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

lidar:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

logistic:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

nbmm:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/nbmm && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

nested4:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

orange:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

orange2:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

orange_cor:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif
pheno:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

polio:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

sdv:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

skewed:
	$(MAKE) diet
	$(MAKE) diet_sk
diet:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\skewed && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/skewed && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

diet_sk:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\skewed && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/skewed && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

socatt:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

spatial:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

union:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

weights: binomial
binomial:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\weights && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/weights && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif
binomial_w2:
ifeq ($(CMDSHELL),cmd)
	pushd admb-re\\weights && $(ADMB_HOME)\\admb $(OPTIONS) $@ && $(PROG) $@ && popd
else
	cd admb-re/weights && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

autodif: bigmin hemholtz io_examp normsim newt s1 autodif-simple simple2 simp1 struct oldstr

bigmin:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd
else
	cd autodif/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@.cpp && $(PROG) ./$@
endif

hemholtz:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp hem_func.cpp && $(PROG) $@ && popd
else
	cd autodif/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@.cpp hem_func.cpp && $(PROG) ./$@
endif

io_examp:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd
else
	cd autodif/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@.cpp && $(PROG) ./$@
endif

minimize:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp userfun.cpp && $(PROG) $@ && popd
else
	cd autodif/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@.cpp userfun.cpp && $(PROG) ./$@
endif

mixture:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp normaliz.cpp reset.cpp like.cpp savepar.cpp xinit.cpp nvarcal.cpp fcomp_m.cpp && $(PROG) $@ && popd
else
	cd autodif/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@.cpp normaliz.cpp reset.cpp like.cpp savepar.cpp xinit.cpp nvarcal.cpp fcomp_m.cpp && $(PROG) ./$@
endif

normsim:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\mixture && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd
else
	cd autodif/mixture && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@.cpp && $(PROG) ./$@
endif

newt:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd
else
	cd autodif/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@.cpp && $(PROG) ./$@
endif

s1:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\simple && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd
else
	cd autodif/simple && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@.cpp && $(PROG) ./$@
endif

autodif-simple:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\simple && $(ADMB_HOME)\\admb $(OPTIONS) simple.cpp fcomp_s.cpp && $(PROG) simple && popd
else
	cd autodif/simple && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) simple.cpp fcomp_s.cpp && $(PROG) ./simple
endif

simple2:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\simple && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp fcomp_s.cpp && $(PROG) $@ && popd
else
	cd autodif/simple && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@.cpp fcomp_s.cpp && $(PROG) ./$@
endif

simp1:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\simple && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp fcomp_s.cpp && $(PROG) $@ && popd
else
	cd autodif/simple && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@.cpp fcomp_s.cpp && $(PROG) ./$@
endif

struct:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd
else
	cd autodif/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@.cpp && $(PROG) ./$@
endif

oldstr:
ifeq ($(CMDSHELL),cmd)
	pushd autodif\\struct && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd
else
	cd autodif/struct && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@.cpp && $(PROG) ./$@
endif

copy:
ifneq ($(DEBUG),yes)
  ifeq ($(CMDSHELL),cmd)
	if not exist ..\build\dist\examples md ..\build\dist\examples
	xcopy ..\examples ..\build\dist\examples /S /Y /D
  else
	cp -Rvf ../examples ../build/dist
  endif
else
  ifeq ($(CMDSHELL),cmd)
	if not exist ..\build\debug\examples md ..\build\debug\examples
	xcopy ..\examples ..\build\debug\examples /S /Y /D
  else
	cp -Rvf ../examples ../build/debug
  endif
endif

clean:
ifeq ($(CMDSHELL),cmd)
	@del admb-re\bcb\admodel.cov
	@del admb-re\\bcb\\admodel.cov
	@del admb-re\\bcb\\admodel.dep
	@del admb-re\\bcb\\admodel.hes
	@del admb-re\\bcb\\bcb.exe
	@del admb-re\\bcb\\bcb.bar
	@del admb-re\\bcb\\bcb.bgs
	@del admb-re\\bcb\\bcb.cor
	@del admb-re\\bcb\\bcb.cpp
	@del admb-re\\bcb\\bcb.eva
	@del admb-re\\bcb\\bcb.htp
	@del admb-re\\bcb\\bcb.log
	@del admb-re\\bcb\\bcb.luu
	@del admb-re\\bcb\\bcb.obj
	@del admb-re\\bcb\\bcb.par
	@del admb-re\\bcb\\bcb.rep
	@del admb-re\\bcb\\bcb.rhes
	@del admb-re\\bcb\\bcb.std
	@del admb-re\\bcb\\fmin.log
	@del admb-re\\bcb\\hesscheck
	@del admb-re\\bcb\\hessian.bin
	@del admb-re\\biglog\\admodel.cov
	@del admb-re\\biglog\\admodel.dep
	@del admb-re\\biglog\\admodel.hes
	@del admb-re\\biglog\\biglog.exe
	@del admb-re\\biglog\\biglog.b01
	@del admb-re\\biglog\\biglog.b02
	@del admb-re\\biglog\\biglog.bar
	@del admb-re\\biglog\\biglog.bgs
	@del admb-re\\biglog\\biglog.cor
	@del admb-re\\biglog\\biglog.cpp
	@del admb-re\\biglog\\biglog.eva
	@del admb-re\\biglog\\biglog.htp
	@del admb-re\\biglog\\biglog.log
	@del admb-re\\biglog\\biglog.luu
	@del admb-re\\biglog\\biglog.obj
	@del admb-re\\biglog\\biglog.p01
	@del admb-re\\biglog\\biglog.p02
	@del admb-re\\biglog\\biglog.par
	@del admb-re\\biglog\\biglog.rhes
	@del admb-re\\biglog\\biglog.std
	@del admb-re\\biglog\\fmin.log
	@del admb-re\\biglog\\hesscheck
	@del admb-re\\biglog\\hessian.bin
	@del admb-re\\caest\\admodel.cov
	@del admb-re\\caest\\admodel.dep
	@del admb-re\\caest\\admodel.hes
	@del admb-re\\caest\\caest.exe
	@del admb-re\\caest\\caest.b01
	@del admb-re\\caest\\caest.bar
	@del admb-re\\caest\\caest.bgs
	@del admb-re\\caest\\caest.cor
	@del admb-re\\caest\\caest.cpp
	@del admb-re\\caest\\caest.eva
	@del admb-re\\caest\\caest.htp
	@del admb-re\\caest\\caest.log
	@del admb-re\\caest\\caest.luu
	@del admb-re\\caest\\caest.obj
	@del admb-re\\caest\\caest.p01
	@del admb-re\\caest\\caest.par
	@del admb-re\\caest\\caest.r01
	@del admb-re\\caest\\caest.rep
	@del admb-re\\caest\\caest.rhes
	@del admb-re\\caest\\caest.std
	@del admb-re\\caest\\fmin.log
	@del admb-re\\caest\\hesscheck
	@del admb-re\\caest\\hessian.bin
	@del admb-re\\gamma\\admodel.cov
	@del admb-re\\gamma\\admodel.dep
	@del admb-re\\gamma\\admodel.hes
	@del admb-re\\gamma\\fmin.log
	@del admb-re\\gamma\\hesscheck
	@del admb-re\\gamma\\hessian.bin
	@del admb-re\\gamma\\liver_gamma.exe
	@del admb-re\\gamma\\liver_gamma.b01
	@del admb-re\\gamma\\liver_gamma.bar
	@del admb-re\\gamma\\liver_gamma.bgs
	@del admb-re\\gamma\\liver_gamma.cor
	@del admb-re\\gamma\\liver_gamma.cpp
	@del admb-re\\gamma\\liver_gamma.eva
	@del admb-re\\gamma\\liver_gamma.htp
	@del admb-re\\gamma\\liver_gamma.log
	@del admb-re\\gamma\\liver_gamma.obj
	@del admb-re\\gamma\\liver_gamma.p01
	@del admb-re\\gamma\\liver_gamma.par
	@del admb-re\\gamma\\liver_gamma.rhes
	@del admb-re\\gamma\\liver_gamma.std
	@del admb-re\\glmmadmb\\admodel.cov
	@del admb-re\\glmmadmb\\admodel.dep
	@del admb-re\\glmmadmb\\admodel.hes
	@del admb-re\\glmmadmb\\b1
	@del admb-re\\glmmadmb\\b2
	@del admb-re\\glmmadmb\\bvprobit.exe
	@del admb-re\\glmmadmb\\bvprobit.b01
	@del admb-re\\glmmadmb\\bvprobit.bar
	@del admb-re\\glmmadmb\\bvprobit.bgs
	@del admb-re\\glmmadmb\\bvprobit.cor
	@del admb-re\\glmmadmb\\bvprobit.cpp
	@del admb-re\\glmmadmb\\bvprobit.eva
	@del admb-re\\glmmadmb\\bvprobit.htp
	@del admb-re\\glmmadmb\\bvprobit.log
	@del admb-re\\glmmadmb\\bvprobit.obj
	@del admb-re\\glmmadmb\\bvprobit.p01
	@del admb-re\\glmmadmb\\bvprobit.par
	@del admb-re\\glmmadmb\\bvprobit.r01
	@del admb-re\\glmmadmb\\bvprobit.rep
	@del admb-re\\glmmadmb\\bvprobit.rhes
	@del admb-re\\glmmadmb\\bvprobit.std
	@del admb-re\\glmmadmb\\fmin.log
	@del admb-re\\glmmadmb\\glmmadmb.exe
	@del admb-re\\glmmadmb\\glmmadmb.b01
	@del admb-re\\glmmadmb\\glmmadmb.b02
	@del admb-re\\glmmadmb\\glmmadmb.b03
	@del admb-re\\glmmadmb\\glmmadmb.b04
	@del admb-re\\glmmadmb\\glmmadmb.bar
	@del admb-re\\glmmadmb\\glmmadmb.bgs
	@del admb-re\\glmmadmb\\glmmadmb.cor
	@del admb-re\\glmmadmb\\glmmadmb.cpp
	@del admb-re\\glmmadmb\\glmmadmb.eva
	@del admb-re\\glmmadmb\\glmmadmb.htp
	@del admb-re\\glmmadmb\\glmmadmb.log
	@del admb-re\\glmmadmb\\glmmadmb.luu
	@del admb-re\\glmmadmb\\glmmadmb.obj
	@del admb-re\\glmmadmb\\glmmadmb.p01
	@del admb-re\\glmmadmb\\glmmadmb.p02
	@del admb-re\\glmmadmb\\glmmadmb.p03
	@del admb-re\\glmmadmb\\glmmadmb.p04
	@del admb-re\\glmmadmb\\glmmadmb.par
	@del admb-re\\glmmadmb\\glmmadmb.r01
	@del admb-re\\glmmadmb\\glmmadmb.r02
	@del admb-re\\glmmadmb\\glmmadmb.r03
	@del admb-re\\glmmadmb\\glmmadmb.r04
	@del admb-re\\glmmadmb\\glmmadmb.rep
	@del admb-re\\glmmadmb\\glmmadmb.rhes
	@del admb-re\\glmmadmb\\glmmadmb.shess
	@del admb-re\\glmmadmb\\glmmadmb.std
	@del admb-re\\glmmadmb\\hesscheck
	@del admb-re\\glmmadmb\\hessian.bin
	@del admb-re\\glmmadmb\\phi.rep
	@del admb-re\\glmmadmb\\s1
	@del admb-re\\glmmadmb\\s2
	@del admb-re\\kidney\\admodel.cov
	@del admb-re\\kidney\\admodel.dep
	@del admb-re\\kidney\\admodel.hes
	@del admb-re\\kidney\\fmin.log
	@del admb-re\\kidney\\hesscheck
	@del admb-re\\kidney\\hessian.bin
	@del admb-re\\kidney\\kidney.exe
	@del admb-re\\kidney\\kidney.bar
	@del admb-re\\kidney\\kidney.bgs
	@del admb-re\\kidney\\kidney.cor
	@del admb-re\\kidney\\kidney.cpp
	@del admb-re\\kidney\\kidney.eva
	@del admb-re\\kidney\\kidney.htp
	@del admb-re\\kidney\\kidney.log
	@del admb-re\\kidney\\kidney.luu
	@del admb-re\\kidney\\kidney.obj
	@del admb-re\\kidney\\kidney.par
	@del admb-re\\kidney\\kidney.rep
	@del admb-re\\kidney\\kidney.rhes
	@del admb-re\\kidney\\kidney.std
	@del admb-re\\lidar\\admodel.cov
	@del admb-re\\lidar\\admodel.dep
	@del admb-re\\lidar\\admodel.hes
	@del admb-re\\lidar\\fmin.log
	@del admb-re\\lidar\\hesscheck
	@del admb-re\\lidar\\hessian.bin
	@del admb-re\\lidar\\lidar.exe
	@del admb-re\\lidar\\lidar.b01
	@del admb-re\\lidar\\lidar.bar
	@del admb-re\\lidar\\lidar.bgs
	@del admb-re\\lidar\\lidar.cor
	@del admb-re\\lidar\\lidar.cpp
	@del admb-re\\lidar\\lidar.eva
	@del admb-re\\lidar\\lidar.htp
	@del admb-re\\lidar\\lidar.log
	@del admb-re\\lidar\\lidar.luu
	@del admb-re\\lidar\\lidar.obj
	@del admb-re\\lidar\\lidar.p01
	@del admb-re\\lidar\\lidar.par
	@del admb-re\\lidar\\lidar.r01
	@del admb-re\\lidar\\lidar.rep
	@del admb-re\\lidar\\lidar.rhes
	@del admb-re\\lidar\\lidar.std
	@del admb-re\\logistic\\admodel.cov
	@del admb-re\\logistic\\admodel.dep
	@del admb-re\\logistic\\admodel.hes
	@del admb-re\\logistic\\fmin.log
	@del admb-re\\logistic\\hesscheck
	@del admb-re\\logistic\\hessian.bin
	@del admb-re\\logistic\\logistic.exe
	@del admb-re\\logistic\\logistic.b01
	@del admb-re\\logistic\\logistic.bar
	@del admb-re\\logistic\\logistic.bgs
	@del admb-re\\logistic\\logistic.cor
	@del admb-re\\logistic\\logistic.cpp
	@del admb-re\\logistic\\logistic.eva
	@del admb-re\\logistic\\logistic.htp
	@del admb-re\\logistic\\logistic.log
	@del admb-re\\logistic\\logistic.luu
	@del admb-re\\logistic\\logistic.obj
	@del admb-re\\logistic\\logistic.p01
	@del admb-re\\logistic\\logistic.par
	@del admb-re\\logistic\\logistic.r01
	@del admb-re\\logistic\\logistic.rep
	@del admb-re\\logistic\\logistic.rhes
	@del admb-re\\logistic\\logistic.std
	@del admb-re\\nbmm\\admodel.cov
	@del admb-re\\nbmm\\admodel.dep
	@del admb-re\\nbmm\\admodel.hes
	@del admb-re\\nbmm\\fmin.log
	@del admb-re\\nbmm\\hesscheck
	@del admb-re\\nbmm\\hessian.bin
	@del admb-re\\nbmm\\nbmm.exe
	@del admb-re\\nbmm\\nbmm.b01
	@del admb-re\\nbmm\\nbmm.b02
	@del admb-re\\nbmm\\nbmm.bar
	@del admb-re\\nbmm\\nbmm.bgs
	@del admb-re\\nbmm\\nbmm.cor
	@del admb-re\\nbmm\\nbmm.cpp
	@del admb-re\\nbmm\\nbmm.eva
	@del admb-re\\nbmm\\nbmm.htp
	@del admb-re\\nbmm\\nbmm.log
	@del admb-re\\nbmm\\nbmm.luu
	@del admb-re\\nbmm\\nbmm.obj
	@del admb-re\\nbmm\\nbmm.p01
	@del admb-re\\nbmm\\nbmm.p02
	@del admb-re\\nbmm\\nbmm.par
	@del admb-re\\nbmm\\nbmm.r01
	@del admb-re\\nbmm\\nbmm.r02
	@del admb-re\\nbmm\\nbmm.rep
	@del admb-re\\nbmm\\nbmm.rhes
	@del admb-re\\nbmm\\nbmm.std
	@del admb-re\\nested4\\admodel.cov
	@del admb-re\\nested4\\admodel.dep
	@del admb-re\\nested4\\admodel.hes
	@del admb-re\\nested4\\fmin.log
	@del admb-re\\nested4\\hesscheck
	@del admb-re\\nested4\\hessian.bin
	@del admb-re\\nested4\\nested4.exe
	@del admb-re\\nested4\\nested4.b01
	@del admb-re\\nested4\\nested4.bar
	@del admb-re\\nested4\\nested4.bgs
	@del admb-re\\nested4\\nested4.cor
	@del admb-re\\nested4\\nested4.cpp
	@del admb-re\\nested4\\nested4.eva
	@del admb-re\\nested4\\nested4.htp
	@del admb-re\\nested4\\nested4.log
	@del admb-re\\nested4\\nested4.obj
	@del admb-re\\nested4\\nested4.p01
	@del admb-re\\nested4\\nested4.par
	@del admb-re\\nested4\\nested4.r01
	@del admb-re\\nested4\\nested4.rep
	@del admb-re\\nested4\\nested4.rhes
	@del admb-re\\nested4\\nested4.std
	@del admb-re\\orange\\admodel.cov
	@del admb-re\\orange\\admodel.dep
	@del admb-re\\orange\\admodel.hes
	@del admb-re\\orange\\fmin.log
	@del admb-re\\orange\\hesscheck
	@del admb-re\\orange\\hessian.bin
	@del admb-re\\orange\\orange.exe
	@del admb-re\\orange\\orange.b01
	@del admb-re\\orange\\orange.bar
	@del admb-re\\orange\\orange.bgs
	@del admb-re\\orange\\orange.cor
	@del admb-re\\orange\\orange.cpp
	@del admb-re\\orange\\orange.eva
	@del admb-re\\orange\\orange.htp
	@del admb-re\\orange\\orange.log
	@del admb-re\\orange\\orange.obj
	@del admb-re\\orange\\orange.p01
	@del admb-re\\orange\\orange.par
	@del admb-re\\orange\\orange.r01
	@del admb-re\\orange\\orange.rep
	@del admb-re\\orange\\orange.rhes
	@del admb-re\\orange\\orange.std
	@del admb-re\\orange2\\admodel.cov
	@del admb-re\\orange2\\admodel.dep
	@del admb-re\\orange2\\admodel.hes
	@del admb-re\\orange2\\fmin.log
	@del admb-re\\orange2\\hesscheck
	@del admb-re\\orange2\\hessian.bin
	@del admb-re\\orange2\\orange2.exe
	@del admb-re\\orange2\\orange2.b01
	@del admb-re\\orange2\\orange2.bar
	@del admb-re\\orange2\\orange2.bgs
	@del admb-re\\orange2\\orange2.cor
	@del admb-re\\orange2\\orange2.cpp
	@del admb-re\\orange2\\orange2.eva
	@del admb-re\\orange2\\orange2.htp
	@del admb-re\\orange2\\orange2.log
	@del admb-re\\orange2\\orange2.luu
	@del admb-re\\orange2\\orange2.obj
	@del admb-re\\orange2\\orange2.p01
	@del admb-re\\orange2\\orange2.par
	@del admb-re\\orange2\\orange2.r01
	@del admb-re\\orange2\\orange2.rep
	@del admb-re\\orange2\\orange2.rhes
	@del admb-re\\orange2\\orange2.std
	@del admb-re\\orange_cor\\admodel.cov
	@del admb-re\\orange_cor\\admodel.dep
	@del admb-re\\orange_cor\\admodel.hes
	@del admb-re\\orange_cor\\fmin.log
	@del admb-re\\orange_cor\\hesscheck
	@del admb-re\\orange_cor\\hessian.bin
	@del admb-re\\orange_cor\\orange_cor.exe
	@del admb-re\\orange_cor\\orange_cor.b01
	@del admb-re\\orange_cor\\orange_cor.bar
	@del admb-re\\orange_cor\\orange_cor.bgs
	@del admb-re\\orange_cor\\orange_cor.cor
	@del admb-re\\orange_cor\\orange_cor.cpp
	@del admb-re\\orange_cor\\orange_cor.eva
	@del admb-re\\orange_cor\\orange_cor.htp
	@del admb-re\\orange_cor\\orange_cor.log
	@del admb-re\\orange_cor\\orange_cor.obj
	@del admb-re\\orange_cor\\orange_cor.p01
	@del admb-re\\orange_cor\\orange_cor.par
	@del admb-re\\orange_cor\\orange_cor.r01
	@del admb-re\\orange_cor\\orange_cor.rep
	@del admb-re\\orange_cor\\orange_cor.rhes
	@del admb-re\\orange_cor\\orange_cor.std
	@del admb-re\\pheno\\admodel.cov
	@del admb-re\\pheno\\admodel.dep
	@del admb-re\\pheno\\admodel.hes
	@del admb-re\\pheno\\fmin.log
	@del admb-re\\pheno\\hesscheck
	@del admb-re\\pheno\\hessian.bin
	@del admb-re\\pheno\\pheno.exe
	@del admb-re\\pheno\\pheno.b01
	@del admb-re\\pheno\\pheno.bar
	@del admb-re\\pheno\\pheno.bgs
	@del admb-re\\pheno\\pheno.cor
	@del admb-re\\pheno\\pheno.cpp
	@del admb-re\\pheno\\pheno.eva
	@del admb-re\\pheno\\pheno.htp
	@del admb-re\\pheno\\pheno.log
	@del admb-re\\pheno\\pheno.obj
	@del admb-re\\pheno\\pheno.p01
	@del admb-re\\pheno\\pheno.par
	@del admb-re\\pheno\\pheno.r01
	@del admb-re\\pheno\\pheno.rep
	@del admb-re\\pheno\\pheno.rhes
	@del admb-re\\pheno\\pheno.std
	@del admb-re\\polio\\admodel.cov
	@del admb-re\\polio\\admodel.dep
	@del admb-re\\polio\\admodel.hes
	@del admb-re\\polio\\fmin.log
	@del admb-re\\polio\\hesscheck
	@del admb-re\\polio\\hessian.bin
	@del admb-re\\polio\\polio.exe
	@del admb-re\\polio\\polio.b01
	@del admb-re\\polio\\polio.bar
	@del admb-re\\polio\\polio.bgs
	@del admb-re\\polio\\polio.cor
	@del admb-re\\polio\\polio.cpp
	@del admb-re\\polio\\polio.eva
	@del admb-re\\polio\\polio.htp
	@del admb-re\\polio\\polio.log
	@del admb-re\\polio\\polio.luu
	@del admb-re\\polio\\polio.obj
	@del admb-re\\polio\\polio.p01
	@del admb-re\\polio\\polio.par
	@del admb-re\\polio\\polio.r01
	@del admb-re\\polio\\polio.rep
	@del admb-re\\polio\\polio.rhes
	@del admb-re\\polio\\polio.std
	@del admb-re\\sdv\\admodel.cov
	@del admb-re\\sdv\\admodel.dep
	@del admb-re\\sdv\\admodel.hes
	@del admb-re\\sdv\\fmin.log
	@del admb-re\\sdv\\hesscheck
	@del admb-re\\sdv\\hessian.bin
	@del admb-re\\sdv\\sdv.exe
	@del admb-re\\sdv\\sdv.b01
	@del admb-re\\sdv\\sdv.bar
	@del admb-re\\sdv\\sdv.bgs
	@del admb-re\\sdv\\sdv.cor
	@del admb-re\\sdv\\sdv.cpp
	@del admb-re\\sdv\\sdv.eva
	@del admb-re\\sdv\\sdv.htp
	@del admb-re\\sdv\\sdv.log
	@del admb-re\\sdv\\sdv.luu
	@del admb-re\\sdv\\sdv.obj
	@del admb-re\\sdv\\sdv.p01
	@del admb-re\\sdv\\sdv.par
	@del admb-re\\sdv\\sdv.r01
	@del admb-re\\sdv\\sdv.rep
	@del admb-re\\sdv\\sdv.rhes
	@del admb-re\\sdv\\sdv.std
	@del admb-re\\skewed\\admodel.cov
	@del admb-re\\skewed\\admodel.dep
	@del admb-re\\skewed\\admodel.hes
	@del admb-re\\skewed\\diet.exe
	@del admb-re\\skewed\\diet.b01
	@del admb-re\\skewed\\diet.bar
	@del admb-re\\skewed\\diet.bgs
	@del admb-re\\skewed\\diet.cor
	@del admb-re\\skewed\\diet.cpp
	@del admb-re\\skewed\\diet.eva
	@del admb-re\\skewed\\diet.htp
	@del admb-re\\skewed\\diet.log
	@del admb-re\\skewed\\diet.obj
	@del admb-re\\skewed\\diet.p01
	@del admb-re\\skewed\\diet.par
	@del admb-re\\skewed\\diet.r01
	@del admb-re\\skewed\\diet.rep
	@del admb-re\\skewed\\diet.rhes
	@del admb-re\\skewed\\diet.std
	@del admb-re\\skewed\\diet_sk.exe
	@del admb-re\\skewed\\diet_sk.b01
	@del admb-re\\skewed\\diet_sk.b02
	@del admb-re\\skewed\\diet_sk.bar
	@del admb-re\\skewed\\diet_sk.bgs
	@del admb-re\\skewed\\diet_sk.cor
	@del admb-re\\skewed\\diet_sk.cpp
	@del admb-re\\skewed\\diet_sk.eva
	@del admb-re\\skewed\\diet_sk.htp
	@del admb-re\\skewed\\diet_sk.log
	@del admb-re\\skewed\\diet_sk.obj
	@del admb-re\\skewed\\diet_sk.p01
	@del admb-re\\skewed\\diet_sk.p02
	@del admb-re\\skewed\\diet_sk.par
	@del admb-re\\skewed\\diet_sk.r01
	@del admb-re\\skewed\\diet_sk.r02
	@del admb-re\\skewed\\diet_sk.rep
	@del admb-re\\skewed\\diet_sk.rhes
	@del admb-re\\skewed\\diet_sk.std
	@del admb-re\\skewed\\fmin.log
	@del admb-re\\skewed\\hesscheck
	@del admb-re\\skewed\\hessian.bin
	@del admb-re\\socatt\\admodel.cov
	@del admb-re\\socatt\\admodel.dep
	@del admb-re\\socatt\\admodel.hes
	@del admb-re\\socatt\\fmin.log
	@del admb-re\\socatt\\hesscheck
	@del admb-re\\socatt\\hessian.bin
	@del admb-re\\socatt\\socatt.exe
	@del admb-re\\socatt\\socatt.bar
	@del admb-re\\socatt\\socatt.bgs
	@del admb-re\\socatt\\socatt.cor
	@del admb-re\\socatt\\socatt.cpp
	@del admb-re\\socatt\\socatt.eva
	@del admb-re\\socatt\\socatt.htp
	@del admb-re\\socatt\\socatt.log
	@del admb-re\\socatt\\socatt.obj
	@del admb-re\\socatt\\socatt.par
	@del admb-re\\socatt\\socatt.rep
	@del admb-re\\socatt\\socatt.rhes
	@del admb-re\\socatt\\socatt.std
	@del admb-re\\spatial\\admodel.cov
	@del admb-re\\spatial\\admodel.dep
	@del admb-re\\spatial\\admodel.hes
	@del admb-re\\spatial\\classcode.tmp
	@del admb-re\\spatial\\fmin.log
	@del admb-re\\spatial\\hesscheck
	@del admb-re\\spatial\\hessian.bin
	@del admb-re\\spatial\\spatial.exe
	@del admb-re\\spatial\\spatial.b01
	@del admb-re\\spatial\\spatial.bar
	@del admb-re\\spatial\\spatial.bgs
	@del admb-re\\spatial\\spatial.cor
	@del admb-re\\spatial\\spatial.cpp
	@del admb-re\\spatial\\spatial.eva
	@del admb-re\\spatial\\spatial.htp
	@del admb-re\\spatial\\spatial.log
	@del admb-re\\spatial\\spatial.luu
	@del admb-re\\spatial\\spatial.obj
	@del admb-re\\spatial\\spatial.p01
	@del admb-re\\spatial\\spatial.par
	@del admb-re\\spatial\\spatial.r01
	@del admb-re\\spatial\\spatial.rep
	@del admb-re\\spatial\\spatial.rhes
	@del admb-re\\spatial\\spatial.std
	@del admb-re\\union\\admodel.cov
	@del admb-re\\union\\admodel.dep
	@del admb-re\\union\\admodel.hes
	@del admb-re\\union\\fmin.log
	@del admb-re\\union\\hesscheck
	@del admb-re\\union\\hessian.bin
	@del admb-re\\union\\union.exe
	@del admb-re\\union\\union.b01
	@del admb-re\\union\\union.bar
	@del admb-re\\union\\union.bgs
	@del admb-re\\union\\union.cor
	@del admb-re\\union\\union.cpp
	@del admb-re\\union\\union.eva
	@del admb-re\\union\\union.htp
	@del admb-re\\union\\union.log
	@del admb-re\\union\\union.luu
	@del admb-re\\union\\union.obj
	@del admb-re\\union\\union.p01
	@del admb-re\\union\\union.par
	@del admb-re\\union\\union.r01
	@del admb-re\\union\\union.rep
	@del admb-re\\union\\union.rhes
	@del admb-re\\union\\union.std
	@del admb-re\\weights\\admodel.cov
	@del admb-re\\weights\\admodel.dep
	@del admb-re\\weights\\admodel.hes
	@del admb-re\\weights\\binomial.exe
	@del admb-re\\weights\\binomial.b01
	@del admb-re\\weights\\binomial.bar
	@del admb-re\\weights\\binomial.bgs
	@del admb-re\\weights\\binomial.cor
	@del admb-re\\weights\\binomial.cpp
	@del admb-re\\weights\\binomial.eva
	@del admb-re\\weights\\binomial.htp
	@del admb-re\\weights\\binomial.log
	@del admb-re\\weights\\binomial.obj
	@del admb-re\\weights\\binomial.p01
	@del admb-re\\weights\\binomial.par
	@del admb-re\\weights\\binomial.rhes
	@del admb-re\\weights\\binomial.std
	@del admb-re\\weights\\fmin.log
	@del admb-re\\weights\\hesscheck
	@del admb-re\\weights\\hessian.bin
	@del admb\\buscycle\\admodel.cov
	@del admb\\buscycle\\admodel.dep
	@del admb\\buscycle\\admodel.hes
	@del admb\\buscycle\\fmin.log
	@del admb\\buscycle\\gradfil1.tmp
	@del admb\\buscycle\\gradfil2.tmp
	@del admb\\buscycle\\ham4.exe
	@del admb\\buscycle\\ham4.b01
	@del admb\\buscycle\\ham4.b02
	@del admb\\buscycle\\ham4.b03
	@del admb\\buscycle\\ham4.b04
	@del admb\\buscycle\\ham4.bar
	@del admb\\buscycle\\ham4.cor
	@del admb\\buscycle\\ham4.cpp
	@del admb\\buscycle\\ham4.eva
	@del admb\\buscycle\\ham4.htp
	@del admb\\buscycle\\ham4.log
	@del admb\\buscycle\\ham4.obj
	@del admb\\buscycle\\ham4.p01
	@del admb\\buscycle\\ham4.p02
	@del admb\\buscycle\\ham4.p03
	@del admb\\buscycle\\ham4.p04
	@del admb\\buscycle\\ham4.par
	@del admb\\buscycle\\ham4.r01
	@del admb\\buscycle\\ham4.r02
	@del admb\\buscycle\\ham4.r03
	@del admb\\buscycle\\ham4.r04
	@del admb\\buscycle\\ham4.rep
	@del admb\\buscycle\\ham4.std
	@del admb\\buscycle\\ham5.exe
	@del admb\\buscycle\\ham5.b01
	@del admb\\buscycle\\ham5.b02
	@del admb\\buscycle\\ham5.b03
	@del admb\\buscycle\\ham5.b04
	@del admb\\buscycle\\ham5.bar
	@del admb\\buscycle\\ham5.cor
	@del admb\\buscycle\\ham5.cpp
	@del admb\\buscycle\\ham5.eva
	@del admb\\buscycle\\ham5.htp
	@del admb\\buscycle\\ham5.log
	@del admb\\buscycle\\ham5.obj
	@del admb\\buscycle\\ham5.p01
	@del admb\\buscycle\\ham5.p02
	@del admb\\buscycle\\ham5.p03
	@del admb\\buscycle\\ham5.p04
	@del admb\\buscycle\\ham5.par
	@del admb\\buscycle\\ham5.r01
	@del admb\\buscycle\\ham5.r02
	@del admb\\buscycle\\ham5.r03
	@del admb\\buscycle\\ham5.r04
	@del admb\\buscycle\\ham5.rep
	@del admb\\buscycle\\ham5.std
	@del admb\\buscycle\\qafter4.tex
	@del admb\\buscycle\\qafter5.tex
	@del admb\\buscycle\\qbefore4.tex
	@del admb\\buscycle\\qbefore5.tex
	@del admb\\buscycle\\varssave.tmp
	@del admb\\chem_eng\\admodel.cov
	@del admb\\chem_eng\\admodel.dep
	@del admb\\chem_eng\\admodel.hes
	@del admb\\chem_eng\\chem_eng.exe
	@del admb\\chem_eng\\chem_eng.bar
	@del admb\\chem_eng\\chem_eng.cor
	@del admb\\chem_eng\\chem_eng.cpp
	@del admb\\chem_eng\\chem_eng.eva
	@del admb\\chem_eng\\chem_eng.htp
	@del admb\\chem_eng\\chem_eng.log
	@del admb\\chem_eng\\chem_eng.obj
	@del admb\\chem_eng\\chem_eng.par
	@del admb\\chem_eng\\chem_eng.std
	@del admb\\chem_eng\\fmin.log
	@del admb\\finance\\admodel.cov
	@del admb\\finance\\admodel.dep
	@del admb\\finance\\admodel.hes
	@del admb\\finance\\finance.exe
	@del admb\\finance\\finance.b01
	@del admb\\finance\\finance.b02
	@del admb\\finance\\finance.bar
	@del admb\\finance\\finance.cor
	@del admb\\finance\\finance.cpp
	@del admb\\finance\\finance.eva
	@del admb\\finance\\finance.htp
	@del admb\\finance\\finance.log
	@del admb\\finance\\finance.obj
	@del admb\\finance\\finance.p01
	@del admb\\finance\\finance.p02
	@del admb\\finance\\finance.par
	@del admb\\finance\\finance.std
	@del admb\\finance\\fmin.log
	@del admb\\forest\\admodel.cov
	@del admb\\forest\\admodel.dep
	@del admb\\forest\\admodel.hes
	@del admb\\forest\\fmin.log
	@del admb\\forest\\forest.exe
	@del admb\\forest\\forest.b01
	@del admb\\forest\\forest.bar
	@del admb\\forest\\forest.cor
	@del admb\\forest\\forest.cpp
	@del admb\\forest\\forest.eva
	@del admb\\forest\\forest.htp
	@del admb\\forest\\forest.log
	@del admb\\forest\\forest.obj
	@del admb\\forest\\forest.p01
	@del admb\\forest\\forest.par
	@del admb\\forest\\forest.r01
	@del admb\\forest\\forest.rep
	@del admb\\forest\\forest.std
	@del admb\\pella_t\\admodel.cov
	@del admb\\pella_t\\admodel.dep
	@del admb\\pella_t\\admodel.hes
	@del admb\\pella_t\\fmin.log
	@del admb\\pella_t\\pella_t.exe
	@del admb\\pella_t\\pella_t.b01
	@del admb\\pella_t\\pella_t.b02
	@del admb\\pella_t\\pella_t.b03
	@del admb\\pella_t\\pella_t.bar
	@del admb\\pella_t\\pella_t.cor
	@del admb\\pella_t\\pella_t.cpp
	@del admb\\pella_t\\pella_t.eva
	@del admb\\pella_t\\pella_t.htp
	@del admb\\pella_t\\pella_t.log
	@del admb\\pella_t\\pella_t.obj
	@del admb\\pella_t\\pella_t.p01
	@del admb\\pella_t\\pella_t.p02
	@del admb\\pella_t\\pella_t.p03
	@del admb\\pella_t\\pella_t.par
	@del admb\\pella_t\\pella_t.std
	@del admb\\robreg\\admodel.cov
	@del admb\\robreg\\admodel.dep
	@del admb\\robreg\\admodel.hes
	@del admb\\robreg\\fmin.log
	@del admb\\robreg\\vonb.exe
	@del admb\\robreg\\vonb.bar
	@del admb\\robreg\\vonb.cor
	@del admb\\robreg\\vonb.cpp
	@del admb\\robreg\\vonb.eva
	@del admb\\robreg\\vonb.htp
	@del admb\\robreg\\vonb.log
	@del admb\\robreg\\vonb.obj
	@del admb\\robreg\\vonb.par
	@del admb\\robreg\\vonb.std
	@del admb\\robreg\\vonbr.exe
	@del admb\\robreg\\vonbr.b01
	@del admb\\robreg\\vonbr.bar
	@del admb\\robreg\\vonbr.cor
	@del admb\\robreg\\vonbr.cpp
	@del admb\\robreg\\vonbr.eva
	@del admb\\robreg\\vonbr.htp
	@del admb\\robreg\\vonbr.log
	@del admb\\robreg\\vonbr.obj
	@del admb\\robreg\\vonbr.p01
	@del admb\\robreg\\vonbr.par
	@del admb\\robreg\\vonbr.std
	@del admb\\truncreg\\admodel.cov
	@del admb\\truncreg\\admodel.dep
	@del admb\\truncreg\\admodel.hes
	@del admb\\truncreg\\fmin.log
	@del admb\\truncreg\\truncreg.exe
	@del admb\\truncreg\\truncreg.bar
	@del admb\\truncreg\\truncreg.cor
	@del admb\\truncreg\\truncreg.cpp
	@del admb\\truncreg\\truncreg.eva
	@del admb\\truncreg\\truncreg.htp
	@del admb\\truncreg\\truncreg.log
	@del admb\\truncreg\\truncreg.obj
	@del admb\\truncreg\\truncreg.par
	@del admb\\truncreg\\truncreg.rep
	@del admb\\truncreg\\truncreg.std
	@del admb\\vol\\admodel.cov
	@del admb\\vol\\admodel.dep
	@del admb\\vol\\admodel.hes
	@del admb\\vol\\fmin.log
	@del admb\\vol\\n2mvol.exe
	@del admb\\vol\\n2mvol.b01
	@del admb\\vol\\n2mvol.bar
	@del admb\\vol\\n2mvol.cor
	@del admb\\vol\\n2mvol.cpp
	@del admb\\vol\\n2mvol.eva
	@del admb\\vol\\n2mvol.htp
	@del admb\\vol\\n2mvol.log
	@del admb\\vol\\n2mvol.obj
	@del admb\\vol\\n2mvol.p01
	@del admb\\vol\\n2mvol.par
	@del admb\\vol\\n2mvol.r01
	@del admb\\vol\\n2mvol.rep
	@del admb\\vol\\n2mvol.std
	@del autodif\\hemholtz\\fmin.log
	@del autodif\\hemholtz\\hem_func.obj
	@del autodif\\hemholtz\\hemholtz.exe
	@del autodif\\hemholtz\\hemholtz.obj
	@del autodif\\io_examp\\file1.tmp
	@del autodif\\io_examp\\file2.tmp
	@del autodif\\io_examp\\fmin.log
	@del autodif\\io_examp\\io_examp.exe
	@del autodif\\io_examp\\io_examp.obj
	@del autodif\\newt\\fmin.log
	@del autodif\\newt\\newt.exe
	@del autodif\\newt\\newt.obj
	@del autodif\\simple\\fcomp_s.obj
	@del autodif\\simple\\fmin.log
	@del autodif\\simple\\s1.exe
	@del autodif\\simple\\s1.obj
	@del autodif\\simple\\simp1.exe
	@del autodif\\simple\\simp1.obj
	@del autodif\\simple\\simple.exe
	@del autodif\\simple\\simple.obj
	@del autodif\\simple\\simple2.exe
	@del autodif\\simple\\simple2.obj
	@del autodif\\struct\\fmin.log
	@del autodif\\struct\\oldstr.exe
	@del autodif\\struct\\oldstr.obj
	@del autodif\\struct\\struct.exe
	@del autodif\\struct\\struct.obj
else
	@rm -vf admb-re/bcb/admodel.cov
	@rm -vf admb-re/bcb/admodel.dep
	@rm -vf admb-re/bcb/admodel.hes
	@rm -vf admb-re/bcb/bcb
	@rm -vf admb-re/bcb/bcb.bar
	@rm -vf admb-re/bcb/bcb.bgs
	@rm -vf admb-re/bcb/bcb.cor
	@rm -vf admb-re/bcb/bcb.cpp
	@rm -vf admb-re/bcb/bcb.eva
	@rm -vf admb-re/bcb/bcb.htp
	@rm -vf admb-re/bcb/bcb.log
	@rm -vf admb-re/bcb/bcb.luu
	@rm -vf admb-re/bcb/bcb.obj
	@rm -vf admb-re/bcb/bcb.par
	@rm -vf admb-re/bcb/bcb.rep
	@rm -vf admb-re/bcb/bcb.rhes
	@rm -vf admb-re/bcb/bcb.std
	@rm -vf admb-re/bcb/fmin.log
	@rm -vf admb-re/bcb/hesscheck
	@rm -vf admb-re/bcb/hessian.bin
	@rm -vf admb-re/biglog/admodel.cov
	@rm -vf admb-re/biglog/admodel.dep
	@rm -vf admb-re/biglog/admodel.hes
	@rm -vf admb-re/biglog/biglog
	@rm -vf admb-re/biglog/biglog.b01
	@rm -vf admb-re/biglog/biglog.b02
	@rm -vf admb-re/biglog/biglog.bar
	@rm -vf admb-re/biglog/biglog.bgs
	@rm -vf admb-re/biglog/biglog.cor
	@rm -vf admb-re/biglog/biglog.cpp
	@rm -vf admb-re/biglog/biglog.eva
	@rm -vf admb-re/biglog/biglog.htp
	@rm -vf admb-re/biglog/biglog.log
	@rm -vf admb-re/biglog/biglog.luu
	@rm -vf admb-re/biglog/biglog.obj
	@rm -vf admb-re/biglog/biglog.p01
	@rm -vf admb-re/biglog/biglog.p02
	@rm -vf admb-re/biglog/biglog.par
	@rm -vf admb-re/biglog/biglog.rhes
	@rm -vf admb-re/biglog/biglog.std
	@rm -vf admb-re/biglog/fmin.log
	@rm -vf admb-re/biglog/hesscheck
	@rm -vf admb-re/biglog/hessian.bin
	@rm -vf admb-re/caest/admodel.cov
	@rm -vf admb-re/caest/admodel.dep
	@rm -vf admb-re/caest/admodel.hes
	@rm -vf admb-re/caest/caest
	@rm -vf admb-re/caest/caest.b01
	@rm -vf admb-re/caest/caest.bar
	@rm -vf admb-re/caest/caest.bgs
	@rm -vf admb-re/caest/caest.cor
	@rm -vf admb-re/caest/caest.cpp
	@rm -vf admb-re/caest/caest.eva
	@rm -vf admb-re/caest/caest.htp
	@rm -vf admb-re/caest/caest.log
	@rm -vf admb-re/caest/caest.luu
	@rm -vf admb-re/caest/caest.obj
	@rm -vf admb-re/caest/caest.p01
	@rm -vf admb-re/caest/caest.par
	@rm -vf admb-re/caest/caest.r01
	@rm -vf admb-re/caest/caest.rep
	@rm -vf admb-re/caest/caest.rhes
	@rm -vf admb-re/caest/caest.std
	@rm -vf admb-re/caest/fmin.log
	@rm -vf admb-re/caest/hesscheck
	@rm -vf admb-re/caest/hessian.bin
	@rm -vf admb-re/gamma/admodel.cov
	@rm -vf admb-re/gamma/admodel.dep
	@rm -vf admb-re/gamma/admodel.hes
	@rm -vf admb-re/gamma/fmin.log
	@rm -vf admb-re/gamma/hesscheck
	@rm -vf admb-re/gamma/hessian.bin
	@rm -vf admb-re/gamma/liver_gamma
	@rm -vf admb-re/gamma/liver_gamma.b01
	@rm -vf admb-re/gamma/liver_gamma.bar
	@rm -vf admb-re/gamma/liver_gamma.bgs
	@rm -vf admb-re/gamma/liver_gamma.cor
	@rm -vf admb-re/gamma/liver_gamma.cpp
	@rm -vf admb-re/gamma/liver_gamma.eva
	@rm -vf admb-re/gamma/liver_gamma.htp
	@rm -vf admb-re/gamma/liver_gamma.log
	@rm -vf admb-re/gamma/liver_gamma.obj
	@rm -vf admb-re/gamma/liver_gamma.p01
	@rm -vf admb-re/gamma/liver_gamma.par
	@rm -vf admb-re/gamma/liver_gamma.rhes
	@rm -vf admb-re/gamma/liver_gamma.std
	@rm -vf admb-re/glmmadmb/admodel.cov
	@rm -vf admb-re/glmmadmb/admodel.dep
	@rm -vf admb-re/glmmadmb/admodel.hes
	@rm -vf admb-re/glmmadmb/b1
	@rm -vf admb-re/glmmadmb/b2
	@rm -vf admb-re/glmmadmb/bvprobit
	@rm -vf admb-re/glmmadmb/bvprobit.b01
	@rm -vf admb-re/glmmadmb/bvprobit.bar
	@rm -vf admb-re/glmmadmb/bvprobit.bgs
	@rm -vf admb-re/glmmadmb/bvprobit.cor
	@rm -vf admb-re/glmmadmb/bvprobit.cpp
	@rm -vf admb-re/glmmadmb/bvprobit.eva
	@rm -vf admb-re/glmmadmb/bvprobit.htp
	@rm -vf admb-re/glmmadmb/bvprobit.log
	@rm -vf admb-re/glmmadmb/bvprobit.obj
	@rm -vf admb-re/glmmadmb/bvprobit.p01
	@rm -vf admb-re/glmmadmb/bvprobit.par
	@rm -vf admb-re/glmmadmb/bvprobit.r01
	@rm -vf admb-re/glmmadmb/bvprobit.rep
	@rm -vf admb-re/glmmadmb/bvprobit.rhes
	@rm -vf admb-re/glmmadmb/bvprobit.std
	@rm -vf admb-re/glmmadmb/fmin.log
	@rm -vf admb-re/glmmadmb/glmmadmb
	@rm -vf admb-re/glmmadmb/glmmadmb.b01
	@rm -vf admb-re/glmmadmb/glmmadmb.b02
	@rm -vf admb-re/glmmadmb/glmmadmb.b03
	@rm -vf admb-re/glmmadmb/glmmadmb.b04
	@rm -vf admb-re/glmmadmb/glmmadmb.bar
	@rm -vf admb-re/glmmadmb/glmmadmb.bgs
	@rm -vf admb-re/glmmadmb/glmmadmb.cor
	@rm -vf admb-re/glmmadmb/glmmadmb.cpp
	@rm -vf admb-re/glmmadmb/glmmadmb.eva
	@rm -vf admb-re/glmmadmb/glmmadmb.htp
	@rm -vf admb-re/glmmadmb/glmmadmb.log
	@rm -vf admb-re/glmmadmb/glmmadmb.luu
	@rm -vf admb-re/glmmadmb/glmmadmb.obj
	@rm -vf admb-re/glmmadmb/glmmadmb.p01
	@rm -vf admb-re/glmmadmb/glmmadmb.p02
	@rm -vf admb-re/glmmadmb/glmmadmb.p03
	@rm -vf admb-re/glmmadmb/glmmadmb.p04
	@rm -vf admb-re/glmmadmb/glmmadmb.par
	@rm -vf admb-re/glmmadmb/glmmadmb.r01
	@rm -vf admb-re/glmmadmb/glmmadmb.r02
	@rm -vf admb-re/glmmadmb/glmmadmb.r03
	@rm -vf admb-re/glmmadmb/glmmadmb.r04
	@rm -vf admb-re/glmmadmb/glmmadmb.rep
	@rm -vf admb-re/glmmadmb/glmmadmb.rhes
	@rm -vf admb-re/glmmadmb/glmmadmb.shess
	@rm -vf admb-re/glmmadmb/glmmadmb.std
	@rm -vf admb-re/glmmadmb/hesscheck
	@rm -vf admb-re/glmmadmb/hessian.bin
	@rm -vf admb-re/glmmadmb/phi.rep
	@rm -vf admb-re/glmmadmb/s1
	@rm -vf admb-re/glmmadmb/s2
	@rm -vf admb-re/kidney/admodel.cov
	@rm -vf admb-re/kidney/admodel.dep
	@rm -vf admb-re/kidney/admodel.hes
	@rm -vf admb-re/kidney/fmin.log
	@rm -vf admb-re/kidney/hesscheck
	@rm -vf admb-re/kidney/hessian.bin
	@rm -vf admb-re/kidney/kidney
	@rm -vf admb-re/kidney/kidney.bar
	@rm -vf admb-re/kidney/kidney.bgs
	@rm -vf admb-re/kidney/kidney.cor
	@rm -vf admb-re/kidney/kidney.cpp
	@rm -vf admb-re/kidney/kidney.eva
	@rm -vf admb-re/kidney/kidney.htp
	@rm -vf admb-re/kidney/kidney.log
	@rm -vf admb-re/kidney/kidney.luu
	@rm -vf admb-re/kidney/kidney.obj
	@rm -vf admb-re/kidney/kidney.par
	@rm -vf admb-re/kidney/kidney.rep
	@rm -vf admb-re/kidney/kidney.rhes
	@rm -vf admb-re/kidney/kidney.std
	@rm -vf admb-re/lidar/admodel.cov
	@rm -vf admb-re/lidar/admodel.dep
	@rm -vf admb-re/lidar/admodel.hes
	@rm -vf admb-re/lidar/fmin.log
	@rm -vf admb-re/lidar/hesscheck
	@rm -vf admb-re/lidar/hessian.bin
	@rm -vf admb-re/lidar/lidar
	@rm -vf admb-re/lidar/lidar.b01
	@rm -vf admb-re/lidar/lidar.bar
	@rm -vf admb-re/lidar/lidar.bgs
	@rm -vf admb-re/lidar/lidar.cor
	@rm -vf admb-re/lidar/lidar.cpp
	@rm -vf admb-re/lidar/lidar.eva
	@rm -vf admb-re/lidar/lidar.htp
	@rm -vf admb-re/lidar/lidar.log
	@rm -vf admb-re/lidar/lidar.luu
	@rm -vf admb-re/lidar/lidar.obj
	@rm -vf admb-re/lidar/lidar.p01
	@rm -vf admb-re/lidar/lidar.par
	@rm -vf admb-re/lidar/lidar.r01
	@rm -vf admb-re/lidar/lidar.rep
	@rm -vf admb-re/lidar/lidar.rhes
	@rm -vf admb-re/lidar/lidar.std
	@rm -vf admb-re/logistic/admodel.cov
	@rm -vf admb-re/logistic/admodel.dep
	@rm -vf admb-re/logistic/admodel.hes
	@rm -vf admb-re/logistic/fmin.log
	@rm -vf admb-re/logistic/hesscheck
	@rm -vf admb-re/logistic/hessian.bin
	@rm -vf admb-re/logistic/logistic
	@rm -vf admb-re/logistic/logistic.b01
	@rm -vf admb-re/logistic/logistic.bar
	@rm -vf admb-re/logistic/logistic.bgs
	@rm -vf admb-re/logistic/logistic.cor
	@rm -vf admb-re/logistic/logistic.cpp
	@rm -vf admb-re/logistic/logistic.eva
	@rm -vf admb-re/logistic/logistic.htp
	@rm -vf admb-re/logistic/logistic.log
	@rm -vf admb-re/logistic/logistic.luu
	@rm -vf admb-re/logistic/logistic.obj
	@rm -vf admb-re/logistic/logistic.p01
	@rm -vf admb-re/logistic/logistic.par
	@rm -vf admb-re/logistic/logistic.r01
	@rm -vf admb-re/logistic/logistic.rep
	@rm -vf admb-re/logistic/logistic.rhes
	@rm -vf admb-re/logistic/logistic.std
	@rm -vf admb-re/nbmm/admodel.cov
	@rm -vf admb-re/nbmm/admodel.dep
	@rm -vf admb-re/nbmm/admodel.hes
	@rm -vf admb-re/nbmm/fmin.log
	@rm -vf admb-re/nbmm/hesscheck
	@rm -vf admb-re/nbmm/hessian.bin
	@rm -vf admb-re/nbmm/nbmm
	@rm -vf admb-re/nbmm/nbmm.b01
	@rm -vf admb-re/nbmm/nbmm.b02
	@rm -vf admb-re/nbmm/nbmm.bar
	@rm -vf admb-re/nbmm/nbmm.bgs
	@rm -vf admb-re/nbmm/nbmm.cor
	@rm -vf admb-re/nbmm/nbmm.cpp
	@rm -vf admb-re/nbmm/nbmm.eva
	@rm -vf admb-re/nbmm/nbmm.htp
	@rm -vf admb-re/nbmm/nbmm.log
	@rm -vf admb-re/nbmm/nbmm.luu
	@rm -vf admb-re/nbmm/nbmm.obj
	@rm -vf admb-re/nbmm/nbmm.p01
	@rm -vf admb-re/nbmm/nbmm.p02
	@rm -vf admb-re/nbmm/nbmm.par
	@rm -vf admb-re/nbmm/nbmm.r01
	@rm -vf admb-re/nbmm/nbmm.r02
	@rm -vf admb-re/nbmm/nbmm.rep
	@rm -vf admb-re/nbmm/nbmm.rhes
	@rm -vf admb-re/nbmm/nbmm.std
	@rm -vf admb-re/nested4/admodel.cov
	@rm -vf admb-re/nested4/admodel.dep
	@rm -vf admb-re/nested4/admodel.hes
	@rm -vf admb-re/nested4/fmin.log
	@rm -vf admb-re/nested4/hesscheck
	@rm -vf admb-re/nested4/hessian.bin
	@rm -vf admb-re/nested4/nested4.b01
	@rm -vf admb-re/nested4/nested4.bar
	@rm -vf admb-re/nested4/nested4.bgs
	@rm -vf admb-re/nested4/nested4.cor
	@rm -vf admb-re/nested4/nested4.cpp
	@rm -vf admb-re/nested4/nested4.eva
	@rm -vf admb-re/nested4/nested4.htp
	@rm -vf admb-re/nested4/nested4.log
	@rm -vf admb-re/nested4/nested4.obj
	@rm -vf admb-re/nested4/nested4.p01
	@rm -vf admb-re/nested4/nested4.par
	@rm -vf admb-re/nested4/nested4.r01
	@rm -vf admb-re/nested4/nested4.rep
	@rm -vf admb-re/nested4/nested4.rhes
	@rm -vf admb-re/nested4/nested4.std
	@rm -vf admb-re/orange/admodel.cov
	@rm -vf admb-re/orange/admodel.dep
	@rm -vf admb-re/orange/admodel.hes
	@rm -vf admb-re/orange/fmin.log
	@rm -vf admb-re/orange/hesscheck
	@rm -vf admb-re/orange/hessian.bin
	@rm -vf admb-re/orange/orange
	@rm -vf admb-re/orange/orange.b01
	@rm -vf admb-re/orange/orange.bar
	@rm -vf admb-re/orange/orange.bgs
	@rm -vf admb-re/orange/orange.cor
	@rm -vf admb-re/orange/orange.cpp
	@rm -vf admb-re/orange/orange.eva
	@rm -vf admb-re/orange/orange.htp
	@rm -vf admb-re/orange/orange.log
	@rm -vf admb-re/orange/orange.obj
	@rm -vf admb-re/orange/orange.p01
	@rm -vf admb-re/orange/orange.par
	@rm -vf admb-re/orange/orange.r01
	@rm -vf admb-re/orange/orange.rep
	@rm -vf admb-re/orange/orange.rhes
	@rm -vf admb-re/orange/orange.std
	@rm -vf admb-re/orange2/admodel.cov
	@rm -vf admb-re/orange2/admodel.dep
	@rm -vf admb-re/orange2/admodel.hes
	@rm -vf admb-re/orange2/fmin.log
	@rm -vf admb-re/orange2/hesscheck
	@rm -vf admb-re/orange2/hessian.bin
	@rm -vf admb-re/orange2/orange2
	@rm -vf admb-re/orange2/orange2.b01
	@rm -vf admb-re/orange2/orange2.bar
	@rm -vf admb-re/orange2/orange2.bgs
	@rm -vf admb-re/orange2/orange2.cor
	@rm -vf admb-re/orange2/orange2.cpp
	@rm -vf admb-re/orange2/orange2.eva
	@rm -vf admb-re/orange2/orange2.htp
	@rm -vf admb-re/orange2/orange2.log
	@rm -vf admb-re/orange2/orange2.luu
	@rm -vf admb-re/orange2/orange2.obj
	@rm -vf admb-re/orange2/orange2.p01
	@rm -vf admb-re/orange2/orange2.par
	@rm -vf admb-re/orange2/orange2.r01
	@rm -vf admb-re/orange2/orange2.rep
	@rm -vf admb-re/orange2/orange2.rhes
	@rm -vf admb-re/orange2/orange2.std
	@rm -vf admb-re/orange_cor/admodel.cov
	@rm -vf admb-re/orange_cor/admodel.dep
	@rm -vf admb-re/orange_cor/admodel.hes
	@rm -vf admb-re/orange_cor/fmin.log
	@rm -vf admb-re/orange_cor/hesscheck
	@rm -vf admb-re/orange_cor/hessian.bin
	@rm -vf admb-re/orange_cor/orange_cor
	@rm -vf admb-re/orange_cor/orange_cor.b01
	@rm -vf admb-re/orange_cor/orange_cor.bar
	@rm -vf admb-re/orange_cor/orange_cor.bgs
	@rm -vf admb-re/orange_cor/orange_cor.cor
	@rm -vf admb-re/orange_cor/orange_cor.cpp
	@rm -vf admb-re/orange_cor/orange_cor.eva
	@rm -vf admb-re/orange_cor/orange_cor.htp
	@rm -vf admb-re/orange_cor/orange_cor.log
	@rm -vf admb-re/orange_cor/orange_cor.obj
	@rm -vf admb-re/orange_cor/orange_cor.p01
	@rm -vf admb-re/orange_cor/orange_cor.par
	@rm -vf admb-re/orange_cor/orange_cor.r01
	@rm -vf admb-re/orange_cor/orange_cor.rep
	@rm -vf admb-re/orange_cor/orange_cor.rhes
	@rm -vf admb-re/orange_cor/orange_cor.std
	@rm -vf admb-re/pheno/admodel.cov
	@rm -vf admb-re/pheno/admodel.dep
	@rm -vf admb-re/pheno/admodel.hes
	@rm -vf admb-re/pheno/fmin.log
	@rm -vf admb-re/pheno/hesscheck
	@rm -vf admb-re/pheno/hessian.bin
	@rm -vf admb-re/pheno/pheno
	@rm -vf admb-re/pheno/pheno.b01
	@rm -vf admb-re/pheno/pheno.bar
	@rm -vf admb-re/pheno/pheno.bgs
	@rm -vf admb-re/pheno/pheno.cor
	@rm -vf admb-re/pheno/pheno.cpp
	@rm -vf admb-re/pheno/pheno.eva
	@rm -vf admb-re/pheno/pheno.htp
	@rm -vf admb-re/pheno/pheno.log
	@rm -vf admb-re/pheno/pheno.obj
	@rm -vf admb-re/pheno/pheno.p01
	@rm -vf admb-re/pheno/pheno.par
	@rm -vf admb-re/pheno/pheno.r01
	@rm -vf admb-re/pheno/pheno.rep
	@rm -vf admb-re/pheno/pheno.rhes
	@rm -vf admb-re/pheno/pheno.std
	@rm -vf admb-re/polio/admodel.cov
	@rm -vf admb-re/polio/admodel.dep
	@rm -vf admb-re/polio/admodel.hes
	@rm -vf admb-re/polio/fmin.log
	@rm -vf admb-re/polio/hesscheck
	@rm -vf admb-re/polio/hessian.bin
	@rm -vf admb-re/polio/polio
	@rm -vf admb-re/polio/polio.b01
	@rm -vf admb-re/polio/polio.bar
	@rm -vf admb-re/polio/polio.bgs
	@rm -vf admb-re/polio/polio.cor
	@rm -vf admb-re/polio/polio.cpp
	@rm -vf admb-re/polio/polio.eva
	@rm -vf admb-re/polio/polio.htp
	@rm -vf admb-re/polio/polio.log
	@rm -vf admb-re/polio/polio.luu
	@rm -vf admb-re/polio/polio.obj
	@rm -vf admb-re/polio/polio.p01
	@rm -vf admb-re/polio/polio.par
	@rm -vf admb-re/polio/polio.r01
	@rm -vf admb-re/polio/polio.rep
	@rm -vf admb-re/polio/polio.rhes
	@rm -vf admb-re/polio/polio.std
	@rm -vf admb-re/sdv/admodel.cov
	@rm -vf admb-re/sdv/admodel.dep
	@rm -vf admb-re/sdv/admodel.hes
	@rm -vf admb-re/sdv/fmin.log
	@rm -vf admb-re/sdv/hesscheck
	@rm -vf admb-re/sdv/hessian.bin
	@rm -vf admb-re/sdv/sdv
	@rm -vf admb-re/sdv/sdv.b01
	@rm -vf admb-re/sdv/sdv.bar
	@rm -vf admb-re/sdv/sdv.bgs
	@rm -vf admb-re/sdv/sdv.cor
	@rm -vf admb-re/sdv/sdv.cpp
	@rm -vf admb-re/sdv/sdv.eva
	@rm -vf admb-re/sdv/sdv.htp
	@rm -vf admb-re/sdv/sdv.log
	@rm -vf admb-re/sdv/sdv.luu
	@rm -vf admb-re/sdv/sdv.obj
	@rm -vf admb-re/sdv/sdv.p01
	@rm -vf admb-re/sdv/sdv.par
	@rm -vf admb-re/sdv/sdv.r01
	@rm -vf admb-re/sdv/sdv.rep
	@rm -vf admb-re/sdv/sdv.rhes
	@rm -vf admb-re/sdv/sdv.std
	@rm -vf admb-re/skewed/admodel.cov
	@rm -vf admb-re/skewed/admodel.dep
	@rm -vf admb-re/skewed/admodel.hes
	@rm -vf admb-re/skewed/diet
	@rm -vf admb-re/skewed/diet.b01
	@rm -vf admb-re/skewed/diet.bar
	@rm -vf admb-re/skewed/diet.bgs
	@rm -vf admb-re/skewed/diet.cor
	@rm -vf admb-re/skewed/diet.cpp
	@rm -vf admb-re/skewed/diet.eva
	@rm -vf admb-re/skewed/diet.htp
	@rm -vf admb-re/skewed/diet.log
	@rm -vf admb-re/skewed/diet.obj
	@rm -vf admb-re/skewed/diet.p01
	@rm -vf admb-re/skewed/diet.par
	@rm -vf admb-re/skewed/diet.r01
	@rm -vf admb-re/skewed/diet.rep
	@rm -vf admb-re/skewed/diet.rhes
	@rm -vf admb-re/skewed/diet.std
	@rm -vf admb-re/skewed/diet_sk
	@rm -vf admb-re/skewed/diet_sk.b01
	@rm -vf admb-re/skewed/diet_sk.b02
	@rm -vf admb-re/skewed/diet_sk.bar
	@rm -vf admb-re/skewed/diet_sk.bgs
	@rm -vf admb-re/skewed/diet_sk.cor
	@rm -vf admb-re/skewed/diet_sk.cpp
	@rm -vf admb-re/skewed/diet_sk.eva
	@rm -vf admb-re/skewed/diet_sk.htp
	@rm -vf admb-re/skewed/diet_sk.log
	@rm -vf admb-re/skewed/diet_sk.obj
	@rm -vf admb-re/skewed/diet_sk.p01
	@rm -vf admb-re/skewed/diet_sk.p02
	@rm -vf admb-re/skewed/diet_sk.par
	@rm -vf admb-re/skewed/diet_sk.r01
	@rm -vf admb-re/skewed/diet_sk.r02
	@rm -vf admb-re/skewed/diet_sk.rep
	@rm -vf admb-re/skewed/diet_sk.rhes
	@rm -vf admb-re/skewed/diet_sk.std
	@rm -vf admb-re/skewed/fmin.log
	@rm -vf admb-re/skewed/hesscheck
	@rm -vf admb-re/skewed/hessian.bin
	@rm -vf admb-re/socatt/admodel.cov
	@rm -vf admb-re/socatt/admodel.dep
	@rm -vf admb-re/socatt/admodel.hes
	@rm -vf admb-re/socatt/fmin.log
	@rm -vf admb-re/socatt/hesscheck
	@rm -vf admb-re/socatt/hessian.bin
	@rm -vf admb-re/socatt/socatt
	@rm -vf admb-re/socatt/socatt.bar
	@rm -vf admb-re/socatt/socatt.bgs
	@rm -vf admb-re/socatt/socatt.cor
	@rm -vf admb-re/socatt/socatt.cpp
	@rm -vf admb-re/socatt/socatt.eva
	@rm -vf admb-re/socatt/socatt.htp
	@rm -vf admb-re/socatt/socatt.log
	@rm -vf admb-re/socatt/socatt.obj
	@rm -vf admb-re/socatt/socatt.par
	@rm -vf admb-re/socatt/socatt.rep
	@rm -vf admb-re/socatt/socatt.rhes
	@rm -vf admb-re/socatt/socatt.std
	@rm -vf admb-re/spatial/admodel.cov
	@rm -vf admb-re/spatial/admodel.dep
	@rm -vf admb-re/spatial/admodel.hes
	@rm -vf admb-re/spatial/classcode.tmp
	@rm -vf admb-re/spatial/fmin.log
	@rm -vf admb-re/spatial/hesscheck
	@rm -vf admb-re/spatial/hessian.bin
	@rm -vf admb-re/spatial/spatial
	@rm -vf admb-re/spatial/spatial.b01
	@rm -vf admb-re/spatial/spatial.bar
	@rm -vf admb-re/spatial/spatial.bgs
	@rm -vf admb-re/spatial/spatial.cor
	@rm -vf admb-re/spatial/spatial.cpp
	@rm -vf admb-re/spatial/spatial.eva
	@rm -vf admb-re/spatial/spatial.htp
	@rm -vf admb-re/spatial/spatial.log
	@rm -vf admb-re/spatial/spatial.luu
	@rm -vf admb-re/spatial/spatial.obj
	@rm -vf admb-re/spatial/spatial.p01
	@rm -vf admb-re/spatial/spatial.par
	@rm -vf admb-re/spatial/spatial.r01
	@rm -vf admb-re/spatial/spatial.rep
	@rm -vf admb-re/spatial/spatial.rhes
	@rm -vf admb-re/spatial/spatial.std
	@rm -vf admb-re/union/admodel.cov
	@rm -vf admb-re/union/admodel.dep
	@rm -vf admb-re/union/admodel.hes
	@rm -vf admb-re/union/fmin.log
	@rm -vf admb-re/union/hesscheck
	@rm -vf admb-re/union/hessian.bin
	@rm -vf admb-re/union/union
	@rm -vf admb-re/union/union.b01
	@rm -vf admb-re/union/union.bar
	@rm -vf admb-re/union/union.bgs
	@rm -vf admb-re/union/union.cor
	@rm -vf admb-re/union/union.cpp
	@rm -vf admb-re/union/union.eva
	@rm -vf admb-re/union/union.htp
	@rm -vf admb-re/union/union.log
	@rm -vf admb-re/union/union.luu
	@rm -vf admb-re/union/union.obj
	@rm -vf admb-re/union/union.p01
	@rm -vf admb-re/union/union.par
	@rm -vf admb-re/union/union.r01
	@rm -vf admb-re/union/union.rep
	@rm -vf admb-re/union/union.rhes
	@rm -vf admb-re/union/union.std
	@rm -vf admb-re/weights/admodel.cov
	@rm -vf admb-re/weights/admodel.dep
	@rm -vf admb-re/weights/admodel.hes
	@rm -vf admb-re/weights/binomial
	@rm -vf admb-re/weights/binomial.b01
	@rm -vf admb-re/weights/binomial.bar
	@rm -vf admb-re/weights/binomial.bgs
	@rm -vf admb-re/weights/binomial.cor
	@rm -vf admb-re/weights/binomial.cpp
	@rm -vf admb-re/weights/binomial.eva
	@rm -vf admb-re/weights/binomial.htp
	@rm -vf admb-re/weights/binomial.log
	@rm -vf admb-re/weights/binomial.obj
	@rm -vf admb-re/weights/binomial.p01
	@rm -vf admb-re/weights/binomial.par
	@rm -vf admb-re/weights/binomial.rhes
	@rm -vf admb-re/weights/binomial.std
	@rm -vf admb-re/weights/fmin.log
	@rm -vf admb-re/weights/hesscheck
	@rm -vf admb-re/weights/hessian.bin
	@rm -vf admb/buscycle/admodel.cov
	@rm -vf admb/buscycle/admodel.dep
	@rm -vf admb/buscycle/admodel.hes
	@rm -vf admb/buscycle/fmin.log
	@rm -vf admb/buscycle/gradfil1.tmp
	@rm -vf admb/buscycle/gradfil2.tmp
	@rm -vf admb/buscycle/ham4
	@rm -vf admb/buscycle/ham4.b01
	@rm -vf admb/buscycle/ham4.b02
	@rm -vf admb/buscycle/ham4.b03
	@rm -vf admb/buscycle/ham4.b04
	@rm -vf admb/buscycle/ham4.bar
	@rm -vf admb/buscycle/ham4.cor
	@rm -vf admb/buscycle/ham4.cpp
	@rm -vf admb/buscycle/ham4.eva
	@rm -vf admb/buscycle/ham4.htp
	@rm -vf admb/buscycle/ham4.log
	@rm -vf admb/buscycle/ham4.obj
	@rm -vf admb/buscycle/ham4.p01
	@rm -vf admb/buscycle/ham4.p02
	@rm -vf admb/buscycle/ham4.p03
	@rm -vf admb/buscycle/ham4.p04
	@rm -vf admb/buscycle/ham4.par
	@rm -vf admb/buscycle/ham4.r01
	@rm -vf admb/buscycle/ham4.r02
	@rm -vf admb/buscycle/ham4.r03
	@rm -vf admb/buscycle/ham4.r04
	@rm -vf admb/buscycle/ham4.rep
	@rm -vf admb/buscycle/ham4.std
	@rm -vf admb/buscycle/ham5
	@rm -vf admb/buscycle/ham5.b01
	@rm -vf admb/buscycle/ham5.b02
	@rm -vf admb/buscycle/ham5.b03
	@rm -vf admb/buscycle/ham5.b04
	@rm -vf admb/buscycle/ham5.bar
	@rm -vf admb/buscycle/ham5.cor
	@rm -vf admb/buscycle/ham5.cpp
	@rm -vf admb/buscycle/ham5.eva
	@rm -vf admb/buscycle/ham5.htp
	@rm -vf admb/buscycle/ham5.log
	@rm -vf admb/buscycle/ham5.obj
	@rm -vf admb/buscycle/ham5.p01
	@rm -vf admb/buscycle/ham5.p02
	@rm -vf admb/buscycle/ham5.p03
	@rm -vf admb/buscycle/ham5.p04
	@rm -vf admb/buscycle/ham5.par
	@rm -vf admb/buscycle/ham5.r01
	@rm -vf admb/buscycle/ham5.r02
	@rm -vf admb/buscycle/ham5.r03
	@rm -vf admb/buscycle/ham5.r04
	@rm -vf admb/buscycle/ham5.rep
	@rm -vf admb/buscycle/ham5.std
	@rm -vf admb/buscycle/qafter4.tex
	@rm -vf admb/buscycle/qafter5.tex
	@rm -vf admb/buscycle/qbefore4.tex
	@rm -vf admb/buscycle/qbefore5.tex
	@rm -vf admb/buscycle/varssave.tmp
	@rm -vf admb/chem_eng/admodel.cov
	@rm -vf admb/chem_eng/admodel.dep
	@rm -vf admb/chem_eng/admodel.hes
	@rm -vf admb/chem_eng/chem_eng
	@rm -vf admb/chem_eng/chem_eng.bar
	@rm -vf admb/chem_eng/chem_eng.cor
	@rm -vf admb/chem_eng/chem_eng.cpp
	@rm -vf admb/chem_eng/chem_eng.eva
	@rm -vf admb/chem_eng/chem_eng.htp
	@rm -vf admb/chem_eng/chem_eng.log
	@rm -vf admb/chem_eng/chem_eng.obj
	@rm -vf admb/chem_eng/chem_eng.par
	@rm -vf admb/chem_eng/chem_eng.std
	@rm -vf admb/chem_eng/fmin.log
	@rm -vf admb/finance/admodel.cov
	@rm -vf admb/finance/admodel.dep
	@rm -vf admb/finance/admodel.hes
	@rm -vf admb/finance/finance
	@rm -vf admb/finance/finance.b01
	@rm -vf admb/finance/finance.b02
	@rm -vf admb/finance/finance.bar
	@rm -vf admb/finance/finance.cor
	@rm -vf admb/finance/finance.cpp
	@rm -vf admb/finance/finance.eva
	@rm -vf admb/finance/finance.htp
	@rm -vf admb/finance/finance.log
	@rm -vf admb/finance/finance.obj
	@rm -vf admb/finance/finance.p01
	@rm -vf admb/finance/finance.p02
	@rm -vf admb/finance/finance.par
	@rm -vf admb/finance/finance.std
	@rm -vf admb/finance/fmin.log
	@rm -vf admb/forest/admodel.cov
	@rm -vf admb/forest/admodel.dep
	@rm -vf admb/forest/admodel.hes
	@rm -vf admb/forest/fmin.log
	@rm -vf admb/forest/forest
	@rm -vf admb/forest/forest.b01
	@rm -vf admb/forest/forest.bar
	@rm -vf admb/forest/forest.cor
	@rm -vf admb/forest/forest.cpp
	@rm -vf admb/forest/forest.eva
	@rm -vf admb/forest/forest.htp
	@rm -vf admb/forest/forest.log
	@rm -vf admb/forest/forest.obj
	@rm -vf admb/forest/forest.p01
	@rm -vf admb/forest/forest.par
	@rm -vf admb/forest/forest.r01
	@rm -vf admb/forest/forest.rep
	@rm -vf admb/forest/forest.std
	@rm -vf admb/pella_t/admodel.cov
	@rm -vf admb/pella_t/admodel.dep
	@rm -vf admb/pella_t/admodel.hes
	@rm -vf admb/pella_t/fmin.log
	@rm -vf admb/pella_t/pella_t
	@rm -vf admb/pella_t/pella_t.b01
	@rm -vf admb/pella_t/pella_t.b02
	@rm -vf admb/pella_t/pella_t.b03
	@rm -vf admb/pella_t/pella_t.bar
	@rm -vf admb/pella_t/pella_t.cor
	@rm -vf admb/pella_t/pella_t.cpp
	@rm -vf admb/pella_t/pella_t.eva
	@rm -vf admb/pella_t/pella_t.htp
	@rm -vf admb/pella_t/pella_t.log
	@rm -vf admb/pella_t/pella_t.obj
	@rm -vf admb/pella_t/pella_t.p01
	@rm -vf admb/pella_t/pella_t.p02
	@rm -vf admb/pella_t/pella_t.p03
	@rm -vf admb/pella_t/pella_t.par
	@rm -vf admb/pella_t/pella_t.std
	@rm -vf admb/robreg/admodel.cov
	@rm -vf admb/robreg/admodel.dep
	@rm -vf admb/robreg/admodel.hes
	@rm -vf admb/robreg/fmin.log
	@rm -vf admb/robreg/vonb
	@rm -vf admb/robreg/vonb.bar
	@rm -vf admb/robreg/vonb.cor
	@rm -vf admb/robreg/vonb.cpp
	@rm -vf admb/robreg/vonb.eva
	@rm -vf admb/robreg/vonb.htp
	@rm -vf admb/robreg/vonb.log
	@rm -vf admb/robreg/vonb.obj
	@rm -vf admb/robreg/vonb.par
	@rm -vf admb/robreg/vonb.std
	@rm -vf admb/robreg/vonbr
	@rm -vf admb/robreg/vonbr.b01
	@rm -vf admb/robreg/vonbr.bar
	@rm -vf admb/robreg/vonbr.cor
	@rm -vf admb/robreg/vonbr.cpp
	@rm -vf admb/robreg/vonbr.eva
	@rm -vf admb/robreg/vonbr.htp
	@rm -vf admb/robreg/vonbr.log
	@rm -vf admb/robreg/vonbr.obj
	@rm -vf admb/robreg/vonbr.p01
	@rm -vf admb/robreg/vonbr.par
	@rm -vf admb/robreg/vonbr.std
	@rm -vf admb/truncreg/admodel.cov
	@rm -vf admb/truncreg/admodel.dep
	@rm -vf admb/truncreg/admodel.hes
	@rm -vf admb/truncreg/fmin.log
	@rm -vf admb/truncreg/truncreg
	@rm -vf admb/truncreg/truncreg.bar
	@rm -vf admb/truncreg/truncreg.cor
	@rm -vf admb/truncreg/truncreg.cpp
	@rm -vf admb/truncreg/truncreg.eva
	@rm -vf admb/truncreg/truncreg.htp
	@rm -vf admb/truncreg/truncreg.log
	@rm -vf admb/truncreg/truncreg.obj
	@rm -vf admb/truncreg/truncreg.par
	@rm -vf admb/truncreg/truncreg.rep
	@rm -vf admb/truncreg/truncreg.std
	@rm -vf admb/vol/admodel.cov
	@rm -vf admb/vol/admodel.dep
	@rm -vf admb/vol/admodel.hes
	@rm -vf admb/vol/fmin.log
	@rm -vf admb/vol/n2mvol
	@rm -vf admb/vol/n2mvol.b01
	@rm -vf admb/vol/n2mvol.bar
	@rm -vf admb/vol/n2mvol.cor
	@rm -vf admb/vol/n2mvol.cpp
	@rm -vf admb/vol/n2mvol.eva
	@rm -vf admb/vol/n2mvol.htp
	@rm -vf admb/vol/n2mvol.log
	@rm -vf admb/vol/n2mvol.obj
	@rm -vf admb/vol/n2mvol.p01
	@rm -vf admb/vol/n2mvol.par
	@rm -vf admb/vol/n2mvol.r01
	@rm -vf admb/vol/n2mvol.rep
	@rm -vf admb/vol/n2mvol.std
	@rm -vf autodif/hemholtz/fmin.log
	@rm -vf autodif/hemholtz/hem_func.obj
	@rm -vf autodif/hemholtz/hemholtz
	@rm -vf autodif/hemholtz/hemholtz.obj
	@rm -vf autodif/io_examp/file1.tmp
	@rm -vf autodif/io_examp/file2.tmp
	@rm -vf autodif/io_examp/fmin.log
	@rm -vf autodif/io_examp/io_examp
	@rm -vf autodif/io_examp/io_examp.obj
	@rm -vf autodif/newt/fmin.log
	@rm -vf autodif/newt/newt
	@rm -vf autodif/newt/newt.obj
	@rm -vf autodif/simple/fcomp_s.obj
	@rm -vf autodif/simple/fmin.log
	@rm -vf autodif/simple/s1
	@rm -vf autodif/simple/s1.obj
	@rm -vf autodif/simple/simp1
	@rm -vf autodif/simple/simp1.obj
	@rm -vf autodif/simple/simple
	@rm -vf autodif/simple/simple.obj
	@rm -vf autodif/simple/simple2
	@rm -vf autodif/simple/simple2.obj
	@rm -vf autodif/struct/fmin.log
	@rm -vf autodif/struct/oldstr
	@rm -vf autodif/struct/oldstr.obj
	@rm -vf autodif/struct/struct
	@rm -vf autodif/struct/struct.obj
	@rm -vf autodif/bigmin/bigmin
	@rm -vf autodif/bigmin/bigmin.obj
	@rm -vf autodif/bigmin/fmin.log
	@rm -vf autodif/mixture/fcomp_m.obj
	@rm -vf autodif/mixture/fmin.log
	@rm -vf autodif/mixture/like.obj
	@rm -vf autodif/mixture/mixture
	@rm -vf autodif/mixture/mixture.obj
	@rm -vf autodif/mixture/normaliz.obj
	@rm -vf autodif/mixture/normsim
	@rm -vf autodif/mixture/normsim.obj
	@rm -vf autodif/mixture/normsim.out
	@rm -vf autodif/mixture/nvarcal.obj
	@rm -vf autodif/mixture/reset.obj
	@rm -vf autodif/mixture/savepar.obj
	@rm -vf autodif/mixture/xinit.obj
	@rm -vf admb/catage/admodel.cov
	@rm -vf admb/catage/admodel.dep
	@rm -vf admb/catage/admodel.hes
	@rm -vf admb/catage/catage
	@rm -vf admb/catage/catage.b01
	@rm -vf admb/catage/catage.b02
	@rm -vf admb/catage/catage.bar
	@rm -vf admb/catage/catage.cor
	@rm -vf admb/catage/catage.cpp
	@rm -vf admb/catage/catage.eva
	@rm -vf admb/catage/catage.htp
	@rm -vf admb/catage/catage.log
	@rm -vf admb/catage/catage.obj
	@rm -vf admb/catage/catage.p01
	@rm -vf admb/catage/catage.p02
	@rm -vf admb/catage/catage.par
	@rm -vf admb/catage/catage.r01
	@rm -vf admb/catage/catage.r02
	@rm -vf admb/catage/catage.rep
	@rm -vf admb/catage/catage.std
	@rm -vf admb/catage/fmin.log
	@rm -vf admb/simple/admodel.cov
	@rm -vf admb/simple/admodel.dep
	@rm -vf admb/simple/admodel.hes
	@rm -vf admb/simple/fmin.log
	@rm -vf admb/simple/simple
	@rm -vf admb/simple/simple.bar
	@rm -vf admb/simple/simple.cor
	@rm -vf admb/simple/simple.cpp
	@rm -vf admb/simple/simple.eva
	@rm -vf admb/simple/simple.htp
	@rm -vf admb/simple/simple.log
	@rm -vf admb/simple/simple.obj
	@rm -vf admb/simple/simple.par
	@rm -vf admb/simple/simple.std
	@rm -vf autodif/bigmin/matinv.est
endif
