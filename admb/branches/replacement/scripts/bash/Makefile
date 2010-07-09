DEBUG_OPTION=
ifdef DEBUG
DEBUG_OPTION=-g
endif

ifdef SAFE_OPTION
SAFE_OPTION=-s
endif

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
	cd examples/admb/buscycle;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;./$@

ham5:
	cd examples/admb/buscycle;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;./$@

catage:
	cd examples/admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;./$@

chem-eng:
	-cd examples/admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;./$@

finance:
	cd examples/admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;./$@

forest:
	-cd examples/admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;./$@

pella-t:
	cd examples/admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;./$@

robreg: vonb vonbr
vonb:
	cd examples/admb/robreg;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;./$@

vonbr:
	cd examples/admb/robreg;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;./$@

simple:
	cd examples/admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;./$@

truncreg:
	@cd examples/admb/$@;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;./$@ -ams 2000000;./$@ -ams 2000000 -gbs 6000000 -cbs 4000000

vol: n2mvol
n2mvol:
	-cd examples/admb/vol;rm -f @.par @.std;admb $(SAFE_OPTION) $(DEBUG_OPTION) $@;./$@

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
	cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@

biglog:
	cd examples/admb-re/$@;rm -f @.par @.std;touch xxalloc4.tmp xxalloc5.tmp;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

bvprobit:
	@#Missing bvprobit.dat
	-cd examples/admb-re/glmmadmb;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

caest:
	-cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

gamma:
	cd examples/admb-re/$@;rm -f @.par @.std;touch xxalloc4.tmp xxalloc5.tmp;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) liver_$@;./liver_$@

kidney:
	cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

lidar:
	cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

logistic:
	@#runtime error
	-cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

nbmm:
	@#Missing .dat file
	-cd examples/admb-re/glmmadmb;rm -f @.par @.std;admb -r $(SAFE_OPTION) $@;./$@

nested4:
	cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

orange:
	cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

orange2:
	cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

orange_cor:
	-cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

pheno:
	cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

polio:
	cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

sdv:
	cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

skewed: diet diet_sk
diet:
	cd examples/admb-re/skewed;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./diet

diet_sk:
	cd examples/admb-re/skewed;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./diet

socatt:
	cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

spatial:
	cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

union:
	@#Runtime errors
	-cd examples/admb-re/$@;rm -f @.par @.std;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

weights: binomial binomial_w2
binomial:
	cd examples/admb-re/weights;rm -f @.par @.std;touch xxalloc4.tmp xxalloc5.tmp;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@

binomial_w2:
	-cd examples/admb-re/weights;rm -f @.par @.std;touch xxalloc4.tmp xxalloc5.tmp;admb -r $(DEBUG_OPTION) $(SAFE_OPTION) $@;./$@
