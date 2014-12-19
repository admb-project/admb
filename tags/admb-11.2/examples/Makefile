SHELL=cmd

ADMB_HOME=..\\..\\..

OPTIONS=$(DEBUG_OPTION) $(FAST_OPTION)

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
	pushd admb\\buscycle & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\buscycle & $@

ham5:
	pushd admb\\buscycle & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\buscycle & $@

catage:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@

chem-eng:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@

finance:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@

forest:
	@REM pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	@REM pushd admb\\$@ & $@

pella-t:
	@REM pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	@REM pushd admb\\$@ & $@

robreg: vonb vonbr
vonb:
	pushd admb\\robreg & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\robreg & $@

vonbr:
	pushd admb\\robreg & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\robreg & $@

simple:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@

truncreg:
	@REM pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	@REM pushd admb\\$@ & $@

vol: n2mvol
n2mvol:
	pushd admb\\vol & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\vol & $@ -nohess

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
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

biglog:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

bvprobit:
	pushd admb-re\\glmmadmb & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\glmmadmb & $@

glmmadmb:
	pushd admb-re\\glmmadmb & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\glmmadmb & $@

caest:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

gamma:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) liver_$@
	pushd admb-re\\$@ & liver_$@

kidney:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

lidar:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

logistic:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

nbmm:
	@REM pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	@REM pushd admb-re\\$@ & $@

nested4:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

orange:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

orange2:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

orange_cor:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ -nohess

pheno:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

polio:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

sdv:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

skewed: diet diet_sk
diet:
	pushd admb-re\\skewed & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\skewed & $@

diet_sk:
	pushd admb-re\\skewed & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\skewed & $@

socatt:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

spatial:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

union:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

weights: binomial
binomial:
	pushd admb-re\\weights & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\weights & $@

binomial_w2:
	pushd admb-re\\weights & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\weights & $@ -nohess
