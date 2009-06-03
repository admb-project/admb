verify: admb admb-re

admb: ham4 ham5 catage finance vonb vonbr n2mvol simple
admb-skip: SS3-Simple chem-eng forest pella-t truncreg union nbmm

admb-re: biglog caest kidney
admb-re-skip: orange2 union skewed weights gamma nested4 bcb sdv pheno orange polio logistic lidar

SS3-Simple:
	cd $(ADMB_HOME)/examples/admb/SS3-Simple;admb SS3;./SS3
	cd $(ADMB_HOME)/examples/admb/SS3-Simple;admb -s SS3;./SS3

ham4:
	cd $(ADMB_HOME)/examples/admb/buscycle;admb ham4;./ham4
	cd $(ADMB_HOME)/examples/admb/buscycle;admb -s ham4;./ham4

ham5:
	cd $(ADMB_HOME)/examples/admb/buscycle;admb ham5;./ham5
	cd $(ADMB_HOME)/examples/admb/buscycle;admb -s ham5;./ham5

catage:
	cd $(ADMB_HOME)/examples/admb/catage;admb catage;./catage
	cd $(ADMB_HOME)/examples/admb/catage;admb -s catage;./catage

chem-eng:
	cd $(ADMB_HOME)/examples/admb/chem-eng;admb chem-eng;./chem-eng
	cd $(ADMB_HOME)/examples/admb/chem-eng;admb -s chem-eng;./chem-eng

finance:
	cd $(ADMB_HOME)/examples/admb/finance;admb finance;./finance
	cd $(ADMB_HOME)/examples/admb/finance;admb -s finance;./finance

forest:
	cd $(ADMB_HOME)/examples/admb/forest;admb forest;./forest
	cd $(ADMB_HOME)/examples/admb/forest;admb -s forest;./forest

pella-t:
	cd $(ADMB_HOME)/examples/admb/pella-t;admb pella-t;./pella-t
	cd $(ADMB_HOME)/examples/admb/pella-t;admb -s pella-t;./pella-t

vonb:
	cd $(ADMB_HOME)/examples/admb/robreg;admb vonb;./vonb
	cd $(ADMB_HOME)/examples/admb/robreg;admb -s vonb;./vonb

vonbr:
	cd $(ADMB_HOME)/examples/admb/robreg;admb vonbr;./vonbr
	cd $(ADMB_HOME)/examples/admb/robreg;admb -s vonbr;./vonbr

simple:
	cd $(ADMB_HOME)/examples/admb/simple;admb simple;./simple
	cd $(ADMB_HOME)/examples/admb/simple;admb -s simple;./simple

truncreg:
	cd $(ADMB_HOME)/examples/admb/truncreg;admb truncreg;./runtrunc;./fruntrunc
	cd $(ADMB_HOME)/examples/admb/truncreg;admb -s truncreg;./runtrunc;./fruntrunc

n2mvol:
	cd $(ADMB_HOME)/examples/admb/vol;admb n2mvol;./n2mvol
	cd $(ADMB_HOME)/examples/admb/vol;admb -s n2mvol;./n2mvol


biglog:
	cd $(ADMB_HOME)/examples/admb-re/biglog;admb -r biglog;./biglog;check-expected-results biglog
	cd $(ADMB_HOME)/examples/admb-re/biglog;admb -r -s biglog;./biglog;check-expected-results biglog

caest:
	cd $(ADMB_HOME)/examples/admb-re/caest;admb -r caest;./caest;check-expected-results caest
	cd $(ADMB_HOME)/examples/admb-re/caest;admb -r -s caest;./caest;check-expected-results caest

skewed:
	cd $(ADMB_HOME)/examples/admb-re/skewed;admb -r diet;./diet;check-expected-results diet
	cd $(ADMB_HOME)/examples/admb-re/skewed;admb -r -s diet;./diet;check-expected-results diet
	cd $(ADMB_HOME)/examples/admb-re/skewed;admb -r diet_sk;./diet_sk;check-expected-results diet_sk
	cd $(ADMB_HOME)/examples/admb-re/skewed;admb -r -s diet_sk;./diet_sk;check-expected-results diet_sk

weights:
	cd $(ADMB_HOME)/examples/admb-re/weights;admb -r binomial_w2;./binomial_w2;check-expected-results binomial_w2
	cd $(ADMB_HOME)/examples/admb-re/weights;admb -r -s binomial_w2;./binomial_w2;check-expected-results binomial_w2

orange_cor:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

gamma:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r liver_$@;./liver_$@;check-expected-results liver_$@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s liver_$@;./liver_$@;check-expected-results liver_$@

nested4:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

bcb:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

orange2:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

sdv:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

kidney:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

pheno:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

orange:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

socatt:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

polio:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

logistic:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

lidar:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

union:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@

spatial:
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r $@;./$@;check-expected-results $@
	cd $(ADMB_HOME)/examples/admb-re/$@;admb -r -s $@;./$@;check-expected-results $@
