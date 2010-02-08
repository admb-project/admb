DEBUG_OPTION=
ifdef DEBUG
DEBUG_OPTION=-g
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
	cd examples/admb/buscycle;admb $(DEBUG_OPTION) $@;./$@
	cd examples/admb/buscycle;admb -s $(DEBUG_OPTION) $@;./$@

ham5:
	cd examples/admb/buscycle;admb $(DEBUG_OPTION) $@;./$@
	cd examples/admb/buscycle;admb -s $(DEBUG_OPTION) $@;./$@

catage:
	cd examples/admb/$@;admb $(DEBUG_OPTION) $@;./$@
	cd examples/admb/$@;admb -s $(DEBUG_OPTION) $@;./$@

chem-eng:
	cd examples/admb/$@;admb $(DEBUG_OPTION) $@;./$@
	cd examples/admb/$@;admb -s $(DEBUG_OPTION) $@;./$@

finance:
	cd examples/admb/$@;admb $(DEBUG_OPTION) $@;./$@
	cd examples/admb/$@;admb -s $(DEBUG_OPTION) $@;./$@

forest:
	-cd examples/admb/$@;admb $(DEBUG_OPTION) $@;./$@
	-cd examples/admb/$@;admb -s $(DEBUG_OPTION) $@;./$@

pella-t:
	cd examples/admb/$@;admb $(DEBUG_OPTION) $@;./$@
	cd examples/admb/$@;admb -s $(DEBUG_OPTION) $@;./$@

robreg: vonb vonbr
vonb:
	cd examples/admb/robreg;admb $(DEBUG_OPTION) $@;./$@
	cd examples/admb/robreg;admb -s $(DEBUG_OPTION) $@;./$@

vonbr:
	cd examples/admb/robreg;admb $(DEBUG_OPTION) $@;./$@
	cd examples/admb/robreg;admb -s $(DEBUG_OPTION) $@;./$@

simple:
	cd examples/admb/$@;admb $(DEBUG_OPTION) $@;./$@
	cd examples/admb/$@;admb -s $(DEBUG_OPTION) $@;./$@

truncreg:
	@#cd examples/admb/$@;admb $@;./runtrunc.bat;./fruntrunc.bat
	@#cd examples/admb/$@;admb -s $@;./runtrunc.bat;./fruntrunc.bat

vol: n2mvol
n2mvol:
	cd examples/admb/vol;admb $(DEBUG_OPTION) $@;./$@
	cd examples/admb/vol;admb -s $(DEBUG_OPTION) $@;./$@

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
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@

biglog:
	@#cd examples/admb-re/$@;admb -r $@;./$@
	@#cd examples/admb-re/$@;admb -r -s $@;./$@

bvprobit:
	@#cd examples/admb-re/glmmadmb;admb -r $@;./$@
	@#cd examples/admb-re/glmmadmb;admb -r -s $@;./$@

caest:
	@#cd examples/admb-re/$@;admb -r $@;./$@
	@#cd examples/admb-re/$@;admb -r -s $@;./$@

gamma:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) liver_$@;./liver_$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) liver_$@;./liver_$@

kidney:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;./$@

lidar:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;./$@

logistic:
	@#cd examples/admb-re/$@;admb -r $@;./$@
	@#cd examples/admb-re/$@;admb -r -s $@;./$@

nbmm:
	@#cd examples/admb-re/glmmadmb;admb -r $@;./$@
	@#cd examples/admb-re/glmmadmb;admb -r -s $@;./$@

nested4:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;./$@

orange:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;./$@

orange2:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;./$@

orange_cor:
	@#cd examples/admb-re/$@;admb -r $@;./$@
	@#cd examples/admb-re/$@;admb -r -s $@;./$@

pheno:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;./$@

polio:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;./$@

sdv:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;./$@

skewed: diet diet_sk
diet:
	cd examples/admb-re/skewed;admb -r $(DEBUG_OPTION) $@;./diet
	cd examples/admb-re/skewed;admb -r -s $(DEBUG_OPTION) $@;./diet

diet_sk:
	cd examples/admb-re/skewed;admb -r $(DEBUG_OPTION) $@;./diet
	cd examples/admb-re/skewed;admb -r -s $(DEBUG_OPTION) $@;./diet

socatt:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;./$@

spatial:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;./$@

union:
	@#cd examples/admb-re/$@;admb -r $@;./$@
	@#cd examples/admb-re/$@;admb -r -s $@;./$@

weights: binomial binomial_w2
binomial:
	cd examples/admb-re/weights;admb -r $(DEBUG_OPTION) $@;./$@
	cd examples/admb-re/weights;admb -r -s $(DEBUG_OPTION) $@;./$@
binomial_w2:
	@#cd examples/admb-re/weights;admb -r $@;./$@
	@#cd examples/admb-re/weights;admb -r -s $@;./$@
