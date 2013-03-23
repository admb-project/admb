all: contribs

contribs: build-statslib build-qfclib build-ecolib
	copy contrib.h $(ADMB_HOME)\contrib\include

build-statslib:
	pushd statslib& ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(ADMB_HOME)" PREFIX_OBJ=$(PREFIX_OBJ)statslib-

build-ecolib:
	pushd ecolib& ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(ADMB_HOME)" PREFIX_OBJ=$(PREFIX_OBJ)ecolib-

build-qfclib:
	pushd qfclib& ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(ADMB_HOME)" PREFIX_OBJ=$(PREFIX_OBJ)qfclib-

test:
	cd ecolib& $(MAKE) test
	cd qfclib& $(MAKE) test

clean:
	cd ecolib& $(MAKE) clean
	cd qfclib& $(MAKE) clean
	cd statslib& $(MAKE) clean
