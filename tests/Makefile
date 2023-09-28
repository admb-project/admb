!IFNDEF ADMB_VER
ADMB_VER=admb
!ENDIF

DESTDIR=..\\build\\$(ADMB_VER)

all:\
  test-4darray\
  test-adnuts\
  tpl-alternatives\
  test-altexample\
  test-atan2\
  test-beta2\
  test-beta3\
  test-beta_deviate\
  test-beta_regression\
  test-betai\
  test-betareg\
  test-changepoint\
  test-colfill\
  test-cov_re\
  test-data_adstring_array\
  test-df33_tester\
  test-dualaveraging\
  test-dtweedie\
  test-expm\
  test-f1b2vc5\
  cpp-globals\
  test-gradients_output\
  test-hess_step\
  test-high_iarray\
  test-hysimple\
  test-initializationfunction\
  test-init_bounded_number_matrix\
  test-issue108\
  test-issue158\
  test-lprof\
  test-mcmc-theta\
  test-orange_mvn\
  test-poisp\
  test-qbeta\
  test-rsimple\
  test-simple_mcmc\
  tpl-strip_full_path\
  test-svd\
  test-testminmax\
  test-tiny\
  test-tiny_ad_fe\
  test-tiny_ad_re\
  test-tinyfun\
  test-vectorize\
  test-vonmises

full:\
  test-ctl\
  test-priors\
  test-rgamma\
  test-bessel\
  test-dd2

remotes:\
  test-agemat\
  test-geolocation\
  test-glmmadmb

unit-gtests:
	$(MAKE) test-gtests

test-gtests:
	pushd gtests& $(MAKE) /NOLOGO all & popd

test-initializationfunction:
	pushd initializationfunction & $(MAKE) /NOLOGO & popd

tpl-strip_full_path:
	pushd strip_full_path & $(MAKE) /NOLOGO & popd

cpp-globals:
	pushd globals & $(MAKE) /NOLOGO & popd

test-rgamma:
	pushd rgamma & $(MAKE) /NOLOGO & popd

test-4darray:
	pushd 4darray & $(MAKE) /NOLOGO & popd

test-adnuts:
	pushd adnuts & $(MAKE) /NOLOGO & popd

test-agemat:
	pushd agemat & $(MAKE) /NOLOGO & popd

tpl-alternatives:
	pushd alternatives & $(MAKE) /NOLOGO & popd

test-altexample:
	pushd altexample & $(MAKE) /NOLOGO & popd

test-atan2:
	pushd atan2 & $(MAKE) /NOLOGO & popd

test-bessel:
	pushd bessel & $(MAKE) /NOLOGO & popd

test-beta2:
	pushd beta2 & $(MAKE) /NOLOGO & popd

test-beta3:
	pushd beta3 & $(MAKE) /NOLOGO & popd

test-beta_regression:
	pushd beta_regression & $(MAKE) /NOLOGO & popd

test-hess_step:
	pushd hess_step & $(MAKE) /NOLOGO & popd

test-beta_deviate:
	pushd beta_deviate& $(MAKE) /NOLOGO & popd

test-betai:
	pushd betai& $(MAKE) /NOLOGO & popd

test-betareg:
	pushd betareg & $(MAKE) /NOLOGO & popd

test-ctl:
	pushd ctl & $(MAKE) /NOLOGO & popd

test-colfill:
	pushd colfill & $(MAKE) /NOLOGO & popd

test-changepoint:
	pushd changepoint & $(MAKE) /NOLOGO & popd

test-cov_re:
	pushd cov_re & $(MAKE) /NOLOGO & popd

test-data_adstring_array:
	pushd data_adstring_array& $(MAKE) /NOLOGO & popd

test-df33_tester:
	pushd df33_tester & $(MAKE) /NOLOGO & popd

test-dd2:
	pushd dd2 & $(MAKE) /NOLOGO & popd

test-dualaveraging:
	pushd dualaveraging & $(MAKE) /NOLOGO & popd

test-dtweedie:
	pushd dtweedie& $(MAKE) /NOLOGO & popd

test-expm:
	pushd expm & $(MAKE) /NOLOGO & popd

