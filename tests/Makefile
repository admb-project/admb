!IFNDEF ADMB_VER
ADMB_VER=admb
!ENDIF

DESTDIR=..\build\$(ADMB_VER)

all:\
  test-4darray\
  test-adnuts\
  test-agemat\
  test-altexample\
  test-bessel\
  test-beta2\
  test-beta3\
  test-beta_deviate\
  test-beta_regression\
  test-betai\
  test-betareg\
  test-changepoint\
  test-colfill\
  test-cov_re\
  test-ctl\
  test-data_adstring_array\
  test-dd2\
  test-dualaveraging\
  test-expm\
  test-f1b2vc5\
  test-geolocation\
  test-gradients_output\
  test-high_iarray\
  test-hysimple\
  test-initializationfunction\
  test-issue108\
  test-lprof\
  test-mcmc-theta\
  test-orange_mvn\
  test-poisp\
  test-priors\
  test-qbeta\
  test-rsimple\
  test-simple_mcmc\
  test-testminmax\
  test-tiny\
  test-tiny_ad_fe\
  test-tiny_ad_re\
  test-tinyfun\
  test-vectorize\
  test-vonmises\
  test-gtests

test-gtests:
	pushd gtests& $(MAKE) all & popd

test-initializationfunction:
	pushd initializationfunction & $(MAKE) & popd

test-4darray:
	pushd 4darray & $(MAKE) & popd

test-adnuts:
	pushd adnuts & $(MAKE) & popd

test-agemat:
	pushd agemat & $(MAKE) & popd

test-altexample:
	pushd altexample & $(MAKE) & popd

test-bessel:
	pushd bessel & $(MAKE) & popd

test-beta2:
	pushd beta2 & $(MAKE) & popd

test-beta3:
	pushd beta3 & $(MAKE) & popd

test-beta_regression:
	pushd beta_regression & $(MAKE) & popd

test-beta_deviate:
	pushd beta_deviate& $(MAKE) & popd

test-betai:
	pushd betai& $(MAKE) & popd

test-betareg:
	pushd betareg & $(MAKE) & popd

test-ctl:
	pushd ctl & $(MAKE) & popd

test-changepoint:
	pushd changepoint & $(MAKE) & popd

test-cov_re:
	pushd cov_re & $(MAKE) & popd

test-data_adstring_array:
	pushd data_adstring_array& $(MAKE) & popd

test-dd2:
	pushd dd2 & $(MAKE) & popd

test-dualaveraging:
	pushd dualaveraging & $(MAKE) & popd

test-expm:
	pushd expm & $(MAKE) & popd

test-f1b2vc5 :
	pushd f1b2vc5 & $(MAKE) & popd

test-geolocation:
	pushd geolocation & $(MAKE) & popd

test-gradients_output:
	pushd gradients_output & $(MAKE) & popd

test-high_iarray:
	pushd high_iarray & $(MAKE) & popd

test-hysimple:
	pushd hysimple & $(MAKE) & popd

test-issue108:
	pushd issue108 & $(MAKE) & popd

test-lprof:
	pushd lprof & $(MAKE) & popd

test-mcmc-theta:
	pushd mcmc-theta & $(MAKE) & popd

test-orange_mvn:
	pushd orange_mvn & $(MAKE) & popd

test-poisp:
	pushd poisp & $(MAKE) & popd

test-priors:
	pushd priors & $(MAKE) & popd

test-qbeta:
	pushd qbeta & $(MAKE) & popd

test-rsimple:
	pushd rsimple & $(MAKE) & popd

test-simple_mcmc:
	pushd simple_mcmc & $(MAKE) & popd

test-testminmax:
	pushd testminmax & $(MAKE) & popd

test-tiny_ad_fe:
	pushd tiny_ad_fe & $(MAKE) & popd

test-tiny_ad_re:
	pushd tiny_ad_re & $(MAKE) & popd

test-tinyfun:
	pushd tinyfun & $(MAKE) & popd

test-tiny:
	pushd tiny & $(MAKE) & popd

test-vectorize:
	pushd vectorize & $(MAKE) & popd

test-vonmises:
	pushd vonmises & $(MAKE) & popd

total-clean: clean
	-pushd glmmadmb & $(MAKE) total-clean & popd
	pushd geolocation & $(MAKE) total-clean & popd
	pushd agemat & $(MAKE) total-clean & popd

clean:
	if exist SS3 rmdir /s /q SS3
	pushd 4darray & $(MAKE) clean & popd
	pushd adnuts & $(MAKE) clean & popd
	pushd agemat & $(MAKE) clean & popd
	pushd altexample & $(MAKE) clean & popd
	pushd bessel & $(MAKE) clean & popd
	pushd beta2 & $(MAKE) clean & popd
	pushd beta3 & $(MAKE) clean & popd
	pushd beta_deviate & $(MAKE) clean & popd
	pushd beta_regression & $(MAKE) clean & popd
	pushd betai & $(MAKE) clean & popd
	pushd betareg & $(MAKE) clean & popd
	pushd changepoint & $(MAKE) clean & popd
	pushd colfill & $(MAKE) clean & popd
	pushd cov_re & $(MAKE) clean & popd
	pushd ctl & $(MAKE) clean & popd
	pushd data_adstring_array & $(MAKE) clean & popd
	pushd dd2 & $(MAKE) clean & popd
	pushd dualaveraging & $(MAKE) clean & popd
	pushd expm & $(MAKE) clean & popd
	pushd f1b2vc5 & $(MAKE) clean & popd
	pushd geolocation & $(MAKE) clean & popd
	pushd gradients_output & $(MAKE) clean & popd
	pushd gtests & $(MAKE) clean & popd
	pushd high_iarray & $(MAKE) clean & popd
	pushd hysimple & $(MAKE) clean & popd
	pushd issue108 & $(MAKE) clean & popd
	pushd lprof & $(MAKE) clean & popd
	pushd mcmc-theta & $(MAKE) clean & popd
	pushd orange_mvn & $(MAKE) clean & popd
	pushd poisp & $(MAKE) clean & popd
	pushd priors & $(MAKE) clean & popd
	pushd qbeta & $(MAKE) clean & popd
	pushd rsimple & $(MAKE) clean & popd
	pushd simple_mcmc & $(MAKE) clean & popd
	pushd testminmax & $(MAKE) clean & popd
	pushd tiny & $(MAKE) clean & popd
	pushd tiny_ad_fe & $(MAKE) clean & popd
	pushd tiny_ad_re & $(MAKE) clean & popd
	pushd tinyfun & $(MAKE) clean & popd
	pushd vectorize & $(MAKE) clean & popd
	pushd vonmises & $(MAKE) clean & popd

