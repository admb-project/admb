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

GTEST_DIR=googletest-read-only

all: test-cov_re test-expm

run-gtests: $(GTEST_DIR)/gtest-all.o
	$(MAKE) --directory=gtests

gtest-colfill: googletest-read-only
	$(MAKE) --directory=colfill

$(GTEST_DIR)/gtest-all.o: googletest-read-only
	$(CXX) -c -g -I$(GTEST_DIR)/include -I$(GTEST_DIR) -o $@ $(GTEST_DIR)/src/gtest-all.cc

googletest-read-only:
	svn checkout http://googletest.googlecode.com/svn/trunk/ googletest-read-only

svn:

main: test-geolocation test-cov_re

test-adstring:
	$(MAKE) --directory=adstring

test-geolocation:
	$(MAKE) --directory=geolocation

test-expm:
	$(MAKE) --directory=expm

test-cov_re:
	$(MAKE) --directory=cov_re

priors:
	CXXFLAGS=$(CXXFLAGS) OPTIONS=-s $(MAKE) --directory=$@

testminmax:
	OPTIONS=-s $(MAKE) --directory=$@

SS3:
	$(MAKE) --directory=$@

admb_messages:
	OPTIONS=-s $(MAKE) --directory=$@

init_bounded_number_matrix:
	OPTIONS=-s $(MAKE) --directory=$@

df33_tester:
	OPTIONS=-s $(MAKE) --directory=$@

beta_regression:
	OPTIONS=-s $(MAKE) --directory=$@

hysimple:
	OPTIONS=-s $(MAKE) --directory=$@

simple_mcmc:
	OPTIONS=-s $(MAKE) --directory=$@

betareg:
	OPTIONS=-s $(MAKE) --directory=$@

gmrf:
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

betai:
	OPTIONS=-s $(MAKE) --directory=$@

beta_deviate:
	OPTIONS=-s $(MAKE) --directory=$@

beta2:
	OPTIONS=-s $(MAKE) --directory=$@

beta3:
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
else
	$(MAKE) --directory=expm clean
	$(MAKE) --directory=priors --file=Makefile clean
	$(MAKE) --directory=beta_regression clean
	$(MAKE) --directory=hysimple clean
	$(MAKE) --directory=admb_messages clean
	$(MAKE) --directory=init_bounded_number_matrix clean
	$(MAKE) --directory=betareg clean
	$(MAKE) --directory=gmrf clean
	$(MAKE) --directory=simple_mcmc clean
	$(MAKE) --directory=testminmax clean
	$(MAKE) --directory=geolocation clean
	$(MAKE) --directory=RC04_solve clean
	$(MAKE) --directory=RC04_det clean
	$(MAKE) --directory=RC04_inv clean
	$(MAKE) --directory=RC10_spline1 clean
	$(MAKE) --directory=RC10_spline2 clean
	$(MAKE) --directory=RC13_dsort clean
	$(MAKE) --directory=RC15_eigen clean
	$(MAKE) --directory=RC26_dflndet clean
	$(MAKE) --directory=RC27_dfsolve1 clean
	$(MAKE) --directory=RC27_dfsolve2 clean
	$(MAKE) --directory=RC05_quad clean
	$(MAKE) --directory=RC01_svd clean
	$(MAKE) --directory=betai clean
	$(MAKE) --directory=beta2 clean
	$(MAKE) --directory=beta3 clean
	$(MAKE) --directory=beta_deviate clean
	$(MAKE) --directory=SS3 clean
	$(MAKE) --directory=cov_re clean
	$(MAKE) --directory=gtests clean
endif

copy:
ifeq ($(SHELL),cmd)
	if not exist ${DIST}\tests md ${DIST}\tests
	xcopy ..\tests $(DIST)\tests /S /Y /D
else
	cp -R ../tests ${DIST}
endif
