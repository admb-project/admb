all: test-geolocation test-cov_re test-expm

test-geolocation:
	pushd geolocation & $(MAKE) & popd

test-expm:
	pushd expm & $(MAKE) & popd

test-cov_re:
	pushd cov_re & $(MAKE) & popd

clean:
	pushd geolocation & $(MAKE) clean & popd
	pushd expm & $(MAKE) clean & popd
	pushd cov_re & $(MAKE) clean & popd

verify:
	pushd ..\build\dist\examples & $(MAKE) FAST_OPTION=-f --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-opt.txt" & popd
	pushd ..\build\dist\examples & $(MAKE) --file=Makefile all
	pushd ..\build\dist & ..\..\scripts\get-outputs.bat > "..\..\benchmarks-saf.txt" & popd
