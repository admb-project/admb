all: clean
	$(MAKE) /NOLOGO run

kalmanfilter:
	git clone --depth 1 https://github.com/positioning/kalmanfilter

run: kalmanfilter
	pushd kalmanfilter\\kfsst\\kfsst\\source & ..\\..\\..\\..\\..\\..\\admb.cmd kfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
	pushd kalmanfilter\\testdir\\kfsst & ..\\..\\kfsst\\kfsst\\source\\kfsst & popd
	pushd kalmanfilter\\kftrack\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd twosegtrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
	pushd kalmanfilter\\kftrack\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd kftrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
	pushd kalmanfilter\\testdir\\kftrack & ..\\..\\kftrack\\inst\\admb\\src\kftrack.exe & popd
	pushd kalmanfilter\\trackit\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd prepro.tpl & popd
	pushd kalmanfilter\\trackit\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd ukf.tpl & popd
	pushd kalmanfilter\\testdir\\trackit & ..\\..\\trackit\\inst\\admb\\src\\ukf.exe & popd
	pushd kalmanfilter\\ukfsst\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd -o ..\\..\\..\\ukfsst.exe ukfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
	pushd kalmanfilter\\testdir\\ukfsst & ..\\..\\..\\ukfsst\\ukfsst.exe & popd

get-outputs:

total-clean:
	@if exist kalmanfilter rmdir /s /q kalmanfilter

clean:
