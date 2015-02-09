.ONESHELL:
ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
SHELL = cmd
ADMB_HOME=$(shell cmd /C cd .. && cd)
else
ADMB_HOME=$(shell cd .. && pwd)
endif
ifeq ($(OS),Windows_NT)
EXT=.sh
endif
ifdef OPTIONS
OPTIONS:= $(OPTIONS)
endif
ifeq ($(DEBUG),yes)
OPTIONS:= $(OPTIONS) -g
endif
ifdef FAST_OPTION
OPTIONS:= $(OPTIONS) -f
endif
ifndef PROG
PROG=time
endif

default: simple

ifdef PROG_VALGRIND
all: simple caest
else
all: admb admb-re
endif

admb:\
 buscycle\
 catage\
 chem-eng\
 forest\
 finance\
 pella-t\
 robreg\
 truncreg\
 simple\
 vol

buscycle:
	$(MAKE) ham4 
	$(MAKE) ham5
ham4:
	cd admb/buscycle && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@ -version && $(PROG) ./$@

ham5:
	cd admb/buscycle && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

catage:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

chem-eng:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

finance:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

forest:
	-cd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

pella-t:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

robreg:
	$(MAKE) vonb
	$(MAKE) vonbr
vonb:
	cd admb/robreg && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

vonbr:
	cd admb/robreg && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

simple:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

truncreg:
	cd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@ -ams 2000000 && $(PROG) ./$@ -ams 2000000 -gbs 6000000 -cbs 4000000

vol: n2mvol
n2mvol:
ifeq ($(PROG),time)
	cd admb/vol && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@ -nohess
endif

admb-re:\
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

bcb:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

biglog:
ifeq ($(PROG),time)
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@
endif

bvprobit:
	@#Do not catch for admb-9.x
	-cd admb-re/glmmadmb && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

glmmadmb:
	@#Do not catch for admb-9.x
	-cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@ -maxph 5 -noinit -shess -crit 1.e-6

caest:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

gamma:
	-cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) liver_$@ && $(PROG) ./liver_$@

kidney:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

lidar:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

logistic:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

nbmm:
	-cd admb-re/nbmm && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

nested4:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

orange:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

orange2:
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@

orange_cor:
ifeq ($(PROG),time)
	cd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@ -nohess
endif

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
	cd admb-re/weights && $(ADMB_HOME)/admb$(EXT) $(OPTIONS) $@ && $(PROG) ./$@ -nohess

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
