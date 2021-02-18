TESTS_REMOTE=yes

ifndef ADMB_VER
  ADMB_VER=admb
endif

ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifneq ($(TERM),cygwin)
      ifneq ($(TERM),xterm)
        ifneq ($(findstring sh.exe,$(shell where sh.exe 2>&1 | findstr sh.exe)),sh.exe)
          SHELL=cmd
          CMDSHELL=cmd
        endif
      endif
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
else
DEBUG_OPTION=
endif

ifeq ($(CMDSHELL),cmd)
OUTPUT_DIR=..\\
DIST=..\\build\\$(ADMB_VER)
else
OUTPUT_DIR=../
DIST=../build/$(ADMB_VER)
endif

all:
	$(MAKE) tests-core
	$(MAKE) tests-contrib
ifeq ($(TESTS_REMOTE),yes)
	$(MAKE) tests-remote
endif

verify: examples
	$(MAKE) all
	$(MAKE) outputs.txt

tests-remote:
	$(MAKE) remote-core-tpls
	$(MAKE) remote-contrib-tpls
	$(MAKE) unit-gtests

tests-core:
	$(MAKE) core-tpls

tests-contrib:
	$(MAKE) contrib-tpls

coverage:
	$(MAKE) unit-gtests
	$(MAKE) core-tpls

unit-gtests:
ifneq ($(USE_GTESTS),no)
	$(MAKE) --directory=gtests
endif

test-rgamma:
	$(MAKE) --directory=rgamma

core-tpls:\
  tpl-4darray\
  tpl-adnuts\
  tpl-altexample\
  tpl-bessel\
  tpl-beta2\
  tpl-beta3\
  tpl-beta_deviate\
  tpl-beta_regression\
  tpl-betai\
  tpl-betareg\
  tpl-colfill\
  tpl-cov_re\
  tpl-data_adstring_array\
  tpl-dd2\
  tpl-dualaveraging\
  tpl-expm\
  tpl-f1b2vc5\
  cpp-globals\
  tpl-gradients_output\
  tpl-high_iarray\
  tpl-hysimple\
  tpl-initializationfunction\
  tpl-issue108\
  tpl-lprof\
  tpl-mcmc-theta\
  tpl-orange_mvn\
  tpl-poisp\
  tpl-qbeta\
  tpl-rsimple\
  tpl-simple_mcmc\
  tpl-testminmax\
  tpl-tiny\
  tpl-tiny_ad_fe\
  tpl-tiny_ad_re\
  tpl-tinyfun\
  tpl-vectorize\
  tpl-vonmises\
  example-prof_like

remote-core-tpls:\
  tpl-changepoint\
  tpl-geolocation\
  tpl-glmmadmb

contrib-tpls:\
  tpl-ctl\
  tpl-priors\
  test-rgamma

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

tpl-altexample:
	$(MAKE) --directory=altexample

tpl-betai:
	$(MAKE) --directory=betai

tpl-beta2:
	$(MAKE) --directory=beta2

tpl-beta3:
	$(MAKE) --directory=beta3

tpl-vonmises:
	$(MAKE) --directory=vonmises

tpl-high_iarray:
	$(MAKE) --directory=high_iarray

tpl-tiny_ad_fe:
	$(MAKE) --directory=tiny_ad_fe

tpl-tiny_ad_re:
	$(MAKE) --directory=tiny_ad_re

tpl-tinyfun:
	$(MAKE) --directory=tinyfun

tpl-tiny:
	$(MAKE) --directory=tiny

tpl-rsimple:
	$(MAKE) --directory=rsimple

tpl-poisp:
	$(MAKE) --directory=poisp

tpl-vectorize:
	$(MAKE) --directory=vectorize

tpl-bessel:
	$(MAKE) --directory=bessel

tpl-qbeta:
	$(MAKE) --directory=qbeta

tpl-dd2:
	$(MAKE) --directory=dd2

tpl-dualaveraging:
	$(MAKE) --directory=dualaveraging

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

tpl-hysimple:
	$(MAKE) --directory=hysimple

