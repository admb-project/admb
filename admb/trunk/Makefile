VERSION=`cat VERSION.txt`

all: inno-windows-setup

dists:
	cd build/dists; ../../scripts/dists/make-dist.sh
	$(INNOSETUP_HOME)/iscc scripts\admb-win32-setup\admb-win32-setup.iss

mingw:
	make -f ming_johnoel.mak

mingw-test:
	make -f ming_johnoel.mak verify

bcc32:
	make -f b502_johnoel.mak
	make -f b502_johnoel.mak verify

bcc55:
	make -f b502_johnoel.mak

bcc55-test:
	make -f b502_johnoel.mak verify

vc:
	make -f vc8-johnoel.mak

inno-setup-bcc551: bcc32
	$(INNOSETUP_HOME)/iscc scripts\admb-windows-setup\inno-setup-bcc551.iss
	mv build/admb-windows-setup.exe build/admb-$(VERSION)-bcc5.5.1.exe

clean:
	make -f b502_johnoel.mak clean
