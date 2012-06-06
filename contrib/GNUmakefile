.PHONY: all ad2csv statslib ecolib qfclib libcontribo.a libcontribs.a test clean

ifeq ($(CXX),CC)
CXXFLAGS:=-c $(CXXFLAGS) -DUSE_LAPLACE -I../${DISK}/include -D__SPDLL__ -D__GNUDOS__ -Dlinux -I../${DISK}/include
else
CXXFLAGS:=-c $(CXXFLAGS) -Wall -DUSE_LAPLACE -D__SPDLL__ -D__GNUDOS__ -Dlinux -I../${DISK}/include
endif

ifeq ($(CXX),g++.exe)
LIBPATH_SAFE=..\${LIBPATH}\contrib-slp
LIBPATH_OPT=..\${LIBPATH}\contrib-olp
LIBPATH_SAFE2=${LIBPATH}\contrib-slp
LIBPATH_OPT2=${LIBPATH}\contrib-olp
DISKDIR=..\${DISK}\contrib
else
LIBPATH_SAFE=../${LIBPATH}/contrib-slp
LIBPATH_OPT=../${LIBPATH}/contrib-olp
LIBPATH_SAFE2=${LIBPATH}/contrib-slp
LIBPATH_OPT2=${LIBPATH}/contrib-olp
DISKDIR=../${DISK}/contrib
endif

all: disk statslib ecolib qfclib libcontribo.a libcontribs.a ad2csv

disk:
ifeq ($(CXX),g++.exe)
	if not exist ${DISK}\contrib md ${DISK}\contrib
	if not exist ${LIBPATH}\contrib-olp md ${LIBPATH}\contrib-olp
	if not exist ${LIBPATH}\contrib-slp md ${LIBPATH}\contrib-slp
	copy contrib.h ${DISK}\contrib
else
	mkdir -p ${DISK}/contrib
	mkdir -p ${LIBPATH}/contrib-olp
	mkdir -p ${LIBPATH}/contrib-slp
	cp contrib.h ${DISK}/contrib
endif

ad2csv:
ifeq ($(CXX),g++.exe)
	$(MAKE) --directory=$@ ADMB_HOME=..\${DISK} PATH="..\${DISK}\bin;$(PATH)"
else
	ADMB_HOME=../${DISK} PATH="../${DISK}/bin:$(PATH)" $(MAKE) --directory=$@
endif

statslib:
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" LIBPATH=$(LIBPATH_OPT) DISKDIR=$(DISKDIR)
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" LIBPATH=$(LIBPATH_SAFE) DISKDIR=$(DISKDIR)

ecolib:
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" LIBPATH=$(LIBPATH_OPT) DISKDIR=$(DISKDIR)
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" LIBPATH=$(LIBPATH_SAFE) DISKDIR=$(DISKDIR)

qfclib:
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" LIBPATH=$(LIBPATH_OPT) DISKDIR=$(DISKDIR)
	$(MAKE) --directory=$@ CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" LIBPATH=$(LIBPATH_SAFE) DISKDIR=$(DISKDIR)

libcontribo.a:
ifeq ($(CXX),g++.exe)
	ar -rs ${DISK}\contrib\$@ $(LIBPATH_OPT2)\*.obj
else
	ar -rs ${DISK}/contrib/$@ $(LIBPATH_OPT2)/*.obj
endif

libcontribs.a:
ifeq ($(CXX),g++.exe)
	ar -rs ${DISK}\contrib\$@ $(LIBPATH_SAFE2)\*.obj
else
	ar -rs ${DISK}/contrib/$@ $(LIBPATH_SAFE2)/*.obj
endif

test:
	CXXFLAGS="" $(MAKE) --directory=ecolib test
	CXXFLAGS="" $(MAKE) --directory=qfclib test

clean:
	$(MAKE) --directory=ecolib clean
	$(MAKE) --directory=qfclib clean
	$(MAKE) --directory=statslib clean
ifeq ($(CXX),g++.exe)
	rm -rf $(DISKDIR)
	rm -rf $(LIBPATH_OPT)
	rm -rf $(LIBPATH_SAFE)
endif