tpl-issue108:
	$(MAKE) --directory=issue108

tpl-initializationfunction:
	$(MAKE) --directory=initializationfunction

tpl-simple_mcmc:
	$(MAKE) --directory=simple_mcmc

tpl-gradients_output:
	$(MAKE) --directory=gradients_output

tpl-geolocation:
	$(MAKE) --directory=geolocation

tpl-gmrf:
	$(MAKE) --directory=gmrf

tpl-adnuts:
	$(MAKE) --directory=adnuts

tpl-priors:
	$(MAKE) --directory=priors

tpl-testminmax:
	$(MAKE) --directory=testminmax

tpl-mcmc-theta:
	$(MAKE) --directory=mcmc-theta

tpl-orange_mvn:
	$(MAKE) --directory=orange_mvn

tpl-lprof:
	$(MAKE) --directory=lprof

example-prof_like:
	$(MAKE) --directory=../examples/admb/prof_like

examples:
ifeq ($(CMDSHELL),cmd)
	if exist $(DIST)\\examples rmdir /s /q $(DESTDIR)\\examples
	md $(DESTDIR)\\examples
	xcopy ..\\examples $(DIST)\examples /S /Y /D
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)\\examples all
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)\\examples get-outputs > outputs-examples-saf.txt
  ifndef SAFE_ONLY
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)\\examples all
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)\\examples get-outputs > outputs-examples-opt.txt
  endif
else
	if [ -d "$(DIST)/examples" ]; then rm -rvf $(DIST)/examples; fi
	cp -Rvf ../examples $(DIST)
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) --directory=$(DIST)/examples all
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) --directory=$(DIST)/examples get-outputs > outputs-examples-saf.txt
  ifndef SAFE_ONLY
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)/examples all
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) --directory=$(DIST)/examples get-outputs > outputs-examples-opt.txt
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
else
	@rm -rvf SS3
endif
	$(MAKE) --directory=4darray clean
	$(MAKE) --directory=adnuts clean
	$(MAKE) --directory=agemat clean
	$(MAKE) --directory=altexample clean
	$(MAKE) --directory=bessel clean
	$(MAKE) --directory=beta2 clean
	$(MAKE) --directory=beta3 clean
	$(MAKE) --directory=beta_deviate clean
	$(MAKE) --directory=beta_regression clean
	$(MAKE) --directory=betai clean
	$(MAKE) --directory=betareg clean
	$(MAKE) --directory=changepoint clean
	$(MAKE) --directory=colfill clean
	$(MAKE) --directory=cov_re clean
	$(MAKE) --directory=ctl clean
	$(MAKE) --directory=data_adstring_array clean
	$(MAKE) --directory=dd2 clean
	$(MAKE) --directory=dualaveraging clean
	$(MAKE) --directory=expm clean
	$(MAKE) --directory=f1b2vc5 clean
	$(MAKE) --directory=geolocation clean
	$(MAKE) --directory=glmmadmb clean
	$(MAKE) --directory=globals clean
	$(MAKE) --directory=gmrf clean
	$(MAKE) --directory=gradients_output clean
	$(MAKE) --directory=gtests clean
	$(MAKE) --directory=high_iarray clean
	$(MAKE) --directory=hysimple clean
	$(MAKE) --directory=initializationfunction clean
	$(MAKE) --directory=issue108 clean
	$(MAKE) --directory=lprof clean
	$(MAKE) --directory=mcmc-theta clean
	$(MAKE) --directory=orange_mvn clean
	$(MAKE) --directory=poisp clean
	$(MAKE) --directory=priors clean
	$(MAKE) --directory=qbeta clean
	$(MAKE) --directory=rgamma clean
	$(MAKE) --directory=rsimple clean
	$(MAKE) --directory=simple_mcmc clean
	$(MAKE) --directory=testminmax clean
	$(MAKE) --directory=tiny clean
	$(MAKE) --directory=tiny_ad_fe clean
	$(MAKE) --directory=tiny_ad_re clean
	$(MAKE) --directory=tinyfun clean
	$(MAKE) --directory=vectorize clean
	$(MAKE) --directory=vonmises clean
	$(MAKE) --directory=../examples/admb/prof_like clean

