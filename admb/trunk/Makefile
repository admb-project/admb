.PHONY: linux-verify solaris-verify

all: 

mingw:
	make --directory=src --file=mingw.mak

mingw-clean:
	make --directory=src --file=mingw.mak clean

mingw-verify:
	make --directory=src --file=mingw.mak verify

bcc:
	make --directory=src --file=bcc.mak

bcc-clean:
	make --directory=src --file=bcc.mak clean

vc:
	cd src& nmake /f vc.mak

vc-verify:
	cd src& nmake /f vc.mak verify

vc-install:
	cd src& nmake /f vc.mak install

vc-clean:
	cd src& nmake /f vc.mak clean

sunstudio:
	make --directory=src --file=sunstudio.mak

sunstudio-verify:
	make --directory=src --file=sunstudio.mak verify

sunstudio-check-admb2r:
	make --directory=src --file=sunstudio.mak check-admb2r

icc:
	make --directory=src --file=icc.mak

icc-verify:
	make --directory=src --file=icc.mak verify

linux:
	make --directory=src --file=linux.mak

linux-debug:
	DEBUG=1 make --directory=src --file=linux.mak

linux-64bit:
	make --directory=src --file=linux.mak dist-64bit

linux-debug-64bit:
	DEBUG=1 make --directory=src --file=linux.mak dist-64bit

linux-verify:
	make --directory=src --file=linux.mak verify

linux-verify-64bit:
	make --directory=src --file=linux.mak verify

linux-verify-debug:
	DEBUG=1 make --directory=src --file=linux.mak verify

linux-verify-debug-64bit:
	DEBUG=1 make --directory=src --file=linux.mak verify

linux-check-admb2r:
	make --directory=src --file=linux.mak check-admb2r

linux-clean: clean
	make --directory=src --file=linux.mak clean

dist:
	scripts/srcCopy.sh

clean:
	@rm -rvf build
	@rm -rvf configure config.log config.status autom4te.cache admb-config.mak
