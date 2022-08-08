ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifndef TERM
      export SHELL=cmd
      CMDSHELL=cmd
    endif
    ifdef CMDSHELL
      EXT=.sh
    endif
  endif
endif

all: rforge-glmmadmb
	$(MAKE) clean
	$(MAKE) glmmadmb
	$(MAKE) nbmm
	$(MAKE) bvprobit
	$(MAKE) admb_tests
	$(MAKE) run

rforge-glmmadmb:
	git clone --depth 1 https://github.com/rforge/glmmadmb.git rforge-glmmadmb

glmmadmb: glmmadmb.tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb $^
else
	../../admb$(EXT) $^
endif

glmmadmb.tpl:
ifeq ($(CMDSHELL),cmd)
	copy rforge-glmmadmb\pkg\inst\tpl\glmmadmb.tpl
else
	cp rforge-glmmadmb/pkg/inst/tpl/glmmadmb.tpl .
endif

nbmm: nbmm.tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb $^
else
	../../admb$(EXT) $^
endif

nbmm.tpl:
ifeq ($(CMDSHELL),cmd)
	copy rforge-glmmadmb\pkg\inst\tpl\nbmm.tpl
else
	cp rforge-glmmadmb/pkg/inst/tpl/nbmm.tpl .
endif

bvprobit: bvprobit.tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb $^
else
	../../admb$(EXT) $^
endif

bvprobit.tpl:
ifeq ($(CMDSHELL),cmd)
	copy rforge-glmmadmb\pkg\inst\tpl\bvprobit.tpl
else
	cp rforge-glmmadmb/pkg/inst/tpl/bvprobit.tpl .
endif

admb_tests:
ifeq ($(CMDSHELL),cmd)
	xcopy rforge-glmmadmb\pkg\inst\admb_tests admb_tests /I
else
	cp -R rforge-glmmadmb/pkg/inst/admb_tests .
endif

run:
ifeq ($(CMDSHELL),cmd)
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
	./glmmadmb -maxfn 500 -maxph 1 -noinit -shess
endif

get-outputs:

total-clean: clean
ifeq ($(CMDSHELL),cmd)
	@if exist rforge-glmmadmb rmdir /s /q rforge-glmmadmb
else
	@rm -rvf rforge-glmmadmb
endif

clean:
ifeq ($(CMDSHELL),cmd)
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
	@del /Q admodel.cov
	@del /Q admodel.dep
	@del /Q admodel.hes
	@del /Q b1
	@del /Q b2
	@del /Q bvprobit.cpp
	@del /Q bvprobit.exe
	@del /Q bvprobit.htp
	@del /Q bvprobit.obj
	@del /Q fmin.log
	@del /Q glmmadmb.b01
	@del /Q glmmadmb.bar
	@del /Q glmmadmb.bgs
	@del /Q glmmadmb.cor
	@del /Q glmmadmb.cpp
	@del /Q glmmadmb.eva
	@del /Q glmmadmb.exe
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
	@del /Q nbmm.cpp
	@del /Q nbmm.exe
	@del /Q nbmm.htp
	@del /Q nbmm.obj
	@del /Q phi.rep
	@del /Q s1
	@del /Q s2
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
	@rm -rvf admb_tests
	@rm -vf bvprobit.tpl
	@rm -vf glmmadmb.tpl
	@rm -vf nbmm.tpl
	@rm -vf glmmadmb.b02
	@rm -vf glmmadmb.b03
	@rm -vf glmmadmb.b04
	@rm -vf glmmadmb.p02
	@rm -vf glmmadmb.p03
	@rm -vf glmmadmb.p04
	@rm -vf glmmadmb.r02
	@rm -vf glmmadmb.r03
	@rm -vf glmmadmb.r04
	@rm -vf glmmadmb.shess
endif
