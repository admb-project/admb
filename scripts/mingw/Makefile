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
	cd examples/admb/buscycle; admb.bat $@
	examples/admb/buscycle/$@
	cd examples/admb/buscycle; admb.bat -s $@
	examples/admb/buscycle/$@

ham5:
	cd examples/admb/buscycle; admb.bat $@
	examples/admb/buscycle/$@
	cd examples/admb/buscycle; admb.bat -s $@
	examples/admb/buscycle/$@

chem-eng:
	cd examples/admb/$@; admb.bat $@
	examples/admb/$@/$@
	cd examples/admb/$@; admb.bat -s $@
	examples/admb/$@/$@

catage:
	cd examples/admb/$@; admb.bat $@
	examples/admb/$@/$@
	cd examples/admb/$@; admb.bat -s $@
	examples/admb/$@/$@

finance:
	cd examples/admb/$@; admb.bat $@
	examples/admb/$@/$@
	cd examples/admb/$@; admb.bat -s $@
	examples/admb/$@/$@

forest:
	@#REM cd examples/admb/$@ && admb.bat $@ && $@
	@#REM cd examples/admb/$@ && admb.bat -s $@ && $@

pella-t:
	cd examples/admb/$@; admb.bat $@
	examples/admb/$@/$@
	cd examples/admb/$@; admb.bat -s $@
	examples/admb/$@/$@

robreg: vonb vonbr
vonb:
	cd examples/admb/robreg; admb.bat $@
	examples/admb/robreg/$@
	cd examples/admb/robreg; admb.bat -s $@
	examples/admb/robreg/$@

vonbr:
	cd examples/admb/robreg; admb.bat $@
	examples/admb/robreg/$@
	cd examples/admb/robreg; admb.bat -s $@
	examples/admb/robreg/$@

simple:
	cd examples/admb/$@; admb.bat $@
	examples/admb/$@/$@
	cd examples/admb/$@; admb.bat -s $@
	examples/admb/$@/$@

truncreg:
	@#REM cd examples/admb/$@ && admb.bat $@ && runtrunc.bat && fruntrunc.bat
	@#REM cd examples/admb/$@ && admb.bat -s $@ && runtrunc.bat && fruntrunc.bat

vol: n2mvol
n2mvol:
	cd examples/admb/vol; admb.bat $@
	examples/admb/vol/$@
	cd examples/admb/vol; admb.bat -s $@
	examples/admb/vol/$@

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
	cd examples/admb-re/$@; admb.bat -r $@
	examples/admb-re/$@/$@
	cd examples/admb-re/$@; admb.bat -r -s $@
	examples/admb-re/$@/$@

biglog:
	@#REM cd examples/admb-re/$@ && admb.bat -r $@ && $@
	@#REM cd examples/admb-re/$@ && admb.bat -r -s $@ && $@

bvprobit:
	@#REM cd examples/admb-re/glmmadmb && admb.bat -r $@ && $@
	@#REM cd examples/admb-re/glmmadmb && admb.bat -r -s $@ && $@

caest:
	@#REM cd examples/admb-re/$@ && admb.bat -r $@ && $@
	@#REM cd examples/admb-re/$@ && admb.bat -r -s $@ && $@

gamma:
	cd examples/admb-re/$@; admb.bat -r liver_$@
	examples/admb-re/$@/liver_$@
	cd examples/admb-re/$@; admb.bat -r -s liver_$@
	examples/admb-re/$@/liver_$@

kidney:
	cd examples/admb-re/$@; admb.bat -r $@
	examples/admb-re/$@/$@
	cd examples/admb-re/$@; admb.bat -r -s $@
	examples/admb-re/$@/$@

lidar:
	cd examples/admb-re/$@; admb.bat -r $@
	examples/admb-re/$@/$@
	cd examples/admb-re/$@; admb.bat -r -s $@
	examples/admb-re/$@/$@

logistic:
	@#REM cd examples/admb-re/$@ && admb.bat -r $@ && $@
	@#REM cd examples/admb-re/$@ && admb.bat -r -s $@ && $@

nbmm:
	@#REM cd examples/admb-re/glmmadmb && admb.bat -r $@ && $@
	@#REM cd examples/admb-re/glmmadmb && admb.bat -r -s $@ && $@

nested4:
	cd examples/admb-re/$@; admb.bat -r $@
	examples/admb-re/$@/$@
	cd examples/admb-re/$@; admb.bat -r -s $@
	examples/admb-re/$@/$@

orange:
	cd examples/admb-re/$@; admb.bat -r $@
	examples/admb-re/$@/$@
	cd examples/admb-re/$@; admb.bat -r -s $@
	examples/admb-re/$@/$@

orange2:
	cd examples/admb-re/$@; admb.bat -r $@
	examples/admb-re/$@/$@
	cd examples/admb-re/$@; admb.bat -r -s $@
	examples/admb-re/$@/$@

orange_cor:
	@#REM cd examples/admb-re/$@ && admb.bat -r $@ && $@
	@#REM cd examples/admb-re/$@ && admb.bat -r -s $@ && $@

pheno:
	cd examples/admb-re/$@; admb.bat -r $@
	examples/admb-re/$@/$@
	cd examples/admb-re/$@; admb.bat -r -s $@
	examples/admb-re/$@/$@

polio:
	cd examples/admb-re/$@; admb.bat -r $@
	cd examples/admb-re/$@; $@
	cd examples/admb-re/$@; admb.bat -r -s $@
	cd examples/admb-re/$@ && $@

sdv:
	cd examples/admb-re/$@; admb.bat -r $@
	examples/admb-re/$@/$@
	cd examples/admb-re/$@; admb.bat -r -s $@
	examples/admb-re/$@/$@

skewed: diet diet_sk
diet:
	cd examples/admb-re/skewed; admb.bat -r $@
	examples/admb-re/skewed/$@
	cd examples/admb-re/skewed; admb.bat -r -s $@
	examples/admb-re/skewed/$@

diet_sk:
	cd examples/admb-re/skewed; admb.bat -r $@
	examples/admb-re/skewed/$@
	cd examples/admb-re/skewed; admb.bat -r -s $@
	examples/admb-re/skewed/$@

socatt:
	cd examples/admb-re/$@; admb.bat -r $@
	examples/admb-re/$@/$@
	cd examples/admb-re/$@; admb.bat -r -s $@
	examples/admb-re/$@/$@

spatial:
	cd examples/admb-re/$@; admb.bat -r $@
	examples/admb-re/$@/$@
	cd examples/admb-re/$@; admb.bat -r -s $@
	examples/admb-re/$@/$@

union:
	@#REM cd examples/admb-re/$@ && admb.bat -r $@ && $@
	@#REM cd examples/admb-re/$@ && admb.bat -r -s $@ && $@

weights: binomial binomial_w2
binomial:
	cd examples/admb-re/weights; admb.bat -r $@
	examples/admb-re/weights/$@
	cd examples/admb-re/weights; admb.bat -r -s $@
	examples/admb-re/weights/$@

binomial_w2:
	@#REM cd examples/admb-re/weights && admb.bat -r $@ && $@
	@#REM cd examples/admb-re/weights && admb.bat -r -s $@ && $@
