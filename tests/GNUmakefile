ifeq ($(OS),Windows_NT)
  ifeq ($(TERM),cygwin)
  else
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
endif

ifeq ($(DEBUG),yes)
DEBUG_OPTION=-g
endif

ifeq ($(SHELL),cmd)
  ifneq ($(DEBUG),yes)
    DIST=..\build\dist
  else
    DIST=..\build\debug
  endif
else
  ifneq ($(DEBUG),yes)
    DIST=../build/dist
  else
    DIST=../build/debug
  endif
endif

ifeq ($(CXX),CC)
all: all-tpls
else
all: all-gtests all-tpls
endif

coverage: all-gtests
	$(MAKE) --directory=../contrib/gdbprintlib CONTRIB_INCLUDE=../../build/debug/include includes
	$(MAKE) --directory=../examples all
	$(MAKE) tpl-f1b2vc5
	$(MAKE) tpl-4darray
	$(MAKE) tpl-glmmadmb
	$(MAKE) tpl-betai
	$(MAKE) tpl-beta2
	$(MAKE) tpl-beta3
	$(MAKE) tpl-vonmises
	$(MAKE) tpl-tiny_ad_fe
	$(MAKE) tpl-tinyfun
	$(MAKE) tpl-poisp
	$(MAKE) tpl-tiny_ad_re
	$(MAKE) tpl-vectorize
	$(MAKE) tpl-bessel
	$(MAKE) tpl-qbeta
	$(MAKE) tpl-dd2
	$(MAKE) tpl-beta_deviate
	$(MAKE) tpl-betareg
	$(MAKE) tpl-beta_regression
	$(MAKE) tpl-changepoint
	$(MAKE) tpl-colfill
	$(MAKE) tpl-cov_re
	$(MAKE) tpl-expm
	$(MAKE) tpl-gradients_output
	$(MAKE) tpl-geolocation
	$(MAKE) tpl-simple_mcmc
	$(MAKE) tpl-hysimple
	$(MAKE) tpl-testminmax
	$(MAKE) tpl-orange_mvn
	$(MAKE) tpl-lprof
	$(MAKE) example-prof_like

all-gtests:
ifneq ($(USE_GTESTS),no)
	$(MAKE) --directory=gtests
endif

test-rgamma:
	$(MAKE) --directory=rgamma

all-tpls:\
  test-rgamma\
  tpl-f1b2vc5\
  tpl-4darray\
  tpl-glmmadmb\
  tpl-agemat\
  tpl-betai\
  tpl-beta2\
  tpl-beta3\
  tpl-vonmises\
  tpl-tiny_ad_fe\
  tpl-tinyfun\
  tpl-poisp\
  tpl-tiny_ad_re\
  tpl-vectorize\
  tpl-bessel\
  tpl-qbeta\
  tpl-dd2\
  tpl-beta_deviate\
  tpl-betareg\
  tpl-beta_regression\
  tpl-changepoint\
  tpl-colfill\
  tpl-cov_re\
  tpl-ctl\
  tpl-expm\
  tpl-gradients_output\
  tpl-geolocation\
  tpl-simple_mcmc\
  tpl-hysimple\
  tpl-priors\
  tpl-testminmax\
  tpl-orange_mvn\
  tpl-lprof

tpl-f1b2vc5:
	$(MAKE) --directory=f1b2vc5

tpl-4darray:
	$(MAKE) --directory=4darray

tpl-glmmadmb:
	-$(MAKE) --directory=glmmadmb

tpl-agemat:
	$(MAKE) --directory=agemat

tpl-betai:
	$(MAKE) --directory=betai

tpl-beta2:
	$(MAKE) --directory=beta2

tpl-beta3:
	$(MAKE) --directory=beta3

tpl-vonmises:
	$(MAKE) --directory=vonmises

tpl-tiny_ad_fe:
	$(MAKE) --directory=tiny_ad_fe

tpl-tinyfun:
	$(MAKE) --directory=tinyfun

tpl-poisp:
	$(MAKE) --directory=poisp

tpl-tiny_ad_re:
	$(MAKE) --directory=tiny_ad_re

tpl-vectorize:
	$(MAKE) --directory=vectorize

tpl-bessel:
	$(MAKE) --directory=bessel

tpl-qbeta:
	$(MAKE) --directory=qbeta

tpl-dd2:
	$(MAKE) --directory=dd2

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

tpl-gradients_output:
	$(MAKE) --directory=gradients_output

tpl-geolocation:
	PATH=../../..:$(PATH) $(MAKE) --directory=geolocation

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

tpl-lprof:
ifneq ($(SHELL),cmd)
	$(MAKE) --directory=lprof
endif

example-prof_like:
	$(MAKE) --directory=../examples/admb/prof_like

