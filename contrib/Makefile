
all: disk

disk:
	rem cp contrib.h $(DISK)/contrib

statslib-opt:
	$(MAKE) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" DISKDIR=..\..\dist\contrib /f ..\..\..\..\contrib\statslib\Makefile

statslib-saf:
	$(MAKE) CXXFLAGS="$(CXXFLAGS)" DISKDIR=..\..\dist\contrib /f ..\..\..\..\contrib\statslib\Makefile

ecolib-opt:
	$(MAKE) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" DISKDIR=..\..\dist\contrib /f ..\..\..\..\contrib\ecolib\Makefile

ecolib-saf:
	$(MAKE) CXXFLAGS="$(CXXFLAGS)" DISKDIR=..\..\dist\contrib /f ..\..\..\..\contrib\ecolib\Makefile

qfclib-opt:
	$(MAKE) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" DISKDIR=..\..\dist\contrib /f ..\..\..\..\contrib\qfclib\Makefile

qfclib-saf:
	$(MAKE) CXXFLAGS="$(CXXFLAGS)" DISKDIR=..\..\dist\contrib /f ..\..\..\..\contrib\qfclib\Makefile

contribo.lib:
  lib /OUT:$@ /NOLOGO /IGNORE:4006 ../../objects/contrib-olp/*.obj

contribs.lib:
  lib /OUT:$@ /NOLOGO /IGNORE:4006 ../../objects/contrib-slp/*.obj

test:
	CXXFLAGS="" $(MAKE) --directory=ecolib test
	CXXFLAGS="" $(MAKE) --directory=qfclib test

clean:
	$(MAKE) --directory=ecolib clean
	$(MAKE) --directory=qfclib clean
	$(MAKE) --directory=statslib clean
	rm -rf $(DISK)/contrib
	rm -rf $(LIBPATH)/contrib-olp
	rm -rf $(LIBPATH)/contrib-slp
