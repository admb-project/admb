ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifneq ($(findstring sh.exe,$(shell where sh.exe 2>&1 | findstr sh.exe)),sh.exe)
      SHELL=cmd
      CMDSHELL=cmd
    endif
  endif
  ifeq ($(CMDSHELL),cmd)
    ifeq ($(wildcard ..\utilities\mingw\bin\g++.exe),..\utilities\mingw\bin\g++.exe)
      PATH:=$(abspath ..\utilities\mingw\bin);$(PATH)
    endif
  else
    ifeq ($(wildcard ../utilities/mingw/bin/g++.exe),../utilities/mingw/bin/g++.exe)
      PATH:=$(abspath ../utilities/mingw/bin):$(PATH)
    endif
  endif
endif

ifeq ($(DEBUG),yes)
DEBUG_OPTION=-g
endif

DIST=../build/admb

all:
	$(MAKE) tests-core
	$(MAKE) tests-contrib
ifeq ($(TESTS_REMOTE),yes)
	$(MAKE) tests-remote
endif

tests-remote:
	$(MAKE) remote-core-tpls
	$(MAKE) remote-contrib-tpls

tests-core:
	$(MAKE) unit-gtests
	$(MAKE) --directory=../examples all
	$(MAKE) core-tpls

tests-contrib:
	$(MAKE) contrib-tpls

coverage:
	$(MAKE) unit-gtests
	$(MAKE) --directory=../examples all
	$(MAKE) core-tpls

unit-gtests:
ifneq ($(USE_GTESTS),no)
	$(MAKE) --directory=gtests
endif

test-rgamma:
	$(MAKE) --directory=rgamma

core-tpls:\
  tpl-data_adstring_array\
  tpl-dd2\
  tpl-testminmax\
  example-prof_like\
  tpl-f1b2vc5\
  tpl-4darray\
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
  tpl-colfill\
  tpl-cov_re\
  tpl-expm\
  tpl-gradients_output\
  tpl-simple_mcmc\
  tpl-hysimple\
  tpl-adnuts\
  tpl-testminmax\
  tpl-orange_mvn\
  cpp-globals\
  tpl-lprof

remote-core-tpls:\
  tpl-geolocation\
  tpl-changepoint\
  tpl-geolocation\
  tpl-glmmadmb

contrib-tpls:\
  tpl-priors\
  test-rgamma\
  tpl-ctl

remote-contrib-tpls:\
  tpl-agemat

cpp-globals:
	$(MAKE) --directory=globals

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

tpl-data_adstring_array:
	$(MAKE) --directory=data_adstring_array

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

tpl-adnuts:
	$(MAKE) --directory=adnuts

tpl-priors:
	$(MAKE) --directory=priors

tpl-testminmax:
	$(MAKE) --directory=testminmax

tpl-orange_mvn:
	$(MAKE) --directory=orange_mvn

tpl-lprof:
ifeq ($(CMDSHELL),cmd)
	$(MAKE) --directory=lprof
endif

example-prof_like:
	$(MAKE) --directory=../examples/admb/prof_like

verify:
ifeq ($(CMDSHELL),cmd)
  ifneq ($(DEBUG),yes)
	del ..\outputs-saf.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C ..\examples all
	pushd .. & scripts\get-outputs.bat > outputs-saf.txt & popd
    ifndef SAFE_ONLY
	del ..\outputs-opt.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C ..\examples all
	pushd .. & scripts\get-outputs.bat > outputs-opt.txt & popd
    endif
  else
    ifndef SAFE_ONLY
	del ..\outputs-opt.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C ..\examples all
	pushd .. & scripts\get-outputs.bat > outputs-opt.txt & popd
    endif
	del ..\outputs-saf.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C ..\examples all
	pushd .. & scripts\get-outputs.bat > outputs-saf.txt & popd
  endif
else
	rm -vf ../outputs-saf.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C ../examples all
	-../scripts/get-outputs.sh ../examples/ > "../outputs-saf.txt"
  ifndef SAFE_ONLY
	rm -vf ../outputs-opt.txt
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C ../examples all
	-../scripts/get-outputs.sh ../examples/ > "../outputs-opt.txt"
  endif
endif

total-clean: clean
	$(MAKE) --directory=glmmadmb total-clean
	$(MAKE) --directory=gtests total-clean
	$(MAKE) --directory=geolocation total-clean
	$(MAKE) --directory=agemat total-clean

clean:
ifeq ($(CMDSHELL),cmd)
	@if exist SS3 rmdir /s /q SS3
	@del dd2\\f1b2list1
	@del dd2\\f1b2list12
	@del dd2\\f1b2list13
	@del dd2\\nf1b2list1
	@del dd2\\nf1b2list12
	@del dd2\\nf1b2list13
	@del dualaveraging\\dualaveraging.cpp
	@del dualaveraging\\dualaveraging.htp
	@del dualaveraging\\dualaveraging.obj
	@del dualaveraging\\hybmcmc.obj
	@del f1b2vc5\\f1b2vc5.b01
	@del f1b2vc5\\f1b2vc5.p01
else
	$(MAKE) --directory=lprof clean
	@rm -rvf SS3
	@rm -vf dd2/f1b2list1
	@rm -vf dd2/f1b2list12
	@rm -vf dd2/f1b2list13
	@rm -vf dd2/nf1b2list1
	@rm -vf dd2/nf1b2list12
	@rm -vf dd2/nf1b2list13
	@rm -vf dualaveraging/dualaveraging.cpp
	@rm -vf dualaveraging/dualaveraging.htp
	@rm -vf dualaveraging/dualaveraging.obj
	@rm -vf dualaveraging/hybmcmc.obj
	@rm -vf f1b2vc5/f1b2vc5.b01
	@rm -vf f1b2vc5/f1b2vc5.p01
endif
	$(MAKE) --directory=rgamma clean
	$(MAKE) --directory=globals clean
	$(MAKE) --directory=f1b2vc5 clean
	$(MAKE) --directory=expm clean
	$(MAKE) --directory=beta_regression clean
	$(MAKE) --directory=changepoint clean
	$(MAKE) --directory=hysimple clean
	$(MAKE) --directory=adnuts clean
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
ifeq ($(CMDSHELL),cmd)
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
ifeq ($(CMDSHELL),cmd)
	if not exist $(DIST)\tests md $(DIST)\tests
	xcopy ..\tests $(DIST)\tests /S /Y /D
else
	cp -Rvf ../tests $(DIST)
endif

outputs:
ifeq ($(CMDSHELL),cmd)
	del outputs-tests.txt
else
	rm -vf outputs-tests.txt
	touch outputs-tests.txt
	$(MAKE) --directory=lprof get-outputs >> outputs-tests.txt
endif
	$(MAKE) --directory=beta_regression get-outputs >> outputs-tests.txt
	$(MAKE) --directory=agemat get-outputs >> outputs-tests.txt
	$(MAKE) --directory=beta_deviate get-outputs >> output-tests.txt
	$(MAKE) --directory=simple_mcmc get-outputs >> output-tests.txt
