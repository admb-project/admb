!IFNDEF ADMB_VER
ADMB_VER=admb
!ENDIF

DESTDIR=..\build\$(ADMB_VER)

all:\
  test-4darray\
  test-adnuts\
  test-agemat\
  test-bessel\
  test-beta_regression\
  test-betareg\
  test-cov_re\
  test-ctl\
  test-changepoint\
  test-dd2\
  test-expm\
  test-high_iarray\
  test-hysimple\
  test-lprof\
  test-mcmc-theta\
  test-orange_mvn\
  test-poisp\
  test-priors\
  test-qbeta\
  test-simple_mcmc\
  test-testminmax\
  test-tiny_ad_fe\
  test-tiny_ad_re\
  test-tinyfun\
  test-vectorize\
  test-vonmises\
  test-gtests

test-gtests:
	pushd gtests& $(MAKE) all & popd

test-4darray:
	pushd 4darray & $(MAKE) & popd

test-adnuts:
	pushd adnuts & $(MAKE) & popd

test-agemat:
	pushd agemat& $(MAKE) & popd

test-bessel:
	pushd bessel & $(MAKE) & popd

test-ctl:
	pushd ctl & $(MAKE) & popd

test-changepoint:
	pushd changepoint & $(MAKE) & popd

test-cov_re:
	pushd cov_re & $(MAKE) & popd

test-dd2:
	pushd dd2 & $(MAKE) & popd

test-expm:
	pushd expm & $(MAKE) & popd

test-geolocation:
	pushd geolocation & $(MAKE) & popd

test-high_iarray:
	pushd high_iarray & $(MAKE) & popd

test-hysimple:
	pushd hysimple & $(MAKE) & popd

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

test-vectorize:
	pushd vectorize & $(MAKE) & popd

test-vonmises:
	pushd vonmises & $(MAKE) & popd

total-clean: clean
	pushd glmmadmb & $(MAKE) total-clean & popd
	pushd geolocation & $(MAKE) total-clean & popd
	pushd agemat & $(MAKE) total-clean & popd

clean:
	pushd gtests & $(MAKE) clean & popd
	pushd 4darray & $(MAKE) clean & popd
	pushd adnuts & $(MAKE) clean & popd
	pushd agemat& $(MAKE) clean & popd
	pushd bessel & $(MAKE) clean & popd
	pushd beta_regression & $(MAKE) clean & popd
	pushd betareg & $(MAKE) clean & popd
	pushd changepoint & $(MAKE) clean & popd
	pushd cov_re & $(MAKE) clean & popd
	pushd ctl & $(MAKE) clean & popd
	pushd dd2 & $(MAKE) clean & popd
	pushd expm & $(MAKE) clean & popd
	pushd geolocation & $(MAKE) clean & popd
	if exist SS3 rmdir /s /q SS3
	pushd high_iarray & $(MAKE) clean & popd
	pushd hysimple & $(MAKE) clean & popd
	pushd lprof & $(MAKE) clean & popd
	pushd mcmc-theta & $(MAKE) clean & popd
	pushd orange_mvn & $(MAKE) clean & popd
	pushd poisp & $(MAKE) clean & popd
	pushd qbeta & $(MAKE) clean & popd
	pushd simple_mcmc & $(MAKE) clean & popd
	pushd testminmax & $(MAKE) clean & popd
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
	del ..\\outputs-tests.txt
	@echo "# tests outputs\n" > ..\\outputs-tests.txt
	pushd 4darray & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd adnuts & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd bessel & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd beta_regression & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd betareg & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd dd2 & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd expm & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd changepoint & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd ctl & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd high_iarray & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd hysimple & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd lprof & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd mcmc-theta & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd orange_mvn & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd poisp & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd qbeta & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd simple_mcmc & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd testminmax & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd tiny_ad_fe & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd tiny_ad_re & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd tinyfun & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd vectorize & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd vonmises & $(MAKE) get-outputs >> ..\outputs-tests.txt
