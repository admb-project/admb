ifndef TESTS_REMOTE
  TESTS_REMOTE=no
endif

ifndef ADMB_VER
  ADMB_VER=admb
endif

ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifndef TERM
      export SHELL=cmd
      CMDSHELL=cmd
    endif
    ifndef CMDSHELL
      EXT=.sh
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
	$(MAKE) examples
	$(MAKE) tests-core
	$(MAKE) tests-contrib
	$(MAKE) outputs.txt
	$(MAKE) unit-gtests

verify:
	$(MAKE) all

full:
	$(MAKE) tests-remote
	$(MAKE) tpl-bessel
	$(MAKE) tpl-dd2

tests-remote:
	$(MAKE) remote-core-tpls
	$(MAKE) remote-contrib-tpls

tests-core:
	$(MAKE) core-tpls

tests-contrib:
	$(MAKE) contrib-tpls

coverage:
	$(MAKE) core-tpls
	$(MAKE) unit-gtests

unit-gtests:
	$(MAKE) --directory=gtests

test-rgamma:
	$(MAKE) --directory=rgamma

core-tpls:\
  tpl-4darray\
  tpl-adnuts\
  tpl-alternatives\
  tpl-altexample\
  tpl-atan2\
  tpl-beta2\
  tpl-beta3\
  tpl-beta_deviate\
  tpl-beta_regression\
  tpl-betai\
  tpl-betareg\
  tpl-changepoint\
  tpl-colfill\
  tpl-cov_re\
  tpl-data_adstring_array\
  tpl-df33_tester\
  tpl-dualaveraging\
  tpl-dtweedie\
  tpl-expm\
  tpl-f1b2vc5\
  cpp-globals\
  tpl-gradients_output\
  tpl-hess_step\
  tpl-high_iarray\
  tpl-hysimple\
  tpl-initializationfunction\
  tpl-init_bounded_number_matrix\
  tpl-issue108\
  tpl-issue158\
  tpl-lprof\
  tpl-mcmc-theta\
  tpl-orange_mvn\
  tpl-poisp\
  tpl-qbeta\
  tpl-rsimple\
  tpl-simple_mcmc\
  tpl-strip_full_path\
  tpl-svd\
  tpl-testminmax\
  tpl-tiny\
  tpl-tiny_ad_fe\
  tpl-tiny_ad_re\
  tpl-tinyfun\
  tpl-vectorize\
  tpl-vonmises

remote-core-tpls:\
  tpl-geolocation\
  tpl-glmmadmb

contrib-tpls:\
  tpl-ctl\
  tpl-priors\
  test-rgamma

remote-contrib-tpls:
ifneq ($(CMDSHELL),cmd)
	$(MAKE) tpl-agemat
endif

tpl-alternatives:
	$(MAKE) --directory=alternatives

tpl-strip_full_path:
	$(MAKE) --directory=strip_full_path

cpp-globals:
	$(MAKE) --directory=globals

tpl-issue158:
	$(MAKE) --directory=issue158

tpl-f1b2vc5:
	$(MAKE) --directory=f1b2vc5

tpl-4darray:
	$(MAKE) --directory=4darray

tpl-glmmadmb:
	$(MAKE) --directory=glmmadmb

tpl-agemat:
	$(MAKE) --directory=agemat

tpl-altexample:
	$(MAKE) --directory=altexample

tpl-atan2:
	$(MAKE) --directory=atan2

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

tpl-df33_tester:
	$(MAKE) --directory=df33_tester

tpl-dd2:
	$(MAKE) --directory=dd2

tpl-dualaveraging:
	$(MAKE) --directory=dualaveraging

tpl-data_adstring_array:
	$(MAKE) --directory=data_adstring_array

tpl-dtweedie:
	$(MAKE) --directory=dtweedie

tpl-beta_deviate:
	$(MAKE) --directory=beta_deviate

tpl-betareg:
	$(MAKE) --directory=betareg

tpl-beta_regression:
	$(MAKE) --directory=beta_regression

tpl-hess_step:
	$(MAKE) --directory=hess_step

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

tpl-init_bounded_number_matrix:
	$(MAKE) --directory=init_bounded_number_matrix

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

tpl-svd:
	$(MAKE) --directory=svd

tpl-testminmax:
	$(MAKE) --directory=testminmax

tpl-mcmc-theta:
	$(MAKE) --directory=mcmc-theta

tpl-orange_mvn:
	$(MAKE) --directory=orange_mvn

tpl-lprof:
	$(MAKE) --directory=lprof

examples:
ifeq ($(CMDSHELL),cmd)
	if exist $(DIST)\\examples rmdir /s /q $(DIST)\\examples
	md $(DIST)\\examples
	xcopy ..\\examples $(DIST)\examples /S /Y /D
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)\\examples all
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)\\examples bhplfine
	@$(MAKE) --no-print-directory DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)\\examples get-outputs > outputs-examples-saf.txt
  ifndef SAFE_ONLY
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)\\examples all
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)\\examples bhplfine
	@$(MAKE) --no-print-directory DEBUG_OPTION=$(DEBUG_OPTION) -C $(DIST)\\examples get-outputs > outputs-examples-opt.txt
  endif
else
	if [ -d "$(DIST)/examples" ]; then rm -rvf $(DIST)/examples; fi
	cp -Rvf ../examples $(DIST)
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) --directory=$(DIST)/examples all
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) --directory=$(DIST)/examples bhplfine
	$(MAKE) --no-print-directory DEBUG_OPTION=$(DEBUG_OPTION) --directory=$(DIST)/examples get-outputs > outputs-examples-saf.txt
  ifndef SAFE_ONLY
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)/examples all
	$(MAKE) DEBUG_OPTION=$(DEBUG_OPTION) FAST_OPTION=-f -C $(DIST)/examples bhplfine
	$(MAKE) --no-print-directory DEBUG_OPTION=$(DEBUG_OPTION) --directory=$(DIST)/examples get-outputs > outputs-examples-opt.txt
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
	@if exist outputs-examples-opt.txt del /Q outputs-examples-opt.txt 2> nul
	@if exist outputs-examples-saf.txt del /Q outputs-examples-saf.txt 2> nul
else
	@rm -rvf SS3
	@rm -vf outputs-examples-opt.txt
	@rm -vf outputs-examples-saf.txt
endif
	$(MAKE) --directory=4darray clean
	$(MAKE) --directory=adnuts clean
	$(MAKE) --directory=agemat clean
	$(MAKE) --directory=altexample clean
	$(MAKE) --directory=alternatives clean
	$(MAKE) --directory=atan2 clean
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
	$(MAKE) --directory=df33_tester clean
	$(MAKE) --directory=dualaveraging clean
	$(MAKE) --directory=dtweedie clean
	$(MAKE) --directory=expm clean
	$(MAKE) --directory=f1b2vc5 clean
	$(MAKE) --directory=geolocation clean
	$(MAKE) --directory=glmmadmb clean
	$(MAKE) --directory=globals clean
	$(MAKE) --directory=gmrf clean
	$(MAKE) --directory=gradients_output clean
	$(MAKE) --directory=gtests clean
	$(MAKE) --directory=hess_step clean
	$(MAKE) --directory=high_iarray clean
	$(MAKE) --directory=hysimple clean
	$(MAKE) --directory=initializationfunction clean
	$(MAKE) --directory=init_bounded_number_matrix clean
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
	$(MAKE) --directory=strip_full_path clean
	$(MAKE) --directory=svd clean
	$(MAKE) --directory=testminmax clean
	$(MAKE) --directory=tiny clean
	$(MAKE) --directory=tiny_ad_fe clean
	$(MAKE) --directory=tiny_ad_re clean
	$(MAKE) --directory=tinyfun clean
	$(MAKE) --directory=vectorize clean
	$(MAKE) --directory=vonmises clean
	$(MAKE) --directory=issue158 clean
	$(MAKE) --directory=dd2 clean

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
	@echo "# outputs\n" > $(OUTPUT_DIR)outputs.txt
ifeq ($(CMDSHELL),cmd)
  ifndef SAFE_ONLY
	echo "# examples diff\n" >> $(OUTPUT_DIR)outputs.txt;
	fc outputs-examples-opt.txt outputs-examples-saf.txt >> $(OUTPUT_DIR)outputs.txt
  endif
	echo "# examples outputs\n" >> $(OUTPUT_DIR)outputs.txt;
	type outputs-examples-saf.txt >> $(OUTPUT_DIR)outputs.txt
