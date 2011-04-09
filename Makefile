mingw:
	make --directory=src --file=mingw.mak

mingw-verify:
	make --directory=src --file=mingw.mak verify

bcc:
	make --directory=src --file=bcc.mak

vc:
	cd src& nmake /f vc.mak

vc-verify:
	cd src& nmake /f vc.mak verify

sunstudio:
	ARCH_CXXFLAGS=-m32 make --directory=src --file=sunstudio.mak

sunstudio-64bit:
	ARCH_CXXFLAGS=-m64 make --directory=src --file=sunstudio.mak dist-64bit

sunstudio-verify:
	make --directory=src --file=sunstudio.mak verify

icc:
	make --directory=src --file=icc.mak

icc-verify:
	make --directory=src --file=icc.mak verify

linux:
	make --directory=src --file=linux.mak

linux-64bit:
	CXXFLAGS=-m64 make --directory=src --file=linux.mak dist-64bit

linux-verify:
	make --directory=src --file=linux.mak verify

clean:
	rm -rvf build
