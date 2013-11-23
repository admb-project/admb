.NOPARALLEL: all
DISK=$(DIST)

all: build-gdbprintlib build-statslib build-ecolib build-qfclib build-src
ifeq ($(SHELL),sh.exe)
	$(AR) -rs $(DISK)\contrib\lib\libcontrib.a ..\build\objects\dist\saflp-contrib-*.obj
	$(AR) -rs $(DISK)\contrib\lib\libcontribo.a ..\build\objects\dist\optlp-contrib-*.obj
else
	$(AR) -rs $(DISK)/contrib/lib/libcontrib.a ../build/objects/dist/saflp-contrib-*.obj
	$(AR) -rs $(DISK)/contrib/lib/libcontribo.a ../build/objects/dist/optlp-contrib-*.obj
endif

ad2csv: build-ad2csv

build-gdbprintlib:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --directory=gdbprintlib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAFE_CONTRIB)" PREFIX_OBJ=..\..\build\objects\dist\saflp-contrib-gdbprintlib-
	$(MAKE) --directory=gdbprintlib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT_CONTRIB)" PREFIX_OBJ=..\..\build\objects\dist\optlp-contrib-gdbprintlib-
	copy gdbprintlib\gdbprintlib.h $(DISK)\contrib\include
else
	$(MAKE) --directory=gdbprintlib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAFE_CONTRIB)" PREFIX_OBJ=../../build/objects/dist/saflp-contrib-gdbprintlib-
	$(MAKE) --directory=gdbprintlib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT_CONTRIB)" PREFIX_OBJ=../../build/objects/dist/optlp-contrib-gdbprintlib-
	cp gdbprintlib/gdbprintlib.h $(DISK)/contrib/include
endif

build-statslib:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAFE_CONTRIB)" PREFIX_OBJ=..\..\build\objects\dist\saflp-contrib-statslib-
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT_CONTRIB)" PREFIX_OBJ=..\..\build\objects\dist\optlp-contrib-statslib-
	copy statslib\statsLib.h $(DISK)\contrib\include
else
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAFE_CONTRIB)" PREFIX_OBJ=../../build/objects/dist/saflp-contrib-statslib-
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT_CONTRIB)" PREFIX_OBJ=../../build/objects/dist/optlp-contrib-statslib-
	cp statslib/statsLib.h $(DISK)/contrib/include
endif

build-ecolib:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAFE_CONTRIB)" PREFIX_OBJ=..\..\build\objects\dist\saflp-contrib-ecolib-
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT_CONTRIB)" PREFIX_OBJ=..\..\build\objects\dist\optlp-contrib-ecolib-
	copy ecolib\ecolib.h $(DISK)\contrib\include
else
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAFE_CONTRIB)" PREFIX_OBJ=../../build/objects/dist/saflp-contrib-ecolib-
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT_CONTRIB)" PREFIX_OBJ=../../build/objects/dist/optlp-contrib-ecolib-
	cp ecolib/ecolib.h $(DISK)/contrib/include
endif

build-qfclib:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAFE_CONTRIB)" PREFIX_OBJ=..\..\build\objects\dist\saflp-contrib-qfclib-
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT_CONTRIB)" PREFIX_OBJ=..\..\build\objects\dist\optlp-contrib-qfclib-
	copy qfclib\qfclib.h $(DISK)\contrib\include
else
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAFE_CONTRIB)" PREFIX_OBJ=../../build/objects/dist/saflp-contrib-qfclib-
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT_CONTRIB)" PREFIX_OBJ=../../build/objects/dist/optlp-contrib-qfclib-
	cp qfclib/qfclib.h $(DISK)/contrib/include
endif

build-ad2csv:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --directory=ad2csv --file=Makefile
else
	$(MAKE) --directory=ad2csv
endif

build-admb2r:
	$(MAKE) --directory=admb2r ADMB_HOME="$(ADMB_HOME)" gcc

build-src:
ifeq ($(SHELL),sh.exe)
	$(MAKE) --directory=src CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT_CONTRIB)" PREFIX_OBJ=..\..\build\objects\dist\optlp-contrib-
	$(MAKE) --directory=src CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAFE_CONTRIB)" PREFIX_OBJ=..\..\build\objects\dist\saflp-contrib-
	copy src\contrib.h $(DISK)\contrib\include
else
	$(MAKE) --directory=src CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_OPT_CONTRIB)" PREFIX_OBJ=../../build/objects/dist/optlp-contrib-
	$(MAKE) --directory=src CXX=$(CXX) CXXFLAGS="$(CXXFLAGS_SAFE_CONTRIB)" PREFIX_OBJ=../../build/objects/dist/saflp-contrib-
	cp src/contrib.h $(DISK)/contrib/include
endif

test:
	$(MAKE) --directory=src ADMB_HOME="$(ADMB_HOME)" test 

test-needR:
	$(MAKE) --directory=ecolib ADMB_HOME="$(ADMB_HOME)" test
	$(MAKE) --directory=qfclib ADMB_HOME="$(ADMB_HOME)" test

clean:
	@$(MAKE) --directory=gdbprintlib clean
	@$(MAKE) --directory=ecolib clean
	@$(MAKE) --directory=qfclib clean
	@$(MAKE) --directory=statslib clean
ifeq ($(SHELL),sh.exe)
	@$(MAKE) --file=Makefile --directory=ad2csv clean
else
	@$(MAKE) --directory=ad2csv clean
	@$(MAKE) --directory=src clean
endif
