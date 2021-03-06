ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifeq ($(findstring sh.exe,$(shell where sh.exe 2>&1 | findstr sh.exe)),sh.exe)
      EXT=.sh
    else
      SHELL=cmd
      CMDSHELL=cmd
    endif
  endif
endif

all: rforge-glmmadmb
ifeq ($(CMDSHELL),cmd)
	$(MAKE) --file=Makefile all
else
	$(MAKE) glmmadmb
	$(MAKE) nbmm
	$(MAKE) bvprobit
	$(MAKE) admb_tests
	$(MAKE) run
endif

rforge-glmmadmb:
	git clone --depth 1 https://github.com/rforge/glmmadmb.git rforge-glmmadmb

glmmadmb: glmmadmb.tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb $^
else
	../../admb$(EXT) $^
endif

glmmadmb.tpl:
	cp rforge-glmmadmb/pkg/inst/tpl/glmmadmb.tpl .

nbmm: nbmm.tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb $^
else
	../../admb$(EXT) $^
endif

nbmm.tpl:
	cp rforge-glmmadmb/pkg/inst/tpl/nbmm.tpl .

bvprobit: bvprobit.tpl
ifeq ($(CMDSHELL),cmd)
	..\\..\\admb $^
else
	../../admb$(EXT) $^
endif

bvprobit.tpl:
	cp rforge-glmmadmb/pkg/inst/tpl/bvprobit.tpl .

admb_tests:
	cp -R rforge-glmmadmb/pkg/inst/admb_tests .

run:
ifeq ($(CMDSHELL),cmd)
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
