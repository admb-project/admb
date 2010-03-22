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
	cd examples\\admb\\buscycle && admb.bat $@ && cmd /c $@
	cd examples\\admb\\buscycle && admb.bat -s $@ && cmd /c $@

ham5:
	cd examples\\admb\\buscycle && admb.bat $@ && cmd /c $@
	cd examples\\admb\\buscycle && admb.bat -s $@ && cmd /c $@

chem-eng:
	cd examples\\admb\\$@ && admb.bat $@ && cmd /c $@
	cd examples\\admb\\$@ && admb.bat -s $@ && cmd /c $@

catage:
	cd examples\\admb\\$@ && admb.bat $@ && cmd /c $@
	cd examples\\admb\\$@ && admb.bat -s $@ && cmd /c $@

finance:
	cd examples\\admb\\$@ && admb.bat $@ && cmd /c $@
	cd examples\\admb\\$@ && admb.bat -s $@ && cmd /c $@

forest:
	-cd examples\\admb\\$@ && admb.bat $@ && cmd /c $@
	-cd examples\\admb\\$@ && admb.bat -s $@ && cmd /c $@

pella-t:
	cd examples\\admb\\$@ && admb.bat $@ && cmd /c $@
	cd examples\\admb\\$@ && admb.bat -s $@ && cmd /c $@

robreg: vonb vonbr
vonb:
	cd examples\\admb\\robreg && admb.bat $@ && cmd /c $@
	cd examples\\admb\\robreg && admb.bat -s $@ && cmd /c $@

vonbr:
	cd examples\\admb\\robreg && admb.bat $@ && cmd /c $@
	cd examples\\admb\\robreg && admb.bat -s $@ && cmd /c $@

simple:
	cd examples\\admb\\$@ && admb.bat $@ && cmd /c $@
	cd examples\\admb\\$@ && admb.bat -s $@ && cmd /c $@

truncreg:
	-cd examples\\admb\\$@ && admb.bat $@ && cmd /c runtrunc.bat && cmd /c fruntrunc.bat
	-cd examples\\admb\\$@ && admb.bat -s $@ && cmd /c runtrunc.bat && cmd /c fruntrunc.bat

vol: n2mvol
n2mvol:
	cd examples\\admb\\vol &&  admb.bat $@ && cmd /c $@
	cd examples\\admb\\vol && admb.bat -s $@ && cmd /c $@

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
	cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

biglog:
	-cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	-cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

bvprobit:
	-cd examples\\admb-re\\glmmadmb && admb.bat -r $@ && cmd /c $@
	-cd examples\\admb-re\\glmmadmb && admb.bat -r -s $@ && cmd /c $@

caest:
	-cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	-cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

gamma:
	cd examples\\admb-re\\$@ && admb.bat -r liver_$@ && cmd /c liver_$@
	cd examples\\admb-re\\$@ && admb.bat -r -s liver_$@ && cmd /c liver_$@

kidney:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

lidar:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

logistic:
	-cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	-cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

nbmm:
	-cd examples\\admb-re\\glmmadmb && admb.bat -r $@ && cmd /c $@
	-cd examples\\admb-re\\glmmadmb && admb.bat -r -s $@ && cmd /c $@

nested4:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

orange:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

orange2:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

orange_cor:
	-cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	-cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

pheno:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

polio:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

sdv:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

skewed: diet diet_sk
diet:
	cd examples\\admb-re\\skewed && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\skewed && admb.bat -r -s $@ && cmd /c $@

diet_sk:
	cd examples\\admb-re\\skewed && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\skewed && admb.bat -r -s $@ && cmd /c $@

socatt:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

spatial:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

union:
	-cd examples\\admb-re\\$@ && admb.bat -r $@ && cmd /c $@
	-cd examples\\admb-re\\$@ && admb.bat -r -s $@ && cmd /c $@

weights: binomial binomial_w2
binomial:
	cd examples\\admb-re\\weights && admb.bat -r $@ && cmd /c $@
	cd examples\\admb-re\\weights && admb.bat -r -s $@ && cmd /c $@

binomial_w2:
	-cd examples\\admb-re\\weights && admb.bat -r $@ && cmd /c $@
	-cd examples\\admb-re\\weights && admb.bat -r -s $@ && cmd /c $@
