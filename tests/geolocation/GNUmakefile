ifeq ($(OS),Windows_NT)
  ifeq ($(SHELL),cmd)
    CMDSHELL=cmd
  else
    ifeq ($(findstring bash.exe,$(shell where bash.exe 2>&1 | findstr bash.exe)),bash.exe)
      EXT=.sh
    else
      CMDSHELL=cmd
    endif
  endif
endif

default: kalmanfilter 
ifeq ($(CMDSHELL),cmd)
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
else
	cd kalmanfilter/testdir/kfsst; cp ../../kfsst/kfsst/source/kfsst .; ./kfsst
	cd kalmanfilter/testdir/kftrack; cp ../../kftrack/inst/admb/src/kftrack .; ./kftrack
	cd kalmanfilter/testdir/trackit; cp ../../trackit/inst/admb/src/ukf .; ./ukf
	cd kalmanfilter/testdir/ukfsst; cp ../../ukfsst/inst/admb/src/ukfsst .; ./ukfsst
endif

clean:
