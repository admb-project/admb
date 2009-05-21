.PHONY=dist

all: 

mingw:
	make --directory=src --file=mingw.mak

bcc:
	make --directory=src --file=bcc.mak

vc:
	make --directory=src --file=vc.mak

linux:
	make --directory=src --file=linux.mak

linux-verify:
	make --directory=src --file=linux.mak verify

dist:
	scripts/srcCopy.sh

clean:
	@rm -rvf build