test-f1b2vc5 :
	pushd f1b2vc5 & $(MAKE) /NOLOGO & popd

test-geolocation:
	pushd geolocation & $(MAKE) /NOLOGO & popd

test-glmmadmb:
	pushd glmmadmb & $(MAKE) /NOLOGO & popd

test-gmrf:
	pushd gmrf & $(MAKE) /NOLOGO & popd

test-gradients_output:
	pushd gradients_output & $(MAKE) /NOLOGO & popd

test-high_iarray:
	pushd high_iarray & $(MAKE) /NOLOGO & popd

test-hysimple:
	pushd hysimple & $(MAKE) /NOLOGO & popd

test-init_bounded_number_matrix:
	pushd init_bounded_number_matrix & $(MAKE) /NOLOGO & popd

test-issue108:
	pushd issue108 & $(MAKE) /NOLOGO & popd

test-issue158:
	pushd issue158 & $(MAKE) /NOLOGO & popd

test-lprof:
	pushd lprof & $(MAKE) /NOLOGO & popd

test-mcmc-theta:
	pushd mcmc-theta & $(MAKE) /NOLOGO & popd

test-orange_mvn:
	pushd orange_mvn & $(MAKE) /NOLOGO & popd

test-poisp:
	pushd poisp & $(MAKE) /NOLOGO & popd

test-priors:
	pushd priors & $(MAKE) /NOLOGO & popd

test-qbeta:
	pushd qbeta & $(MAKE) /NOLOGO & popd

test-rsimple:
	pushd rsimple & $(MAKE) /NOLOGO & popd

test-simple_mcmc:
	pushd simple_mcmc & $(MAKE) /NOLOGO & popd

test-svd:
	pushd svd & $(MAKE) /NOLOGO & popd

test-testminmax:
	pushd testminmax & $(MAKE) /NOLOGO & popd

test-tiny_ad_fe:
	pushd tiny_ad_fe & $(MAKE) /NOLOGO & popd

test-tiny_ad_re:
	pushd tiny_ad_re & $(MAKE) /NOLOGO & popd

test-tinyfun:
	pushd tinyfun & $(MAKE) /NOLOGO & popd

test-tiny:
	pushd tiny & $(MAKE) /NOLOGO & popd

test-vectorize:
	pushd vectorize & $(MAKE) /NOLOGO & popd

test-vonmises:
	pushd vonmises & $(MAKE) /NOLOGO & popd

total-clean: clean
	pushd glmmadmb & $(MAKE) /NOLOGO total-clean & popd
	pushd geolocation & $(MAKE) /NOLOGO total-clean & popd
	pushd agemat & $(MAKE) /NOLOGO total-clean & popd

clean:
	if exist SS3 rmdir /s /q SS3
	pushd 4darray & $(MAKE) /NOLOGO clean & popd
	pushd adnuts & $(MAKE) /NOLOGO clean & popd
	pushd agemat & $(MAKE) /NOLOGO clean & popd
	pushd altexample & $(MAKE) /NOLOGO clean & popd
	pushd atan2 & $(MAKE) /NOLOGO clean & popd
	pushd bessel & $(MAKE) /NOLOGO clean & popd
	pushd beta2 & $(MAKE) /NOLOGO clean & popd
	pushd beta3 & $(MAKE) /NOLOGO clean & popd
	pushd beta_deviate & $(MAKE) /NOLOGO clean & popd
	pushd beta_regression & $(MAKE) /NOLOGO clean & popd
	pushd betai & $(MAKE) /NOLOGO clean & popd
	pushd betareg & $(MAKE) /NOLOGO clean & popd
	pushd changepoint & $(MAKE) /NOLOGO clean & popd
	pushd colfill & $(MAKE) /NOLOGO clean & popd
	pushd cov_re & $(MAKE) /NOLOGO clean & popd
	pushd ctl & $(MAKE) /NOLOGO clean & popd
	pushd data_adstring_array & $(MAKE) /NOLOGO clean & popd
	pushd dd2 & $(MAKE) /NOLOGO clean & popd
	pushd dualaveraging & $(MAKE) /NOLOGO clean & popd
	pushd dtweedie & $(MAKE) /NOLOGO clean & popd
	pushd df33_tester & $(MAKE) /NOLOGO clean & popd
	pushd expm & $(MAKE) /NOLOGO clean & popd
	pushd f1b2vc5 & $(MAKE) /NOLOGO clean & popd
	pushd geolocation & $(MAKE) /NOLOGO clean & popd
	pushd gradients_output & $(MAKE) /NOLOGO clean & popd
	pushd gtests & $(MAKE) /NOLOGO clean & popd
	pushd high_iarray & $(MAKE) /NOLOGO clean & popd
	pushd hysimple & $(MAKE) /NOLOGO clean & popd
	pushd init_bounded_number_matrix & $(MAKE) /NOLOGO clean & popd
	pushd issue108 & $(MAKE) /NOLOGO clean & popd
	pushd lprof & $(MAKE) /NOLOGO clean & popd
	pushd mcmc-theta & $(MAKE) /NOLOGO clean & popd
	pushd orange_mvn & $(MAKE) /NOLOGO clean & popd
	pushd poisp & $(MAKE) /NOLOGO clean & popd
	pushd priors & $(MAKE) /NOLOGO clean & popd
	pushd qbeta & $(MAKE) /NOLOGO clean & popd
	pushd rsimple & $(MAKE) /NOLOGO clean & popd
	pushd simple_mcmc & $(MAKE) /NOLOGO clean & popd
	pushd svd & $(MAKE) /NOLOGO clean & popd
	pushd testminmax & $(MAKE) /NOLOGO clean & popd
	pushd tiny & $(MAKE) /NOLOGO clean & popd
	pushd tiny_ad_fe & $(MAKE) /NOLOGO clean & popd
	pushd tiny_ad_re & $(MAKE) /NOLOGO clean & popd
	pushd tinyfun & $(MAKE) /NOLOGO clean & popd
	pushd vectorize & $(MAKE) /NOLOGO clean & popd
	pushd vonmises & $(MAKE) /NOLOGO clean & popd

verify: examples
!IF DEFINED(TESTS_REMOTE)
	$(MAKE) /NOLOGO test-gtests
!ELSE
	$(MAKE) /NOLOGO all
	$(MAKE) /NOLOGO test-gtests
!ENDIF
	$(MAKE) /NOLOGO outputs.txt

examples:
	if not exist $(DESTDIR)\\examples md $(DESTDIR)\\examples
	xcopy ..\\examples $(DESTDIR)\\examples /S /Y /D
	pushd $(DESTDIR)\\examples && $(MAKE) /NOLOGO all
	pushd $(DESTDIR)\\examples && $(MAKE) /NOLOGO get-outputs > ..\\..\\..\\tests\\outputs-examples-saf.txt
!IFNDEF SAFE_ONLY
	pushd $(DESTDIR)\\examples && $(MAKE) /NOLOGO FAST_OPTION=-f all
	pushd $(DESTDIR)\\examples && $(MAKE) /NOLOGO get-outputs > ..\\..\\..\\tests\\outputs-examples-opt.txt
!ENDIF

copy:
	IF NOT EXIST $(DESTDIR)\tests xcopy /I /E /Y ..\tests $(DESTDIR)\tests

outputs.txt:
	@if exist ..\\outputs.txt del /Q ..\\outputs.txt
	@echo ^# outputs > ..\\outputs.txt
!IF EXISTS(outputs-examples-saf.txt)
!IF EXISTS(outputs-examples-opt.txt)
	@echo ^# examples diff >> ..\\outputs.txt
	@fc outputs-examples-opt.txt outputs-examples-saf.txt >> ..\\outputs.txt
!ENDIF
	@echo ^# examples outputs >> ..\\outputs.txt
	@type outputs-examples-saf.txt >> ..\\outputs.txt
!ENDIF
	@echo ^# tests outputs >> ..\\outputs.txt
	$(MAKE) /NOLOGO get-outputs >> ..\\outputs.txt

