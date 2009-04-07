.PHONY=dist

VERSION=`cat VERSION.txt`

all: 

mingw:
	make -f mingw.mak

bcc:
	make -f bcc.mak

vc:
	make -f vc.mak

linux:
	make -f linux.mak

dist:
	./srcCopy.sh

clean:
	@rm -rvf build
