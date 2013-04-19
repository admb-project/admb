all: contribs

contribs: build-src build-statslib build-qfclib build-ecolib

build-statslib:
	pushd statslib& ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(ADMB_HOME)" PREFIX_OBJ=$(PREFIX_OBJ)statslib-
	copy statslib\statsLib.h $(ADMB_HOME)\contrib\include

build-ecolib:
	pushd ecolib& ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(ADMB_HOME)" PREFIX_OBJ=$(PREFIX_OBJ)ecolib-
	copy ecolib\ecolib.h $(ADMB_HOME)\contrib\include

build-qfclib:
	pushd qfclib& ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(ADMB_HOME)" PREFIX_OBJ=$(PREFIX_OBJ)qfclib-
	copy qfclib\qfclib.h $(ADMB_HOME)\contrib\include

build-src:
	pushd src& ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(ADMB_HOME)" PREFIX_OBJ=$(PREFIX_OBJ)contributions-
	copy src\contrib.h $(ADMB_HOME)\contrib\include

test:
	cd ecolib& $(MAKE) test
	cd qfclib& $(MAKE) test

clean:
	cd ecolib& $(MAKE) clean
	cd qfclib& $(MAKE) clean
	cd statslib& $(MAKE) clean
	cd ad2csv& $(MAKE) clean
