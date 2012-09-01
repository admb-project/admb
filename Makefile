mingw:
	$(MAKE) --directory=src --file=mingw.mak

mingw-clean:
	if exist build rd /Q /S build
	$(MAKE) --directory=src --file=mingw.mak clean

mingw-verify:
	$(MAKE) --directory=src --file=mingw.mak verify

bcc:
	$(MAKE) --directory=src --file=bcc.mak

clang:
	$(MAKE) --directory=src --file=clang.mak

vc:
	cd src& nmake /f vc.mak

vc-verify:
	cd src& nmake /f vc.mak verify

sunstudio:
	ARCH_CXXFLAGS=-m32 $(MAKE) --directory=src --file=linux.mak CC=cc CXX=CC

sunstudio-64bit:
	ARCH_CXXFLAGS=-m64 $(MAKE) --directory=src --file=linux.mak CC=cc CXX=CC dist-64bit

sunstudio-verify:
	$(MAKE) --directory=src --file=sunstudio.mak CC=cc CXX=CC verify

icc:
	$(MAKE) --directory=src --file=linux.mak CC=icc CXX=icpc

icc-verify:
	$(MAKE) --directory=src --file=linux.mak CC=icc CXX=icpc verify

linux:
	$(MAKE) --directory=src --file=linux.mak

linux-64bit:
	CXXFLAGS=-m64 $(MAKE) --directory=src --file=linux.mak dist-64bit

linux-contrib:
	CC=gcc CXX=g++ CXXFLAGS="" LIBPATH=../build/gcc411-fedora8 DISK=../build/dists/admb_gcc411_fedora8 $(MAKE) --directory=contrib

linux-verify:
	$(MAKE) --directory=src --file=linux.mak verify

it:
	./configure CFLAGS=-m32 CXXFLAGS="-m32 -mmacosx-version-min=10.5"

it2:
	$(MAKE) MACOSX_DEPLOYMENT_TARGET=10.5 CFLAGS=-m32 CXXFLAGS="-m32 -mmacosx-version-min=10.5" LDFLAGS="-m32 -Wl,-macosx_version_min,10.5" verify

clean:
	rm -rvf build
