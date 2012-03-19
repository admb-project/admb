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
	$@ -version
	$@
	cd ..\\..

ham5:
	cd admb\\buscycle
	admb $(OPTION) $@
	$@
	cd ..\\..

catage:
	cd admb\\$@
	admb $(OPTION) $@
	$@
	cd ..\\..

chem-eng:
	cd admb\\$@
	admb $(OPTION) $@
	$@
	cd ..\\..

finance:
	cd admb\\$@
	admb $(OPTION) $@
	$@
	cd ..\\..

forest:
	cd admb\\$@
	admb $(OPTION) $@
	@REM $@
	cd ..\\..


pella-t:
	cd admb\\$@
	admb $(OPTION) $@
	@REM $@
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
	cd admb\\$@
	admb $(OPTION) $@
	$@
	cd ..\\..

truncreg:
	cd admb\\$@
	cd ..\\..

vol: n2mvol
n2mvol:
	cd admb\\vol
	admb $(OPTION) $@
	$@ -nohess
	cd ..\\..

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
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

biglog:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

bvprobit:
	cd admb-re\\glmmadmb
	admb -r $(OPTION) $@
	$@
	cd ..\\..

glmmadmb:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

caest:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

gamma:
	cd admb-re\\$@
	admb -r $(OPTION) liver_$@
	liver_$@
	cd ..\\..

kidney:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

lidar:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

logistic:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

nbmm:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	@REM $@
	cd ..\\..

nested4:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

orange:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

orange2:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

orange_cor:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@ -nohess
	cd ..\\..

pheno:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

polio:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

sdv:
	cd admb-re\\$@
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
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

spatial:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

union:
	cd admb-re\\$@
	admb -r $(OPTION) $@
	$@
	cd ..\\..

weights: binomial
binomial:
	cd admb-re\\weights
	admb -r $(OPTION) $@
	$@
	cd ..\\..

binomial_w2:
	cd admb-re\\weights
	admb -r $(OPTION) $@
	$@
	cd ..\\..
