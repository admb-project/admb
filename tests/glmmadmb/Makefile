all: admb_tests glmmadmb.exe nbmm.exe bvprobit.exe run

glmmadmb.exe: glmmadmb.tpl
	..\\..\\admb $^

glmmadmb.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/tpl/$@ > $@

nbmm.exe: nbmm.tpl
	..\\..\\admb $^

nbmm.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/tpl/$@ > $@

bvprobit.exe: bvprobit.tpl
	..\\..\\admb $^

bvprobit.tpl:
	svn cat svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/tpl/$@ > $@

admb_tests:
	svn checkout svn://scm.r-forge.r-project.org/svnroot/glmmadmb/pkg/inst/$@ $@ 

run:
	copy glmmadmb.exe admb_tests\\bacteria.exe
	pushd admb_tests & bacteria
	copy glmmadmb.exe admb_tests\\betabinom.exe
	pushd admb_tests & betabinom
	copy glmmadmb.exe admb_tests\\epil2.exe
	pushd admb_tests & epil2 -nohess
	copy glmmadmb.exe admb_tests\\hurdle_biochem1.exe
	pushd admb_tests & hurdle_biochem1
	copy glmmadmb.exe admb_tests\\hurdle_biochem2.exe
	pushd admb_tests & hurdle_biochem2
	copy glmmadmb.exe admb_tests\\zi_owls.exe
	pushd admb_tests & zi_owls
	glmmadmb.exe

total-clean: clean
	@if exist admb_tests rmdir /s /q admb_tests
	@if exist bvprobit.tpl del bvprobit.tpl
	@if exist glmmadmb.tpl del glmmadmb.tpl
	@if exist nbmm.tpl del nbmm.tpl

clean:
	@del admodel.cov
	@del admodel.dep
	@del admodel.hes
	@del b1
	@del b2
	@del eigv.rpt
	@del fmin.log
	@del glmmadmb.exe
	@del nbmm.exe
	@del bvprobit.exe
	@del glmmadmb.b01
	@del glmmadmb.bar
	@del glmmadmb.bgs
	@del glmmadmb.cor
	@del glmmadmb.cpp
	@del glmmadmb.eva
	@del glmmadmb.htp
	@del glmmadmb.log
	@del glmmadmb.luu
	@del glmmadmb.obj
	@del glmmadmb.p01
	@del glmmadmb.par
	@del glmmadmb.r01
	@del glmmadmb.rep
	@del glmmadmb.rhes
	@del glmmadmb.std
	@del hesscheck
	@del hessian.bin
	@del phi.rep
	@del s1
	@del s2
	@del variance
	@del bvprobit.cpp bvprobit.obj bvprobit bvprobit.htp
	@del nbmm.cpp nbmm.obj nbmm nbmm.htp
