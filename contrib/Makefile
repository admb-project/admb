all: contribs

contribs: build-statslib build-ecolib build-qfclib

build-statslib:
	pushd statslib& ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(ADMB_HOME)" PREFIX_OBJ=$(PREFIX_OBJ)statslib-

build-ecolib:
	pushd ecolib& ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(ADMB_HOME)" PREFIX_OBJ=$(PREFIX_OBJ)ecolib-

build-qfclib:
	pushd qfclib& ..\..\utilities\make CXX=$(CXX) CXXFLAGS="$(CXXFLAGS)" ADMB_HOME="$(ADMB_HOME)" PREFIX_OBJ=$(PREFIX_OBJ)qfclib-

contribo.lib:
	lib /OUT:$@ /NOLOGO /IGNORE:4006 ..\..\objects\contrib-olp\*.obj

contribs.lib:
	lib /OUT:$@ /NOLOGO /IGNORE:4006 ..\..\objects\contrib-slp\*.obj

test:
	cd ecolib& $(MAKE) test
	cd qfclib& $(MAKE) test

clean:
	cd ecolib& $(MAKE) clean
	cd qfclib& $(MAKE) clean
	cd statslib& $(MAKE) clean
	IF EXIST $(DISK)\contrib rd /S /Q $(DISK)\contrib
	IF EXIST $(DISK)\objects\contrib-olp rd /S /Q $(DISK)\objects\contrib-olp
	IF EXIST $(DISK)\objects\contrib-slp rd /S /Q $(DISK)\objects\contrib-slp
