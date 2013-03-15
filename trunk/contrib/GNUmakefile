ifndef DISK
DISK=../../build/dist
endif

ifndef LIBPATH
LIBPATH=../../build/objects/dist
endif

ifeq ($(CXX),CC)
CXXFLAGS:=$(CXXFLAGS) -DUSE_LAPLACE -D__SPDLL__ -D__GNUDOS__ -Dlinux -I${DISK}/include
else
CXXFLAGS:=$(CXXFLAGS) -Wall -DUSE_LAPLACE -D__SPDLL__ -D__GNUDOS__ -Dlinux -I${DISK}/include
endif

all: contribs build-ad2csv

contribs: build-statslib build-ecolib build-qfclib build-sample
ifeq ($(SHELL),sh.exe)
	copy contrib.h ..\build\dist\contrib
else
	$(AR) -rs ../build/dist/contrib/libcontrib.a ../build/objects/dist/saflp-contrib-*.obj
	$(AR) -rs ../build/dist/contrib/libcontribo.a ../build/objects/dist/optlp-contrib-*.obj
	cp contrib.h ../build/dist/contrib
endif

build-admb2r:
	$(MAKE) --directory=admb2r ADMB_HOME="${DISK}" PATH="${DISK}/bin:$(PATH)" gcc

build-statslib:
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="-c -DOPT_LIB $(CXXFLAGS)" DISK="$(DISK)" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-statslib-
	$(MAKE) --directory=statslib CXX=$(CXX) CXXFLAGS="-c -DSAFE_ALL $(CXXFLAGS)" DISK="$(DISK)" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-statslib-

build-ecolib:
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="-c -DOPT_LIB $(CXXFLAGS)" DISK="$(DISK)" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-ecolib-
	$(MAKE) --directory=ecolib CXX=$(CXX) CXXFLAGS="-c -DSAFE_ALL $(CXXFLAGS)" DISK="$(DISK)" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-ecolib-

build-qfclib:
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="-c -DOPT_LIB $(CXXFLAGS)" DISK="$(DISK)" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-qfclib-
	$(MAKE) --directory=qfclib CXX=$(CXX) CXXFLAGS="-c -DSAFE_ALL $(CXXFLAGS)" DISK="$(DISK)" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-qfclib-

build-ad2csv:
ifeq ($(CXX),g++.exe)
	$(MAKE) --directory=ad2csv ADMB_HOME="${DISK}" PATH="${DISK}\bin;$(PATH)"
	copy ad2csv\ad2csv.exe ..\build\dist\bin
else
	ADMB_HOME="${DISK}/dist" PATH="${DISK}/bin:$(PATH)" $(MAKE) --directory=ad2csv
	cp -v ad2csv/ad2csv ../build/dist/bin
endif

build-sample:
	$(MAKE) --directory=sample CXX=$(CXX) CXXFLAGS="-c -DOPT_LIB $(CXXFLAGS)" DISK="$(DISK)" PREFIX_OBJ=$(LIBPATH)/optlp-contrib-sample-
	$(MAKE) --directory=sample CXX=$(CXX) CXXFLAGS="-c -DSAFE_ALL $(CXXFLAGS)" DISK="$(DISK)" PREFIX_OBJ=$(LIBPATH)/saflp-contrib-sample-

test:
	ADMB_HOME="${DISK}" $(MAKE) --directory=sample test

test-notworking:
ifneq ($(CXX),g++.exe)
	ADMB_HOME="${DISK}" $(MAKE) --directory=ecolib test
	ADMB_HOME="${DISK}" $(MAKE) --directory=qfclib test
endif

clean:
	@rm -rvf build
	@rm -vf ad2csv/ad2csv
	@rm -vf ad2csv/ad2csv.o
	$(MAKE) --directory=ecolib clean
	$(MAKE) --directory=qfclib clean
	$(MAKE) --directory=statslib clean
	$(MAKE) --directory=sample clean
