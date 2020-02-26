DESTDIR=..\build\admb

all:\
  test-agemat\
  test-cov_re\
  test-expm\
  test-gtests

test-gtests:
	pushd gtests& $(MAKE) all & popd

test-agemat:
	pushd agemat& $(MAKE) & popd

test-cov_re:
	pushd cov_re & $(MAKE) & popd

test-expm:
	pushd expm & $(MAKE) & popd

test-geolocation:
	pushd geolocation & $(MAKE) & popd

total-clean: clean
	pushd glmmadmb & $(MAKE) total-clean & popd
	pushd geolocation & $(MAKE) total-clean & popd
	pushd agemat & $(MAKE) total-clean & popd

clean:
	pushd gtests& $(MAKE) clean & popd
	pushd agemat& $(MAKE) clean & popd
	pushd cov_re & $(MAKE) clean & popd
	pushd expm & $(MAKE) clean & popd
	pushd geolocation & $(MAKE) clean & popd
	if exist SS3 rmdir /s /q SS3

verify:
	del ..\outputs-saf.txt
	del ..\outputs-opt.txt
	if not exist ..\build\admb\examples md  ..\build\admb\examples
	xcopy ..\examples ..\build\admb\examples  /S /Y /D
	pushd ..\build\admb\examples & $(MAKE) all
	pushd ..\build\admb & ..\..\scripts\get-outputs.bat > "..\..\outputs-saf.txt" & popd
!IFNDEF SAFE_ONLY
	pushd ..\build\admb\examples & $(MAKE) FAST_OPTION=-f all
	pushd ..\build\admb & ..\..\scripts\get-outputs.bat > "..\..\outputs-opt.txt" & popd
!ENDIF

copy:
	IF NOT EXIST $(DESTDIR)\tests xcopy /I /E /Y ..\tests $(DESTDIR)\tests
