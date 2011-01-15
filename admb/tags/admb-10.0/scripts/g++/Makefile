DEBUG_OPTION=
ifdef DEBUG
DEBUG_OPTION=-g
endif

ifdef SAFE_OPTION
SAFE_OPTION=-s
endif

PROG=time

default: simple

all: admb admb-re

admb: \
buscycle\
catage \
chem-eng \
forest \
finance \
pella-t \
robreg \
truncreg \
simple \
vol

buscycle: ham4 ham5
ham4:
	cd admb/buscycle;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;$(PROG) ./$@

ham5:
	cd admb/buscycle;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;$(PROG) ./$@

catage:
	cd admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;$(PROG) ./$@

chem-eng:
	-cd admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;$(PROG) ./$@

finance:
	cd admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;$(PROG) ./$@

forest:
	-cd admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;$(PROG) ./$@

pella-t:
	cd admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;$(PROG) ./$@

robreg: vonb vonbr
vonb:
	cd admb/robreg;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;$(PROG) ./$@

vonbr:
	cd admb/robreg;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;$(PROG) ./$@

simple:
	cd admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;$(PROG) ./$@

truncreg:
	@cd admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;$(PROG) ./$@ -ams 2000000;$(PROG) ./$@ -ams 2000000 -gbs 6000000 -cbs 4000000

vol: n2mvol
n2mvol:
	-cd admb/vol;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;$(PROG) ./$@

admb-re:\
bcb \
biglog \
bvprobit \
caest \
gamma \
kidney \
lidar \
logistic \
nbmm \
nested4 \
orange \
orange2 \
orange_cor \
pheno \
polio \
sdv \
skewed \
socatt \
spatial \
union \
weights

bcb:
	-cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

biglog:
	cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

bvprobit:
	@#Missing bvprobit.dat
	-cd admb-re/glmmadmb;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

caest:
	-cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

gamma:
	cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) liver_$@;$(PROG) ./liver_$@

kidney:
	cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

lidar:
	cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

logistic:
	@#runtime error
	-cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

nbmm:
	@#Missing .dat file
	-cd admb-re/nbmm;rm -f @.par @.std;admb -r $(SAFE_OPTION) $@;$(PROG) ./$@

nested4:
	cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

orange:
	cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

orange2:
	cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

orange_cor:
	-cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

pheno:
	cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

polio:
	cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

sdv:
	cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

skewed: diet diet_sk
diet:
	cd admb-re/skewed;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

diet_sk:
	cd admb-re/skewed;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

socatt:
	cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

spatial:
	cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

union:
	@#Runtime errors
	-cd admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@

weights: binomial binomial_w2
binomial:
	cd admb-re/weights;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@
binomial_w2:
	-cd admb-re/weights;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;$(PROG) ./$@