dist-clean:
ifeq ($(CMDSHELL),cmd)
	if exist gtests/googletest-read-only rd /S /Q gtests/googletest-read-only
else
	rm -rvf gtests/googletest-read-only
endif

copy:
ifeq ($(CMDSHELL),cmd)
	if not exist $(DIST)\tests md $(DIST)\tests
	xcopy ..\tests $(DIST)\tests /S /Y /D
else
	cp -Rvf ../tests $(DIST)
endif

outputs.txt:
ifeq ($(CMDSHELL),cmd)
	del /Q ..\\outputs.txt
else
	rm -vf ../outputs.txt
endif
	@echo "# outputs\n" > $(OUTPUT_DIR)outputs.txt
	@echo "# examples outputs\n" >> $(OUTPUT_DIR)outputs.txt
ifeq ($(OS),Windows_NT)
	@fc outputs-examples-opt.txt outputs-examples-saf.txt >> $(OUTPUT_DIR)outputs.txt
	@type outputs-examples-saf.txt >> $(OUTPUT_DIR)outputs.txt
else
	@diff -w outputs-examples-opt.txt outputs-examples-saf.txt >> $(OUTPUT_DIR)outputs.txt
	@cat outputs-examples-saf.txt >> $(OUTPUT_DIR)outputs.txt
endif
	@echo "# tests outputs\n" >> $(OUTPUT_DIR)outputs.txt
	$(MAKE) get-outputs >> $(OUTPUT_DIR)outputs.txt

get-outputs:
	$(MAKE) --directory=4darray get-outputs
	$(MAKE) --directory=agemat get-outputs
	$(MAKE) --directory=altexample get-outputs
	$(MAKE) --directory=adnuts get-outputs
	$(MAKE) --directory=bessel get-outputs
	$(MAKE) --directory=beta2 get-outputs
	$(MAKE) --directory=beta3 get-outputs
	$(MAKE) --directory=beta_deviate get-outputs
	$(MAKE) --directory=betai get-outputs
	$(MAKE) --directory=betareg get-outputs
	$(MAKE) --directory=changepoint get-outputs
	$(MAKE) --directory=colfill get-outputs
	$(MAKE) --directory=cov_re get-outputs
	$(MAKE) --directory=ctl get-outputs
	$(MAKE) --directory=data_adstring_array get-outputs
	$(MAKE) --directory=dd2 get-outputs
	$(MAKE) --directory=dualaveraging get-outputs
	$(MAKE) --directory=expm get-outputs
	$(MAKE) --directory=f1b2vc5 get-outputs
	$(MAKE) --directory=geolocation get-outputs
	$(MAKE) --directory=glmmadmb get-outputs
	$(MAKE) --directory=globals get-outputs
	$(MAKE) --directory=gradients_output get-outputs
	$(MAKE) --directory=high_iarray get-outputs
	$(MAKE) --directory=hysimple get-outputs
	$(MAKE) --directory=initializationfunction get-outputs
	$(MAKE) --directory=issue108 get-outputs
	$(MAKE) --directory=lprof get-outputs
	$(MAKE) --directory=mcmc-theta get-outputs
	$(MAKE) --directory=orange_mvn get-outputs
	$(MAKE) --directory=poisp get-outputs
	$(MAKE) --directory=priors get-outputs
	$(MAKE) --directory=qbeta get-outputs
	$(MAKE) --directory=rgamma get-outputs
	$(MAKE) --directory=rsimple get-outputs
	$(MAKE) --directory=simple_mcmc get-outputs
	$(MAKE) --directory=testminmax get-outputs
	$(MAKE) --directory=tiny get-outputs
	$(MAKE) --directory=tiny_ad_fe get-outputs
	$(MAKE) --directory=tiny_ad_re get-outputs
	$(MAKE) --directory=tinyfun get-outputs
	$(MAKE) --directory=vectorize get-outputs
	$(MAKE) --directory=vonmises get-outputs
