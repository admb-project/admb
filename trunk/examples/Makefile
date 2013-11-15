all: admb admb-re

admb:\
buscycle \
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
	pushd admb\\buscycle & admb $(OPTIONS) $@ & $@ & popd

ham5:
	pushd admb\\buscycle & admb $(OPTIONS) $@ & $@ & popd

catage:
	pushd admb\\$@ & admb $(OPTIONS) $@ & $@ & popd

chem-eng:
	pushd admb\\$@ & admb $(OPTIONS) $@ & $@ & popd

finance:
	pushd admb\\$@ & admb $(OPTIONS) $@ & $@ & popd

forest:
	@REM pushd admb\\$@ & admb $(OPTIONS) $@ & $@ & popd

pella-t:
	@REM pushd admb\\$@ & admb $(OPTIONS) $@ & $@ & popd

robreg: vonb vonbr
vonb:
	pushd admb\\robreg & admb $(OPTIONS) $@ & $@ & popd

vonbr:
	pushd admb\\robreg & admb $(OPTIONS) $@ & $@ & popd

simple:
	pushd admb\\$@ & admb $(OPTIONS) $@ & $@ & popd

truncreg:
	@REM pushd admb\\$@ & admb $(OPTIONS) $@ & $@ & popd

vol: n2mvol
n2mvol:
	pushd admb\\vol & admb $(OPTIONS) $@ & $@ -nohess & popd

admb-re:\
bcb \
biglog \
bvprobit \
glmmadmb \
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
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

biglog:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

bvprobit:
	pushd admb-re\\glmmadmb & admb -r $(OPTIONS) $@ & $@ & popd

glmmadmb:
	pushd admb-re\\glmmadmb & admb -r $(OPTIONS) $@ & $@ & popd

caest:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

gamma:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

kidney:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

lidar:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

logistic:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

nbmm:
	@REM pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

nested4:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

orange:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

orange2:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

orange_cor:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ -nohess & popd

pheno:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

polio:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

sdv:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

skewed: diet diet_sk
diet:
	pushd admb-re\\skewed & admb -r $(OPTIONS) $@ & $@ & popd

diet_sk:
	pushd admb-re\\skewed & admb -r $(OPTIONS) $@ & $@ & popd

socatt:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

spatial:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

union:
	pushd admb-re\\$@ & admb -r $(OPTIONS) $@ & $@ & popd

weights: binomial
binomial:
	pushd admb-re\\weights & admb -r $(OPTIONS) $@ & $@ & popd

binomial_w2:
	pushd admb-re\\weights & admb -r $(OPTIONS) $@ & $@ & popd
