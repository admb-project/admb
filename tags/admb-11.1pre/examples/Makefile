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
	pushd admb\\buscycle & admb $(OPTION) $@ & $@ & popd

ham5:
	pushd admb\\buscycle & admb $(OPTION) $@ & $@ & popd

catage:
	pushd admb\\$@ & admb $(OPTION) $@ & $@ & popd

chem-eng:
	pushd admb\\$@ & admb $(OPTION) $@ & $@ & popd

finance:
	pushd admb\\$@ & admb $(OPTION) $@ & $@ & popd

forest:
	@REM pushd admb\\$@ & admb $(OPTION) $@ & $@ & popd

pella-t:
	@REM pushd admb\\$@ & admb $(OPTION) $@ & $@ & popd

robreg: vonb vonbr
vonb:
	pushd admb\\robreg & admb $(OPTION) $@ & $@ & popd

vonbr:
	pushd admb\\robreg & admb $(OPTION) $@ & $@ & popd

simple:
	pushd admb\\$@ & admb $(OPTION) $@ & $@ & popd

truncreg:
	@REM pushd admb\\$@ & admb $(OPTION) $@ & $@ & popd

vol: n2mvol
n2mvol:
	pushd admb\\vol & admb $(OPTION) $@ & $@ -nohess & popd

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
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

biglog:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

bvprobit:
	pushd admb-re\\glmmadmb & admb -r $(OPTION) $@ & $@ & popd

glmmadmb:
	pushd admb-re\\glmmadmb & admb -r $(OPTION) $@ & $@ & popd

caest:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

gamma:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

kidney:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

lidar:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

logistic:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

nbmm:
	@REM pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

nested4:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

orange:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

orange2:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

orange_cor:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ -nohess & popd

pheno:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

polio:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

sdv:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

skewed: diet diet_sk
diet:
	pushd admb-re\\skewed & admb -r $(OPTION) $@ & $@ & popd

diet_sk:
	pushd admb-re\\skewed & admb -r $(OPTION) $@ & $@ & popd

socatt:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

spatial:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

union:
	pushd admb-re\\$@ & admb -r $(OPTION) $@ & $@ & popd

weights: binomial
binomial:
	pushd admb-re\\weights & admb -r $(OPTION) $@ & $@ & popd

binomial_w2:
	pushd admb-re\\weights & admb -r $(OPTION) $@ & $@ & popd