verify:
ifeq ($(SHELL),cmd)
  ifneq ($(DEBUG),yes)
	del ..\benchmarks-opt.txt
	del ..\benchmarks-saf.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)\examples --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-opt.txt" & popd
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)\examples --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-saf.txt" & popd
  else
	del ..\benchmarks-opt.txt
	del ..\benchmarks-saf.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)\examples --file=Makefile all
	pushd ..\build\debug & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-opt.txt" & popd
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)\examples --file=Makefile all
	pushd ..\build\debug & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-saf.txt" & popd
  endif
else
	rm -vf ../benchmarks-opt.txt
	rm -vf ../benchmarks-saf.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)/examples all
	-../scripts/get-outputs.sh ${DIST}/examples/ > "../benchmarks-opt.txt"
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)/examples all
	-../scripts/get-outputs.sh ${DIST}/examples/ > "../benchmarks-saf.txt"
endif

total-clean: clean
	$(MAKE) --directory=glmmadmb total-clean
	$(MAKE) --directory=gtests total-clean
	$(MAKE) --directory=geolocation total-clean
	$(MAKE) --directory=agemat total-clean

clean:
ifeq ($(SHELL),cmd)
	@if exist SS3 rmdir /s /q SS3
else
	$(MAKE) --directory=lprof clean
	@rm -rvf SS3
endif
	$(MAKE) --directory=f1b2vc5 clean
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
	$(MAKE) --directory=vonmises clean
	$(MAKE) --directory=tiny_ad_fe clean
	$(MAKE) --directory=tinyfun clean
	$(MAKE) --directory=poisp clean
	$(MAKE) --directory=tiny_ad_re clean
	$(MAKE) --directory=vectorize clean
	$(MAKE) --directory=bessel clean
	$(MAKE) --directory=qbeta clean
	$(MAKE) --directory=dd2 clean
	$(MAKE) --directory=beta_deviate clean
	$(MAKE) --directory=cov_re clean
	$(MAKE) --directory=gtests clean
	$(MAKE) --directory=agemat clean
	$(MAKE) --directory=ctl clean
	$(MAKE) --directory=priors clean
	$(MAKE) --directory=colfill clean
	$(MAKE) --directory=glmmadmb clean
	$(MAKE) --directory=orange_mvn clean
	$(MAKE) --directory=gradients_output clean
	$(MAKE) --directory=4darray clean
	$(MAKE) --directory=../examples/admb/prof_like clean

dist-clean:
ifeq ($(SHELL),cmd)
	del agemat/agemat.dat
	del agemat/agemat.tpl
	if exist geolocation/kfsst rd /S /Q geolocation/kfsst
	if exist geolocation/kftrack rd /S /Q geolocation/kftrack
	if exist geolocation/trackit rd /S /Q geolocation/trackit
	if exist geolocation/ukfsst rd /S /Q geolocation/ukfsst
	if exist glmmadmb/admb_tests rd /S /Q glmmadmb/admb_tests
	del glmmadmb/bvprobit.tpl
	del glmmadmb/glmmadmb.tpl
	del glmmadmb/nbmm.tpl
	if exist gtests/googletest-read-only rd /S /Q gtests/googletest-read-only
else
	rm -vf agemat/agemat.dat
	rm -vf agemat/agemat.tpl
	rm -rvf geolocation/kfsst
	rm -rvf geolocation/kftrack
	rm -rvf geolocation/trackit
	rm -rvf geolocation/ukfsst
	rm -rvf glmmadmb/admb_tests
	rm -vf glmmadmb/bvprobit.tpl
	rm -vf glmmadmb/glmmadmb.tpl
	rm -vf glmmadmb/nbmm.tpl
	rm -rvf gtests/googletest-read-only
endif

copy:
ifeq ($(SHELL),cmd)
	if not exist $(DIST)\tests md $(DIST)\tests
	xcopy ..\tests $(DIST)\tests /S /Y /D
	$(MAKE) --directory=$(DIST)\tests total-clean
else
	cp -Rvf ../tests $(DIST)
	$(MAKE) --directory=$(DIST)/tests total-clean
endif

benchmarks:
ifeq ($(SHELL),cmd)
	del benchmarks-tests.txt
else
	rm -vf benchmarks-tests.txt
	touch benchmarks-tests.txt
	$(MAKE) --directory=lprof get-outputs >> benchmarks-tests.txt
endif
	$(MAKE) --directory=beta_regression get-outputs >> benchmarks-tests.txt
	$(MAKE) --directory=agemat get-outputs >> benchmarks-tests.txt
	$(MAKE) --directory=beta_deviate get-outputs >> benchmarks-tests.txt
	$(MAKE) --directory=simple_mcmc get-outputs >> benchmarks-tests.txt
