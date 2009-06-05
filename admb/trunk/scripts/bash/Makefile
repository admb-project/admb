all: admb admb-re

admb: \
buscycle\
catage \
chem-eng \
finance \
pella-t \
robreg \
simple \
vol

admb-skip: forest truncreg SS3-Simple

buscycle: ham4 ham5
ham4:
	cd $(ADMB_HOME)/examples/admb/buscycle;admb $@;./$@
	cd $(ADMB_HOME)/examples/admb/buscycle;admb -s $@;./$@

ham5:
	cd $(ADMB_HOME)/examples/admb/buscycle;admb $@;./$@
	cd $(ADMB_HOME)/examples/admb/buscycle;admb -s $@;./$@

catage:
	cd $(ADMB_HOME)/examples/admb/$@;admb $@;./$@
	cd $(ADMB_HOME)/examples/admb/$@;admb -s $@;./$@

chem-eng:
	cd $(ADMB_HOME)/examples/admb/$@;admb $@;./$@
	cd $(ADMB_HOME)/examples/admb/$@;admb -s $@;./$@

finance:
	cd $(ADMB_HOME)/examples/admb/$@;admb $@;./$@
	cd $(ADMB_HOME)/examples/admb/$@;admb -s $@;./$@

forest:
	cd $(ADMB_HOME)/examples/admb/$@;admb $@;./$@
	cd $(ADMB_HOME)/examples/admb/$@;admb -s $@;./$@

pella-t:
	cd $(ADMB_HOME)/examples/admb/$@;admb $@;./$@
	cd $(ADMB_HOME)/examples/admb/$@;admb -s $@;./$@

robreg: vonb vonbr
vonb:
	cd $(ADMB_HOME)/examples/admb/robreg;admb $@;./$@
	cd $(ADMB_HOME)/examples/admb/robreg;admb -s $@;./$@

vonbr:
	cd $(ADMB_HOME)/examples/admb/robreg;admb $@;./$@
	cd $(ADMB_HOME)/examples/admb/robreg;admb -s $@;./$@

simple:
	cd $(ADMB_HOME)/examples/admb/$@;admb $@;./$@
	cd $(ADMB_HOME)/examples/admb/$@;admb -s $@;./$@

truncreg:
	cd $(ADMB_HOME)/examples/admb/$@;admb $@;./runtrunc.bat;./fruntrunc.bat
	cd $(ADMB_HOME)/examples/admb/$@;admb -s $@;./runtrunc.bat;./fruntrunc.bat

vol: n2mvol
n2mvol:
	cd $(ADMB_HOME)/examples/admb/vol;admb $@;./$@
	cd $(ADMB_HOME)/examples/admb/vol;admb -s $@;./$@

SS3-Simple:
	cd $(ADMB_HOME)/examples/admb/SS3-Simple;admb SS3;./SS3
	cd $(ADMB_HOME)/examples/admb/SS3-Simple;admb -s SS3;./SS3

admb-re:\
bcb \
biglog \
caest \
gamma \
kidney \
lidar \
logistic \
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

admb-re-skip: nbmm

bcb:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

biglog:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

caest:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

gamma:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r liver_$@;./liver_$@;check-expected-results liver_$@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s liver_$@;./liver_$@;check-expected-results liver_$@

kidney:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

lidar:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

logistic:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

nested4:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

orange:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

orange2:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

orange_cor:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

pheno:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

polio:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

sdv:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

skewed: diet diet_sk
diet:
	cd $(ADMB_HOME)/examples/admb-re/skewed;admb -r $@;./diet;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/skewed;admb -r -s $@;./diet;check-expected-results $@

diet_sk:
	cd $(ADMB_HOME)/examples/admb-re/skewed;admb -r $@;./diet;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/skewed;admb -r -s $@;./diet;check-expected-results $@

socatt:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

spatial:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

union:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

weights: binomial binomial_w2
binomial:
	cd $(ADMB_HOME)/examples/admb-re/weights;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/weights;admb -r -s $@;./$@;check-expected-results $@
binomial_w2:
	cd $(ADMB_HOME)/examples/admb-re/weights;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/weights;admb -r -s $@;./$@;check-expected-results $@