else
  ifndef SAFE_ONLY
	echo "# examples diff\n" >> $(OUTPUT_DIR)outputs.txt;
	-diff -a -w outputs-examples-opt.txt outputs-examples-saf.txt >> $(OUTPUT_DIR)outputs.txt
  endif
	echo "# examples outputs\n" >> $(OUTPUT_DIR)outputs.txt;
	cat outputs-examples-saf.txt >> $(OUTPUT_DIR)outputs.txt;
endif
	@echo "# tests outputs\n" >> $(OUTPUT_DIR)outputs.txt
	@$(MAKE) --no-print-directory get-outputs >> $(OUTPUT_DIR)outputs.txt

no-get-outputs:
	@$(MAKE) --no-print-directory --directory=bessel get-outputs
	@$(MAKE) --no-print-directory --directory=dd2 get-outputs
	@$(MAKE) --no-print-directory --directory=qbeta get-outputs
	@$(MAKE) --no-print-directory --directory=rgamma get-outputs
	@$(MAKE) --no-print-directory --directory=globals get-outputs

get-outputs:
	@$(MAKE) --no-print-directory --directory=4darray get-outputs
	@$(MAKE) --no-print-directory --directory=agemat get-outputs
	@$(MAKE) --no-print-directory --directory=altexample get-outputs
	@$(MAKE) --no-print-directory --directory=alternatives get-outputs
	@$(MAKE) --no-print-directory --directory=adnuts get-outputs
	@$(MAKE) --no-print-directory --directory=beta2 get-outputs
	@$(MAKE) --no-print-directory --directory=beta3 get-outputs
	@$(MAKE) --no-print-directory --directory=beta_deviate get-outputs
	@$(MAKE) --no-print-directory --directory=beta_regression get-outputs
	@$(MAKE) --no-print-directory --directory=betai get-outputs
	@$(MAKE) --no-print-directory --directory=betareg get-outputs
	@$(MAKE) --no-print-directory --directory=changepoint get-outputs
	@$(MAKE) --no-print-directory --directory=colfill get-outputs
	@$(MAKE) --no-print-directory --directory=cov_re get-outputs
	@$(MAKE) --no-print-directory --directory=ctl get-outputs
	@$(MAKE) --no-print-directory --directory=data_adstring_array get-outputs
	@$(MAKE) --no-print-directory --directory=dualaveraging get-outputs
	@$(MAKE) --no-print-directory --directory=expm get-outputs
	@$(MAKE) --no-print-directory --directory=f1b2vc5 get-outputs
	@$(MAKE) --no-print-directory --directory=geolocation get-outputs
	@$(MAKE) --no-print-directory --directory=glmmadmb get-outputs
	@$(MAKE) --no-print-directory --directory=gradients_output get-outputs
	@$(MAKE) --no-print-directory --directory=hess_step get-outputs
	@$(MAKE) --no-print-directory --directory=high_iarray get-outputs
	@$(MAKE) --no-print-directory --directory=hysimple get-outputs
	@$(MAKE) --no-print-directory --directory=initializationfunction get-outputs
	@$(MAKE) --no-print-directory --directory=init_bounded_number_matrix get-outputs
	@$(MAKE) --no-print-directory --directory=issue108 get-outputs
	@$(MAKE) --no-print-directory --directory=mcmc-theta get-outputs
	@$(MAKE) --no-print-directory --directory=orange_mvn get-outputs
	@$(MAKE) --no-print-directory --directory=poisp get-outputs
	@$(MAKE) --no-print-directory --directory=priors get-outputs
	@$(MAKE) --no-print-directory --directory=rsimple get-outputs
	@$(MAKE) --no-print-directory --directory=simple_mcmc get-outputs
	@$(MAKE) --no-print-directory --directory=svd get-outputs
	@$(MAKE) --no-print-directory --directory=testminmax get-outputs
	@$(MAKE) --no-print-directory --directory=tiny get-outputs
	@$(MAKE) --no-print-directory --directory=tiny_ad_fe get-outputs
	@$(MAKE) --no-print-directory --directory=tiny_ad_re get-outputs
	@$(MAKE) --no-print-directory --directory=tinyfun get-outputs
	@$(MAKE) --no-print-directory --directory=vectorize get-outputs
	@$(MAKE) --no-print-directory --directory=vonmises get-outputs
	@$(MAKE) --no-print-directory --directory=atan2 get-outputs
	@$(MAKE) --no-print-directory --directory=df33_tester get-outputs
	@$(MAKE) --no-print-directory --directory=lprof get-outputs
