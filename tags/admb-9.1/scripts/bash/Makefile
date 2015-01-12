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
	cd examples/admb/buscycle;admb $@;./$@
	cd examples/admb/buscycle;admb -s $@;./$@

ham5:
	cd examples/admb/buscycle;admb $@;./$@
	cd examples/admb/buscycle;admb -s $@;./$@

catage:
	cd examples/admb/$@;admb $@;./$@
	cd examples/admb/$@;admb -s $@;./$@

chem-eng:
	cd examples/admb/$@;admb $@;./$@
	cd examples/admb/$@;admb -s $@;./$@

finance:
	cd examples/admb/$@;admb $@;./$@
	cd examples/admb/$@;admb -s $@;./$@

forest:
	-cd examples/admb/$@;admb $@;./$@
	-cd examples/admb/$@;admb -s $@;./$@

pella-t:
	cd examples/admb/$@;admb $@;./$@
	cd examples/admb/$@;admb -s $@;./$@

robreg: vonb vonbr
vonb:
	cd examples/admb/robreg;admb $@;./$@
	cd examples/admb/robreg;admb -s $@;./$@

vonbr:
	cd examples/admb/robreg;admb $@;./$@
	cd examples/admb/robreg;admb -s $@;./$@

simple:
	cd examples/admb/$@;admb $@;./$@
	cd examples/admb/$@;admb -s $@;./$@

truncreg:
	@#cd examples/admb/$@;admb $@;./runtrunc.bat;./fruntrunc.bat
	@#cd examples/admb/$@;admb -s $@;./runtrunc.bat;./fruntrunc.bat

vol: n2mvol
n2mvol:
	cd examples/admb/vol;admb $@;./$@
	cd examples/admb/vol;admb -s $@;./$@

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
	cd examples/admb-re/$@;admb -r $@
	cd examples/admb-re/$@;admb -r -s $@

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
	cd examples/admb-re/$@;admb -r liver_$@;./liver_$@
	cd examples/admb-re/$@;admb -r -s liver_$@;./liver_$@

kidney:
	cd examples/admb-re/$@;admb -r $@;./$@
	cd examples/admb-re/$@;admb -r -s $@;./$@

lidar:
	cd examples/admb-re/$@;admb -r $@;./$@
	cd examples/admb-re/$@;admb -r -s $@;./$@

logistic:
	@#cd examples/admb-re/$@;admb -r $@;./$@
	@#cd examples/admb-re/$@;admb -r -s $@;./$@

nbmm:
	@#cd examples/admb-re/glmmadmb;admb -r $@;./$@
	@#cd examples/admb-re/glmmadmb;admb -r -s $@;./$@

nested4:
	cd examples/admb-re/$@;admb -r $@;./$@
	cd examples/admb-re/$@;admb -r -s $@;./$@

orange:
	cd examples/admb-re/$@;admb -r $@;./$@
	cd examples/admb-re/$@;admb -r -s $@;./$@

orange2:
	cd examples/admb-re/$@;admb -r $@;./$@
	cd examples/admb-re/$@;admb -r -s $@;./$@

orange_cor:
	@#cd examples/admb-re/$@;admb -r $@;./$@
	@#cd examples/admb-re/$@;admb -r -s $@;./$@

pheno:
	cd examples/admb-re/$@;admb -r $@;./$@
	cd examples/admb-re/$@;admb -r -s $@;./$@

polio:
	cd examples/admb-re/$@;admb -r $@;./$@
	cd examples/admb-re/$@;admb -r -s $@;./$@

sdv:
	cd examples/admb-re/$@;admb -r $@;./$@
	cd examples/admb-re/$@;admb -r -s $@;./$@

skewed: diet diet_sk
diet:
	cd examples/admb-re/skewed;admb -r $@;./diet
	cd examples/admb-re/skewed;admb -r -s $@;./diet

diet_sk:
	cd examples/admb-re/skewed;admb -r $@;./diet
	cd examples/admb-re/skewed;admb -r -s $@;./diet

socatt:
	cd examples/admb-re/$@;admb -r $@;./$@
	cd examples/admb-re/$@;admb -r -s $@;./$@

spatial:
	cd examples/admb-re/$@;admb -r $@;./$@
	cd examples/admb-re/$@;admb -r -s $@;./$@

union:
	@#cd examples/admb-re/$@;admb -r $@;./$@
	@#cd examples/admb-re/$@;admb -r -s $@;./$@

weights: binomial binomial_w2
binomial:
	cd examples/admb-re/weights;admb -r $@;./$@
	cd examples/admb-re/weights;admb -r -s $@;./$@
binomial_w2:
	@#cd examples/admb-re/weights;admb -r $@;./$@
	@#cd examples/admb-re/weights;admb -r -s $@;./$@
