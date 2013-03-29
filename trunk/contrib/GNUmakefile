ifndef LIBPATH
LIBPATH=../../build/objects/dist
endif

ifeq ($(CXX),CC)
CXXFLAGS:=$(CXXFLAGS) -DUSE_LAPLACE -D__SPDLL__ -D__GNUDOS__ -Dlinux -I$(ADMB_HOME)/include
else
CXXFLAGS:=$(CXXFLAGS) -Wall -DUSE_LAPLACE -D__SPDLL__ -D__GNUDOS__ -Dlinux -I$(ADMB_HOME)/include
endif

all: contribs build-ad2csv

contribs: build-statslib build-ecolib build-qfclib
ifeq ($(SHELL),sh.exe)
	copy contrib.h $(ADMB_HOME)\contrib\include
else
	$(AR) -rs $(ADMB_HOME)/contrib/lib/libcontrib.a ../build/objects/dist/saflp-contrib-*.obj
	$(AR) -rs $(ADMB_HOME)/contrib/lib/libcontribo.a ../build/objects/dist/optlp-contrib-*.obj
	cp contrib.h $(ADMB_HOME)/contrib/include
endif


build-statslib:
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS)" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-statslib-
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-statslib-
	cp statslib/statsLib.h $(ADMB_HOME)/contrib/include

build-ecolib:
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS)" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-ecolib-
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-ecolib-
	cp ecolib/ecolib.h $(ADMB_HOME)/contrib/include

build-qfclib:
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS)" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-qfclib-
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-qfclib-
	cp qfclib/qfclib.h $(ADMB_HOME)/contrib/include

build-ad2csv:
	$(MAKE) --directory=ad2csv ADMB_HOME="$(ADMB_HOME)"

build-admb2r:
	$(MAKE) --directory=admb2r ADMB_HOME="$(ADMB_HOME)" gcc

build-sample:
	$(MAKE) --directory=sample CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-sample-
	$(MAKE) --directory=sample CXX=$(CXX) CXXFLAGS="-DSAFE_ALL $(CXXFLAGS)" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-sample-
	cp sample/sample.h $(ADMB_HOME)/contrib/include

test:
	$(MAKE) --directory=sample ADMB_HOME="$(ADMB_HOME)" test 

test-notworking:
	$(MAKE) --directory=ecolib ADMB_HOME="$(ADMB_HOME)" test
	$(MAKE) --directory=qfclib ADMB_HOME="$(ADMB_HOME)" test

clean:
	$(MAKE) --directory=ecolib clean
	$(MAKE) --directory=qfclib clean
	$(MAKE) --directory=statslib clean
	$(MAKE) --directory=sample clean
