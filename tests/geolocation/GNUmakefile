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
	copy chol.h kalmanfilter\\trackit\\inst\\admb\\src
	copy nLogNormal.h kalmanfilter\\trackit\\inst\\admb\\src
	copy ukf.tpl kalmanfilter\\trackit\\inst\\admb\\src
	pushd kalmanfilter\\trackit\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd -o ..\\ukf.exe ukf.tpl & popd
	pushd kalmanfilter\\trackit\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd -o ..\\prepro.exe prepro.tpl & popd
	copy chol.h kalmanfilter\\ukfsst\\inst\\admb\\src
	copy nLogNormal.h kalmanfilter\\ukfsst\\inst\\admb\\src
	copy ukf.tpl kalmanfilter\\ukfsst\\inst\\admb\\src
	pushd kalmanfilter\\ukfsst\\inst\\admb\\src & ..\\..\\..\\..\\..\\..\\..\\admb.cmd -o ..\\..\\..\\ukfsst.exe ukfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp & popd
else
	cd kalmanfilter/kfsst/kfsst/source; ../../../../../../admb$(EXT) kfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
	cd kalmanfilter/kftrack/inst/admb/src; ../../../../../../../admb$(EXT) kftrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
	cd kalmanfilter/kftrack/inst/admb/src; ../../../../../../../admb$(EXT) twosegtrack.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
	cd kalmanfilter/trackit/inst/admb/src; PATH=../../../../../../..:$(PATH) make clean all
	cd kalmanfilter/ukfsst/inst/admb/src; ../../../../../../../admb$(EXT) -o ../../../ukfsst ukfsst.tpl yrmonday.cpp azimuth.cpp banner.cpp solstice.cpp
endif
	$(MAKE) run

kalmanfilter:
	git clone --depth 1 https://github.com/positioning/kalmanfilter

run:
ifeq ($(CMDSHELL),cmd)
	pushd kalmanfilter\\testdir\\kfsst & ..\\..\\kfsst\\kfsst\\source\\kfsst & popd
	pushd kalmanfilter\\testdir\\kftrack & ..\\..\\kftrack\\inst\\admb\\src\\kftrack & popd
	pushd kalmanfilter\\testdir\\trackit & ..\\..\\trackit\\inst\\admb\\ukf & popd
	pushd kalmanfilter\\testdir\\ukfsst & ..\\..\\ukfsst\\ukfsst.exe & popd
else
	-cd kalmanfilter/testdir/kfsst; ../../kfsst/kfsst/source/kfsst
	-cd kalmanfilter/testdir/kftrack; ../../kftrack/inst/admb/src/kftrack
	-cd kalmanfilter/testdir/trackit; ../../trackit/inst/admb/ukf
	-cd kalmanfilter/testdir/ukfsst; ../../ukfsst/ukfsst
endif

get-outputs:
ifeq ($(CMDSHELL),cmd)
	@cd kalmanfilter\\testdir\\kfsst && ..\\..\\..\\..\\..\\scripts\\get-outputs.sh kfsst
	@cd kalmanfilter\\testdir\\kftrack && ..\\..\\..\\..\\..\\scripts\\get-outputs.sh kftrack
	@cd kalmanfilter\\testdir\\trackit && ..\\..\\..\\..\\..\\scripts\\get-outputs.sh ukf
	@cd kalmanfilter\\testdir\\ukfsst && ..\\..\\..\\..\\..\\scripts\\get-outputs.sh ukfsst
else
	@[ -d kalmanfilter/testdir/kfsst] && cd kalmanfilter/testdir/kfsst && sh ../../../../../scripts/get-outputs.sh kfsst
	@[ -d kalmanfilter/testdir/kftrack] && cd kalmanfilter/testdir/kftrack && sh ../../../../../scripts/get-outputs.sh kftrack
	@[ -d kalmanfilter/testdir/trackit] && cd kalmanfilter/testdir/trackit && sh ../../../../../scripts/get-outputs.sh ukf
	@[ -d kalmanfilter/testdir/ukfsst] && cd kalmanfilter/testdir/ukfsst && sh ../../../../../scripts/get-outputs.sh ukfsst
endif

total-clean:
ifeq ($(CMDSHELL),cmd)
	@if exist kalmanfilter rmdir /s /q kalmanfilter
else
	@rm -rvf kalmanfilter
endif

clean:
