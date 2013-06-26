.NOPARALLEL: all

ifeq ($(OS),Windows_NT)
  ifeq ($(TERM),cygwin)
    TERMINAL=cygwin
  else
    TERMINAL=dos
  endif
endif

ifeq ($(TERMINAL),dos)
DISK=..\build\dist
PATH:=$(PATH):..\..\utilities\mingw\bin
LIBPATH=..\..\build\objects\dist
else
DISK=../build/dist
LIBPATH=../../build/objects/dist
endif

all: build-gdbprintlib build-statslib build-ecolib build-qfclib build-src
ifeq ($(TERMINAL),dos)
	$(AR) -rs $(DISK)\contrib\lib\libcontrib.a ..\build\objects\dist\saflp-contrib-*.obj
	$(AR) -rs $(DISK)\contrib\lib\libcontribo.a ..\build\objects\dist\optlp-contrib-*.obj
else
	$(AR) -rs $(DISK)/contrib/lib/libcontrib.a ../build/objects/dist/saflp-contrib-*.obj
	$(AR) -rs $(DISK)/contrib/lib/libcontribo.a ../build/objects/dist/optlp-contrib-*.obj
endif

ad2csv: build-ad2csv

build-gdbprintlib:
ifeq ($(TERMINAL),dos)
	$(MAKE) --directory=gdbprintlib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)\include\"" PREFIX_OBJ=$(LIBPATH)\saflp-contrib-gdbprintlib-
	$(MAKE) --directory=gdbprintlib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)\include\"" PREFIX_OBJ=$(LIBPATH)\optlp-contrib-gdbprintlib-
	copy gdbprintlib\gdbprintlib.h $(DISK)\contrib\include
else
	$(MAKE) --directory=gdbprintlib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-gdbprintlib-
	$(MAKE) --directory=gdbprintlib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-gdbprintlib-
	cp gdbprintlib/gdbprintlib.h $(DISK)/contrib/include
endif

build-statslib:
ifeq ($(TERMINAL),dos)
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)\include\"" PREFIX_OBJ=$(LIBPATH)\saflp-contrib-statslib-
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)\include\"" PREFIX_OBJ=$(LIBPATH)\optlp-contrib-statslib-
	copy statslib\statsLib.h $(DISK)\contrib\include
else
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-statslib-
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-statslib-
	cp statslib/statsLib.h $(DISK)/contrib/include
endif

build-ecolib:
ifeq ($(TERMINAL),dos)
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)\include\"" PREFIX_OBJ=$(LIBPATH)\saflp-contrib-ecolib-
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)\include\"" PREFIX_OBJ=$(LIBPATH)\optlp-contrib-ecolib-
	copy ecolib\ecolib.h $(DISK)\contrib\include
else
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-ecolib-
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-ecolib-
	cp ecolib/ecolib.h $(DISK)/contrib/include
endif

build-qfclib:
ifeq ($(TERMINAL),dos)
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)\include\"" PREFIX_OBJ=$(LIBPATH)\saflp-contrib-qfclib-
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)\include\"" PREFIX_OBJ=$(LIBPATH)\optlp-contrib-qfclib-
	copy qfclib\qfclib.h $(DISK)\contrib\include
else
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-qfclib-
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-qfclib-
	cp qfclib/qfclib.h $(DISK)/contrib/include
endif

build-ad2csv:
ifeq ($(TERMINAL),dos)
	$(MAKE) --directory=ad2csv --file=Makefile ADMB_HOME="$(ADMB_HOME)"
else
	$(MAKE) --directory=ad2csv ADMB_HOME="$(ADMB_HOME)"
endif

build-admb2r:
	$(MAKE) --directory=admb2r ADMB_HOME="$(ADMB_HOME)" gcc

build-src:
ifeq ($(TERMINAL),dos)
	$(MAKE) --directory=src CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)\include\"" PREFIX_OBJ=$(LIBPATH)\optlp-contrib-
	$(MAKE) --directory=src CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)\include\"" PREFIX_OBJ=$(LIBPATH)\saflp-contrib-
	copy src\contrib.h $(DISK)\contrib\include
else
	$(MAKE) --directory=src CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-
	$(MAKE) --directory=src CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-
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
	@$(MAKE) --directory=ad2csv clean
	@$(MAKE) --directory=src clean
