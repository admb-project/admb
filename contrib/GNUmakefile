.PHONY: all statslib ecolib QFC libcontribo.a libcontribs.a clean

CXXFLAGS:=-c $(CXXFLAGS) -Wall -Wno-deprecated -DUSE_LAPLACE -fpermissive -I../${DISK}/include -D__SPDLL__ -D__GNUDOS__ -Dlinux

all: disk statslib ecolib QFC libcontribo.a libcontribs.a

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

QFC:
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" LIBPATH=../${LIBPATH}/contrib-olp DISKDIR=../${DISK}/contrib
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" LIBPATH=../${LIBPATH}/contrib-slp DISKDIR=../${DISK}/contrib

libcontribo.a:
	ar -rs ${DISK}/contrib/$@ $(LIBPATH)/contrib-olp/*.obj

libcontribs.a:
	ar -rs ${DISK}/contrib/$@ $(LIBPATH)/contrib-slp/*.obj

clean:
	rm -rf ${DISK}/contrib
	rm -rf ${LIBPATH}/contrib-olp
	rm -rf ${LIBPATH}/contrib-slp
