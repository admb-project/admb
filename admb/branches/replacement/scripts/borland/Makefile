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
	cd admb\\buscycle
	admb ham4
	ham4
	admb -s ham4
	ham4
	cd ..\\..

ham5:
	cd admb\\buscycle
	admb ham5
	ham5
	admb -s ham5
	ham5
	cd ..\\..

catage:
	cd admb\\catage
	admb catage
	catage
	admb -s catage
	catage
	cd ..\\..

chem-eng:
	cd admb\\chem-eng
	admb chem-eng
	chem-eng
	admb -s chem-eng
	chem-eng
	cd ..\\..

finance:
	cd admb\\finance
	admb finance
	finance
	admb -s finance
	finance
	cd ..\\..

forest:
	cd admb\\forest
	cd ..\\..


pella-t:
	cd admb\\pella-t
	admb pella-t
	pella-t
	admb -s pella-t
	pella-t
	cd ..\\..

robreg: vonb vonbr
vonb:
	cd admb\\robreg
	admb vonb
	vonb
	admb -s vonb
	vonb
	cd ..\\..

vonbr:
	cd admb\\robreg
	admb vonbr
	vonbr
	admb -s vonbr
	vonbr
	cd ..\\..

simple:
	cd admb\\simple
	admb simple
	simple
	admb -s simple
	simple
	cd ..\\..

truncreg:
	cd admb\\truncreg
	cd ..\\..

vol: n2mvol
n2mvol:
	cd admb\\vol
	admb n2mvol
	n2mvol
	admb -s n2mvol
	n2mvol
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
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

biglog:
	cd admb-re\\biglog
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

bvprobit:
	cd admb-re\\glmmadmb
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

caest:
	cd admb-re\\caest
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

gamma:
	cd admb-re\\gamma
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

kidney:
	cd admb-re\\kidney
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

lidar:
	cd admb-re\\lidar
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

logistic:
	cd admb-re\\logistic
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

nbmm:
	cd admb-re\\glmmadmb
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

nested4:
	cd admb-re\\nested4
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

orange:
	cd admb-re\\orange
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

orange2:
	cd admb-re\\orange2
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

orange_cor:
	cd admb-re\\orange_cor
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

pheno:
	cd admb-re\\pheno
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

polio:
	cd admb-re\\polio
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

sdv:
	cd admb-re\\sdv
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

skewed: diet diet_sk
diet:
	cd admb-re\\skewed
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

diet_sk:
	cd admb-re\\skewed
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

socatt:
	cd admb-re\\socatt
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

spatial:
	cd admb-re\\spatial
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

union:
	cd admb-re\\union
	admb -r $@
	@REM $@
	admb -r -s $@
	@REM $@
	cd ..\\..

weights: binomial
binomial:
	cd admb-re\\weights
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..

binomial_w2:
	cd admb-re\\weights
	admb -r $@
	-$@
	admb -r -s $@
	-$@
	cd ..\\..
