all: clean
	$(MAKE) kalmanfilter
	$(MAKE) run

kalmanfilter\\testdir\\kfsst\\kfsst.exe:
	pushd kalmanfilter\\kfsst\\kfsst\\source & ..\\..\\..\\..\\..\\..\\admb.cmd -o ..\\..\\..\\..\\$@ kfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd

kalmanfilter\\testdir\\kftrack\kftrack.exe:
	pushd kalmanfilter\\kftrack\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd -o ..\\..\\..\\..\\..\\$@ kftrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd

kalmanfilter\\testdir\\kftrack\twosegtrack.exe:
	pushd kalmanfilter\\kftrack\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd -o ..\\..\\..\\..\\..\\$@ twosegtrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd

kalmanfilter\\testdir\\trackit\\ukf.exe:
	pushd kalmanfilter\\trackit\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd -o ..\\..\\..\\..\\..\\$@ ukf.tpl & popd

kalmanfilter\\testdir\\trackit\\prepro.exe:
	pushd kalmanfilter\\trackit\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd -o ..\\..\\..\\..\\..\\$@ prepro.tpl & popd

kalmanfilter\\testdir\\ukfsst\\ukfsst.exe:
	pushd kalmanfilter\\ukfsst\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd -o ..\\..\\..\\..\\..\\$@ ukfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd

kalmanfilter:
	git clone --depth 1 https://github.com/positioning/kalmanfilter

run: kalmanfilter\\testdir\\kfsst\\kfsst.exe kalmanfilter\\testdir\\kftrack\kftrack.exe kalmanfilter\\testdir\\kftrack\twosegtrack.exe kalmanfilter\\testdir\\trackit\\ukf.exe kalmanfilter\\testdir\\trackit\\prepro.exe kalmanfilter\\testdir\\ukfsst\\ukfsst.exe
	pushd kalmanfilter\\testdir\\kfsst & kfsst & popd
	pushd kalmanfilter\\testdir\\kftrack & kftrack & popd
	pushd kalmanfilter\\testdir\\trackit & ukf & popd
	pushd kalmanfilter\\testdir\\ukfsst & ukfsst & popd

get-outputs:

total-clean:
	@if [ -d "kalmanfilter" ]; then $(MAKE) --directory=kalmanfilter clean; fi

clean:
