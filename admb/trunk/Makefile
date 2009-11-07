.PHONY=dist

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

linux-verify:
	make --directory=src --file=linux.mak verify

linux-check-admb2r:
	make --directory=src --file=linux.mak check-admb2r

linux-64bit:
	make --directory=src --file=linux.mak dist-64bit

dist:
	scripts/srcCopy.sh

clean:
	@rm -rvf build
	@make --directory=src --file=linux.mak clean
