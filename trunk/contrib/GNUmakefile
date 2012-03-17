.PHONY: all statslib ecolib qfclib libcontribo.a libcontribs.a test clean

ifeq ($(CXX),CC)
CXXFLAGS:=-c $(CXXFLAGS) -DUSE_LAPLACE -fpermissive -I../${DISK}/include -D__SPDLL__ -D__GNUDOS__ -Dlinux
else
CXXFLAGS:=-c $(CXXFLAGS) -Wall -Wno-deprecated -DUSE_LAPLACE -fpermissive -I../${DISK}/include -D__SPDLL__ -D__GNUDOS__ -Dlinux
endif

all: disk statslib ecolib qfclib libcontribo.a libcontribs.a

disk:
	mkdir -p ${DISK}/contrib
	mkdir -p ${LIBPATH}/contrib-olp
	mkdir -p ${LIBPATH}/contrib-slp
	cp contrib.h ${DISK}/contrib

statslib:
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" LIBPATH=../${LIBPATH}/contrib-olp DISKDIR=../${DISK}/contrib
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" LIBPATH=../${LIBPATH}/contrib-slp DISKDIR=../${DISK}/contrib

ecolib:
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" LIBPATH=../${LIBPATH}/contrib-olp DISKDIR=../${DISK}/contrib
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" LIBPATH=../${LIBPATH}/contrib-slp DISKDIR=../${DISK}/contrib

qfclib:
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" LIBPATH=../${LIBPATH}/contrib-olp DISKDIR=../${DISK}/contrib
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" LIBPATH=../${LIBPATH}/contrib-slp DISKDIR=../${DISK}/contrib

libcontribo.a:
	ar -rs ${DISK}/contrib/$@ $(LIBPATH)/contrib-olp/*.obj

libcontribs.a:
	ar -rs ${DISK}/contrib/$@ $(LIBPATH)/contrib-slp/*.obj

test:
	CXXFLAGS="" $(MAKE) --directory=ecolib test
	CXXFLAGS="" $(MAKE) --directory=qfclib test

clean:
	$(MAKE) --directory=ecolib clean
	$(MAKE) --directory=qfclib clean
	$(MAKE) --directory=statslib clean
	rm -rf ${DISK}/contrib
	rm -rf ${LIBPATH}/contrib-olp
	rm -rf ${LIBPATH}/contrib-slp
