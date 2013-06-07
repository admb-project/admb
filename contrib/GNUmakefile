.NOPARALLEL: all

ifneq ($(SHELL),sh.exe)
DISK=../build/dist
else
DISK=..\build\dist
  ifndef MINGW_HOME
    PATH:=..\..\utilities\mingw\bin:$(PATH)
    AR=..\utilities\mingw\bin\ar
    MAKE=..\utilities\make
  endif
endif

ifndef LIBPATH
LIBPATH=../../build/objects/dist
endif

ad2csv: build-ad2csv

all: build-statslib build-ecolib build-qfclib build-src
ifneq ($(SHELL),sh.exe)
	$(AR) -rs $(DISK)/contrib/lib/libcontrib.a ../build/objects/dist/saflp-contrib-*.obj
	$(AR) -rs $(DISK)/contrib/lib/libcontribo.a ../build/objects/dist/optlp-contrib-*.obj
else
	$(AR) -rs $(DISK)\contrib\lib\libcontrib.a ..\build\objects\dist\saflp-contrib-*.obj
	$(AR) -rs $(DISK)\contrib\lib\libcontribo.a ..\build\objects\dist\optlp-contrib-*.obj
endif

build-statslib:
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-statslib-
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-statslib-
ifeq ($(SHELL),sh.exe)
	copy statslib\statsLib.h $(DISK)\contrib\include
else
	cp statslib/statsLib.h $(DISK)/contrib/include
endif

build-ecolib:
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-ecolib-
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-ecolib-
ifeq ($(SHELL),sh.exe)
	copy ecolib\ecolib.h $(DISK)\contrib\include
else
	cp ecolib/ecolib.h $(DISK)/contrib/include
endif

build-qfclib:
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-qfclib-
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-qfclib-
ifeq ($(SHELL),sh.exe)
	copy qfclib\qfclib.h $(DISK)\contrib\include
else
	cp qfclib/qfclib.h $(DISK)/contrib/include
endif

build-ad2csv: all
ifneq ($(SHELL),sh.exe)
	$(MAKE) --directory=ad2csv ADMB_HOME="$(ADMB_HOME)"
endif

build-admb2r:
ifneq ($(SHELL),sh.exe)
	$(MAKE) --directory=admb2r ADMB_HOME="$(ADMB_HOME)" gcc
endif

build-src:
	$(MAKE) --directory=src CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-
	$(MAKE) --directory=src CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS) -I\"$(ADMB_HOME)/include\"" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-
ifeq ($(SHELL),sh.exe)
	copy src\contrib.h $(DISK)\contrib\include
else
	cp src/contrib.h $(DISK)/contrib/include
endif

test:
	$(MAKE) --directory=src ADMB_HOME="$(ADMB_HOME)" test 

test-needR:
	$(MAKE) --directory=ecolib ADMB_HOME="$(ADMB_HOME)" test
	$(MAKE) --directory=qfclib ADMB_HOME="$(ADMB_HOME)" test

clean:
	@$(MAKE) --directory=ecolib clean
	@$(MAKE) --directory=qfclib clean
	@$(MAKE) --directory=statslib clean
	@$(MAKE) --directory=ad2csv clean
	@$(MAKE) --directory=src clean
