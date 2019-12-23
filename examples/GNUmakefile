.ONESHELL:

ifeq ($(TERM),cygwin)
ifeq ($(OS),Windows_NT)
  ifeq ($(strip $(TERM)),)
    SHELL=cmd
    ADMB_HOME=$(shell cmd /C cd .. && cd)
  else
    EXT=.sh
    ADMB_HOME=$(shell cd .. && pwd)
  endif
endif

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
ifneq ($(TERM),cygwin)
PROG=time
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

all: admb admb-re
	cd autodif && $(MAKE)

admb: $(ADMB_TPLS)

buscycle:
	$(MAKE) ham4 
	$(MAKE) ham5
ham4:
	cd admb/buscycle && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

ham5:
	cd admb/buscycle && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

catage:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

chem_eng:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

finance:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

forest:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

pella_t:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

robreg:
	$(MAKE) vonb
	$(MAKE) vonbr
vonb:
	cd admb/robreg && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

vonbr:
	cd admb/robreg && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

simple-version:
	cd admb/ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@ -version

simple:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

truncreg:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@ -ams 2000000 && $(PROG) ./$@ -ams 2000000 -gbs 6000000 -cbs 4000000

vol: n2mvol
n2mvol:
	cd admb/vol && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@ -iprint 1

admb-re: $(ADMB_RE_TPLS)

bcb:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT)  $(OPTIONS) $@ && $(PROG) ./$@

biglog:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT)  $(OPTIONS) $@ && $(PROG) ./$@

bvprobit:
	cd admb-re/glmmadmb && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

glmmadmb:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@ -maxph 5 -noinit -shess -crit 1.e-6

caest:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

gamma:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) liver_$@ && $(PROG) ./liver_$@

kidney:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

lidar:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

logistic:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

nbmm:
	cd admb-re/nbmm && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

nested4:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

orange:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

orange2:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

orange_cor:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
pheno:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

polio:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

sdv:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

skewed:
	$(MAKE) diet
	$(MAKE) diet_sk
diet:
	cd admb-re/skewed && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

diet_sk:
	cd admb-re/skewed && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

socatt:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

spatial:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

union:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

weights: binomial
binomial:
	cd admb-re/weights && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
binomial_w2:
	cd admb-re/weights && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

copy:
ifneq ($(DEBUG),yes)
  ifeq ($(SHELL),cmd)
	if not exist ..\build\dist\examples md ..\build\dist\examples
	xcopy ..\examples ..\build\dist\examples /S /Y /D
  else
	cp -Rvf ../examples ../build/dist
  endif
else
  ifeq ($(SHELL),cmd)
	if not exist ..\build\debug\examples md ..\build\debug\examples
	xcopy ..\examples ..\build\debug\examples /S /Y /D
  else
	cp -Rvf ../examples ../build/debug
  endif
endif

clean:
ifeq ($(SHELL),cmd)
else
	rm -vf admb-re/bcb/admodel.cov
	rm -vf admb-re/bcb/admodel.dep
	rm -vf admb-re/bcb/admodel.hes
	rm -vf admb-re/bcb/bcb
	rm -vf admb-re/bcb/bcb.bar
	rm -vf admb-re/bcb/bcb.bgs
	rm -vf admb-re/bcb/bcb.cor
	rm -vf admb-re/bcb/bcb.cpp
	rm -vf admb-re/bcb/bcb.eva
	rm -vf admb-re/bcb/bcb.htp
	rm -vf admb-re/bcb/bcb.log
	rm -vf admb-re/bcb/bcb.luu
	rm -vf admb-re/bcb/bcb.obj
	rm -vf admb-re/bcb/bcb.par
	rm -vf admb-re/bcb/bcb.rep
	rm -vf admb-re/bcb/bcb.rhes
	rm -vf admb-re/bcb/bcb.std
	rm -vf admb-re/bcb/fmin.log
	rm -vf admb-re/bcb/hesscheck
	rm -vf admb-re/bcb/hessian.bin
	rm -vf admb-re/biglog/admodel.cov
	rm -vf admb-re/biglog/admodel.dep
	rm -vf admb-re/biglog/admodel.hes
	rm -vf admb-re/biglog/biglog
	rm -vf admb-re/biglog/biglog.b01
	rm -vf admb-re/biglog/biglog.b02
	rm -vf admb-re/biglog/biglog.bar
	rm -vf admb-re/biglog/biglog.bgs
	rm -vf admb-re/biglog/biglog.cor
	rm -vf admb-re/biglog/biglog.cpp
	rm -vf admb-re/biglog/biglog.eva
	rm -vf admb-re/biglog/biglog.htp
	rm -vf admb-re/biglog/biglog.log
	rm -vf admb-re/biglog/biglog.luu
	rm -vf admb-re/biglog/biglog.obj
	rm -vf admb-re/biglog/biglog.p01
	rm -vf admb-re/biglog/biglog.p02
	rm -vf admb-re/biglog/biglog.par
	rm -vf admb-re/biglog/biglog.rhes
	rm -vf admb-re/biglog/biglog.std
	rm -vf admb-re/biglog/fmin.log
	rm -vf admb-re/biglog/hesscheck
	rm -vf admb-re/biglog/hessian.bin
	rm -vf admb-re/caest/admodel.cov
	rm -vf admb-re/caest/admodel.dep
	rm -vf admb-re/caest/admodel.hes
	rm -vf admb-re/caest/caest
	rm -vf admb-re/caest/caest.b01
	rm -vf admb-re/caest/caest.bar
	rm -vf admb-re/caest/caest.bgs
	rm -vf admb-re/caest/caest.cor
	rm -vf admb-re/caest/caest.cpp
	rm -vf admb-re/caest/caest.eva
	rm -vf admb-re/caest/caest.htp
	rm -vf admb-re/caest/caest.log
	rm -vf admb-re/caest/caest.luu
	rm -vf admb-re/caest/caest.obj
	rm -vf admb-re/caest/caest.p01
	rm -vf admb-re/caest/caest.par
	rm -vf admb-re/caest/caest.r01
	rm -vf admb-re/caest/caest.rep
	rm -vf admb-re/caest/caest.rhes
	rm -vf admb-re/caest/caest.std
	rm -vf admb-re/caest/fmin.log
	rm -vf admb-re/caest/hesscheck
	rm -vf admb-re/caest/hessian.bin
	rm -vf admb-re/gamma/admodel.cov
	rm -vf admb-re/gamma/admodel.dep
	rm -vf admb-re/gamma/admodel.hes
	rm -vf admb-re/gamma/fmin.log
	rm -vf admb-re/gamma/hesscheck
	rm -vf admb-re/gamma/hessian.bin
	rm -vf admb-re/gamma/liver_gamma
	rm -vf admb-re/gamma/liver_gamma.b01
	rm -vf admb-re/gamma/liver_gamma.bar
	rm -vf admb-re/gamma/liver_gamma.bgs
	rm -vf admb-re/gamma/liver_gamma.cor
	rm -vf admb-re/gamma/liver_gamma.cpp
	rm -vf admb-re/gamma/liver_gamma.eva
	rm -vf admb-re/gamma/liver_gamma.htp
	rm -vf admb-re/gamma/liver_gamma.log
	rm -vf admb-re/gamma/liver_gamma.obj
	rm -vf admb-re/gamma/liver_gamma.p01
	rm -vf admb-re/gamma/liver_gamma.par
	rm -vf admb-re/gamma/liver_gamma.rhes
	rm -vf admb-re/gamma/liver_gamma.std
	rm -vf admb-re/glmmadmb/admodel.cov
	rm -vf admb-re/glmmadmb/admodel.dep
	rm -vf admb-re/glmmadmb/admodel.hes
	rm -vf admb-re/glmmadmb/b1
	rm -vf admb-re/glmmadmb/b2
	rm -vf admb-re/glmmadmb/bvprobit
	rm -vf admb-re/glmmadmb/bvprobit.b01
	rm -vf admb-re/glmmadmb/bvprobit.bar
	rm -vf admb-re/glmmadmb/bvprobit.bgs
	rm -vf admb-re/glmmadmb/bvprobit.cor
	rm -vf admb-re/glmmadmb/bvprobit.cpp
	rm -vf admb-re/glmmadmb/bvprobit.eva
	rm -vf admb-re/glmmadmb/bvprobit.htp
	rm -vf admb-re/glmmadmb/bvprobit.log
	rm -vf admb-re/glmmadmb/bvprobit.obj
	rm -vf admb-re/glmmadmb/bvprobit.p01
	rm -vf admb-re/glmmadmb/bvprobit.par
	rm -vf admb-re/glmmadmb/bvprobit.r01
	rm -vf admb-re/glmmadmb/bvprobit.rep
	rm -vf admb-re/glmmadmb/bvprobit.rhes
	rm -vf admb-re/glmmadmb/bvprobit.std
	rm -vf admb-re/glmmadmb/fmin.log
	rm -vf admb-re/glmmadmb/glmmadmb
	rm -vf admb-re/glmmadmb/glmmadmb.b01
	rm -vf admb-re/glmmadmb/glmmadmb.b02
	rm -vf admb-re/glmmadmb/glmmadmb.b03
	rm -vf admb-re/glmmadmb/glmmadmb.b04
	rm -vf admb-re/glmmadmb/glmmadmb.bar
	rm -vf admb-re/glmmadmb/glmmadmb.bgs
	rm -vf admb-re/glmmadmb/glmmadmb.cor
	rm -vf admb-re/glmmadmb/glmmadmb.cpp
	rm -vf admb-re/glmmadmb/glmmadmb.eva
	rm -vf admb-re/glmmadmb/glmmadmb.htp
	rm -vf admb-re/glmmadmb/glmmadmb.log
	rm -vf admb-re/glmmadmb/glmmadmb.luu
	rm -vf admb-re/glmmadmb/glmmadmb.obj
	rm -vf admb-re/glmmadmb/glmmadmb.p01
	rm -vf admb-re/glmmadmb/glmmadmb.p02
	rm -vf admb-re/glmmadmb/glmmadmb.p03
	rm -vf admb-re/glmmadmb/glmmadmb.p04
	rm -vf admb-re/glmmadmb/glmmadmb.par
	rm -vf admb-re/glmmadmb/glmmadmb.r01
	rm -vf admb-re/glmmadmb/glmmadmb.r02
	rm -vf admb-re/glmmadmb/glmmadmb.r03
	rm -vf admb-re/glmmadmb/glmmadmb.r04
	rm -vf admb-re/glmmadmb/glmmadmb.rep
	rm -vf admb-re/glmmadmb/glmmadmb.rhes
	rm -vf admb-re/glmmadmb/glmmadmb.shess
	rm -vf admb-re/glmmadmb/glmmadmb.std
	rm -vf admb-re/glmmadmb/hesscheck
	rm -vf admb-re/glmmadmb/hessian.bin
	rm -vf admb-re/glmmadmb/phi.rep
	rm -vf admb-re/glmmadmb/s1
	rm -vf admb-re/glmmadmb/s2
	rm -vf admb-re/kidney/admodel.cov
	rm -vf admb-re/kidney/admodel.dep
	rm -vf admb-re/kidney/admodel.hes
	rm -vf admb-re/kidney/fmin.log
	rm -vf admb-re/kidney/hesscheck
	rm -vf admb-re/kidney/hessian.bin
	rm -vf admb-re/kidney/kidney
	rm -vf admb-re/kidney/kidney.bar
	rm -vf admb-re/kidney/kidney.bgs
	rm -vf admb-re/kidney/kidney.cor
	rm -vf admb-re/kidney/kidney.cpp
	rm -vf admb-re/kidney/kidney.eva
	rm -vf admb-re/kidney/kidney.htp
	rm -vf admb-re/kidney/kidney.log
	rm -vf admb-re/kidney/kidney.luu
	rm -vf admb-re/kidney/kidney.obj
	rm -vf admb-re/kidney/kidney.par
	rm -vf admb-re/kidney/kidney.rep
	rm -vf admb-re/kidney/kidney.rhes
	rm -vf admb-re/kidney/kidney.std
	rm -vf admb-re/lidar/admodel.cov
	rm -vf admb-re/lidar/admodel.dep
	rm -vf admb-re/lidar/admodel.hes
	rm -vf admb-re/lidar/fmin.log
	rm -vf admb-re/lidar/hesscheck
	rm -vf admb-re/lidar/hessian.bin
	rm -vf admb-re/lidar/lidar
	rm -vf admb-re/lidar/lidar.b01
	rm -vf admb-re/lidar/lidar.bar
	rm -vf admb-re/lidar/lidar.bgs
	rm -vf admb-re/lidar/lidar.cor
	rm -vf admb-re/lidar/lidar.cpp
	rm -vf admb-re/lidar/lidar.eva
	rm -vf admb-re/lidar/lidar.htp
	rm -vf admb-re/lidar/lidar.log
	rm -vf admb-re/lidar/lidar.luu
	rm -vf admb-re/lidar/lidar.obj
	rm -vf admb-re/lidar/lidar.p01
	rm -vf admb-re/lidar/lidar.par
	rm -vf admb-re/lidar/lidar.r01
	rm -vf admb-re/lidar/lidar.rep
	rm -vf admb-re/lidar/lidar.rhes
	rm -vf admb-re/lidar/lidar.std
	rm -vf admb-re/logistic/admodel.cov
	rm -vf admb-re/logistic/admodel.dep
	rm -vf admb-re/logistic/admodel.hes
	rm -vf admb-re/logistic/fmin.log
	rm -vf admb-re/logistic/hesscheck
	rm -vf admb-re/logistic/hessian.bin
	rm -vf admb-re/logistic/logistic
	rm -vf admb-re/logistic/logistic.b01
	rm -vf admb-re/logistic/logistic.bar
	rm -vf admb-re/logistic/logistic.bgs
	rm -vf admb-re/logistic/logistic.cor
	rm -vf admb-re/logistic/logistic.cpp
	rm -vf admb-re/logistic/logistic.eva
	rm -vf admb-re/logistic/logistic.htp
	rm -vf admb-re/logistic/logistic.log
	rm -vf admb-re/logistic/logistic.luu
	rm -vf admb-re/logistic/logistic.obj
	rm -vf admb-re/logistic/logistic.p01
	rm -vf admb-re/logistic/logistic.par
	rm -vf admb-re/logistic/logistic.r01
	rm -vf admb-re/logistic/logistic.rep
	rm -vf admb-re/logistic/logistic.rhes
	rm -vf admb-re/logistic/logistic.std
	rm -vf admb-re/nbmm/admodel.cov
	rm -vf admb-re/nbmm/admodel.dep
	rm -vf admb-re/nbmm/admodel.hes
	rm -vf admb-re/nbmm/fmin.log
	rm -vf admb-re/nbmm/hesscheck
	rm -vf admb-re/nbmm/hessian.bin
	rm -vf admb-re/nbmm/nbmm
	rm -vf admb-re/nbmm/nbmm.b01
	rm -vf admb-re/nbmm/nbmm.b02
	rm -vf admb-re/nbmm/nbmm.bar
	rm -vf admb-re/nbmm/nbmm.bgs
	rm -vf admb-re/nbmm/nbmm.cor
	rm -vf admb-re/nbmm/nbmm.cpp
	rm -vf admb-re/nbmm/nbmm.eva
	rm -vf admb-re/nbmm/nbmm.htp
	rm -vf admb-re/nbmm/nbmm.log
	rm -vf admb-re/nbmm/nbmm.luu
	rm -vf admb-re/nbmm/nbmm.obj
	rm -vf admb-re/nbmm/nbmm.p01
	rm -vf admb-re/nbmm/nbmm.p02
	rm -vf admb-re/nbmm/nbmm.par
	rm -vf admb-re/nbmm/nbmm.r01
	rm -vf admb-re/nbmm/nbmm.r02
	rm -vf admb-re/nbmm/nbmm.rep
	rm -vf admb-re/nbmm/nbmm.rhes
	rm -vf admb-re/nbmm/nbmm.std
	rm -vf admb-re/nested4/admodel.cov
	rm -vf admb-re/nested4/admodel.dep
	rm -vf admb-re/nested4/admodel.hes
	rm -vf admb-re/nested4/fmin.log
	rm -vf admb-re/nested4/hesscheck
	rm -vf admb-re/nested4/hessian.bin
	rm -vf admb-re/nested4/nested4.b01
	rm -vf admb-re/nested4/nested4.bar
	rm -vf admb-re/nested4/nested4.bgs
	rm -vf admb-re/nested4/nested4.cor
	rm -vf admb-re/nested4/nested4.cpp
	rm -vf admb-re/nested4/nested4.eva
	rm -vf admb-re/nested4/nested4.htp
	rm -vf admb-re/nested4/nested4.log
	rm -vf admb-re/nested4/nested4.obj
	rm -vf admb-re/nested4/nested4.p01
	rm -vf admb-re/nested4/nested4.par
	rm -vf admb-re/nested4/nested4.r01
	rm -vf admb-re/nested4/nested4.rep
	rm -vf admb-re/nested4/nested4.rhes
	rm -vf admb-re/nested4/nested4.std
	rm -vf admb-re/orange/admodel.cov
	rm -vf admb-re/orange/admodel.dep
	rm -vf admb-re/orange/admodel.hes
	rm -vf admb-re/orange/fmin.log
	rm -vf admb-re/orange/hesscheck
	rm -vf admb-re/orange/hessian.bin
	rm -vf admb-re/orange/orange
	rm -vf admb-re/orange/orange.b01
	rm -vf admb-re/orange/orange.bar
	rm -vf admb-re/orange/orange.bgs
	rm -vf admb-re/orange/orange.cor
	rm -vf admb-re/orange/orange.cpp
	rm -vf admb-re/orange/orange.eva
	rm -vf admb-re/orange/orange.htp
	rm -vf admb-re/orange/orange.log
	rm -vf admb-re/orange/orange.obj
	rm -vf admb-re/orange/orange.p01
	rm -vf admb-re/orange/orange.par
	rm -vf admb-re/orange/orange.r01
	rm -vf admb-re/orange/orange.rep
	rm -vf admb-re/orange/orange.rhes
	rm -vf admb-re/orange/orange.std
	rm -vf admb-re/orange2/admodel.cov
	rm -vf admb-re/orange2/admodel.dep
	rm -vf admb-re/orange2/admodel.hes
	rm -vf admb-re/orange2/fmin.log
	rm -vf admb-re/orange2/hesscheck
	rm -vf admb-re/orange2/hessian.bin
	rm -vf admb-re/orange2/orange2
	rm -vf admb-re/orange2/orange2.b01
	rm -vf admb-re/orange2/orange2.bar
	rm -vf admb-re/orange2/orange2.bgs
	rm -vf admb-re/orange2/orange2.cor
	rm -vf admb-re/orange2/orange2.cpp
	rm -vf admb-re/orange2/orange2.eva
	rm -vf admb-re/orange2/orange2.htp
	rm -vf admb-re/orange2/orange2.log
	rm -vf admb-re/orange2/orange2.luu
	rm -vf admb-re/orange2/orange2.obj
	rm -vf admb-re/orange2/orange2.p01
	rm -vf admb-re/orange2/orange2.par
	rm -vf admb-re/orange2/orange2.r01
	rm -vf admb-re/orange2/orange2.rep
	rm -vf admb-re/orange2/orange2.rhes
	rm -vf admb-re/orange2/orange2.std
	rm -vf admb-re/orange_cor/admodel.cov
	rm -vf admb-re/orange_cor/admodel.dep
	rm -vf admb-re/orange_cor/admodel.hes
	rm -vf admb-re/orange_cor/fmin.log
	rm -vf admb-re/orange_cor/hesscheck
	rm -vf admb-re/orange_cor/hessian.bin
	rm -vf admb-re/orange_cor/orange_cor
	rm -vf admb-re/orange_cor/orange_cor.b01
	rm -vf admb-re/orange_cor/orange_cor.bar
	rm -vf admb-re/orange_cor/orange_cor.bgs
	rm -vf admb-re/orange_cor/orange_cor.cor
	rm -vf admb-re/orange_cor/orange_cor.cpp
	rm -vf admb-re/orange_cor/orange_cor.eva
	rm -vf admb-re/orange_cor/orange_cor.htp
	rm -vf admb-re/orange_cor/orange_cor.log
	rm -vf admb-re/orange_cor/orange_cor.obj
	rm -vf admb-re/orange_cor/orange_cor.p01
	rm -vf admb-re/orange_cor/orange_cor.par
	rm -vf admb-re/orange_cor/orange_cor.r01
	rm -vf admb-re/orange_cor/orange_cor.rep
	rm -vf admb-re/orange_cor/orange_cor.rhes
	rm -vf admb-re/orange_cor/orange_cor.std
	rm -vf admb-re/pheno/admodel.cov
	rm -vf admb-re/pheno/admodel.dep
	rm -vf admb-re/pheno/admodel.hes
	rm -vf admb-re/pheno/fmin.log
	rm -vf admb-re/pheno/hesscheck
	rm -vf admb-re/pheno/hessian.bin
	rm -vf admb-re/pheno/pheno
	rm -vf admb-re/pheno/pheno.b01
	rm -vf admb-re/pheno/pheno.bar
	rm -vf admb-re/pheno/pheno.bgs
	rm -vf admb-re/pheno/pheno.cor
	rm -vf admb-re/pheno/pheno.cpp
	rm -vf admb-re/pheno/pheno.eva
	rm -vf admb-re/pheno/pheno.htp
	rm -vf admb-re/pheno/pheno.log
	rm -vf admb-re/pheno/pheno.obj
	rm -vf admb-re/pheno/pheno.p01
	rm -vf admb-re/pheno/pheno.par
	rm -vf admb-re/pheno/pheno.r01
	rm -vf admb-re/pheno/pheno.rep
	rm -vf admb-re/pheno/pheno.rhes
	rm -vf admb-re/pheno/pheno.std
	rm -vf admb-re/polio/admodel.cov
	rm -vf admb-re/polio/admodel.dep
	rm -vf admb-re/polio/admodel.hes
	rm -vf admb-re/polio/fmin.log
	rm -vf admb-re/polio/hesscheck
	rm -vf admb-re/polio/hessian.bin
	rm -vf admb-re/polio/polio
	rm -vf admb-re/polio/polio.b01
	rm -vf admb-re/polio/polio.bar
	rm -vf admb-re/polio/polio.bgs
	rm -vf admb-re/polio/polio.cor
	rm -vf admb-re/polio/polio.cpp
	rm -vf admb-re/polio/polio.eva
	rm -vf admb-re/polio/polio.htp
	rm -vf admb-re/polio/polio.log
	rm -vf admb-re/polio/polio.luu
	rm -vf admb-re/polio/polio.obj
	rm -vf admb-re/polio/polio.p01
	rm -vf admb-re/polio/polio.par
	rm -vf admb-re/polio/polio.r01
	rm -vf admb-re/polio/polio.rep
	rm -vf admb-re/polio/polio.rhes
	rm -vf admb-re/polio/polio.std
	rm -vf admb-re/sdv/admodel.cov
	rm -vf admb-re/sdv/admodel.dep
	rm -vf admb-re/sdv/admodel.hes
	rm -vf admb-re/sdv/fmin.log
	rm -vf admb-re/sdv/hesscheck
	rm -vf admb-re/sdv/hessian.bin
	rm -vf admb-re/sdv/sdv
	rm -vf admb-re/sdv/sdv.b01
	rm -vf admb-re/sdv/sdv.bar
	rm -vf admb-re/sdv/sdv.bgs
	rm -vf admb-re/sdv/sdv.cor
	rm -vf admb-re/sdv/sdv.cpp
	rm -vf admb-re/sdv/sdv.eva
	rm -vf admb-re/sdv/sdv.htp
	rm -vf admb-re/sdv/sdv.log
	rm -vf admb-re/sdv/sdv.luu
	rm -vf admb-re/sdv/sdv.obj
	rm -vf admb-re/sdv/sdv.p01
	rm -vf admb-re/sdv/sdv.par
	rm -vf admb-re/sdv/sdv.r01
	rm -vf admb-re/sdv/sdv.rep
	rm -vf admb-re/sdv/sdv.rhes
	rm -vf admb-re/sdv/sdv.std
	rm -vf admb-re/skewed/admodel.cov
	rm -vf admb-re/skewed/admodel.dep
	rm -vf admb-re/skewed/admodel.hes
	rm -vf admb-re/skewed/diet
	rm -vf admb-re/skewed/diet.b01
	rm -vf admb-re/skewed/diet.bar
	rm -vf admb-re/skewed/diet.bgs
	rm -vf admb-re/skewed/diet.cor
	rm -vf admb-re/skewed/diet.cpp
	rm -vf admb-re/skewed/diet.eva
	rm -vf admb-re/skewed/diet.htp
	rm -vf admb-re/skewed/diet.log
	rm -vf admb-re/skewed/diet.obj
	rm -vf admb-re/skewed/diet.p01
	rm -vf admb-re/skewed/diet.par
	rm -vf admb-re/skewed/diet.r01
	rm -vf admb-re/skewed/diet.rep
	rm -vf admb-re/skewed/diet.rhes
	rm -vf admb-re/skewed/diet.std
	rm -vf admb-re/skewed/diet_sk
	rm -vf admb-re/skewed/diet_sk.b01
	rm -vf admb-re/skewed/diet_sk.b02
	rm -vf admb-re/skewed/diet_sk.bar
	rm -vf admb-re/skewed/diet_sk.bgs
	rm -vf admb-re/skewed/diet_sk.cor
	rm -vf admb-re/skewed/diet_sk.cpp
	rm -vf admb-re/skewed/diet_sk.eva
	rm -vf admb-re/skewed/diet_sk.htp
	rm -vf admb-re/skewed/diet_sk.log
	rm -vf admb-re/skewed/diet_sk.obj
	rm -vf admb-re/skewed/diet_sk.p01
	rm -vf admb-re/skewed/diet_sk.p02
	rm -vf admb-re/skewed/diet_sk.par
	rm -vf admb-re/skewed/diet_sk.r01
	rm -vf admb-re/skewed/diet_sk.r02
	rm -vf admb-re/skewed/diet_sk.rep
	rm -vf admb-re/skewed/diet_sk.rhes
	rm -vf admb-re/skewed/diet_sk.std
	rm -vf admb-re/skewed/fmin.log
	rm -vf admb-re/skewed/hesscheck
	rm -vf admb-re/skewed/hessian.bin
	rm -vf admb-re/socatt/admodel.cov
	rm -vf admb-re/socatt/admodel.dep
	rm -vf admb-re/socatt/admodel.hes
	rm -vf admb-re/socatt/fmin.log
	rm -vf admb-re/socatt/hesscheck
	rm -vf admb-re/socatt/hessian.bin
	rm -vf admb-re/socatt/socatt
	rm -vf admb-re/socatt/socatt.bar
	rm -vf admb-re/socatt/socatt.bgs
	rm -vf admb-re/socatt/socatt.cor
	rm -vf admb-re/socatt/socatt.cpp
	rm -vf admb-re/socatt/socatt.eva
	rm -vf admb-re/socatt/socatt.htp
	rm -vf admb-re/socatt/socatt.log
	rm -vf admb-re/socatt/socatt.obj
	rm -vf admb-re/socatt/socatt.par
	rm -vf admb-re/socatt/socatt.rep
	rm -vf admb-re/socatt/socatt.rhes
	rm -vf admb-re/socatt/socatt.std
	rm -vf admb-re/spatial/admodel.cov
	rm -vf admb-re/spatial/admodel.dep
	rm -vf admb-re/spatial/admodel.hes
	rm -vf admb-re/spatial/classcode.tmp
	rm -vf admb-re/spatial/fmin.log
	rm -vf admb-re/spatial/hesscheck
	rm -vf admb-re/spatial/hessian.bin
	rm -vf admb-re/spatial/spatial
	rm -vf admb-re/spatial/spatial.b01
	rm -vf admb-re/spatial/spatial.bar
	rm -vf admb-re/spatial/spatial.bgs
	rm -vf admb-re/spatial/spatial.cor
	rm -vf admb-re/spatial/spatial.cpp
	rm -vf admb-re/spatial/spatial.eva
	rm -vf admb-re/spatial/spatial.htp
	rm -vf admb-re/spatial/spatial.log
	rm -vf admb-re/spatial/spatial.luu
	rm -vf admb-re/spatial/spatial.obj
	rm -vf admb-re/spatial/spatial.p01
	rm -vf admb-re/spatial/spatial.par
	rm -vf admb-re/spatial/spatial.r01
	rm -vf admb-re/spatial/spatial.rep
	rm -vf admb-re/spatial/spatial.rhes
	rm -vf admb-re/spatial/spatial.std
	rm -vf admb-re/union/admodel.cov
	rm -vf admb-re/union/admodel.dep
	rm -vf admb-re/union/admodel.hes
	rm -vf admb-re/union/fmin.log
	rm -vf admb-re/union/hesscheck
	rm -vf admb-re/union/hessian.bin
	rm -vf admb-re/union/union
	rm -vf admb-re/union/union.b01
	rm -vf admb-re/union/union.bar
	rm -vf admb-re/union/union.bgs
	rm -vf admb-re/union/union.cor
	rm -vf admb-re/union/union.cpp
	rm -vf admb-re/union/union.eva
	rm -vf admb-re/union/union.htp
	rm -vf admb-re/union/union.log
	rm -vf admb-re/union/union.luu
	rm -vf admb-re/union/union.obj
	rm -vf admb-re/union/union.p01
	rm -vf admb-re/union/union.par
	rm -vf admb-re/union/union.r01
	rm -vf admb-re/union/union.rep
	rm -vf admb-re/union/union.rhes
	rm -vf admb-re/union/union.std
	rm -vf admb-re/weights/admodel.cov
	rm -vf admb-re/weights/admodel.dep
	rm -vf admb-re/weights/admodel.hes
	rm -vf admb-re/weights/binomial
	rm -vf admb-re/weights/binomial.b01
	rm -vf admb-re/weights/binomial.bar
	rm -vf admb-re/weights/binomial.bgs
	rm -vf admb-re/weights/binomial.cor
	rm -vf admb-re/weights/binomial.cpp
	rm -vf admb-re/weights/binomial.eva
	rm -vf admb-re/weights/binomial.htp
	rm -vf admb-re/weights/binomial.log
	rm -vf admb-re/weights/binomial.obj
	rm -vf admb-re/weights/binomial.p01
	rm -vf admb-re/weights/binomial.par
	rm -vf admb-re/weights/binomial.rhes
	rm -vf admb-re/weights/binomial.std
	rm -vf admb-re/weights/fmin.log
	rm -vf admb-re/weights/hesscheck
	rm -vf admb-re/weights/hessian.bin
	rm -vf admb/buscycle/admodel.cov
	rm -vf admb/buscycle/admodel.dep
	rm -vf admb/buscycle/admodel.hes
	rm -vf admb/buscycle/fmin.log
	rm -vf admb/buscycle/gradfil1.tmp
	rm -vf admb/buscycle/gradfil2.tmp
	rm -vf admb/buscycle/ham4
	rm -vf admb/buscycle/ham4.b01
	rm -vf admb/buscycle/ham4.b02
	rm -vf admb/buscycle/ham4.b03
	rm -vf admb/buscycle/ham4.b04
	rm -vf admb/buscycle/ham4.bar
	rm -vf admb/buscycle/ham4.cor
	rm -vf admb/buscycle/ham4.cpp
	rm -vf admb/buscycle/ham4.eva
	rm -vf admb/buscycle/ham4.htp
	rm -vf admb/buscycle/ham4.log
	rm -vf admb/buscycle/ham4.obj
	rm -vf admb/buscycle/ham4.p01
	rm -vf admb/buscycle/ham4.p02
	rm -vf admb/buscycle/ham4.p03
	rm -vf admb/buscycle/ham4.p04
	rm -vf admb/buscycle/ham4.par
	rm -vf admb/buscycle/ham4.r01
	rm -vf admb/buscycle/ham4.r02
	rm -vf admb/buscycle/ham4.r03
	rm -vf admb/buscycle/ham4.r04
	rm -vf admb/buscycle/ham4.rep
	rm -vf admb/buscycle/ham4.std
	rm -vf admb/buscycle/ham5
	rm -vf admb/buscycle/ham5.b01
	rm -vf admb/buscycle/ham5.b02
	rm -vf admb/buscycle/ham5.b03
	rm -vf admb/buscycle/ham5.b04
	rm -vf admb/buscycle/ham5.bar
	rm -vf admb/buscycle/ham5.cor
	rm -vf admb/buscycle/ham5.cpp
	rm -vf admb/buscycle/ham5.eva
	rm -vf admb/buscycle/ham5.htp
	rm -vf admb/buscycle/ham5.log
	rm -vf admb/buscycle/ham5.obj
	rm -vf admb/buscycle/ham5.p01
	rm -vf admb/buscycle/ham5.p02
	rm -vf admb/buscycle/ham5.p03
	rm -vf admb/buscycle/ham5.p04
	rm -vf admb/buscycle/ham5.par
	rm -vf admb/buscycle/ham5.r01
	rm -vf admb/buscycle/ham5.r02
	rm -vf admb/buscycle/ham5.r03
	rm -vf admb/buscycle/ham5.r04
	rm -vf admb/buscycle/ham5.rep
	rm -vf admb/buscycle/ham5.std
	rm -vf admb/buscycle/qafter4.tex
	rm -vf admb/buscycle/qafter5.tex
	rm -vf admb/buscycle/qbefore4.tex
	rm -vf admb/buscycle/qbefore5.tex
	rm -vf admb/buscycle/varssave.tmp
	rm -vf admb/chem_eng/admodel.cov
	rm -vf admb/chem_eng/admodel.dep
	rm -vf admb/chem_eng/admodel.hes
	rm -vf admb/chem_eng/chem_eng
	rm -vf admb/chem_eng/chem_eng.bar
	rm -vf admb/chem_eng/chem_eng.cor
	rm -vf admb/chem_eng/chem_eng.cpp
	rm -vf admb/chem_eng/chem_eng.eva
	rm -vf admb/chem_eng/chem_eng.htp
	rm -vf admb/chem_eng/chem_eng.log
	rm -vf admb/chem_eng/chem_eng.obj
	rm -vf admb/chem_eng/chem_eng.par
	rm -vf admb/chem_eng/chem_eng.std
	rm -vf admb/chem_eng/fmin.log
	rm -vf admb/finance/admodel.cov
	rm -vf admb/finance/admodel.dep
	rm -vf admb/finance/admodel.hes
	rm -vf admb/finance/finance
	rm -vf admb/finance/finance.b01
	rm -vf admb/finance/finance.b02
	rm -vf admb/finance/finance.bar
	rm -vf admb/finance/finance.cor
	rm -vf admb/finance/finance.cpp
	rm -vf admb/finance/finance.eva
	rm -vf admb/finance/finance.htp
	rm -vf admb/finance/finance.log
	rm -vf admb/finance/finance.obj
	rm -vf admb/finance/finance.p01
	rm -vf admb/finance/finance.p02
	rm -vf admb/finance/finance.par
	rm -vf admb/finance/finance.std
	rm -vf admb/finance/fmin.log
	rm -vf admb/forest/admodel.cov
	rm -vf admb/forest/admodel.dep
	rm -vf admb/forest/admodel.hes
	rm -vf admb/forest/fmin.log
	rm -vf admb/forest/forest
	rm -vf admb/forest/forest.b01
	rm -vf admb/forest/forest.bar
	rm -vf admb/forest/forest.cor
	rm -vf admb/forest/forest.cpp
	rm -vf admb/forest/forest.eva
	rm -vf admb/forest/forest.htp
	rm -vf admb/forest/forest.log
	rm -vf admb/forest/forest.obj
	rm -vf admb/forest/forest.p01
	rm -vf admb/forest/forest.par
	rm -vf admb/forest/forest.r01
	rm -vf admb/forest/forest.rep
	rm -vf admb/forest/forest.std
	rm -vf admb/pella_t/admodel.cov
	rm -vf admb/pella_t/admodel.dep
	rm -vf admb/pella_t/admodel.hes
	rm -vf admb/pella_t/fmin.log
	rm -vf admb/pella_t/pella_t
	rm -vf admb/pella_t/pella_t.b01
	rm -vf admb/pella_t/pella_t.b02
	rm -vf admb/pella_t/pella_t.b03
	rm -vf admb/pella_t/pella_t.bar
	rm -vf admb/pella_t/pella_t.cor
	rm -vf admb/pella_t/pella_t.cpp
	rm -vf admb/pella_t/pella_t.eva
	rm -vf admb/pella_t/pella_t.htp
	rm -vf admb/pella_t/pella_t.log
	rm -vf admb/pella_t/pella_t.obj
	rm -vf admb/pella_t/pella_t.p01
	rm -vf admb/pella_t/pella_t.p02
	rm -vf admb/pella_t/pella_t.p03
	rm -vf admb/pella_t/pella_t.par
	rm -vf admb/pella_t/pella_t.std
	rm -vf admb/robreg/admodel.cov
	rm -vf admb/robreg/admodel.dep
	rm -vf admb/robreg/admodel.hes
	rm -vf admb/robreg/fmin.log
	rm -vf admb/robreg/vonb
	rm -vf admb/robreg/vonb.bar
	rm -vf admb/robreg/vonb.cor
	rm -vf admb/robreg/vonb.cpp
	rm -vf admb/robreg/vonb.eva
	rm -vf admb/robreg/vonb.htp
	rm -vf admb/robreg/vonb.log
	rm -vf admb/robreg/vonb.obj
	rm -vf admb/robreg/vonb.par
	rm -vf admb/robreg/vonb.std
	rm -vf admb/robreg/vonbr
	rm -vf admb/robreg/vonbr.b01
	rm -vf admb/robreg/vonbr.bar
	rm -vf admb/robreg/vonbr.cor
	rm -vf admb/robreg/vonbr.cpp
	rm -vf admb/robreg/vonbr.eva
	rm -vf admb/robreg/vonbr.htp
	rm -vf admb/robreg/vonbr.log
	rm -vf admb/robreg/vonbr.obj
	rm -vf admb/robreg/vonbr.p01
	rm -vf admb/robreg/vonbr.par
	rm -vf admb/robreg/vonbr.std
	rm -vf admb/truncreg/admodel.cov
	rm -vf admb/truncreg/admodel.dep
	rm -vf admb/truncreg/admodel.hes
	rm -vf admb/truncreg/fmin.log
	rm -vf admb/truncreg/truncreg
	rm -vf admb/truncreg/truncreg.bar
	rm -vf admb/truncreg/truncreg.cor
	rm -vf admb/truncreg/truncreg.cpp
	rm -vf admb/truncreg/truncreg.eva
	rm -vf admb/truncreg/truncreg.htp
	rm -vf admb/truncreg/truncreg.log
	rm -vf admb/truncreg/truncreg.obj
	rm -vf admb/truncreg/truncreg.par
	rm -vf admb/truncreg/truncreg.rep
	rm -vf admb/truncreg/truncreg.std
	rm -vf admb/vol/admodel.cov
	rm -vf admb/vol/admodel.dep
	rm -vf admb/vol/admodel.hes
	rm -vf admb/vol/fmin.log
	rm -vf admb/vol/n2mvol
	rm -vf admb/vol/n2mvol.b01
	rm -vf admb/vol/n2mvol.bar
	rm -vf admb/vol/n2mvol.cor
	rm -vf admb/vol/n2mvol.cpp
	rm -vf admb/vol/n2mvol.eva
	rm -vf admb/vol/n2mvol.htp
	rm -vf admb/vol/n2mvol.log
	rm -vf admb/vol/n2mvol.obj
	rm -vf admb/vol/n2mvol.p01
	rm -vf admb/vol/n2mvol.par
	rm -vf admb/vol/n2mvol.r01
	rm -vf admb/vol/n2mvol.rep
	rm -vf admb/vol/n2mvol.std
	rm -vf autodif/hemholtz/fmin.log
	rm -vf autodif/hemholtz/hem_func.obj
	rm -vf autodif/hemholtz/hemholtz
	rm -vf autodif/hemholtz/hemholtz.obj
	rm -vf autodif/io_examp/file1.tmp
	rm -vf autodif/io_examp/file2.tmp
	rm -vf autodif/io_examp/fmin.log
	rm -vf autodif/io_examp/io_examp
	rm -vf autodif/io_examp/io_examp.obj
	rm -vf autodif/newt/fmin.log
	rm -vf autodif/newt/newt
	rm -vf autodif/newt/newt.obj
	rm -vf autodif/simple/fcomp_s.obj
	rm -vf autodif/simple/fmin.log
	rm -vf autodif/simple/s1
	rm -vf autodif/simple/s1.obj
	rm -vf autodif/simple/simp1
	rm -vf autodif/simple/simp1.obj
	rm -vf autodif/simple/simple
	rm -vf autodif/simple/simple.obj
	rm -vf autodif/simple/simple2
	rm -vf autodif/simple/simple2.obj
	rm -vf autodif/struct/fmin.log
	rm -vf autodif/struct/oldstr
	rm -vf autodif/struct/oldstr.obj
	rm -vf autodif/struct/struct
	rm -vf autodif/struct/struct.obj
endif
