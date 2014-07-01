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
ifneq ($(USE_GTESTS),no)
	$(MAKE) --directory=gtests
endif

all-tpls:\
  tpl-glmmadmb\
  tpl-agemat\
  tpl-betai\
  tpl-beta2\
  tpl-beta3\
  tpl-beta_deviate\
  tpl-betareg\
  tpl-beta_regression\
  tpl-changepoint\
  tpl-colfill\
  tpl-cov_re\
  tpl-ctl\
  tpl-expm\
  tpl-geolocation\
  tpl-simple_mcmc\
  tpl-hysimple\
  tpl-priors\
  tpl-testminmax\
  tpl-orange_mvn\
  tpl-SS3

tpl-glmmadmb:
	$(MAKE) --directory=glmmadmb

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

tpl-changepoint:
	$(MAKE) --directory=changepoint

tpl-colfill:
	$(MAKE) --directory=colfill

tpl-cov_re:
	$(MAKE) --directory=cov_re

tpl-ctl:
	$(MAKE) --directory=ctl

tpl-expm:
	$(MAKE) --directory=expm

tpl-simple_mcmc:
	$(MAKE) --directory=simple_mcmc

tpl-geolocation:
	$(MAKE) --directory=geolocation

tpl-gmrf:
	$(MAKE) --directory=gmrf

tpl-hysimple:
	$(MAKE) --directory=hysimple

tpl-priors:
	$(MAKE) --directory=priors

tpl-testminmax:
	$(MAKE) --directory=testminmax

tpl-orange_mvn:
	$(MAKE) --directory=orange_mvn

tpl-SS3:
ifneq ($(CXX),openCC)
	$(MAKE) --directory=SS3
endif

verify:
ifeq ($(SHELL),cmd)
	del ..\benchmarks-opt.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)\examples --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-opt.txt" & popd
	del ..\benchmarks-saf.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)\examples --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-saf.txt" & popd
else
	rm -vf ../benchmarks-opt.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)/examples all
	-../scripts/get-outputs.sh ${DIST}/examples/ > "../benchmarks-opt.txt"
	rm -vf ../benchmarks-saf.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)/examples all
	-../scripts/get-outputs.sh ${DIST}/examples/ > "../benchmarks-saf.txt"
endif

clean:
ifeq ($(SHELL),cmd)
	$(MAKE) --directory=glmmadmb --file=Makefile clean
	$(MAKE) --directory=agemat --file=Makefile clean
endif
	$(MAKE) --directory=expm clean
	$(MAKE) --directory=beta_regression clean
	$(MAKE) --directory=changepoint clean
	$(MAKE) --directory=hysimple clean
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
	$(MAKE) --directory=colfill clean
	$(MAKE) --directory=glmmadmb clean
	$(MAKE) --directory=orange_mvn clean

copy:
ifeq ($(SHELL),cmd)
	if not exist ${DIST}\tests md ${DIST}\tests
	xcopy ..\tests $(DIST)\tests /S /Y /D
else
	cp -Rvf ../tests ${DIST}
endif
