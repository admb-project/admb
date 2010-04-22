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

ADMB_HOME:=$(shell pwd)
export ADMB_HOME
PATH:=$(ADMB_HOME)\bin:$(PATH)

buscycle: ham4 ham5
ham4:
	cmd /C "cd examples\\admb\\buscycle && admb.bat $@ && $@"
	cmd /C "cd examples\\admb\\buscycle && admb.bat -s $@ && $@"

ham5:
	cmd /C "cd examples\\admb\\buscycle && admb.bat $@ && $@"
	cmd /C "cd examples\\admb\\buscycle && admb.bat -s $@ && $@"

chem-eng:
	cmd /C "cd examples\\admb\\$@ && admb.bat $@ && $@"
	cmd /C "cd examples\\admb\\$@ && admb.bat -s $@ && $@"

catage:
	cmd /C "cd examples\\admb\\$@ && admb.bat $@ && $@"
	cmd /C "cd examples\\admb\\$@ && admb.bat -s $@ && $@"

finance:
	cmd /C "cd examples\\admb\\$@ && admb.bat $@ && $@"
	cmd /C "cd examples\\admb\\$@ && admb.bat -s $@ && $@"

forest:
	-cmd /C "cd examples\\admb\\$@ && admb.bat $@ && $@"
	-cmd /C "cd examples\\admb\\$@ && admb.bat -s $@ && $@"

pella-t:
	cmd /C "cd examples\\admb\\$@ && admb.bat $@ && $@"
	cmd /C "cd examples\\admb\\$@ && admb.bat -s $@ && $@"

robreg: vonb vonbr
vonb:
	cmd /C "cd examples\\admb\\robreg && admb.bat $@ && $@"
	cmd /C "cd examples\\admb\\robreg && admb.bat -s $@ && $@"

vonbr:
	cmd /C "cd examples\\admb\\robreg && admb.bat $@ && $@"
	cmd /C "cd examples\\admb\\robreg && admb.bat -s $@ && $@"

simple:
	cmd /C "cd examples\\admb\\$@ && admb.bat $@ && $@"
	cmd /C "cd examples\\admb\\$@ && admb.bat -s $@ && $@"

truncreg:
	-cmd /C "cd examples\\admb\\$@ && admb.bat $@ && runtrunc.bat && fruntrunc.bat"
	-cmd /C "cd examples\\admb\\$@ && admb.bat -s $@ && runtrunc.bat && fruntrunc.bat"

vol: n2mvol
n2mvol:
	cmd /C "cd examples\\admb\\vol &&  admb.bat $@ && $@"
	cmd /C "cd examples\\admb\\vol && admb.bat -s $@ && $@"

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
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

biglog:
	-cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	-cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

bvprobit:
	-cmd /C "cd examples\\admb-re\\glmmadmb && admb.bat -r $@ && $@"
	-cmd /C "cd examples\\admb-re\\glmmadmb && admb.bat -r -s $@ && $@"

caest:
	-cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	-cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

gamma:
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r liver_$@ && liver_$@"
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s liver_$@ && liver_$@"

kidney:
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

lidar:
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

logistic:
	-cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	-cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

nbmm:
	-cmd /C "cd examples\\admb-re\\glmmadmb && admb.bat -r $@ && $@"
	-cmd /C "cd examples\\admb-re\\glmmadmb && admb.bat -r -s $@ && $@"

nested4:
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

orange:
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

orange2:
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

orange_cor:
	-cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	-cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

pheno:
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

polio:
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

sdv:
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

skewed: diet diet_sk
diet:
	cmd /C "cd examples\\admb-re\\skewed && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\skewed && admb.bat -r -s $@ && $@"

diet_sk:
	cmd /C "cd examples\\admb-re\\skewed && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\skewed && admb.bat -r -s $@ && $@"

socatt:
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

spatial:
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

union:
	-cmd /C "cd examples\\admb-re\\$@ && admb.bat -r $@ && $@"
	-cmd /C "cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@"

weights: binomial binomial_w2
binomial:
	cmd /C "cd examples\\admb-re\\weights && admb.bat -r $@ && $@"
	cmd /C "cd examples\\admb-re\\weights && admb.bat -r -s $@ && $@"

binomial_w2:
	-cmd /C "cd examples\\admb-re\\weights && admb.bat -r $@ && $@"
	-cmd /C "cd examples\\admb-re\\weights && admb.bat -r -s $@ && $@"