verify: examples
	$(MAKE) all
	$(MAKE) get-outputs

examples:
	del ..\outputs-saf.txt
	del ..\outputs-opt.txt
	if not exist $(DESTDIR)\examples md  $(DESTDIR)\examples
	xcopy ..\examples $(DESTDIR)\examples  /S /Y /D
	pushd $(DESTDIR)\examples & $(MAKE) all
	pushd $(DESTDIR) & ..\..\scripts\get-outputs.bat > "..\..\outputs-saf.txt" & popd
!IFNDEF SAFE_ONLY
	pushd $(DESTDIR)\examples & $(MAKE) FAST_OPTION=-f all
	pushd $(DESTDIR) & ..\..\scripts\get-outputs.bat > "..\..\outputs-opt.txt" & popd
!ENDIF

copy:
	IF NOT EXIST $(DESTDIR)\tests xcopy /I /E /Y ..\tests $(DESTDIR)\tests

get-outputs:
	del ..\\outputs.txt
	@echo "# tests outputs\n" > ..\\outputs.txt
	pushd 4darray & $(MAKE) get-outputs >> ..\outputs.txt
	pushd agemat & $(MAKE) get-outputs >> ..\outputs.txt
	pushd altexample & $(MAKE) get-outputs >> ..\outputs.txt
	pushd adnuts & $(MAKE) get-outputs >> ..\outputs.txt
	pushd bessel & $(MAKE) get-outputs >> ..\outputs.txt
	pushd beta2 & $(MAKE) get-outputs >> ..\outputs.txt
	pushd beta3 & $(MAKE) get-outputs >> ..\outputs.txt
	pushd beta_deviate & $(MAKE) get-outputs >> ..\outputs.txt
	pushd beta_regression & $(MAKE) get-outputs >> ..\outputs.txt
	pushd betai & $(MAKE) get-outputs >> ..\outputs.txt
	pushd betareg & $(MAKE) get-outputs >> ..\outputs.txt
	pushd changepoint & $(MAKE) get-outputs >> ..\outputs.txt
	pushd colfill & $(MAKE) get-outputs >> ..\outputs.txt
	pushd cov_re & $(MAKE) get-outputs >> ..\outputs.txt
	pushd ctl & $(MAKE) get-outputs >> ..\outputs.txt
	pushd data_adstring_array & $(MAKE) get-outputs >> ..\outputs.txt
	pushd dd2 & $(MAKE) get-outputs >> ..\outputs.txt
	pushd dualaveraging & $(MAKE) get-outputs >> ..\outputs.txt
	pushd expm & $(MAKE) get-outputs >> ..\outputs.txt
	pushd f1b2vc5 & $(MAKE) get-outputs >> ..\outputs.txt
	pushd geolocation & $(MAKE) get-outputs >> ..\outputs.txt
	pushd high_iarray & $(MAKE) get-outputs >> ..\outputs.txt
	pushd hysimple & $(MAKE) get-outputs >> ..\outputs.txt
	pushd initializationfunction & $(MAKE) get-outputs >> ..\outputs.txt
	pushd issue108 & $(MAKE) get-outputs >> ..\outputs.txt
	pushd lprof & $(MAKE) get-outputs >> ..\outputs.txt
	pushd mcmc-theta & $(MAKE) get-outputs >> ..\outputs.txt
	pushd orange_mvn & $(MAKE) get-outputs >> ..\outputs.txt
	pushd poisp & $(MAKE) get-outputs >> ..\outputs.txt
	pushd priors & $(MAKE) get-outputs >> ..\outputs.txt
	pushd qbeta & $(MAKE) get-outputs >> ..\outputs.txt
	pushd rgamma & $(MAKE) get-outputs >> ..\outputs.txt
	pushd rsimple & $(MAKE) get-outputs >> ..\outputs.txt
	pushd simple_mcmc & $(MAKE) get-outputs >> ..\outputs.txt
	pushd testminmax & $(MAKE) get-outputs >> ..\outputs.txt
	pushd tiny & $(MAKE) get-outputs >> ..\outputs.txt
	pushd tiny_ad_fe & $(MAKE) get-outputs >> ..\outputs.txt
	pushd tiny_ad_re & $(MAKE) get-outputs >> ..\outputs.txt
	pushd tinyfun & $(MAKE) get-outputs >> ..\outputs.txt
	pushd vectorize & $(MAKE) get-outputs >> ..\outputs.txt
	pushd vonmises & $(MAKE) get-outputs >> ..\outputs.txt
