mingw:
	make --directory=src --file=linux.mak

mingw-verify:
	make --directory=src --file=linux.mak verify

bcc:
	make --directory=src --file=bcc.mak

vc:
	cd src& nmake /f vc.mak

vc-verify:
	cd src& nmake /f vc.mak verify

sunstudio:
	ARCH_CXXFLAGS=-m32 make --directory=src --file=linux.mak CC=cc CXX=CC

sunstudio-64bit:
	ARCH_CXXFLAGS=-m64 make --directory=src --file=linux.mak CC=cc CXX=CC dist-64bit

sunstudio-verify:
	make --directory=src --file=sunstudio.mak CC=cc CXX=CC verify 

icc:
	make --directory=src --file=linux.mak CC=icc CXX=icpc

icc-verify:
	make --directory=src --file=linux.mak CC=icc CXX=icpc verify

linux:
	make --directory=src --file=linux.mak

linux-64bit:
	CXXFLAGS=-m64 make --directory=src --file=linux.mak dist-64bit

linux-verify:
	make --directory=src --file=linux.mak verify

it:
	./configure CXXFLAGS="-m32 -mmacosx-version-min=10.5"

it2:
	make MACOSX_DEPLOYMENT_TARGET=10.5 CXXFLAGS="-m32 -mmacosx-version-min=10.5" LDFLAGS="-m32 -Wl,-macosx_version_min,10.5" verify

clean:
	rm -rvf build
