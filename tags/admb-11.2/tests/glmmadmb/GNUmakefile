ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL=cmd
  else
    EXT=.sh
  endif
endif

all: 
ifeq ($(SHELL),cmd)
	$(MAKE) --file=Makefile all
else
	$(MAKE) glmmadmb nbmm bvprobit admb_tests
	$(MAKE) run
endif

glmmadmb: glmmadmb.tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb $^
else
	../../admb$(EXT) $^
endif

glmmadmb.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/tpl/$@ > $@

nbmm: nbmm.tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb $^
else
	../../admb$(EXT) $^
endif

nbmm.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/tpl/$@ > $@

bvprobit: bvprobit.tpl
ifeq ($(SHELL),cmd)
	..\\..\\admb $^
else
	../../admb$(EXT) $^
endif

bvprobit.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/tpl/$@ > $@

admb_tests:
	svn checkout svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/$@ $@ 

run:
ifeq ($(SHELL),cmd)
	$(MAKE) --file=Makefile run
else
	cp -vf glmmadmb admb_tests/bacteria
	cd admb_tests && ./bacteria
	cp -vf glmmadmb admb_tests/betabinom
	cd admb_tests && ./betabinom
	cp -vf glmmadmb admb_tests/epil2
	cd admb_tests && ./epil2 -nohess
	cp -vf glmmadmb admb_tests/hurdle_biochem1
	cd admb_tests && ./hurdle_biochem1
	cp -vf glmmadmb admb_tests/hurdle_biochem2
	cd admb_tests && ./hurdle_biochem2
	cp -vf glmmadmb admb_tests/zi_owls
	cd admb_tests && ./zi_owls
	./glmmadmb
endif

total-clean: clean
ifeq ($(SHELL),cmd)
	$(MAKE) --file=Makefile total-clean
else
	@rm -rvf admb_tests
	@rm -vf bvprobit.tpl
	@rm -vf glmmadmb.tpl
	@rm -vf nbmm.tpl
endif

clean:
ifeq ($(SHELL),cmd)
	$(MAKE) --file=Makefile clean
else
	@rm -vf admodel.cov
	@rm -vf admodel.dep
	@rm -vf admodel.hes
	@rm -vf b1
	@rm -vf b2
	@rm -vf eigv.rpt
	@rm -vf fmin.log
	@rm -vf glmmadmb
	@rm -vf glmmadmb.b01
	@rm -vf glmmadmb.bar
	@rm -vf glmmadmb.bgs
	@rm -vf glmmadmb.cor
	@rm -vf glmmadmb.cpp
	@rm -vf glmmadmb.eva
	@rm -vf glmmadmb.htp
	@rm -vf glmmadmb.log
	@rm -vf glmmadmb.luu
	@rm -vf glmmadmb.obj
	@rm -vf glmmadmb.p01
	@rm -vf glmmadmb.par
	@rm -vf glmmadmb.r01
	@rm -vf glmmadmb.rep
	@rm -vf glmmadmb.rhes
	@rm -vf glmmadmb.std
	@rm -vf hesscheck
	@rm -vf hessian.bin
	@rm -vf phi.rep
	@rm -vf s1
	@rm -vf s2
	@rm -vf variance
	@rm -vf bvprobit.cpp bvprobit.obj bvprobit bvprobit.htp
	@rm -vf nbmm.cpp nbmm.obj nbmm nbmm.htp
	@rm -vf admb_tests/admodel.cov
	@rm -vf admb_tests/admodel.dep
	@rm -vf admb_tests/admodel.hes
	@rm -vf admb_tests/b1
	@rm -vf admb_tests/b2
	@rm -vf admb_tests/bacteria
	@rm -vf admb_tests/bacteria.b01
	@rm -vf admb_tests/bacteria.bar
	@rm -vf admb_tests/bacteria.bgs
	@rm -vf admb_tests/bacteria.cor
	@rm -vf admb_tests/bacteria.eva
	@rm -vf admb_tests/bacteria.log
	@rm -vf admb_tests/bacteria.luu
	@rm -vf admb_tests/bacteria.p01
	@rm -vf admb_tests/bacteria.r01
	@rm -vf admb_tests/bacteria.rep
	@rm -vf admb_tests/bacteria.rhes
	@rm -vf admb_tests/betabinom
	@rm -vf admb_tests/betabinom.b01
	@rm -vf admb_tests/betabinom.bar
	@rm -vf admb_tests/betabinom.cor
	@rm -vf admb_tests/betabinom.eva
	@rm -vf admb_tests/betabinom.log
	@rm -vf admb_tests/betabinom.p01
	@rm -vf admb_tests/betabinom.r01
	@rm -vf admb_tests/betabinom.rep
	@rm -vf admb_tests/eigv.rpt
	@rm -vf admb_tests/epil2
	@rm -vf admb_tests/epil2.b01
	@rm -vf admb_tests/epil2.b02
	@rm -vf admb_tests/epil2.bar
	@rm -vf admb_tests/epil2.eva
	@rm -vf admb_tests/epil2.log
	@rm -vf admb_tests/epil2.luu
	@rm -vf admb_tests/epil2.p01
	@rm -vf admb_tests/epil2.p02
	@rm -vf admb_tests/epil2.r01
	@rm -vf admb_tests/epil2.r02
	@rm -vf admb_tests/epil2.rep
	@rm -vf admb_tests/epil2.rhes
	@rm -vf admb_tests/fmin.log
	@rm -vf admb_tests/hesscheck
	@rm -vf admb_tests/hessian.bin
	@rm -vf admb_tests/hurdle_biochem1
	@rm -vf admb_tests/hurdle_biochem1.bar
	@rm -vf admb_tests/hurdle_biochem1.cor
	@rm -vf admb_tests/hurdle_biochem1.eva
	@rm -vf admb_tests/hurdle_biochem1.log
	@rm -vf admb_tests/hurdle_biochem1.rep
	@rm -vf admb_tests/hurdle_biochem2
	@rm -vf admb_tests/hurdle_biochem2.bar
	@rm -vf admb_tests/hurdle_biochem2.cor
	@rm -vf admb_tests/hurdle_biochem2.eva
	@rm -vf admb_tests/hurdle_biochem2.log
	@rm -vf admb_tests/hurdle_biochem2.rep
	@rm -vf admb_tests/phi.rep
	@rm -vf admb_tests/s1
	@rm -vf admb_tests/s2
	@rm -vf admb_tests/variance
	@rm -vf admb_tests/zi_owls
	@rm -vf admb_tests/zi_owls.b01
	@rm -vf admb_tests/zi_owls.b02
	@rm -vf admb_tests/zi_owls.bar
	@rm -vf admb_tests/zi_owls.bgs
	@rm -vf admb_tests/zi_owls.cor
	@rm -vf admb_tests/zi_owls.eva
	@rm -vf admb_tests/zi_owls.log
	@rm -vf admb_tests/zi_owls.luu
	@rm -vf admb_tests/zi_owls.p01
	@rm -vf admb_tests/zi_owls.p02
	@rm -vf admb_tests/zi_owls.r01
	@rm -vf admb_tests/zi_owls.r02
	@rm -vf admb_tests/zi_owls.rep
	@rm -vf admb_tests/zi_owls.rhes
endif
