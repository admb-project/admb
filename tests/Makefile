!IFNDEF ADMB_VER
ADMB_VER=admb
!ENDIF

DESTDIR=..\build\$(ADMB_VER)

all:\
  test-4darray\
  test-adnuts\
  test-agemat\
  test-cov_re\
  test-expm\
  test-tiny\
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

test-cov_re:
	pushd cov_re & $(MAKE) & popd

test-expm:
	pushd expm & $(MAKE) & popd

test-geolocation:
	pushd geolocation & $(MAKE) & popd

test-tiny:
	pushd tiny & $(MAKE) & popd

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
	pushd cov_re & $(MAKE) clean & popd
	pushd expm & $(MAKE) clean & popd
	pushd geolocation & $(MAKE) clean & popd
	if exist SS3 rmdir /s /q SS3
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
	pushd expm & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd tiny & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd tiny_ad_fe & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd tiny_ad_re & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd tinyfun & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd vectorize & $(MAKE) get-outputs >> ..\outputs-tests.txt
	pushd vonmises & $(MAKE) get-outputs >> ..\outputs-tests.txt
