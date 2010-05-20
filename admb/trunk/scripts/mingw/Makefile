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
	cmd /C "cd examples\\admb\\buscycle& admb $@& $@"
	cmd /C "cd examples\\admb\\buscycle& admb -s $@& $@"

ham5:
	cmd /C "cd examples\\admb\\buscycle& admb $@& $@"
	cmd /C "cd examples\\admb\\buscycle& admb -s $@& $@"

chem-eng:
	cmd /C "cd examples\\admb\\$@& admb $@& $@"
	cmd /C "cd examples\\admb\\$@& admb -s $@& $@"

catage:
	cmd /C "cd examples\\admb\\$@& admb $@& $@"
	cmd /C "cd examples\\admb\\$@& admb -s $@& $@"

finance:
	cmd /C "cd examples\\admb\\$@& admb $@& $@"
	cmd /C "cd examples\\admb\\$@& admb -s $@& $@"

forest:
	-cmd /C "cd examples\\admb\\$@& admb $@& $@"
	-cmd /C "cd examples\\admb\\$@& admb -s $@& $@"

pella-t:
	cmd /C "cd examples\\admb\\$@& admb $@& $@"
	cmd /C "cd examples\\admb\\$@& admb -s $@& $@"

robreg: vonb vonbr
vonb:
	cmd /C "cd examples\\admb\\robreg& admb $@& $@"
	cmd /C "cd examples\\admb\\robreg& admb -s $@& $@"

vonbr:
	cmd /C "cd examples\\admb\\robreg& admb $@& $@"
	cmd /C "cd examples\\admb\\robreg& admb -s $@& $@"

simple:
	cmd /C "cd examples\\admb\\$@& admb $@& $@"
	cmd /C "cd examples\\admb\\$@& admb -s $@& $@"

truncreg:
	-cmd /C "cd examples\\admb\\$@& admb $@& runtrunc.bat& fruntrunc.bat"
	-cmd /C "cd examples\\admb\\$@& admb -s $@& runtrunc.bat& fruntrunc.bat"

vol: n2mvol
n2mvol:
	cmd /C "cd examples\\admb\\vol&  admb $@& $@"
	cmd /C "cd examples\\admb\\vol& admb -s $@& $@"

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
	cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

biglog:
	-cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	-cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

bvprobit:
	-cmd /C "cd examples\\admb-re\\glmmadmb& admb -r $@& $@"
	-cmd /C "cd examples\\admb-re\\glmmadmb& admb -r -s $@& $@"

caest:
	-cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	-cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

gamma:
	cmd /C "cd examples\\admb-re\\$@& admb -r liver_$@& liver_$@"
	cmd /C "cd examples\\admb-re\\$@& admb -r -s liver_$@& liver_$@"

kidney:
	cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

lidar:
	cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

logistic:
	-cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	-cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

nbmm:
	-cmd /C "cd examples\\admb-re\\glmmadmb& admb -r $@& $@"
	-cmd /C "cd examples\\admb-re\\glmmadmb& admb -r -s $@& $@"

nested4:
	cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

orange:
	cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

orange2:
	cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

orange_cor:
	-cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	-cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

pheno:
	cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

polio:
	cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

sdv:
	cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

skewed: diet diet_sk
diet:
	cmd /C "cd examples\\admb-re\\skewed& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\skewed& admb -r -s $@& $@"

diet_sk:
	cmd /C "cd examples\\admb-re\\skewed& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\skewed& admb -r -s $@& $@"

socatt:
	cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

spatial:
	cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

union:
	-cmd /C "cd examples\\admb-re\\$@& admb -r $@& $@"
	-cmd /C "cd examples\\admb-re\\$@& admb -r -s $@& $@"

weights: binomial binomial_w2
binomial:
	cmd /C "cd examples\\admb-re\\weights& admb -r $@& $@"
	cmd /C "cd examples\\admb-re\\weights& admb -r -s $@& $@"

binomial_w2:
	-cmd /C "cd examples\\admb-re\\weights& admb -r $@& $@"
	-cmd /C "cd examples\\admb-re\\weights& admb -r -s $@& $@"
