all: disk

disk:
	rem cp contrib.h $(DISK)/contrib

statslib-opt:
	$(MAKE) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" DISKDIR=..\..\dist\contrib /f ..\..\..\contrib\statslib\Makefile

statslib-saf:
	$(MAKE) CXXFLAGS="$(CXXFLAGS)" DISKDIR=..\..\dist\contrib /f ..\..\..\contrib\statslib\Makefile

ecolib-opt:
	$(MAKE) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" DISKDIR=..\..\dist\contrib /f ..\..\..\contrib\ecolib\Makefile

ecolib-saf:
	$(MAKE) CXXFLAGS="$(CXXFLAGS)" DISKDIR=..\..\dist\contrib /f ..\..\..\contrib\ecolib\Makefile

qfclib-opt:
	$(MAKE) CXXFLAGS="-DOPT_LIB $(CXXFLAGS)" DISKDIR=..\..\dist\contrib /f ..\..\..\contrib\qfclib\Makefile

qfclib-saf:
	$(MAKE) CXXFLAGS="$(CXXFLAGS)" DISKDIR=..\..\dist\contrib /f ..\..\..\contrib\qfclib\Makefile

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
