.PHONY: tests

default: linux

verify: linux-verify

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

solarisstudio: solarisstudio-dist solarisstudio-contrib

solarisstudio-dist:
	$(MAKE) --directory=src --file=linux.mak CC=cc CXX=CC

solarisstudio-contrib:
	$(MAKE) --directory=contrib CC=cc CXX=CC

solarisstudio-verify: solarisstudio
	$(MAKE) --directory=src --file=linux.mak CC=cc CXX=CC verify

sunstudio: solarisstudio
sunstudio-verify: solarisstudio-verify

sunstudio-64bit:
	ARCH_CXXFLAGS=-m64 $(MAKE) --directory=src --file=linux.mak CC=cc CXX=CC dist-64bit

icc:
	$(MAKE) --directory=src --file=linux.mak CC=icc CXX=icpc

icc-verify:
	$(MAKE) --directory=src --file=linux.mak CC=icc CXX=icpc verify

linux: linux-dist linux-contrib

linux-dist:
	$(MAKE) --directory=src --file=linux.mak

linux-64bit: linux-contrib
	CXXFLAGS=-m64 $(MAKE) --directory=src --file=linux.mak dist-64bit

linux-contrib:
	$(MAKE) --directory=contrib CC=gcc CXX=g++

linux-verify:
	$(MAKE) --directory=src --file=linux.mak verify

intel: intel64-dist intel64-contrib

intel64-dist:
	source /opt/intel/bin/compilervars.sh intel64& $(MAKE) --directory=src --file=linux.mak CXX=icpc CC=icc

intel64-contrib:
	source /opt/intel/bin/compilervars.sh intel64& $(MAKE) --directory=src --file=linux.mak CXX=icpc CC=icc contrib

intel64-verify: intel
	source /opt/intel/bin/compilervars.sh intel64& $(MAKE) --directory=src --file=linux.mak CXX=icpc CC=icc verify

it:
	./configure CFLAGS=-m32 CXXFLAGS="-m32 -mmacosx-version-min=10.5"

it2:
	$(MAKE) MACOSX_DEPLOYMENT_TARGET=10.5 CFLAGS=-m32 CXXFLAGS="-m32 -mmacosx-version-min=10.5" LDFLAGS="-m32 -Wl,-macosx_version_min,10.5" verify


tests:
	ADMB_HOME="$(CURDIR)/build/dists/admb_gcc411_fedora8" $(MAKE) --directory=tests

dist:
	rm -f admb.zip admb
	ln -sf build/dist/ admb
	zip -r admb admb/*

clean:
	rm -rvf build
	$(MAKE) --directory=contrib clean
	$(MAKE) --directory=tests clean
