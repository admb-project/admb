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
ifdef DEBUG_OPTION
OPTIONS:= $(OPTIONS) -g
endif
ifdef FAST_OPTION
OPTIONS:= $(OPTIONS) -f
endif
ifdef PROG_VALGRIND
PROG=valgrind -v --leak-check=full --show-reachable=no --track-origins=yes
else
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
	pushd admb/buscycle && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@ -version && $(PROG) ./$@

ham5:
	pushd admb/buscycle && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

catage:
	pushd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

chem-eng:
	pushd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

finance:
	pushd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

forest:
	-pushd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

pella-t:
	pushd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

robreg:
	$(MAKE) vonb
	$(MAKE) vonbr
vonb:
	pushd admb/robreg && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

vonbr:
	pushd admb/robreg && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

simple:
	pushd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@

truncreg:
	pushd admb/$@ && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@ -ams 2000000 && $(PROG) ./$@ -ams 2000000 -gbs 6000000 -cbs 4000000

vol: n2mvol
n2mvol:
	pushd admb/vol && $(ADMB_HOME)/admb$(EXT)$(OPTIONS) $@ && $(PROG) ./$@ -nohess

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
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

biglog:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

bvprobit:
	@#Do not catch for admb-9.x
	-pushd admb-re/glmmadmb && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

glmmadmb:
	@#Do not catch for admb-9.x
	-pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

caest:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

gamma:
	-pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) liver_$@ && $(PROG) ./liver_$@

kidney:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

lidar:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

logistic:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

nbmm:
	-pushd admb-re/nbmm && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

nested4:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

orange:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

orange2:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

orange_cor:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@ -nohess

pheno:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

polio:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

sdv:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

skewed:
	$(MAKE) diet
	$(MAKE) diet_sk
diet:
	pushd admb-re/skewed && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

diet_sk:
	pushd admb-re/skewed && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

socatt:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

spatial:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

union:
	pushd admb-re/$@ && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@

weights: binomial
binomial:
	pushd admb-re/weights && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@
binomial_w2:
	pushd admb-re/weights && $(ADMB_HOME)/admb$(EXT) -r$(OPTIONS) $@ && $(PROG) ./$@ -nohess

copy:
ifeq ($(SHELL),cmd)
	if not exist ..\build\dist\examples md ..\build\dist\examples
	xcopy ..\examples ..\build\dist\examples /S /Y /D
else
	cp -R ../examples ../build/dist
endif
