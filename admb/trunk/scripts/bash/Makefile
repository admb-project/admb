DEBUG_OPTION=-g

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
	cd examples/admb/buscycle;admb $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb/buscycle;admb -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

ham5:
	cd examples/admb/buscycle;admb $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb/buscycle;admb -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

catage:
	cd examples/admb/$@;admb $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb/$@;admb -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

chem-eng:
	cd examples/admb/$@;admb $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb/$@;admb -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

finance:
	cd examples/admb/$@;admb $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb/$@;admb -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

forest:
	-cd examples/admb/$@;admb $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	-cd examples/admb/$@;admb -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

pella-t:
	cd examples/admb/$@;admb $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb/$@;admb -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

robreg: vonb vonbr
vonb:
	cd examples/admb/robreg;admb $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb/robreg;admb -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

vonbr:
	cd examples/admb/robreg;admb $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb/robreg;admb -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

simple:
	cd examples/admb/$@;admb $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb/$@;admb -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

truncreg:
	@cd examples/admb/$@;admb $@;./$@ -ams 2000000;./$@ -ams 2000000 -gbs 6000000 -cbs 4000000
	@cd examples/admb/$@;admb -s $@;./$@ -ams 2000000;./$@ -ams 2000000 -gbs 6000000 -cbs 4000000

vol: n2mvol
n2mvol:
	cd examples/admb/vol;admb $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb/vol;admb -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

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
	@cd examples/admb-re/$@;admb -r $@;valgrind --leak-check=yes ./$@
	@cd examples/admb-re/$@;admb -r -s $@;valgrind --leak-check=yes ./$@

bvprobit:
	@#Missing bvprobit.dat
	@-cd examples/admb-re/glmmadmb;admb -r $@;valgrind --leak-check=yes ./$@
	@-cd examples/admb-re/glmmadmb;admb -r -s $@;valgrind --leak-check=yes ./$@

caest:
	@-cd examples/admb-re/$@;admb -r $@;valgrind --leak-check=yes ./$@
	@-cd examples/admb-re/$@;admb -r -s $@;valgrind --leak-check=yes ./$@

gamma:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) liver_$@;valgrind --leak-check=yes ./liver_$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) liver_$@;valgrind --leak-check=yes ./liver_$@

kidney:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

lidar:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

logistic:
	@#runtime error
	@-cd examples/admb-re/$@;admb -r $@;valgrind --leak-check=yes ./$@
	@-cd examples/admb-re/$@;admb -r -s $@;valgrind --leak-check=yes ./$@

nbmm:
	@#Missing .dat file
	@-cd examples/admb-re/glmmadmb;admb -r $@;valgrind --leak-check=yes ./$@
	@-cd examples/admb-re/glmmadmb;admb -r -s $@;valgrind --leak-check=yes ./$@

nested4:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

orange:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

orange2:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

orange_cor:
	@-cd examples/admb-re/$@;admb -r $@;valgrind --leak-check=yes ./$@
	@-cd examples/admb-re/$@;admb -r -s $@;valgrind --leak-check=yes ./$@

pheno:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

polio:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

sdv:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

skewed: diet diet_sk
diet:
	cd examples/admb-re/skewed;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./diet
	cd examples/admb-re/skewed;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./diet

diet_sk:
	cd examples/admb-re/skewed;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./diet
	cd examples/admb-re/skewed;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./diet

socatt:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

spatial:
	cd examples/admb-re/$@;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb-re/$@;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@

union:
	@#Runtine errors
	@-cd examples/admb-re/$@;admb -r $@;valgrind --leak-check=yes ./$@
	@-cd examples/admb-re/$@;admb -r -s $@;valgrind --leak-check=yes ./$@

weights: binomial binomial_w2
binomial:
	cd examples/admb-re/weights;admb -r $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
	cd examples/admb-re/weights;admb -r -s $(DEBUG_OPTION) $@;valgrind --leak-check=yes ./$@
binomial_w2:
	@-cd examples/admb-re/weights;admb -r $@;valgrind --leak-check=yes ./$@
	@-cd examples/admb-re/weights;admb -r -s $@;valgrind --leak-check=yes ./$@
