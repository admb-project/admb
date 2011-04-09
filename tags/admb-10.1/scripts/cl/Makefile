default: simple

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
	cd admb\\buscycle
	admb $(OPTION) $@
	$@
	cd ..\\..

ham5:
	cd admb\\buscycle
	admb $(OPTION) $@
	$@
	cd ..\\..

catage:
	cd admb\\catage
	admb $(OPTION) $@
	$@
	cd ..\\..

chem-eng:
	cd admb\\chem-eng
	admb $(OPTION) $@
	$@
	cd ..\\..

finance:
	cd admb\\finance
	admb $(OPTION) $@
	$@
	cd ..\\..

forest:
	cd admb\\forest
	admb $(OPTION) $@
	REM $@
	cd ..\\..


pella-t:
	cd admb\\pella-t
	admb $(OPTION) $@
	REM $@
	cd ..\\..

robreg: vonb vonbr
vonb:
	cd admb\\robreg
	admb $(OPTION) $@
	$@
	cd ..\\..

vonbr:
	cd admb\\robreg
	admb $(OPTION) $@
	$@
	cd ..\\..

simple:
	cd admb\\simple
	admb $(OPTION) $@
	$@
	cd ..\\..

truncreg:
	cd admb\\truncreg
	cd ..\\..

vol: n2mvol
n2mvol:
	cd admb\\vol
	admb $(OPTION) $@
	$@
	cd ..\\..

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
	cd admb-re\\bcb
	admb -r $(OPTION) $@
	$@
	cd ..\\..

biglog:
	cd admb-re\\biglog
	admb -r $(OPTION) $@
	@REM $@
	cd ..\\..

bvprobit:
	cd admb-re\\glmmadmb
	admb -r $(OPTION) $@
	@REM $@
	cd ..\\..

caest:
	cd admb-re\\caest
	admb -r $(OPTION) $@
	$@
	cd ..\\..

gamma:
	cd admb-re\\gamma
	admb -r $(OPTION) liver_$@
	liver_$@
	cd ..\\..

kidney:
	cd admb-re\\kidney
	admb -r $(OPTION) $@
	$@
	cd ..\\..

lidar:
	cd admb-re\\lidar
	admb -r $(OPTION) $@
	$@
	cd ..\\..

logistic:
	cd admb-re\\logistic
	admb -r $(OPTION) $@
	$@
	cd ..\\..

nbmm:
	cd admb-re\\glmmadmb
	admb -r $(OPTION) $@
	@REM $@
	cd ..\\..

nested4:
	cd admb-re\\nested4
	admb -r $(OPTION) $@
	$@
	cd ..\\..

orange:
	cd admb-re\\orange
	admb -r $(OPTION) $@
	$@
	cd ..\\..

orange2:
	cd admb-re\\orange2
	admb -r $(OPTION) $@
	$@
	cd ..\\..

orange_cor:
	cd admb-re\\orange_cor
	admb -r $(OPTION) $@
	@REM $@
	cd ..\\..

pheno:
	cd admb-re\\pheno
	admb -r $(OPTION) $@
	$@
	cd ..\\..

polio:
	cd admb-re\\polio
	admb -r $(OPTION) $@
	$@
	cd ..\\..

sdv:
	cd admb-re\\sdv
	admb -r $(OPTION) $@
	$@
	cd ..\\..

skewed: diet diet_sk
diet:
	cd admb-re\\skewed
	admb -r $(OPTION) $@
	$@
	cd ..\\..

diet_sk:
	cd admb-re\\skewed
	admb -r $(OPTION) $@
	$@
	cd ..\\..

socatt:
	cd admb-re\\socatt
	admb -r $(OPTION) $@
	$@
	cd ..\\..

spatial:
	cd admb-re\\spatial
	admb -r $(OPTION) $@
	$@
	cd ..\\..

union:
	cd admb-re\\union
	admb -r $(OPTION) $@
	$@
	cd ..\\..

weights: binomial binomial_w2
binomial:
	cd admb-re\\weights
	admb -r $(OPTION) $@
	$@
	cd ..\\..

binomial_w2:
	cd admb-re\\weights
	admb -r $(OPTION) $@
	@REM $@
	cd ..\\..
