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
	$(MAKE) run

ifeq ($(CMDSHELL),cmd)
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
else
kalmanfilter/testdir/kfsst/kfsst:
	cd kalmanfilter/kfsst/kfsst/source; ../../../../../../admb$(EXT) -o ../../../../$@ kfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp

kalmanfilter/testdir/kftrack/kftrack:
	cd kalmanfilter/kftrack/inst/admb/src; ../../../../../../../admb$(EXT) -o ../../../../../$@ kftrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp

kalmanfilter/testdir/kftrack/twosegtrack:
	cd kalmanfilter/kftrack/inst/admb/src; ../../../../../../../admb$(EXT) -o ../../../../../$@ twosegtrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp

kalmanfilter/testdir/trackit/ukf:
	cd kalmanfilter/trackit/inst/admb/src; ../../../../../../../admb$(EXT) -o ../../../../../$@ ukf.tpl

kalmanfilter/testdir/trackit/prepro:
	cd kalmanfilter/trackit/inst/admb/src; ../../../../../../../admb$(EXT) -o ../../../../../$@ prepro.tpl

kalmanfilter/testdir/ukfsst/ukfsst:
	cd kalmanfilter/ukfsst/inst/admb/src; ../../../../../../../admb$(EXT) -o ../../../../../$@ ukfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
endif

kalmanfilter:
	git clone --depth 1 https://github.com/positioning/kalmanfilter

ifeq ($(CMDSHELL),cmd)
run: kalmanfilter\\testdir\\kfsst\\kfsst.exe kalmanfilter\\testdir\\kftrack\kftrack.exe kalmanfilter\\testdir\\kftrack\twosegtrack.exe kalmanfilter\\testdir\\trackit\\ukf.exe kalmanfilter\\testdir\\trackit\\prepro.exe kalmanfilter\\testdir\\ukfsst\\ukfsst.exe
	pushd kalmanfilter\\testdir\\kfsst & kfsst & popd
	pushd kalmanfilter\\testdir\\kftrack & kftrack & popd
	pushd kalmanfilter\\testdir\\trackit & ukf & popd
	pushd kalmanfilter\\testdir\\ukfsst & ukfsst & popd
else
run: kalmanfilter/testdir/kfsst/kfsst kalmanfilter/testdir/kftrack/kftrack kalmanfilter/testdir/kftrack/twosegtrack kalmanfilter/testdir/trackit/ukf kalmanfilter/testdir/trackit/prepro kalmanfilter/testdir/ukfsst/ukfsst
	cd kalmanfilter/testdir/kfsst; ./kfsst
	cd kalmanfilter/testdir/kftrack; ./kftrack
	cd kalmanfilter/testdir/trackit; ./ukf
	cd kalmanfilter/testdir/ukfsst; ./ukfsst
endif

get-outputs:

total-clean:
ifeq ($(CMDSHELL),cmd)
	@if [ -d "kalmanfilter" ]; then $(MAKE) --directory=kalmanfilter clean; fi
else
	@rm -rvf kalmanfilter
endif

clean:
