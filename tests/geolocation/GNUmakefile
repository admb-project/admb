ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifeq ($(findstring sh.exe,$(shell where sh.exe 2>&1 | findstr sh.exe)),sh.exe)
      EXT=.sh
    else
      SHELL=cmd
      CMDSHELL=cmd
    endif
  endif
endif

all: clean
	$(MAKE) kalmanfilter
ifeq ($(CMDSHELL),cmd)
	pushd kalmanfilter\\kfsst\\kfsst\\source & ..\\..\\..\\..\\..\\..\\admb.cmd kfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
	pushd kalmanfilter\\kftrack\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd kftrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
	pushd kalmanfilter\\kftrack\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd twosegtrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
	pushd kalmanfilter\\trackit\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd ukf.tpl & popd
	pushd kalmanfilter\\trackit\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd prepro.tpl & popd
	pushd kalmanfilter\\ukfsst\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd -o ..\\..\\..\\ukfsst.exe ukfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
else
	cd kalmanfilter/kfsst/kfsst/source; ../../../../../../admb$(EXT) kfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
	cd kalmanfilter/kftrack/inst/admb/src; ../../../../../../../admb$(EXT) kftrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
	cd kalmanfilter/kftrack/inst/admb/src; ../../../../../../../admb$(EXT) twosegtrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
	cd kalmanfilter/trackit/inst/admb/src; ../../../../../../../admb$(EXT) ukf.tpl
	cd kalmanfilter/trackit/inst/admb/src; ../../../../../../../admb$(EXT) prepro.tpl
	cd kalmanfilter/ukfsst/inst/admb/src; ../../../../../../../admb$(EXT) -o ../../../ukfsst ukfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
endif
	$(MAKE) run

kalmanfilter:
	git clone --depth 1 https://github.com/positioning/kalmanfilter

run:
ifeq ($(CMDSHELL),cmd)
	pushd kalmanfilter\\testdir\\kfsst & ..\\..\\kfsst\\kfsst\\source\\kfsst & popd
	pushd kalmanfilter\\testdir\\kftrack & ..\\..\\kftrack\\inst\\admb\\src\\kftrack & popd
	pushd kalmanfilter\\testdir\\trackit & ..\\..\\trackit\\inst\\admb\\src\\ukf & popd
	pushd kalmanfilter\\testdir\\ukfsst & ..\\..\\ukfsst\\ukfsst.exe & popd
else
	cd kalmanfilter/testdir/kfsst; ../../kfsst/kfsst/source/kfsst
	cd kalmanfilter/testdir/kftrack; ../../kftrack/inst/admb/src/kftrack
	cd kalmanfilter/testdir/trackit; ../../trackit/inst/admb/src/ukf
	cd kalmanfilter/testdir/ukfsst; ../../ukfsst/ukfsst
endif

get-outputs:

total-clean:
ifeq ($(CMDSHELL),cmd)
	@if exist kalmanfilter rmdir /s /q kalmanfilter
else
	@rm -rvf kalmanfilter
endif

clean:
