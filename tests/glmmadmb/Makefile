all: rforge-glmmadmb
	$(MAKE) admb_tests
	$(MAKE) glmmadmb.exe
	$(MAKE) nbmm.exe
	$(MAKE) bvprobit.exe
	$(MAKE) run

rforge-glmmadmb:
	git clone --depth 1 https://github.com/rforge/glmmadmb.git rforge-glmmadmb

glmmadmb.exe: glmmadmb.tpl
	..\\..\\admb glmmadmb

glmmadmb.tpl:
	copy rforge-glmmadmb\\pkg\\inst\\tpl\\glmmadmb.tpl

nbmm.exe: nbmm.tpl
	..\\..\\admb nbmm

nbmm.tpl:
	copy rforge-glmmadmb\\pkg\\inst\\tpl\\nbmm.tpl

bvprobit.exe: bvprobit.tpl
	..\\..\\admb bvprobit

bvprobit.tpl:
	copy rforge-glmmadmb\\pkg\\inst\\tpl\\bvprobit.tpl

admb_tests:
	xcopy rforge-glmmadmb\\pkg\\inst\\admb_tests

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
	glmmadmb.exe -maxfn 500 -maxph 5 -noinit -shess

total-clean: clean
	@if exist rforge-glmmadmb rmdir /s /q rforge-glmmadmb

clean:
	@del /Q admodel.cov
	@del /Q admodel.dep
	@del /Q admodel.hes
	@del /Q b1
	@del /Q b2
	@del /Q eigv.rpt
	@del /Q fmin.log
	@del /Q glmmadmb.exe
	@del /Q nbmm.exe
	@del /Q bvprobit.exe
	@del /Q glmmadmb.b01
	@del /Q glmmadmb.bar
	@del /Q glmmadmb.bgs
	@del /Q glmmadmb.cor
	@del /Q glmmadmb.cpp
	@del /Q glmmadmb.eva
	@del /Q glmmadmb.htp
	@del /Q glmmadmb.log
	@del /Q glmmadmb.luu
	@del /Q glmmadmb.obj
	@del /Q glmmadmb.p01
	@del /Q glmmadmb.par
	@del /Q glmmadmb.r01
	@del /Q glmmadmb.rep
	@del /Q glmmadmb.rhes
	@del /Q glmmadmb.std
	@del /Q hesscheck
	@del /Q hessian.bin
	@del /Q phi.rep
	@del /Q s1
	@del /Q s2
	@del /Q variance
	@del /Q bvprobit.cpp bvprobit.obj bvprobit bvprobit.htp
	@del /Q nbmm.cpp nbmm.obj nbmm nbmm.htp
	@if exist admb_tests rmdir /s /q admb_tests
	@if exist bvprobit.tpl del bvprobit.tpl
	@if exist glmmadmb.tpl del glmmadmb.tpl
	@if exist nbmm.tpl del nbmm.tpl
	@del /Q glmmadmb.b02
	@del /Q glmmadmb.b03
	@del /Q glmmadmb.b04
	@del /Q glmmadmb.p02
	@del /Q glmmadmb.p03
	@del /Q glmmadmb.p04
	@del /Q glmmadmb.r02
	@del /Q glmmadmb.r03
	@del /Q glmmadmb.r04
	@del /Q glmmadmb.shess
