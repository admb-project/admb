.PHONY: dist df32testigam

ADMB_VERSION=9.0.x
export ADMB_VERSION

all: 

mingw:
	make --directory=src --file=mingw.mak

mingw-clean:
	make --directory=src --file=mingw.mak clean

bcc:
	make --directory=src --file=bcc.mak

bcc-clean:
	make --directory=src --file=bcc.mak clean

vc:
	make --directory=src --file=vc.mak

vc-clean:
	make --directory=src --file=vc.mak clean

sunstudio:
	make --directory=src --file=sunstudio.mak

sunstudio-verify:
	make --directory=src --file=sunstudio.mak verify

sunstudio-check-admb2r:
	make --directory=src --file=sunstudio.mak check-admb2r

linux:
	make --directory=src --file=linux.mak

linux-debug:
	DEBUG=1 make --directory=src --file=linux.mak

linux-verify:
	make --directory=src --file=linux.mak verify

linux-verify-debug:
linux-verify-debug-64bit:
	DEBUG=1 make --directory=src --file=linux.mak verify

linux-check-admb2r:
	make --directory=src --file=linux.mak check-admb2r

linux-64bit:
	make --directory=src --file=linux.mak dist-64bit

linux-debug-64bit:
	DEBUG=1 make --directory=src --file=linux.mak dist-64bit

dist:
	scripts/srcCopy.sh

df32testigam:
	g++ -Wno-deprecated -DOPT_LIB -D__GNUDOS__ -Dlinux -DUSE_LAPLACE -Ibuild/dists/admb_gcc411_fedora8/include -Lbuild/dists/admb_gcc411_fedora8/lib -ladmod -ladt -lado -ldf1b2o -o df32testigam tests/df32testigam.cpp

clean:
	@rm -rvf build
	@make --directory=src --file=linux.mak clean
