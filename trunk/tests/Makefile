all:\
  test-agemat\
  test-cov_re\
  test-expm\
  test-geolocation

test-agemat:
	pushd agemat& $(MAKE) & popd

test-cov_re:
	pushd cov_re & $(MAKE) & popd

test-expm:
	pushd expm & $(MAKE) & popd

test-geolocation:
	pushd geolocation & $(MAKE) & popd

clean:
	pushd agemat& $(MAKE) clean & popd
	pushd cov_re & $(MAKE) clean & popd
	pushd expm & $(MAKE) clean & popd
	pushd geolocation & $(MAKE) clean & popd

verify:
	del ..\benchmarks-saf.txt
	del ..\benchmarks-opt.txt
	if not exist ..\build\dist\examples md  ..\build\dist\examples
	xcopy ..\examples ..\build\dist\examples  /S /Y /D
	pushd ..\build\dist\examples & $(MAKE) all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-saf.txt" & popd
	pushd ..\build\dist\examples & $(MAKE) FAST_OPTION=-f all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-opt.txt" & popd
