ADMB_HOME=..\\..\\..

!IF EXISTS(..\\..\\..\\scripts\\get-outputs.bat)
SCRIPTS_DIR=..\\..\\..\\..\\..\\scripts\\
!ELSE
SCRIPTS_DIR=..\\..\\..\\scripts\\
!ENDIF

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
bhplfine \
vol

buscycle: ham4 ham5
ham4:
	pushd admb\\buscycle & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\buscycle & $@ $(ADMB_RUN_ARGS)

ham5:
	pushd admb\\buscycle & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\buscycle & $@ $(ADMB_RUN_ARGS)

catage:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@ $(ADMB_RUN_ARGS)

chem_eng:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@ $(ADMB_RUN_ARGS)

finance:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@ $(ADMB_RUN_ARGS)

forest:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@ $(ADMB_RUN_ARGS)

pella_t:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@ $(ADMB_RUN_ARGS)

robreg: vonb vonbr
vonb:
	pushd admb\\robreg & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\robreg & $@ $(ADMB_RUN_ARGS)

vonbr:
	pushd admb\\robreg & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\robreg & $@ $(ADMB_RUN_ARGS)

simple:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@ $(ADMB_RUN_ARGS)

truncreg:
	pushd admb\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\$@ & $@ $(ADMB_RUN_ARGS)

vol: n2mvol
n2mvol:
	pushd admb\\vol & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb\\vol & $@ $(ADMB_RUN_ARGS)

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
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

biglog:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

bvprobit:
	pushd admb-re\\glmmadmb & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\glmmadmb & $@ $(ADMB_RUN_ARGS)

glmmadmb:
	pushd admb-re\\glmmadmb & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\glmmadmb & $@ $(ADMB_RUN_ARGS)

caest:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

gamma:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) liver_$@
	pushd admb-re\\$@ & liver_$@ $(ADMB_RUN_ARGS)

kidney:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

lidar:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

logistic:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

nbmm:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

nested4:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

orange:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

orange2:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

orange_cor:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

pheno:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

polio:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

sdv:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

skewed: diet diet_sk
diet:
	pushd admb-re\\skewed & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\skewed & $@ $(ADMB_RUN_ARGS)

diet_sk:
	pushd admb-re\\skewed & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\skewed & $@ $(ADMB_RUN_ARGS)

socatt:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

spatial:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

union:
	pushd admb-re\\$@ & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\$@ & $@ $(ADMB_RUN_ARGS)

weights: binomial
binomial:
	pushd admb-re\\weights & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\weights & $@ $(ADMB_RUN_ARGS)

binomial_w2:
	pushd admb-re\\weights & $(ADMB_HOME)\\admb $(OPTIONS) $@
	pushd admb-re\\weights & $@ $(ADMB_RUN_ARGS)

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

contrib-statslib:
	$(MAKE) statslib-catage
	$(MAKE) statslib-simple

statslib-catage:
        pushd statslib\\catage && $(ADMB_HOME)\\admb $(OPTIONS) catage && $(PROG) catage $(ADMB_RUN_ARGS) && popd

statslib-simple:
        pushd statslib\\simple && $(ADMB_HOME)\\admb $(OPTIONS) simple && $(PROG) simple $(ADMB_RUN_ARGS) && popd

clean:

get-outputs:
	@pushd admb\\buscycle && $(SCRIPTS_DIR)get-outputs.bat ham4 && popd
	@pushd admb\\buscycle && $(SCRIPTS_DIR)get-outputs.bat ham5 && popd
	@pushd admb\\catage && $(SCRIPTS_DIR)get-outputs.bat catage && popd
	@pushd admb\\chem_eng && $(SCRIPTS_DIR)get-outputs.bat chem_eng && popd
	@pushd admb\\forest && $(SCRIPTS_DIR)get-outputs.bat forest && popd
	@pushd admb\\finance && $(SCRIPTS_DIR)get-outputs.bat finance && popd
	@pushd admb\\pella_t && $(SCRIPTS_DIR)get-outputs.bat pella_t && popd
	@pushd admb\\robreg && $(SCRIPTS_DIR)get-outputs.bat vonbr && popd
	@pushd admb\\robreg && $(SCRIPTS_DIR)get-outputs.bat vonb && popd
	@pushd admb\\truncreg && $(SCRIPTS_DIR)get-outputs.bat truncreg && popd
	@pushd admb\\simple && $(SCRIPTS_DIR)get-outputs.bat simple && popd
	@pushd admb\\prof_like && $(SCRIPTS_DIR)get-outputs.bat bhplfine && popd
	@pushd admb\\vol && $(SCRIPTS_DIR)get-outputs.bat n2mvol && popd
	@pushd admb-re\\bcb && $(SCRIPTS_DIR)get-outputs.bat bcb && popd
	@pushd admb-re\\biglog && $(SCRIPTS_DIR)get-outputs.bat biglog && popd
	@pushd admb-re\\glmmadmb && $(SCRIPTS_DIR)get-outputs.bat bvprobit && popd
	@pushd admb-re\\glmmadmb && $(SCRIPTS_DIR)get-outputs.bat glmmadmb && popd
	@pushd admb-re\\glmmadmb && $(SCRIPTS_DIR)get-outputs.bat nbmm && popd
	@pushd admb-re\\caest && $(SCRIPTS_DIR)get-outputs.bat caest && popd
	@pushd admb-re\\gamma && $(SCRIPTS_DIR)get-outputs.bat liver_gamma && popd
	@pushd admb-re\\kidney && $(SCRIPTS_DIR)get-outputs.bat kidney && popd
	@pushd admb-re\\lidar && $(SCRIPTS_DIR)get-outputs.bat lidar && popd
	@pushd admb-re\\logistic && $(SCRIPTS_DIR)get-outputs.bat logistic && popd
	@pushd admb-re\\nbmm && $(SCRIPTS_DIR)get-outputs.bat nbmm && popd
	@pushd admb-re\\nested4 && $(SCRIPTS_DIR)get-outputs.bat nested4 && popd
	@pushd admb-re\\orange && $(SCRIPTS_DIR)get-outputs.bat orange && popd
	@pushd admb-re\\orange2 && $(SCRIPTS_DIR)get-outputs.bat orange2 && popd
	@pushd admb-re\\orange_cor && $(SCRIPTS_DIR)get-outputs.bat orange_cor && popd
	@pushd admb-re\\pheno && $(SCRIPTS_DIR)get-outputs.bat pheno && popd
	@pushd admb-re\\polio && $(SCRIPTS_DIR)get-outputs.bat polio && popd
	@pushd admb-re\\sdv && $(SCRIPTS_DIR)get-outputs.bat sdv && popd
	@pushd admb-re\\skewed && $(SCRIPTS_DIR)get-outputs.bat diet_sk && popd
	@pushd admb-re\\skewed && $(SCRIPTS_DIR)get-outputs.bat diet && popd
	@pushd admb-re\\socatt && $(SCRIPTS_DIR)get-outputs.bat socatt && popd
	@pushd admb-re\\spatial && $(SCRIPTS_DIR)get-outputs.bat spatial && popd
	@pushd admb-re\\union && $(SCRIPTS_DIR)get-outputs.bat union && popd
	@pushd admb-re\\weights && $(SCRIPTS_DIR)get-outputs.bat binomial_w2 && popd
	@pushd admb-re\\weights && $(SCRIPTS_DIR)get-outputs.bat binomial && popd
        @pushd statslib\\simple && $(SCRIPTS_DIR)get-outputs.bat simple && popd
        @pushd statslib\\catage && $(SCRIPTS_DIR)get-outputs.bat catage && popd
