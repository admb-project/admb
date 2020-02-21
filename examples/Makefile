SHELL=cmd

ADMB_HOME=..\\..\\..

!IFDEF DEBUG
OPTIONS=-g $(DEBUG_OPTION) $(FAST_OPTION)
!ELSE
OPTIONS=$(DEBUG_OPTION) $(FAST_OPTION)
!ENDIF

all: admb admb-re autodif

admb:\
buscycle \
catage \
chem_eng \
forest \
finance \
pella_t \
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

chem_eng:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@

finance:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@

forest:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@

pella_t:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@

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
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@

vol: n2mvol
n2mvol:
	pushd admb\\vol & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\vol & $@

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
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@

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
	pushd admb-re\\$@ & $@

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
	pushd admb-re\\weights & $@

autodif: bigmin hemholtz io_examp normsim newt s1 autodif-simple simple2 simp1 struct oldstr

bigmin:
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd

hemholtz:
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp hem_func.cpp && $(PROG) $@ && popd

io_examp:
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd

minimize:
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp userfun.cpp && $(PROG) $@ && popd

mixture:
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp normaliz.cpp reset.cpp like.cpp savepar.cpp xinit.cpp nvarcal.cpp fcomp_m.cpp && $(PROG) $@ && popd

normsim:
	pushd autodif\\mixture && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd

newt:
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd

s1:
	pushd autodif\\simple && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd

autodif-simple:
	pushd autodif\\simple && $(ADMB_HOME)\\admb $(OPTIONS) simple.cpp fcomp_s.cpp && $(PROG) simple && popd

simple2:
	pushd autodif\\simple && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp fcomp_s.cpp && $(PROG) $@ && popd

simp1:
	pushd autodif\\simple && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp fcomp_s.cpp && $(PROG) $@ && popd

struct:
	pushd autodif\\$@ && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd

oldstr:
	pushd autodif\\struct && $(ADMB_HOME)\\admb $(OPTIONS) $@.cpp && $(PROG) $@ && popd

clean:
	del admb-re\\bcb\\admodel.cov
	del admb-re\\bcb\\admodel.dep
	del admb-re\\bcb\\admodel.hes
	del admb-re\\bcb\\bcb.exe
	del admb-re\\bcb\\bcb.bar
	del admb-re\\bcb\\bcb.bgs
	del admb-re\\bcb\\bcb.cor
	del admb-re\\bcb\\bcb.cpp
	del admb-re\\bcb\\bcb.eva
	del admb-re\\bcb\\bcb.htp
	del admb-re\\bcb\\bcb.log
	del admb-re\\bcb\\bcb.luu
	del admb-re\\bcb\\bcb.obj
	del admb-re\\bcb\\bcb.par
	del admb-re\\bcb\\bcb.rep
	del admb-re\\bcb\\bcb.rhes
	del admb-re\\bcb\\bcb.std
	del admb-re\\bcb\\fmin.log
	del admb-re\\bcb\\hesscheck
	del admb-re\\bcb\\hessian.bin
	del admb-re\\biglog\\admodel.cov
	del admb-re\\biglog\\admodel.dep
	del admb-re\\biglog\\admodel.hes
	del admb-re\\biglog\\biglog.exe
	del admb-re\\biglog\\biglog.b01
	del admb-re\\biglog\\biglog.b02
	del admb-re\\biglog\\biglog.bar
	del admb-re\\biglog\\biglog.bgs
	del admb-re\\biglog\\biglog.cor
	del admb-re\\biglog\\biglog.cpp
	del admb-re\\biglog\\biglog.eva
	del admb-re\\biglog\\biglog.htp
	del admb-re\\biglog\\biglog.log
	del admb-re\\biglog\\biglog.luu
	del admb-re\\biglog\\biglog.obj
	del admb-re\\biglog\\biglog.p01
	del admb-re\\biglog\\biglog.p02
	del admb-re\\biglog\\biglog.par
	del admb-re\\biglog\\biglog.rhes
	del admb-re\\biglog\\biglog.std
	del admb-re\\biglog\\fmin.log
	del admb-re\\biglog\\hesscheck
	del admb-re\\biglog\\hessian.bin
	del admb-re\\caest\\admodel.cov
	del admb-re\\caest\\admodel.dep
	del admb-re\\caest\\admodel.hes
	del admb-re\\caest\\caest.exe
	del admb-re\\caest\\caest.b01
	del admb-re\\caest\\caest.bar
	del admb-re\\caest\\caest.bgs
	del admb-re\\caest\\caest.cor
	del admb-re\\caest\\caest.cpp
	del admb-re\\caest\\caest.eva
	del admb-re\\caest\\caest.htp
	del admb-re\\caest\\caest.log
	del admb-re\\caest\\caest.luu
	del admb-re\\caest\\caest.obj
	del admb-re\\caest\\caest.p01
	del admb-re\\caest\\caest.par
	del admb-re\\caest\\caest.r01
	del admb-re\\caest\\caest.rep
	del admb-re\\caest\\caest.rhes
	del admb-re\\caest\\caest.std
	del admb-re\\caest\\fmin.log
	del admb-re\\caest\\hesscheck
	del admb-re\\caest\\hessian.bin
	del admb-re\\gamma\\admodel.cov
	del admb-re\\gamma\\admodel.dep
	del admb-re\\gamma\\admodel.hes
	del admb-re\\gamma\\fmin.log
	del admb-re\\gamma\\hesscheck
	del admb-re\\gamma\\hessian.bin
	del admb-re\\gamma\\liver_gamma.exe
	del admb-re\\gamma\\liver_gamma.b01
	del admb-re\\gamma\\liver_gamma.bar
	del admb-re\\gamma\\liver_gamma.bgs
	del admb-re\\gamma\\liver_gamma.cor
	del admb-re\\gamma\\liver_gamma.cpp
	del admb-re\\gamma\\liver_gamma.eva
	del admb-re\\gamma\\liver_gamma.htp
	del admb-re\\gamma\\liver_gamma.log
	del admb-re\\gamma\\liver_gamma.obj
	del admb-re\\gamma\\liver_gamma.p01
	del admb-re\\gamma\\liver_gamma.par
	del admb-re\\gamma\\liver_gamma.rhes
	del admb-re\\gamma\\liver_gamma.std
	del admb-re\\glmmadmb\\admodel.cov
	del admb-re\\glmmadmb\\admodel.dep
	del admb-re\\glmmadmb\\admodel.hes
	del admb-re\\glmmadmb\\b1
	del admb-re\\glmmadmb\\b2
	del admb-re\\glmmadmb\\bvprobit.exe
	del admb-re\\glmmadmb\\bvprobit.b01
	del admb-re\\glmmadmb\\bvprobit.bar
	del admb-re\\glmmadmb\\bvprobit.bgs
	del admb-re\\glmmadmb\\bvprobit.cor
	del admb-re\\glmmadmb\\bvprobit.cpp
	del admb-re\\glmmadmb\\bvprobit.eva
	del admb-re\\glmmadmb\\bvprobit.htp
	del admb-re\\glmmadmb\\bvprobit.log
	del admb-re\\glmmadmb\\bvprobit.obj
	del admb-re\\glmmadmb\\bvprobit.p01
	del admb-re\\glmmadmb\\bvprobit.par
	del admb-re\\glmmadmb\\bvprobit.r01
	del admb-re\\glmmadmb\\bvprobit.rep
	del admb-re\\glmmadmb\\bvprobit.rhes
	del admb-re\\glmmadmb\\bvprobit.std
	del admb-re\\glmmadmb\\fmin.log
	del admb-re\\glmmadmb\\glmmadmb.exe
	del admb-re\\glmmadmb\\glmmadmb.b01
	del admb-re\\glmmadmb\\glmmadmb.b02
	del admb-re\\glmmadmb\\glmmadmb.b03
	del admb-re\\glmmadmb\\glmmadmb.b04
	del admb-re\\glmmadmb\\glmmadmb.bar
	del admb-re\\glmmadmb\\glmmadmb.bgs
	del admb-re\\glmmadmb\\glmmadmb.cor
	del admb-re\\glmmadmb\\glmmadmb.cpp
	del admb-re\\glmmadmb\\glmmadmb.eva
	del admb-re\\glmmadmb\\glmmadmb.htp
	del admb-re\\glmmadmb\\glmmadmb.log
	del admb-re\\glmmadmb\\glmmadmb.luu
	del admb-re\\glmmadmb\\glmmadmb.obj
	del admb-re\\glmmadmb\\glmmadmb.p01
	del admb-re\\glmmadmb\\glmmadmb.p02
	del admb-re\\glmmadmb\\glmmadmb.p03
	del admb-re\\glmmadmb\\glmmadmb.p04
	del admb-re\\glmmadmb\\glmmadmb.par
	del admb-re\\glmmadmb\\glmmadmb.r01
	del admb-re\\glmmadmb\\glmmadmb.r02
	del admb-re\\glmmadmb\\glmmadmb.r03
	del admb-re\\glmmadmb\\glmmadmb.r04
	del admb-re\\glmmadmb\\glmmadmb.rep
	del admb-re\\glmmadmb\\glmmadmb.rhes
	del admb-re\\glmmadmb\\glmmadmb.shess
	del admb-re\\glmmadmb\\glmmadmb.std
	del admb-re\\glmmadmb\\hesscheck
	del admb-re\\glmmadmb\\hessian.bin
	del admb-re\\glmmadmb\\phi.rep
	del admb-re\\glmmadmb\\s1
	del admb-re\\glmmadmb\\s2
	del admb-re\\kidney\\admodel.cov
	del admb-re\\kidney\\admodel.dep
	del admb-re\\kidney\\admodel.hes
	del admb-re\\kidney\\fmin.log
	del admb-re\\kidney\\hesscheck
	del admb-re\\kidney\\hessian.bin
	del admb-re\\kidney\\kidney.exe
	del admb-re\\kidney\\kidney.bar
	del admb-re\\kidney\\kidney.bgs
	del admb-re\\kidney\\kidney.cor
	del admb-re\\kidney\\kidney.cpp
	del admb-re\\kidney\\kidney.eva
	del admb-re\\kidney\\kidney.htp
	del admb-re\\kidney\\kidney.log
	del admb-re\\kidney\\kidney.luu
	del admb-re\\kidney\\kidney.obj
	del admb-re\\kidney\\kidney.par
	del admb-re\\kidney\\kidney.rep
	del admb-re\\kidney\\kidney.rhes
	del admb-re\\kidney\\kidney.std
	del admb-re\\lidar\\admodel.cov
	del admb-re\\lidar\\admodel.dep
	del admb-re\\lidar\\admodel.hes
	del admb-re\\lidar\\fmin.log
	del admb-re\\lidar\\hesscheck
	del admb-re\\lidar\\hessian.bin
	del admb-re\\lidar\\lidar.exe
	del admb-re\\lidar\\lidar.b01
	del admb-re\\lidar\\lidar.bar
	del admb-re\\lidar\\lidar.bgs
	del admb-re\\lidar\\lidar.cor
	del admb-re\\lidar\\lidar.cpp
	del admb-re\\lidar\\lidar.eva
	del admb-re\\lidar\\lidar.htp
	del admb-re\\lidar\\lidar.log
	del admb-re\\lidar\\lidar.luu
	del admb-re\\lidar\\lidar.obj
	del admb-re\\lidar\\lidar.p01
	del admb-re\\lidar\\lidar.par
	del admb-re\\lidar\\lidar.r01
	del admb-re\\lidar\\lidar.rep
	del admb-re\\lidar\\lidar.rhes
	del admb-re\\lidar\\lidar.std
	del admb-re\\logistic\\admodel.cov
	del admb-re\\logistic\\admodel.dep
	del admb-re\\logistic\\admodel.hes
	del admb-re\\logistic\\fmin.log
	del admb-re\\logistic\\hesscheck
	del admb-re\\logistic\\hessian.bin
	del admb-re\\logistic\\logistic.exe
	del admb-re\\logistic\\logistic.b01
	del admb-re\\logistic\\logistic.bar
	del admb-re\\logistic\\logistic.bgs
	del admb-re\\logistic\\logistic.cor
	del admb-re\\logistic\\logistic.cpp
	del admb-re\\logistic\\logistic.eva
	del admb-re\\logistic\\logistic.htp
	del admb-re\\logistic\\logistic.log
	del admb-re\\logistic\\logistic.luu
	del admb-re\\logistic\\logistic.obj
	del admb-re\\logistic\\logistic.p01
	del admb-re\\logistic\\logistic.par
	del admb-re\\logistic\\logistic.r01
	del admb-re\\logistic\\logistic.rep
	del admb-re\\logistic\\logistic.rhes
	del admb-re\\logistic\\logistic.std
	del admb-re\\nbmm\\admodel.cov
	del admb-re\\nbmm\\admodel.dep
	del admb-re\\nbmm\\admodel.hes
	del admb-re\\nbmm\\fmin.log
	del admb-re\\nbmm\\hesscheck
	del admb-re\\nbmm\\hessian.bin
	del admb-re\\nbmm\\nbmm.exe
	del admb-re\\nbmm\\nbmm.b01
	del admb-re\\nbmm\\nbmm.b02
	del admb-re\\nbmm\\nbmm.bar
	del admb-re\\nbmm\\nbmm.bgs
	del admb-re\\nbmm\\nbmm.cor
	del admb-re\\nbmm\\nbmm.cpp
	del admb-re\\nbmm\\nbmm.eva
	del admb-re\\nbmm\\nbmm.htp
	del admb-re\\nbmm\\nbmm.log
	del admb-re\\nbmm\\nbmm.luu
	del admb-re\\nbmm\\nbmm.obj
	del admb-re\\nbmm\\nbmm.p01
	del admb-re\\nbmm\\nbmm.p02
	del admb-re\\nbmm\\nbmm.par
	del admb-re\\nbmm\\nbmm.r01
	del admb-re\\nbmm\\nbmm.r02
	del admb-re\\nbmm\\nbmm.rep
	del admb-re\\nbmm\\nbmm.rhes
	del admb-re\\nbmm\\nbmm.std
	del admb-re\\nested4\\admodel.cov
	del admb-re\\nested4\\admodel.dep
	del admb-re\\nested4\\admodel.hes
	del admb-re\\nested4\\fmin.log
	del admb-re\\nested4\\hesscheck
	del admb-re\\nested4\\hessian.bin
	del admb-re\\nested4\\nested4.exe
	del admb-re\\nested4\\nested4.b01
	del admb-re\\nested4\\nested4.bar
	del admb-re\\nested4\\nested4.bgs
	del admb-re\\nested4\\nested4.cor
	del admb-re\\nested4\\nested4.cpp
	del admb-re\\nested4\\nested4.eva
	del admb-re\\nested4\\nested4.htp
	del admb-re\\nested4\\nested4.log
	del admb-re\\nested4\\nested4.obj
	del admb-re\\nested4\\nested4.p01
	del admb-re\\nested4\\nested4.par
	del admb-re\\nested4\\nested4.r01
	del admb-re\\nested4\\nested4.rep
	del admb-re\\nested4\\nested4.rhes
	del admb-re\\nested4\\nested4.std
	del admb-re\\orange\\admodel.cov
	del admb-re\\orange\\admodel.dep
	del admb-re\\orange\\admodel.hes
	del admb-re\\orange\\fmin.log
	del admb-re\\orange\\hesscheck
	del admb-re\\orange\\hessian.bin
	del admb-re\\orange\\orange.exe
	del admb-re\\orange\\orange.b01
	del admb-re\\orange\\orange.bar
	del admb-re\\orange\\orange.bgs
	del admb-re\\orange\\orange.cor
	del admb-re\\orange\\orange.cpp
	del admb-re\\orange\\orange.eva
	del admb-re\\orange\\orange.htp
	del admb-re\\orange\\orange.log
	del admb-re\\orange\\orange.obj
	del admb-re\\orange\\orange.p01
	del admb-re\\orange\\orange.par
	del admb-re\\orange\\orange.r01
	del admb-re\\orange\\orange.rep
	del admb-re\\orange\\orange.rhes
	del admb-re\\orange\\orange.std
	del admb-re\\orange2\\admodel.cov
	del admb-re\\orange2\\admodel.dep
	del admb-re\\orange2\\admodel.hes
	del admb-re\\orange2\\fmin.log
	del admb-re\\orange2\\hesscheck
	del admb-re\\orange2\\hessian.bin
	del admb-re\\orange2\\orange2.exe
	del admb-re\\orange2\\orange2.b01
	del admb-re\\orange2\\orange2.bar
	del admb-re\\orange2\\orange2.bgs
	del admb-re\\orange2\\orange2.cor
	del admb-re\\orange2\\orange2.cpp
	del admb-re\\orange2\\orange2.eva
	del admb-re\\orange2\\orange2.htp
	del admb-re\\orange2\\orange2.log
	del admb-re\\orange2\\orange2.luu
	del admb-re\\orange2\\orange2.obj
	del admb-re\\orange2\\orange2.p01
	del admb-re\\orange2\\orange2.par
	del admb-re\\orange2\\orange2.r01
	del admb-re\\orange2\\orange2.rep
	del admb-re\\orange2\\orange2.rhes
	del admb-re\\orange2\\orange2.std
	del admb-re\\orange_cor\\admodel.cov
	del admb-re\\orange_cor\\admodel.dep
	del admb-re\\orange_cor\\admodel.hes
	del admb-re\\orange_cor\\fmin.log
	del admb-re\\orange_cor\\hesscheck
	del admb-re\\orange_cor\\hessian.bin
	del admb-re\\orange_cor\\orange_cor.exe
	del admb-re\\orange_cor\\orange_cor.b01
	del admb-re\\orange_cor\\orange_cor.bar
	del admb-re\\orange_cor\\orange_cor.bgs
	del admb-re\\orange_cor\\orange_cor.cor
	del admb-re\\orange_cor\\orange_cor.cpp
	del admb-re\\orange_cor\\orange_cor.eva
	del admb-re\\orange_cor\\orange_cor.htp
	del admb-re\\orange_cor\\orange_cor.log
	del admb-re\\orange_cor\\orange_cor.obj
	del admb-re\\orange_cor\\orange_cor.p01
	del admb-re\\orange_cor\\orange_cor.par
	del admb-re\\orange_cor\\orange_cor.r01
	del admb-re\\orange_cor\\orange_cor.rep
	del admb-re\\orange_cor\\orange_cor.rhes
	del admb-re\\orange_cor\\orange_cor.std
	del admb-re\\pheno\\admodel.cov
	del admb-re\\pheno\\admodel.dep
	del admb-re\\pheno\\admodel.hes
	del admb-re\\pheno\\fmin.log
	del admb-re\\pheno\\hesscheck
	del admb-re\\pheno\\hessian.bin
	del admb-re\\pheno\\pheno.exe
	del admb-re\\pheno\\pheno.b01
	del admb-re\\pheno\\pheno.bar
	del admb-re\\pheno\\pheno.bgs
	del admb-re\\pheno\\pheno.cor
	del admb-re\\pheno\\pheno.cpp
	del admb-re\\pheno\\pheno.eva
	del admb-re\\pheno\\pheno.htp
	del admb-re\\pheno\\pheno.log
	del admb-re\\pheno\\pheno.obj
	del admb-re\\pheno\\pheno.p01
	del admb-re\\pheno\\pheno.par
	del admb-re\\pheno\\pheno.r01
	del admb-re\\pheno\\pheno.rep
	del admb-re\\pheno\\pheno.rhes
	del admb-re\\pheno\\pheno.std
	del admb-re\\polio\\admodel.cov
	del admb-re\\polio\\admodel.dep
	del admb-re\\polio\\admodel.hes
	del admb-re\\polio\\fmin.log
	del admb-re\\polio\\hesscheck
	del admb-re\\polio\\hessian.bin
	del admb-re\\polio\\polio.exe
	del admb-re\\polio\\polio.b01
	del admb-re\\polio\\polio.bar
	del admb-re\\polio\\polio.bgs
	del admb-re\\polio\\polio.cor
	del admb-re\\polio\\polio.cpp
	del admb-re\\polio\\polio.eva
	del admb-re\\polio\\polio.htp
	del admb-re\\polio\\polio.log
	del admb-re\\polio\\polio.luu
	del admb-re\\polio\\polio.obj
	del admb-re\\polio\\polio.p01
	del admb-re\\polio\\polio.par
	del admb-re\\polio\\polio.r01
	del admb-re\\polio\\polio.rep
	del admb-re\\polio\\polio.rhes
	del admb-re\\polio\\polio.std
	del admb-re\\sdv\\admodel.cov
	del admb-re\\sdv\\admodel.dep
	del admb-re\\sdv\\admodel.hes
	del admb-re\\sdv\\fmin.log
	del admb-re\\sdv\\hesscheck
	del admb-re\\sdv\\hessian.bin
	del admb-re\\sdv\\sdv.exe
	del admb-re\\sdv\\sdv.b01
	del admb-re\\sdv\\sdv.bar
	del admb-re\\sdv\\sdv.bgs
	del admb-re\\sdv\\sdv.cor
	del admb-re\\sdv\\sdv.cpp
	del admb-re\\sdv\\sdv.eva
	del admb-re\\sdv\\sdv.htp
	del admb-re\\sdv\\sdv.log
	del admb-re\\sdv\\sdv.luu
	del admb-re\\sdv\\sdv.obj
	del admb-re\\sdv\\sdv.p01
	del admb-re\\sdv\\sdv.par
	del admb-re\\sdv\\sdv.r01
	del admb-re\\sdv\\sdv.rep
	del admb-re\\sdv\\sdv.rhes
	del admb-re\\sdv\\sdv.std
	del admb-re\\skewed\\admodel.cov
	del admb-re\\skewed\\admodel.dep
	del admb-re\\skewed\\admodel.hes
	del admb-re\\skewed\\diet.exe
	del admb-re\\skewed\\diet.b01
	del admb-re\\skewed\\diet.bar
	del admb-re\\skewed\\diet.bgs
	del admb-re\\skewed\\diet.cor
	del admb-re\\skewed\\diet.cpp
	del admb-re\\skewed\\diet.eva
	del admb-re\\skewed\\diet.htp
	del admb-re\\skewed\\diet.log
	del admb-re\\skewed\\diet.obj
	del admb-re\\skewed\\diet.p01
	del admb-re\\skewed\\diet.par
	del admb-re\\skewed\\diet.r01
	del admb-re\\skewed\\diet.rep
	del admb-re\\skewed\\diet.rhes
	del admb-re\\skewed\\diet.std
	del admb-re\\skewed\\diet_sk.exe
	del admb-re\\skewed\\diet_sk.b01
	del admb-re\\skewed\\diet_sk.b02
	del admb-re\\skewed\\diet_sk.bar
	del admb-re\\skewed\\diet_sk.bgs
	del admb-re\\skewed\\diet_sk.cor
	del admb-re\\skewed\\diet_sk.cpp
	del admb-re\\skewed\\diet_sk.eva
	del admb-re\\skewed\\diet_sk.htp
	del admb-re\\skewed\\diet_sk.log
	del admb-re\\skewed\\diet_sk.obj
	del admb-re\\skewed\\diet_sk.p01
	del admb-re\\skewed\\diet_sk.p02
	del admb-re\\skewed\\diet_sk.par
	del admb-re\\skewed\\diet_sk.r01
	del admb-re\\skewed\\diet_sk.r02
	del admb-re\\skewed\\diet_sk.rep
	del admb-re\\skewed\\diet_sk.rhes
	del admb-re\\skewed\\diet_sk.std
	del admb-re\\skewed\\fmin.log
	del admb-re\\skewed\\hesscheck
	del admb-re\\skewed\\hessian.bin
	del admb-re\\socatt\\admodel.cov
	del admb-re\\socatt\\admodel.dep
	del admb-re\\socatt\\admodel.hes
	del admb-re\\socatt\\fmin.log
	del admb-re\\socatt\\hesscheck
	del admb-re\\socatt\\hessian.bin
	del admb-re\\socatt\\socatt.exe
	del admb-re\\socatt\\socatt.bar
	del admb-re\\socatt\\socatt.bgs
	del admb-re\\socatt\\socatt.cor
	del admb-re\\socatt\\socatt.cpp
	del admb-re\\socatt\\socatt.eva
	del admb-re\\socatt\\socatt.htp
	del admb-re\\socatt\\socatt.log
	del admb-re\\socatt\\socatt.obj
	del admb-re\\socatt\\socatt.par
	del admb-re\\socatt\\socatt.rep
	del admb-re\\socatt\\socatt.rhes
	del admb-re\\socatt\\socatt.std
	del admb-re\\spatial\\admodel.cov
	del admb-re\\spatial\\admodel.dep
	del admb-re\\spatial\\admodel.hes
	del admb-re\\spatial\\classcode.tmp
	del admb-re\\spatial\\fmin.log
	del admb-re\\spatial\\hesscheck
	del admb-re\\spatial\\hessian.bin
	del admb-re\\spatial\\spatial.exe
	del admb-re\\spatial\\spatial.b01
	del admb-re\\spatial\\spatial.bar
	del admb-re\\spatial\\spatial.bgs
	del admb-re\\spatial\\spatial.cor
	del admb-re\\spatial\\spatial.cpp
	del admb-re\\spatial\\spatial.eva
	del admb-re\\spatial\\spatial.htp
	del admb-re\\spatial\\spatial.log
	del admb-re\\spatial\\spatial.luu
	del admb-re\\spatial\\spatial.obj
	del admb-re\\spatial\\spatial.p01
	del admb-re\\spatial\\spatial.par
	del admb-re\\spatial\\spatial.r01
	del admb-re\\spatial\\spatial.rep
	del admb-re\\spatial\\spatial.rhes
	del admb-re\\spatial\\spatial.std
	del admb-re\\union\\admodel.cov
	del admb-re\\union\\admodel.dep
	del admb-re\\union\\admodel.hes
	del admb-re\\union\\fmin.log
	del admb-re\\union\\hesscheck
	del admb-re\\union\\hessian.bin
	del admb-re\\union\\union.exe
	del admb-re\\union\\union.b01
	del admb-re\\union\\union.bar
	del admb-re\\union\\union.bgs
	del admb-re\\union\\union.cor
	del admb-re\\union\\union.cpp
	del admb-re\\union\\union.eva
	del admb-re\\union\\union.htp
	del admb-re\\union\\union.log
	del admb-re\\union\\union.luu
	del admb-re\\union\\union.obj
	del admb-re\\union\\union.p01
	del admb-re\\union\\union.par
	del admb-re\\union\\union.r01
	del admb-re\\union\\union.rep
	del admb-re\\union\\union.rhes
	del admb-re\\union\\union.std
	del admb-re\\weights\\admodel.cov
	del admb-re\\weights\\admodel.dep
	del admb-re\\weights\\admodel.hes
	del admb-re\\weights\\binomial.exe
	del admb-re\\weights\\binomial.b01
	del admb-re\\weights\\binomial.bar
	del admb-re\\weights\\binomial.bgs
	del admb-re\\weights\\binomial.cor
	del admb-re\\weights\\binomial.cpp
	del admb-re\\weights\\binomial.eva
	del admb-re\\weights\\binomial.htp
	del admb-re\\weights\\binomial.log
	del admb-re\\weights\\binomial.obj
	del admb-re\\weights\\binomial.p01
	del admb-re\\weights\\binomial.par
	del admb-re\\weights\\binomial.rhes
	del admb-re\\weights\\binomial.std
	del admb-re\\weights\\fmin.log
	del admb-re\\weights\\hesscheck
	del admb-re\\weights\\hessian.bin
	del admb\\buscycle\\admodel.cov
	del admb\\buscycle\\admodel.dep
	del admb\\buscycle\\admodel.hes
	del admb\\buscycle\\fmin.log
	del admb\\buscycle\\gradfil1.tmp
	del admb\\buscycle\\gradfil2.tmp
	del admb\\buscycle\\ham4.exe
	del admb\\buscycle\\ham4.b01
	del admb\\buscycle\\ham4.b02
	del admb\\buscycle\\ham4.b03
	del admb\\buscycle\\ham4.b04
	del admb\\buscycle\\ham4.bar
	del admb\\buscycle\\ham4.cor
	del admb\\buscycle\\ham4.cpp
	del admb\\buscycle\\ham4.eva
	del admb\\buscycle\\ham4.htp
	del admb\\buscycle\\ham4.log
	del admb\\buscycle\\ham4.obj
	del admb\\buscycle\\ham4.p01
	del admb\\buscycle\\ham4.p02
	del admb\\buscycle\\ham4.p03
	del admb\\buscycle\\ham4.p04
	del admb\\buscycle\\ham4.par
	del admb\\buscycle\\ham4.r01
	del admb\\buscycle\\ham4.r02
	del admb\\buscycle\\ham4.r03
	del admb\\buscycle\\ham4.r04
	del admb\\buscycle\\ham4.rep
	del admb\\buscycle\\ham4.std
	del admb\\buscycle\\ham5.exe
	del admb\\buscycle\\ham5.b01
	del admb\\buscycle\\ham5.b02
	del admb\\buscycle\\ham5.b03
	del admb\\buscycle\\ham5.b04
	del admb\\buscycle\\ham5.bar
	del admb\\buscycle\\ham5.cor
	del admb\\buscycle\\ham5.cpp
	del admb\\buscycle\\ham5.eva
	del admb\\buscycle\\ham5.htp
	del admb\\buscycle\\ham5.log
	del admb\\buscycle\\ham5.obj
	del admb\\buscycle\\ham5.p01
	del admb\\buscycle\\ham5.p02
	del admb\\buscycle\\ham5.p03
	del admb\\buscycle\\ham5.p04
	del admb\\buscycle\\ham5.par
	del admb\\buscycle\\ham5.r01
	del admb\\buscycle\\ham5.r02
	del admb\\buscycle\\ham5.r03
	del admb\\buscycle\\ham5.r04
	del admb\\buscycle\\ham5.rep
	del admb\\buscycle\\ham5.std
	del admb\\buscycle\\qafter4.tex
	del admb\\buscycle\\qafter5.tex
	del admb\\buscycle\\qbefore4.tex
	del admb\\buscycle\\qbefore5.tex
	del admb\\buscycle\\varssave.tmp
	del admb\\chem_eng\\admodel.cov
	del admb\\chem_eng\\admodel.dep
	del admb\\chem_eng\\admodel.hes
	del admb\\chem_eng\\chem_eng.exe
	del admb\\chem_eng\\chem_eng.bar
	del admb\\chem_eng\\chem_eng.cor
	del admb\\chem_eng\\chem_eng.cpp
	del admb\\chem_eng\\chem_eng.eva
	del admb\\chem_eng\\chem_eng.htp
	del admb\\chem_eng\\chem_eng.log
	del admb\\chem_eng\\chem_eng.obj
	del admb\\chem_eng\\chem_eng.par
	del admb\\chem_eng\\chem_eng.std
	del admb\\chem_eng\\fmin.log
	del admb\\finance\\admodel.cov
	del admb\\finance\\admodel.dep
	del admb\\finance\\admodel.hes
	del admb\\finance\\finance.exe
	del admb\\finance\\finance.b01
	del admb\\finance\\finance.b02
	del admb\\finance\\finance.bar
	del admb\\finance\\finance.cor
	del admb\\finance\\finance.cpp
	del admb\\finance\\finance.eva
	del admb\\finance\\finance.htp
	del admb\\finance\\finance.log
	del admb\\finance\\finance.obj
	del admb\\finance\\finance.p01
	del admb\\finance\\finance.p02
	del admb\\finance\\finance.par
	del admb\\finance\\finance.std
	del admb\\finance\\fmin.log
	del admb\\forest\\admodel.cov
	del admb\\forest\\admodel.dep
	del admb\\forest\\admodel.hes
	del admb\\forest\\fmin.log
	del admb\\forest\\forest.exe
	del admb\\forest\\forest.b01
	del admb\\forest\\forest.bar
	del admb\\forest\\forest.cor
	del admb\\forest\\forest.cpp
	del admb\\forest\\forest.eva
	del admb\\forest\\forest.htp
	del admb\\forest\\forest.log
	del admb\\forest\\forest.obj
	del admb\\forest\\forest.p01
	del admb\\forest\\forest.par
	del admb\\forest\\forest.r01
	del admb\\forest\\forest.rep
	del admb\\forest\\forest.std
	del admb\\pella_t\\admodel.cov
	del admb\\pella_t\\admodel.dep
	del admb\\pella_t\\admodel.hes
	del admb\\pella_t\\fmin.log
	del admb\\pella_t\\pella_t.exe
	del admb\\pella_t\\pella_t.b01
	del admb\\pella_t\\pella_t.b02
	del admb\\pella_t\\pella_t.b03
	del admb\\pella_t\\pella_t.bar
	del admb\\pella_t\\pella_t.cor
	del admb\\pella_t\\pella_t.cpp
	del admb\\pella_t\\pella_t.eva
	del admb\\pella_t\\pella_t.htp
	del admb\\pella_t\\pella_t.log
	del admb\\pella_t\\pella_t.obj
	del admb\\pella_t\\pella_t.p01
	del admb\\pella_t\\pella_t.p02
	del admb\\pella_t\\pella_t.p03
	del admb\\pella_t\\pella_t.par
	del admb\\pella_t\\pella_t.std
	del admb\\robreg\\admodel.cov
	del admb\\robreg\\admodel.dep
	del admb\\robreg\\admodel.hes
	del admb\\robreg\\fmin.log
	del admb\\robreg\\vonb.exe
	del admb\\robreg\\vonb.bar
	del admb\\robreg\\vonb.cor
	del admb\\robreg\\vonb.cpp
	del admb\\robreg\\vonb.eva
	del admb\\robreg\\vonb.htp
	del admb\\robreg\\vonb.log
	del admb\\robreg\\vonb.obj
	del admb\\robreg\\vonb.par
	del admb\\robreg\\vonb.std
	del admb\\robreg\\vonbr.exe
	del admb\\robreg\\vonbr.b01
	del admb\\robreg\\vonbr.bar
	del admb\\robreg\\vonbr.cor
	del admb\\robreg\\vonbr.cpp
	del admb\\robreg\\vonbr.eva
	del admb\\robreg\\vonbr.htp
	del admb\\robreg\\vonbr.log
	del admb\\robreg\\vonbr.obj
	del admb\\robreg\\vonbr.p01
	del admb\\robreg\\vonbr.par
	del admb\\robreg\\vonbr.std
	del admb\\truncreg\\admodel.cov
	del admb\\truncreg\\admodel.dep
	del admb\\truncreg\\admodel.hes
	del admb\\truncreg\\fmin.log
	del admb\\truncreg\\truncreg.exe
	del admb\\truncreg\\truncreg.bar
	del admb\\truncreg\\truncreg.cor
	del admb\\truncreg\\truncreg.cpp
	del admb\\truncreg\\truncreg.eva
	del admb\\truncreg\\truncreg.htp
	del admb\\truncreg\\truncreg.log
	del admb\\truncreg\\truncreg.obj
	del admb\\truncreg\\truncreg.par
	del admb\\truncreg\\truncreg.rep
	del admb\\truncreg\\truncreg.std
	del admb\\vol\\admodel.cov
	del admb\\vol\\admodel.dep
	del admb\\vol\\admodel.hes
	del admb\\vol\\fmin.log
	del admb\\vol\\n2mvol.exe
	del admb\\vol\\n2mvol.b01
	del admb\\vol\\n2mvol.bar
	del admb\\vol\\n2mvol.cor
	del admb\\vol\\n2mvol.cpp
	del admb\\vol\\n2mvol.eva
	del admb\\vol\\n2mvol.htp
	del admb\\vol\\n2mvol.log
	del admb\\vol\\n2mvol.obj
	del admb\\vol\\n2mvol.p01
	del admb\\vol\\n2mvol.par
	del admb\\vol\\n2mvol.r01
	del admb\\vol\\n2mvol.rep
	del admb\\vol\\n2mvol.std
	del autodif\\hemholtz\\fmin.log
	del autodif\\hemholtz\\hem_func.obj
	del autodif\\hemholtz\\hemholtz.exe
	del autodif\\hemholtz\\hemholtz.obj
	del autodif\\io_examp\\file1.tmp
	del autodif\\io_examp\\file2.tmp
	del autodif\\io_examp\\fmin.log
	del autodif\\io_examp\\io_examp.exe
	del autodif\\io_examp\\io_examp.obj
	del autodif\\newt\\fmin.log
	del autodif\\newt\\newt.exe
	del autodif\\newt\\newt.obj
	del autodif\\simple\\fcomp_s.obj
	del autodif\\simple\\fmin.log
	del autodif\\simple\\s1.exe
	del autodif\\simple\\s1.obj
	del autodif\\simple\\simp1.exe
	del autodif\\simple\\simp1.obj
	del autodif\\simple\\simple.exe
	del autodif\\simple\\simple.obj
	del autodif\\simple\\simple2.exe
	del autodif\\simple\\simple2.obj
	del autodif\\struct\\fmin.log
	del autodif\\struct\\oldstr.exe
	del autodif\\struct\\oldstr.obj
	del autodif\\struct\\struct.exe
	del autodif\\struct\\struct.obj
