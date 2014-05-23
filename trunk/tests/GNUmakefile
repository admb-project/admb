ifeq ($(OS),Windows_NT)
  ifeq (sh.exe,$(findstring sh.exe,$(SHELL)))
    SHELL = cmd
    ifeq ($(SHELL),cmd)
      MYPWD=$(shell cd)
    else
      MYPWD=$(shell cmd /C cd)
    endif
    PATH:=$(MYPWD)\..\utilities\mingw\bin;$(PATH);$(MYPWD)\..\utilities
  else
    ifneq ($(TERM),xterm)
      MYPWD=$(shell pwd)
      PATH:=$(MYPWD)/../utilities/mingw/bin:$(PATH)
    endif
    PATH:=$(PATH):$(MYPWD)/../utilities
  endif
endif

ifeq ($(DEBUG),yes)
DEBUG_OPTION=-g
endif

DIST=../build/dist

ifeq ($(CXX),CC)
all: all-tpls
else
all: all-gtests all-tpls
endif

all-gtests:
	$(MAKE) --directory=gtests

all-tpls:\
  tpl-agemat\
  tpl-betai\
  tpl-beta2\
  tpl-beta3\
  tpl-beta_deviate\
  tpl-betareg\
  tpl-beta_regression\
  tpl-cov_re\
  tpl-ctl\
  tpl-expm\
  tpl-gmrf\
  tpl-simple_mcmc\
  tpl-hysimple\
  tpl-priors\
  tpl-testminmax\
  tpl-SS3

tpl-agemat:
	$(MAKE) --directory=agemat

tpl-betai:
	$(MAKE) --directory=betai

tpl-beta2:
	$(MAKE) --directory=beta2

tpl-beta3:
	$(MAKE) --directory=beta3

tpl-beta_deviate:
	$(MAKE) --directory=beta_deviate

tpl-betareg:
	$(MAKE) --directory=betareg

tpl-beta_regression:
	$(MAKE) --directory=beta_regression

tpl-cov_re:
	$(MAKE) --directory=cov_re

tpl-ctl:
	$(MAKE) --directory=ctl

tpl-expm:
	$(MAKE) --directory=expm

tpl-simple_mcmc:
	$(MAKE) --directory=simple_mcmc

tpl-gmrf:
	$(MAKE) --directory=gmrf

tpl-hysimple:
	$(MAKE) --directory=hysimple

tpl-priors:
	$(MAKE) --directory=priors

tpl-simple_mcmc:
	$(MAKE) --directory=simple_mcmc

tpl-testminmax:
	$(MAKE) --directory=testminmax

tpl-SS3:
ifneq ($(CXX),openCC)
	$(MAKE) --directory=SS3
endif

gtest-colfill: googletest-read-only
	$(MAKE) --directory=colfill

svn:

main: test-geolocation test-cov_re

test-adstring:
	$(MAKE) --directory=adstring

test-geolocation:
	$(MAKE) --directory=geolocation

admb_messages:
	OPTIONS=-s $(MAKE) --directory=$@

init_bounded_number_matrix:
	OPTIONS=-s $(MAKE) --directory=$@

df33_tester:
	OPTIONS=-s $(MAKE) --directory=$@

RC04_solve:
	OPTIONS=-s $(MAKE) --directory=$@

RC04_det:
	OPTIONS=-s $(MAKE) --directory=$@

RC04_inv:
	OPTIONS=-s $(MAKE) --directory=$@

RC10_spline1:
	OPTIONS=-s $(MAKE) --directory=$@

RC10_spline2:
	OPTIONS=-s $(MAKE) --directory=$@

RC13_dsort:
	OPTIONS=-s $(MAKE) --directory=$@

RC15_eigen:
	OPTIONS=-s $(MAKE) --directory=$@

RC26_dflndet:
	OPTIONS=-s $(MAKE) --directory=$@

RC27_dfsolve1:
	OPTIONS=-s $(MAKE) --directory=$@

RC27_dfsolve2:
	OPTIONS=-s $(MAKE) --directory=$@

RC05_quad:
	OPTIONS=-s $(MAKE) --directory=$@

RC01_svd:
	OPTIONS=-s $(MAKE) --directory=$@

verify:
ifeq ($(SHELL),cmd)
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)\examples --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-opt.txt" & popd
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)\examples --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-saf.txt" & popd
else
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)/examples all
	-../scripts/get-outputs.sh ${DIST}/examples/ > "../benchmarks-opt.txt"
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)/examples all
	-../scripts/get-outputs.sh ${DIST}/examples/ > "../benchmarks-saf.txt"
endif

clean:
ifeq ($(SHELL),cmd)
	$(MAKE) --directory=expm --file=Makefile clean
	$(MAKE) --directory=priors --file=Makefile clean
	$(MAKE) --directory=agemat --file=Makefile clean
else
	$(MAKE) --directory=expm clean
	$(MAKE) --directory=beta_regression clean
	$(MAKE) --directory=hysimple clean
	$(MAKE) --directory=admb_messages clean
	$(MAKE) --directory=init_bounded_number_matrix clean
	$(MAKE) --directory=betareg clean
	$(MAKE) --directory=gmrf clean
	$(MAKE) --directory=simple_mcmc clean
	$(MAKE) --directory=testminmax clean
	$(MAKE) --directory=geolocation clean
	$(MAKE) --directory=betai clean
	$(MAKE) --directory=beta2 clean
	$(MAKE) --directory=beta3 clean
	$(MAKE) --directory=beta_deviate clean
	$(MAKE) --directory=SS3 clean
	$(MAKE) --directory=cov_re clean
	$(MAKE) --directory=gtests clean
	$(MAKE) --directory=agemat clean
	$(MAKE) --directory=ctl clean
	$(MAKE) --directory=priors clean
endif

copy:
ifeq ($(SHELL),cmd)
	if not exist ${DIST}\tests md ${DIST}\tests
	xcopy ..\tests $(DIST)\tests /S /Y /D
else
	cp -Rvf ../tests ${DIST}
endif
