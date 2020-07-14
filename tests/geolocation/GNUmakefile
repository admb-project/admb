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

default: kalmanfilter
ifeq ($(CMDSHELL),cmd)
	pushd kalmanfilter\\kfsst\\kfsst\\source & ..\\..\\..\\..\\..\\..\\admb.cmd kfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
	pushd kalmanfilter\\kftrack\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd kftrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
	pushd kalmanfilter\\kftrack\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd twosegtrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
	pushd kalmanfilter\\trackit\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd ukf.tpl & popd
	pushd kalmanfilter\\trackit\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd prepro.tpl & popd
	pushd kalmanfilter\\ukfsst\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd ukfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
else
	cd kalmanfilter/kfsst/kfsst/source; ../../../../../../admb$(EXT) kfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
	cd kalmanfilter/kftrack/inst/admb/src; ../../../../../../../admb$(EXT) kftrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
	cd kalmanfilter/kftrack/inst/admb/src; ../../../../../../../admb$(EXT) twosegtrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
	cd kalmanfilter/trackit/inst/admb/src; ../../../../../../../admb$(EXT) ukf.tpl
	cd kalmanfilter/trackit/inst/admb/src; ../../../../../../../admb$(EXT) prepro.tpl
	cd kalmanfilter/ukfsst/inst/admb/src; ../../../../../../../admb$(EXT) ukfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
endif
	$(MAKE) run

kalmanfilter:
	git clone --depth 1 https://github.com/positioning/kalmanfilter

run:
ifeq ($(CMDSHELL),cmd)
	pushd kalmanfilter\\testdir\\kfsst & copy ..\\..\\kfsst\\kfsst\\source\\kfsst.exe & kfsst & popd
	pushd kalmanfilter\\testdir\\kftrack & copy ..\\..\\kftrack\\inst\\admb\\src\\kftrack.exe & kftrack & popd
	pushd kalmanfilter\\testdir\\trackit & copy ..\\..\\trackit\\inst\\admb\\src\\ukf.exe & ukf & popd
	pushd kalmanfilter\\testdir\\ukfsst & copy ..\\..\\ukfsst\\inst\\admb\\src\\ukfsst.exe & ukfsst & popd
else
	cd kalmanfilter/testdir/kfsst; cp ../../kfsst/kfsst/source/kfsst .; ./kfsst
	cd kalmanfilter/testdir/kftrack; cp ../../kftrack/inst/admb/src/kftrack .; ./kftrack
	cd kalmanfilter/testdir/trackit; cp ../../trackit/inst/admb/src/ukf .; ./ukf
	@# cd kalmanfilter/testdir/ukfsst; cp ../../ukfsst/inst/admb/src/ukfsst .; ./ukfsst
endif

total-clean: clean
	rm -rvf kalmanfilter
	rm -rvf ukfsst
	rm -rvf trackit
	rm -rvf kftrack
	rm -rvf kfsst
clean:
ifeq ($(CMDSHELL),cmd)
	if exist kalmanfilter pushd kalmanfilter & git clean -f & git checkout -- . &  popd
else
	@if [ -d "kalmanfilter" ]; then cd kalmanfilter; git clean -f; git checkout --; fi
endif
