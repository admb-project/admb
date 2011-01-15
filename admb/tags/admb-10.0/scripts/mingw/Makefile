.PHONY: check

default: check simple

all: check admb admb-re

check:
	@if "%ADMB_HOME%"=="" echo "Error: ADMB_HOME is not defined" && exit 1 
	@if not exist %ADMB_HOME2%\admb.bat echo "Error: admb.bat does not exist" && exit 1 

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
	cd examples\\admb\\buscycle && admb.bat $@ && $@
	cd examples\\admb\\buscycle && admb.bat -s $@ && $@

ham5:
	cd examples\\admb\\buscycle && admb.bat $@ && $@
	cd examples\\admb\\buscycle && admb.bat -s $@ && $@

chem-eng:
	cd examples\\admb\\$@ && admb.bat $@ && $@
	cd examples\\admb\\$@ && admb.bat -s $@ && $@

catage:
	cd examples\\admb\\$@ && admb.bat $@ && $@
	cd examples\\admb\\$@ && admb.bat -s $@ && $@

finance:
	cd examples\\admb\\$@ && admb.bat $@ && $@
	cd examples\\admb\\$@ && admb.bat -s $@ && $@

forest:
	@REM cd examples/admb/$@ && admb.bat $@ && $@
	@REM cd examples/admb/$@ && admb.bat -s $@ && $@

pella-t:
	cd examples\\admb\\$@ && admb.bat $@ && $@
	cd examples\\admb\\$@ && admb.bat -s $@ && $@

robreg: vonb vonbr
vonb:
	cd examples\\admb\\robreg && admb.bat $@ && $@
	cd examples\\admb\\robreg && admb.bat -s $@ && $@

vonbr:
	cd examples\\admb\\robreg && admb.bat $@ && $@
	cd examples\\admb\\robreg && admb.bat -s $@ && $@

simple:
	cd examples\\admb\\$@ && admb.bat $@ && $@
	cd examples\\admb\\$@ && admb.bat -s $@ && $@

truncreg:
	@REM cd examples/admb/$@ && admb.bat $@ && runtrunc.bat && fruntrunc.bat
	@REM cd examples/admb/$@ && admb.bat -s $@ && runtrunc.bat && fruntrunc.bat

vol: n2mvol
n2mvol:
	cd examples\\admb\\vol && admb.bat $@ && $@
	cd examples\\admb\\vol && admb.bat -s $@ && $@

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
	cd examples\\admb-re\\$@ && admb.bat -r $@ && $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@

biglog:
	@REM cd examples/admb-re/$@ && admb.bat -r $@ && $@
	@REM cd examples/admb-re/$@ && admb.bat -r -s $@ && $@

bvprobit:
	@REM cd examples/admb-re/glmmadmb && admb.bat -r $@ && $@
	@REM cd examples/admb-re/glmmadmb && admb.bat -r -s $@ && $@

caest:
	@REM cd examples/admb-re/$@ && admb.bat -r $@ && $@
	@REM cd examples/admb-re/$@ && admb.bat -r -s $@ && $@

gamma:
	cd examples\\admb-re\\$@ && admb.bat -r liver_$@ && liver_$@
	cd examples\\admb-re\\$@ && admb.bat -r -s liver_$@ && liver_$@

kidney:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@

lidar:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@

logistic:
	@REM cd examples/admb-re/$@ && admb.bat -r $@ && $@
	@REM cd examples/admb-re/$@ && admb.bat -r -s $@ && $@

nbmm:
	@REM cd examples/admb-re/glmmadmb && admb.bat -r $@ && $@
	@REM cd examples/admb-re/glmmadmb && admb.bat -r -s $@ && $@

nested4:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@

orange:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@

orange2:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@

orange_cor:
	@REM cd examples/admb-re/$@ && admb.bat -r $@ && $@
	@REM cd examples/admb-re/$@ && admb.bat -r -s $@ && $@

pheno:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@

polio:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@

sdv:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@

skewed: diet diet_sk
diet:
	cd examples\\admb-re\\skewed && admb.bat -r $@ && $@
	cd examples\\admb-re\\skewed && admb.bat -r -s $@ && $@

diet_sk:
	cd examples\\admb-re\\skewed && admb.bat -r $@ && $@
	cd examples\\admb-re\\skewed && admb.bat -r -s $@ && $@

socatt:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@

spatial:
	cd examples\\admb-re\\$@ && admb.bat -r $@ && $@
	cd examples\\admb-re\\$@ && admb.bat -r -s $@ && $@

union:
	@REM cd examples/admb-re/$@ && admb.bat -r $@ && $@
	@REM cd examples/admb-re/$@ && admb.bat -r -s $@ && $@

weights: binomial binomial_w2
binomial:
	cd examples\\admb-re\\weights && admb.bat -r $@ && $@
	cd examples\\admb-re\\weights && admb.bat -r -s $@ && $@

binomial_w2:
	@REM cd examples/admb-re/weights && admb.bat -r $@ && $@
	@REM cd examples/admb-re/weights && admb.bat -r -s $@ && $@