no-get-outputs:
	@pushd bessel & $(MAKE) /NOLOGO get-outputs & popd
	@pushd dd2 & $(MAKE) /NOLOGO get-outputs & popd
	@pushd qbeta & $(MAKE) /NOLOGO get-outputs & popd
	@pushd rgamma & $(MAKE) /NOLOGO get-outputs & popd
	@pushd globals & $(MAKE) /NOLOGO get-outputs & popd

get-outputs:
	@pushd 4darray & $(MAKE) /NOLOGO get-outputs & popd
	@pushd agemat & $(MAKE) /NOLOGO get-outputs & popd
	@pushd altexample & $(MAKE) /NOLOGO get-outputs & popd
	@REM pushd alternatives & $(MAKE) /NOLOGO get-outputs & popd
	@pushd adnuts & $(MAKE) /NOLOGO get-outputs & popd
	@pushd beta2 & $(MAKE) /NOLOGO get-outputs & popd
	@pushd beta3 & $(MAKE) /NOLOGO get-outputs & popd
	@pushd beta_deviate & $(MAKE) /NOLOGO get-outputs & popd
	@pushd beta_regression & $(MAKE) /NOLOGO get-outputs & popd
	@pushd betai & $(MAKE) /NOLOGO get-outputs & popd
	@pushd betareg & $(MAKE) /NOLOGO get-outputs & popd
	@pushd changepoint & $(MAKE) /NOLOGO get-outputs & popd
	@pushd colfill & $(MAKE) /NOLOGO get-outputs & popd
	@pushd cov_re & $(MAKE) /NOLOGO get-outputs & popd
	@pushd ctl & $(MAKE) /NOLOGO get-outputs & popd
	@pushd data_adstring_array & $(MAKE) /NOLOGO get-outputs & popd
	@pushd dualaveraging & $(MAKE) /NOLOGO get-outputs & popd
	@pushd expm & $(MAKE) /NOLOGO get-outputs & popd
	@pushd f1b2vc5 & $(MAKE) /NOLOGO get-outputs & popd
	@pushd geolocation & $(MAKE) /NOLOGO get-outputs & popd
	@REM pushd glmmadmb & $(MAKE) /NOLOGO get-outputs & popd
	@pushd gradients_output & $(MAKE) /NOLOGO get-outputs & popd
	@pushd hess_step & $(MAKE) /NOLOGO get-outputs & popd
	@pushd high_iarray & $(MAKE) /NOLOGO get-outputs & popd
	@pushd hysimple & $(MAKE) /NOLOGO get-outputs & popd
	@pushd initializationfunction & $(MAKE) /NOLOGO get-outputs & popd
	@pushd init_bounded_number_matrix & $(MAKE) /NOLOGO get-outputs & popd
	@pushd issue108 & $(MAKE) /NOLOGO get-outputs & popd
	@pushd mcmc-theta & $(MAKE) /NOLOGO get-outputs & popd
	@pushd orange_mvn & $(MAKE) /NOLOGO get-outputs & popd
	@pushd poisp & $(MAKE) /NOLOGO get-outputs & popd
	@pushd priors & $(MAKE) /NOLOGO get-outputs & popd
	@pushd rsimple & $(MAKE) /NOLOGO get-outputs & popd
	@pushd simple_mcmc & $(MAKE) /NOLOGO get-outputs & popd
	@pushd svd & $(MAKE) /NOLOGO get-outputs & popd
	@pushd testminmax & $(MAKE) /NOLOGO get-outputs & popd
	@pushd tiny & $(MAKE) /NOLOGO get-outputs & popd
	@pushd tiny_ad_fe & $(MAKE) /NOLOGO get-outputs & popd
	@pushd tiny_ad_re & $(MAKE) /NOLOGO get-outputs & popd
	@pushd tinyfun & $(MAKE) /NOLOGO get-outputs & popd
	@pushd vectorize & $(MAKE) /NOLOGO get-outputs & popd
	@pushd vonmises & $(MAKE) /NOLOGO get-outputs & popd
	@pushd atan2 & $(MAKE) /NOLOGO get-outputs & popd
	@pushd df33_tester & $(MAKE) /NOLOGO get-outputs & popd
	@pushd lprof & $(MAKE) /NOLOGO get-outputs & popd
